#include <iostream>
#include <fstream>
#include <string>

#define FILE_NAME "data.bin"

//aclef 1140310316 15.11.14

using namespace std;

class ItemNode
{
public:
	string	S_Name;
	string	S_Brand;
	double	D_Price;
	int		I_Quantity;
	ItemNode* P_Succ;
	ItemNode* P_Prev;
};


extern ItemNode* P_Head = NULL;
extern int Item_Count = 0;




ItemNode* Item_GetPointer(string Key_Name)
{
	ItemNode* Temp_Ptr=P_Head;
	for (int i = 0; i < Item_Count; i++)
	{
		if (Temp_Ptr->S_Name == Key_Name)
			return Temp_Ptr;
		Temp_Ptr = Temp_Ptr->P_Succ;
	};
	return NULL;
};

void Item_Search(string Key_Name)
{
	ItemNode* Temp_Ptr = Item_GetPointer(Key_Name);
	if (Temp_Ptr == NULL)
	{
		cout << "No such item found." << endl;
		return;
	}
	else
	{
		cout << "Information of item " << Key_Name << ":" << endl;
		cout << "Brand: " << Temp_Ptr->S_Brand << " Price: " << Temp_Ptr->D_Price << " Quantity: " << Temp_Ptr->I_Quantity << endl;
		return;
	};
};

void Item_Delete(ItemNode* Ptr)
{
	if (Item_Count == 1)
	{
		delete Ptr;
		Item_Count = 0;
		return;
	};
	if (Ptr == P_Head)
	{
		(P_Head->P_Succ)->P_Prev = NULL;
		P_Head = P_Head->P_Succ;
		delete Ptr;
		Item_Count--;
		return;
	};
	if (Ptr->P_Succ != NULL)
		(Ptr->P_Succ)->P_Prev = Ptr->P_Prev;
	(Ptr->P_Prev)->P_Succ = Ptr->P_Succ;
	Item_Count--;
	return;
};

int Item_Insert(const string Name,const string Brand,double Price,int Quantity)
{
	if (Quantity == 0)
	{
		cout << "You can't insert a item with zero quantity" << endl;
		return 0;
	};
	if (Item_Count == 0)
	{
		P_Head = new ItemNode;
		P_Head->P_Prev = NULL;
		P_Head->P_Succ = NULL;
		P_Head->S_Name = Name;
		P_Head->S_Brand = Brand;
		P_Head->D_Price = Price;
		P_Head->I_Quantity = Quantity;
		Item_Count = 1;
		return 1;
	}
	else if (Item_GetPointer(Name))
	{
		cout << "Item already exist, insert failed. " << endl;
		cout << "Please use the update function" << endl;
		return 0;
	}
	else
	{
		ItemNode* Temp_Ptr = P_Head;
		int Flag_FoundBigger = 0;
		for (int i = 0; i < Item_Count; i++)
		{
			if (Temp_Ptr->D_Price > Price)
			{
				Flag_FoundBigger = 1;
				break;
			};
			if (Temp_Ptr->P_Succ != NULL)
				Temp_Ptr = Temp_Ptr->P_Succ;
		};
		if (Flag_FoundBigger)
		{
			int Flag_IsSmallest = 0;
			if (Temp_Ptr == P_Head)
				Flag_IsSmallest = 1;
			ItemNode *New_Ptr = new ItemNode;
			New_Ptr->S_Name = Name;
			New_Ptr->S_Brand = Brand;
			New_Ptr->D_Price = Price;
			New_Ptr->I_Quantity = Quantity;
			if (Flag_IsSmallest)
			{
				New_Ptr->P_Succ = Temp_Ptr;
				New_Ptr->P_Prev = NULL;
				Temp_Ptr->P_Prev = New_Ptr;
			}
			else
			{
				(Temp_Ptr->P_Prev)->P_Succ = New_Ptr;
				New_Ptr->P_Prev = Temp_Ptr->P_Prev;
				New_Ptr->P_Succ = Temp_Ptr;
				Temp_Ptr->P_Prev = New_Ptr;
			};
		}
		else
		{
			Temp_Ptr->P_Succ = new ItemNode;
			(Temp_Ptr->P_Succ)->P_Prev = Temp_Ptr;
			(Temp_Ptr->P_Succ)->P_Succ = NULL;
			(Temp_Ptr->P_Succ)->S_Name = Name;
			(Temp_Ptr->P_Succ)->S_Brand = Brand;
			(Temp_Ptr->P_Succ)->D_Price = Price;
			(Temp_Ptr->P_Succ)->I_Quantity = Quantity;
		};

		Item_Count++;
		return 1;
	}
	return 0;
};


int File_Exist(void)
{
	fstream File;
	File.open(FILE_NAME, ios::in);
	if (!File)
	{
		File.close();
		return 0;
	}
	else
	{
		File.close();
		return 1;
	};
	return 0;
};

void File_Save()
{
	ofstream fout(FILE_NAME);
	fout << Item_Count << endl;
	ItemNode* Temp_Ptr = P_Head;
	for (int i = 0; i < Item_Count; i++)
	{
		fout << Temp_Ptr->S_Name << ' ';
		fout << Temp_Ptr->S_Brand << ' ';
		fout << Temp_Ptr->D_Price << ' ';
		fout << Temp_Ptr->I_Quantity << endl;
		Temp_Ptr = Temp_Ptr->P_Succ;
	};
	fout.close();
};

void File_Read()
{
	string Temp_Name, Temp_Brand;
	double Temp_Price;
	int Temp_Quantity, Temp_Count;
	ifstream fin(FILE_NAME);
	fin >> Temp_Count;
	for (int i = 0; i < Temp_Count; i++)
	{
		fin >> Temp_Name;
		fin >> Temp_Brand;
		fin >> Temp_Price;
		fin >> Temp_Quantity;
		Item_Insert(Temp_Name, Temp_Brand, Temp_Price, Temp_Quantity);
	};
	fin.close();
};


int main()
{
	if (File_Exist())
	{
		cout << "Data file already exists." << endl;
		File_Read();
		cout << "Data file readed." << endl;
	}
	else
	{
		cout << "The data file data.bin doesn's exist." << endl;
		cout << "Start with a empty list." << endl;
	};
	int Flag_Running = 1;
	while (Flag_Running)
	{
		int Func_Option = 0;
		cout << endl <<  "Please choose a function(enter the number of function):" << endl;
		cout << "1.Insert items" << endl;
		cout << "2.Sell out items" << endl;
		cout << "3.Update information" << endl;
		cout << "4.Search information" << endl;
		cout << "5.Save data file" << endl;
		cout << "6.Save and exit" << endl;
		cout << ">>";
		cin >> Func_Option;
		switch (Func_Option)
		{
			case 1:
			{
				while (1)
				{
					string Temp_Name,Temp_Brand;
					double Temp_Price;
					int Temp_Quantity;
					cout << "Please input Name, Brand, price, quantity seprated by white space.Input 'exit' to back." << endl;
					cin >> Temp_Name;
					if (Temp_Name == "exit")
						break;
					cin >> Temp_Brand >> Temp_Price >> Temp_Quantity;
					Item_Insert(Temp_Name, Temp_Brand, Temp_Price, Temp_Quantity);
				};
				break;
			};
			case 2:
			{
				cout << "Please input the name and quantity to sell.(Seperate by while space)" << endl;
				string Temp_Name;
				int Temp_Quantity;
				cin >> Temp_Name >> Temp_Quantity;
				ItemNode* Temp_Ptr = Item_GetPointer(Temp_Name);
				if (Temp_Ptr == NULL)
				{
					cout << "No such item. Please check your input." << endl;
					break;
				};
				if (Temp_Quantity > Temp_Ptr->I_Quantity)
				{
					cout << "Not enough quantity to sell.Please check your input" << endl;
					break;
				};
				if (Temp_Quantity == Temp_Ptr->I_Quantity)
				{
					cout << "This item is sold out" << endl;
					Item_Delete(Temp_Ptr);
					break;
				};
				Temp_Ptr->I_Quantity -= Temp_Quantity;
				cout << "Successfully sold " << Temp_Quantity << " items. " << Temp_Ptr->I_Quantity << " items left." << endl;
				break;
			};
			case 3:
			{
				while (1)
				{
					string Temp_Name, Temp_Brand;
					double Temp_Price;
					int Temp_Quantity;
					cout << "Please input Name, Brand, price, quantity seprated by white space.Input 'exit' to back." << endl;
					cin >> Temp_Name;
					if (Temp_Name == "exit")
						break;
					cin >> Temp_Brand >> Temp_Price >> Temp_Quantity;

					ItemNode* Temp_Ptr = Item_GetPointer(Temp_Name);
					if (Temp_Ptr == NULL)
					{
						cout << "No such item, please check your input";
						break;
					};
					Item_Delete(Temp_Ptr);
					Item_Insert(Temp_Name, Temp_Brand, Temp_Price, Temp_Quantity);
				};
				break;
			};
			case 4:
			{
				while (1)
				{
					string Temp_Name;
					cout << "Input name to search(input exit to back):";
					cin >> Temp_Name;
					if (Temp_Name == "exit")
						break;
					Item_Search(Temp_Name);
				};
				break;
			};
			case 5:
			{
				cout << "Saving file..." << endl;
				File_Save();
				break;
			};
			case 6:
			{
				cout << "Saving file..." << endl;
				File_Save();
				cout << "File saved, excited!" << endl;
				Flag_Running = 0;
				break;
			};
			default:
			{
				cout << "Input error:No such choice, please retry." << endl;
				break;
			};
		};

	};
	
	return 0;
};

