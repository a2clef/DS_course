#include <iostream>
#include <stdio.h>

#define MAXIMUM_NODE_COUNT 100

//=================================================================================================
//===============================STACK DEFINITION START===Ver 1.05=================================
//=================================================================================================

template<class T>
struct Node{
	T info;
	Node<T> *next;
};


template<class T>
class Stack
{
public:
	Stack() :top(NULL) {};							//default constructor
	Stack(const Stack<T> &original);				//copy constructor
	~Stack();										//destructor
	Stack<T>& operator=(const Stack<T> &original);	//operator = reloaded
	void push(T element);							//push
	bool pop(T &element);							//pop
	bool peek(T &topEle);							//peek: get the value of top element
	bool isEmpty() const;							//is empty
	void makeEmpty();								//clear the stack
private:
	Node<T> *top;									//top pointer
	inline void deepCopy(const Stack<T> &original);
};

template<class T>
Stack<T>::Stack(const Stack<T> &original)
{
	deepCopy(original);
}
template<class T>
Stack<T>::~Stack()
{
	makeEmpty();
}
template<class T>
Stack<T>& Stack<T>::operator =(const Stack<T> &original)
{
	deepCopy(original);
	return this;
}
template<class T>
void Stack<T>::push(T element)
{
	Node<T> *ptr = new Node < T >;
	ptr->info = element;
	ptr->next = top;
	top = ptr;
}
template<class T>
bool Stack<T>::pop(T &element)
{
	if (top == NULL)
		return false;
	element = top->info;
	Node<T> *ptr = top;
	top = top->next;
	delete ptr;
	return true;
}
template<class T>
bool Stack<T>::peek(T &topEle)
{
	if (top == NULL)
		return false;
	topEle = top->info;
	return true;
}
template<class T>
bool Stack<T>::isEmpty() const
{
	if (top == NULL)
		return true;
	return false;
}
template<class T>
void Stack<T>::makeEmpty()
{
	Node<T> *ptr = top;
	while (top != NULL)
	{
		ptr = top;
		top = top->next;
		delete ptr;
	}
}
template<class T>

void Stack<T>::deepCopy(const Stack<T> &original)
{
	Node<T> *oriPtr = original.top;
	Node<T> *copyPtr = top = new Node < T >;
	copyPtr->info = oriPtr->info;
	while (oriPtr->next != NULL)
	{
		copyPtr->next = new Node < T >;
		copyPtr = copyPtr->next;
		oriPtr = oriPtr->next;
		copyPtr->info = oriPtr->info;
	}
	copyPtr->next = NULL;
}

//=================================================================================================
//===============================STACK DIFINITION END==============================================
//=================================================================================================


using namespace std;
int Element_Count;
/*
	Arr_Mid stores the Mid-Order sequence
	Arr_Pre stores the Pre-Order sequence
*/
int Arr_Mid[MAXIMUM_NODE_COUNT], Arr_Pre[MAXIMUM_NODE_COUNT];



class TNode					//The node of a tree
{
public:
	TNode* Father;			
	TNode* Child_L;
	TNode* Child_R;
	int Key_Value;
};

TNode* Tree_Build_Recursive(int Pa,int Ma,int Len)
/*
	Build a binary tree using Arr_Pre and Arr_Mid
	Method: Recursive
*/
{
	if (Len == 0)						//return NULL if no root node
		return NULL;
	int Temp, Pos_root;					//Temp=Value of root node
	TNode* Ptr_Temp;
	Temp = Arr_Pre[Pa];
	for (int i = Ma; i < Ma + Len; i++)	//Pos_root=position of root node in Arr_Mid
		if (Arr_Mid[i] == Temp)
		{
			Pos_root = i;
			break;
		};
	Ptr_Temp = new TNode;
	Ptr_Temp->Father = NULL;
	Ptr_Temp->Key_Value = Temp;			//split Arrs into 2 parts as left and right sub_tree
	Ptr_Temp->Child_L = Tree_Build_Recursive(Pa + 1, Ma, Pos_root - Ma);
	if (Ptr_Temp->Child_L != NULL)
		(Ptr_Temp->Child_L)->Father = Ptr_Temp;
	Ptr_Temp->Child_R = Tree_Build_Recursive(Pa + Pos_root - Ma + 1, Pos_root + 1, Len - Pos_root + Ma - 1);
	if (Ptr_Temp->Child_R != NULL)
		(Ptr_Temp->Child_R)->Father = Ptr_Temp;
	return Ptr_Temp;
};


void Tree_Build_NRecursive(TNode* &Ptr_Root)
/*
	Build a binary tree using Arr_Pre and Arr_Mid
	Method: Non-Recursive, BFS
			using a query to store elements to put into the tree
*/
{
	int Temp_Count = Element_Count;
	struct{ TNode* Ptr;
		int Pa, Ma, Len;
	} Q[MAXIMUM_NODE_COUNT];			//QUERY
	int PosIn = 1, PosOut = 0,PosMid;	//PosIn:Position to put element into the query

	Ptr_Root = new TNode;
	Ptr_Root->Father = NULL;
	Ptr_Root->Key_Value = Arr_Pre[0];
	
	Q[0].Ptr = Ptr_Root;
	Q[0].Pa = 0;
	Q[0].Ma = 0;
	Q[0].Len = Element_Count;

	while (Temp_Count)
	{
		for (int i = Q[PosOut].Ma; i < Q[PosOut].Ma + Q[PosOut].Len; i++)	//Get the position of this element in Arr_Mid
			if (Arr_Mid[i] == Arr_Pre[Q[PosOut].Pa])
			{
				PosMid = i;
				break;
			};

		if (PosMid == Q[PosOut].Ma)		//if this node have no left child
		{
			Q[PosOut].Ptr->Child_L = NULL;
		}
		else
		{
			Q[PosOut].Ptr->Child_L = new TNode; //Put this element into Tree
			(Q[PosOut].Ptr->Child_L)->Father = Q[PosOut].Ptr;
			Q[PosOut].Ptr->Child_L->Key_Value = Arr_Pre[Q[PosOut].Pa + 1];
			
			Q[PosIn].Ptr = Q[PosOut].Ptr->Child_L;	//Put this element into Query
			Q[PosIn].Len = PosMid - Q[PosOut].Ma;
			Q[PosIn].Ma = Q[PosOut].Ma;
			Q[PosIn].Pa = Q[PosOut].Pa + 1;

			PosIn++;

		};

		if (PosMid == (Q[PosOut].Ma + Q[PosOut].Len - 1))//if the element is at the rightest of the mid-arr->have no right child
		{
			Q[PosOut].Ptr->Child_R = NULL;
		}
		else
		{
			Q[PosOut].Ptr->Child_R = new TNode;
			(Q[PosOut].Ptr->Child_R)->Father = Q[PosOut].Ptr;
			Q[PosOut].Ptr->Child_R->Key_Value = Arr_Pre[Q[PosOut].Pa + PosMid - Q[PosOut].Ma + 1];

			Q[PosIn].Ptr = Q[PosOut].Ptr->Child_R;
			Q[PosIn].Len = Q[PosOut].Len - PosMid - 1 + Q[PosOut].Ma;
			Q[PosIn].Ma = PosMid + 1;
			Q[PosIn].Pa = Q[PosOut].Pa + PosMid - Q[PosOut].Ma + 1;

			PosIn++;

		};

		Temp_Count--;
		PosOut++;
	};



};


void Tree_Walk_PreOrder_Recursive(TNode* Ptr_Root)
/*
	Walk the tree in Pre-Order
	Simplest recursive method
*/
{
	if (Ptr_Root == NULL)
		return;
	cout << Ptr_Root->Key_Value << ' ';
	Tree_Walk_PreOrder_Recursive(Ptr_Root->Child_L);
	Tree_Walk_PreOrder_Recursive(Ptr_Root->Child_R);
	return;
};

void Tree_Walk_MidOrder_Recursive(TNode* Ptr_Root)
/*
	Walk the tree in Mid-Order
	Simplest recursive method
*/
{
	if (Ptr_Root == NULL)
		return;
	Tree_Walk_MidOrder_Recursive(Ptr_Root->Child_L);
	cout << Ptr_Root->Key_Value << ' ';
	Tree_Walk_MidOrder_Recursive(Ptr_Root->Child_R);
	return;
};

void Tree_Walk_SucOrder_Recursive(TNode* Ptr_Root)
/*
	Walk the tree in Succ-Order
	Simplest recursive method
*/
{
	if (Ptr_Root == NULL)
		return;
	Tree_Walk_SucOrder_Recursive(Ptr_Root->Child_L);
	Tree_Walk_SucOrder_Recursive(Ptr_Root->Child_R);
	cout << Ptr_Root->Key_Value << ' ';
	return;
};
      
void Tree_Walk_PreOrder_NonRecursive_Stack(TNode* Ptr_Root)
/*
	walk the tree in Pre-Order, Non-Recursive
	Using a Stack, basically the same as recursive method
*/
{
	Stack<TNode*> Temp_Stack;
	TNode* Temp_Ptr = Ptr_Root;
	while (Temp_Ptr != NULL || !Temp_Stack.isEmpty())
	{
		while (Temp_Ptr != NULL)
		{
			cout << Temp_Ptr->Key_Value << " ";
			Temp_Stack.push(Temp_Ptr);
			Temp_Ptr = Temp_Ptr->Child_L;
		};
		if (!Temp_Stack.isEmpty())
		{
			Temp_Stack.pop(Temp_Ptr);
			Temp_Ptr = Temp_Ptr->Child_R;
		};
	};
	return;
};


void Tree_Walk_SucOrder_NonRecursive_Stack(TNode* Ptr_Root)
/*
	walk the tree in suc-order, Non recursive
	using a stack
	*/
{
	Stack<TNode*> Temp_Stack;
	Stack<int> Flag_Stack;
	TNode* Temp_Ptr = Ptr_Root;
	int Temp,Temp_Count=Element_Count;
	while (Temp_Count || !Temp_Stack.isEmpty())
	{
		while (Temp_Ptr != NULL)
		{
			//cout << Temp_Ptr->Key_Value << " ";
			Temp_Stack.push(Temp_Ptr);
			Flag_Stack.push(1);
			Temp_Ptr = Temp_Ptr->Child_L;
		};
		Flag_Stack.peek(Temp);
		while (!Temp_Stack.isEmpty() && Temp==0)
		{
			Temp_Stack.pop(Temp_Ptr);
			cout << Temp_Ptr->Key_Value << ' ';
			Temp_Count--;
			//Temp_Ptr = Temp_Ptr->Child_R;
			Flag_Stack.pop(Temp);
			Flag_Stack.peek(Temp);
		};
		if (!Temp_Stack.isEmpty())
		{
			int bin;
			Flag_Stack.pop(bin);
			Flag_Stack.push(0);
			Temp_Stack.peek(Temp_Ptr);
			Temp_Ptr=Temp_Ptr->Child_R;
		};
	};
	return;
};

void Tree_Walk_PreOrder_NonRecursive_NoStack_LowSpaceCost(TNode* Ptr_Root)
/*
	Walk the tree in pre-order
	Non-Recursive, No Stack, Very low constant space cost
	Order(1)
	Maybe little lower time cost than recursive method.
*/
{
	int Temp_Count = Element_Count;
	TNode* Now_Ptr = Ptr_Root;
	TNode* Temp_Ptr = Ptr_Root;
	int Sub_Walking = 1;
	while (Sub_Walking)
	{
		while (1)			//walk to the right until null
		{
			cout << Now_Ptr->Key_Value << ' ';
			Temp_Count--;
			if (Now_Ptr->Child_L != NULL)
				Now_Ptr = Now_Ptr->Child_L;
			else
				break;
		};
		if (Temp_Count == 0)	//if process is finished, exit the function
		{
			Sub_Walking = 0;
			break;
		};

		if (Now_Ptr->Child_R != NULL)	//if this Node have a right subtree, then walk it first
		{
			Now_Ptr = Now_Ptr->Child_R;
			continue;
		};

		while (1)						//if this Node have no subtree, than walk back until find a Node with right subtree
		{
			Temp_Ptr = Now_Ptr;
			Now_Ptr = Now_Ptr->Father;
			if (Now_Ptr->Child_L == Temp_Ptr)
				if (Now_Ptr->Child_R != NULL)
				{
					Now_Ptr = Now_Ptr->Child_R;
					break;
				};
		};

	};
};

void Tree_Walk_LvlOrder_BFS(TNode* Ptr_Root)
/*
	Walk the tree in level first order
	using BFS method 
	Order(n) space cost
*/
{
	TNode* QueuePtr[MAXIMUM_NODE_COUNT];
	QueuePtr[0] = Ptr_Root;
	int PosIn = 1, PosOut = 0;
	int Temp_Count = Element_Count;
	while (Temp_Count)
	{
		cout << QueuePtr[PosOut]->Key_Value << ' ';
		if (QueuePtr[PosOut]->Child_L != NULL)
		{
			QueuePtr[PosIn] = QueuePtr[PosOut]->Child_L;
			PosIn++;
		};
		if (QueuePtr[PosOut]->Child_R != NULL)
		{
			QueuePtr[PosIn] = QueuePtr[PosOut]->Child_R;
			PosIn++;
		};
		PosOut++;
		Temp_Count--;

	};

};

TNode* GetPointer(int Key,TNode* Ptr_Root)
/*
	Give a key of a element, return its pointer
	Modified from Tree_Walk_PreOrder_NonRecursive_NoStack_LowSpaceCost(TNode* Ptr_Root)
	Order(1) space cost
*/
{
	int Temp_Count = Element_Count;
	TNode* Now_Ptr = Ptr_Root;
	TNode* Temp_Ptr = Ptr_Root;
	int Sub_Walking = 1;
	while (Sub_Walking)
	{
		while (1)
		{
			//cout << Now_Ptr->Key_Value << ' ';
			if (Now_Ptr->Key_Value == Key)
			{
				return Now_Ptr;
			};
			Temp_Count--;
			if (Now_Ptr->Child_L != NULL)
				Now_Ptr = Now_Ptr->Child_L;
			else
				break;
		};
		if (Temp_Count == 0)
		{
			Sub_Walking = 0;
			break;
		};

		if (Now_Ptr->Child_R != NULL)
		{
			Now_Ptr = Now_Ptr->Child_R;
			continue;
		};

		while (1)
		{
			Temp_Ptr = Now_Ptr;
			Now_Ptr = Now_Ptr->Father;
			if (Now_Ptr->Child_L == Temp_Ptr)
				if (Now_Ptr->Child_R != NULL)
				{
					Now_Ptr = Now_Ptr->Child_R;
					break;
				};
		};

	};
	return NULL; 
};

int GetDepth(TNode* Ptr)
/*
	Give a pointer of a node, return its depth in the tree
	NOTICE:	DEFAULT=1, dont work correctly if this pointer doesn't point to a node in the tree
*/
{
	int Temp=1;
	TNode* Temp_Ptr = Ptr;
	while (Temp_Ptr->Father != NULL)
	{
		Temp_Ptr = Temp_Ptr->Father;
		Temp++;
	};
	return Temp;
};

TNode* LowestMutualFather(TNode* Ptr_A, TNode* Ptr_B)
/*
	Give 2 pointers of 2 nodes in the tree, return the pointer of their lowest mutual father
	Return NULL if they dont have one
	TimeCost=Order(ln(n))
	SpaceCost=Order(1)
*/
{
	int Depth_A = GetDepth(Ptr_A), Depth_B = GetDepth(Ptr_B);
	if ((Depth_A == 1) || (Depth_B == 1))
		return NULL;
	TNode* Temp_Ptr_A = Ptr_A;
	TNode* Temp_Ptr_B = Ptr_B;
	if (Depth_A > Depth_B)		//if a pointer is deeper than another one, then go up
	{
		for (int i = 0; i < (Depth_A - Depth_B); i++)
			Temp_Ptr_A = Temp_Ptr_A->Father;
		Depth_A = Depth_B;
	}
	else
	{
		for (int i = 0; i < (Depth_B - Depth_A); i++)
			Temp_Ptr_B = Temp_Ptr_B->Father;
		Depth_B = Depth_A;
	};

	for (int i=0; i < Depth_A; i++)		//2 pointers go up simultaneously until they meet
	{
		Temp_Ptr_A = Temp_Ptr_A->Father;
		Temp_Ptr_B = Temp_Ptr_B->Father;
		if (Temp_Ptr_A->Key_Value == Temp_Ptr_B->Key_Value)
			return Temp_Ptr_A;
	};
	return NULL;
};

int main()
{

	cout << "NOTICE:ALL ELEMENT INPUT IN THE TREE SHOULD BE UNIQUE." << endl;
	cout << "A POSSIBLE INPUT EXAMPLE:" << endl;
	cout << "8" << endl;
	cout << "1 2 4 7 3 5 6 8" << endl;
	cout << "4 7 2 1 5 3 8 6" << endl << endl;

	cout << "Please input the size of the tree:";
	cin >> Element_Count;

	cout << "Please input the Pre-order array(seprate with while spaces):" << endl;
	for (int i = 0; i < Element_Count; i++)
		cin >> Arr_Pre[i];

	cout << "Please input the Mid-order array(seprate with white spaces):" << endl;
	for (int i = 0; i < Element_Count; i++)
		cin >> Arr_Mid[i];
	cout << endl;

	int Choice;
	while (1)
	{
		cout << "Please choose a method to build the tree('1'=recursive,'0'=non-recursive):";
		cin >> Choice;
		if (Choice*Choice != Choice)
		{
			cout << "Wrong input, please check." << endl;
			continue;
		};
		break;
	};

	TNode* Root_Ptr = NULL;
	if (Choice)
		Root_Ptr = Tree_Build_Recursive(0, 0, Element_Count);
	else
		Tree_Build_NRecursive(Root_Ptr);

	cout << endl << "Tree successfully build." << endl;
	cout << "Now you can choose a way you like to walk the tree." << endl;

	int Walking = 1;
	while (Walking)
	{
		cout << endl <<  "1.Pre-Order, Recursive" << endl;
		cout << "2.Mid-Order, Recursive" << endl;
		cout << "3.Suc-Order, Recursive" << endl;
		cout << "4.Pre-Order, Non-Recursive, Stack" << endl;
		cout << "5.Pre-Order, Non-Recursive, NoStack, LowSpaceCost" << endl;
		cout << "6.Lvl_Order, BFS Method" << endl;
		cout << "7.Suc-Order, Non-Recursive, Stack"<<endl;
		cout << "998.End loop" << endl;
		cout << "Your choice:";
		cin >> Choice;
		switch (Choice)
		{
		case 1:
			Tree_Walk_PreOrder_Recursive(Root_Ptr);
			cout << endl;
			break;
		case 2:
			Tree_Walk_MidOrder_Recursive(Root_Ptr);
			cout << endl;
			break;
		case 3:
			Tree_Walk_SucOrder_Recursive(Root_Ptr);
			cout << endl;
			break;
		case 4:
			Tree_Walk_PreOrder_NonRecursive_Stack(Root_Ptr);
			cout << endl;
			break;
		case 5:
			Tree_Walk_PreOrder_NonRecursive_NoStack_LowSpaceCost(Root_Ptr);
			cout << endl;
			break;
		case 6:
			Tree_Walk_LvlOrder_BFS(Root_Ptr);
			cout << endl;
			break;
		case 7:
			Tree_Walk_SucOrder_NonRecursive_Stack(Root_Ptr);
			cout<<endl;
			break;
		case 998:
			Walking = 0;
			cout << endl;
			break;
		default:
			cout << "No such choice.Please check your input." << endl;
			break;
		}
	};

	cout << "Now let's test the func: ElementsLowestMutualFather" << endl;

	while (1)
	{
		int Num_A, Num_B;
		cout << "Input the 2 elements to find their lowest mutual father." << endl;
		cout << "(seperate by white space, input both 0 to exit the loop)." << endl;
		cout << ">>";
		cin >> Num_A >> Num_B;
		if ((Num_A == 0) || (Num_B == 0))
			break;
		TNode* Ptr_A = GetPointer(Num_A, Root_Ptr);
		TNode* Ptr_B = GetPointer(Num_B,Root_Ptr);
		if ((int)Ptr_A*(int)Ptr_B == 0)
		{
			cout << "At least one of these element doesn's exist." << endl;
			cout << "Please check your input." << endl;
			continue;
		}; 
		TNode* Temp_Ptr_Father = LowestMutualFather(Ptr_A, Ptr_B);
		if (Temp_Ptr_Father != NULL)
			cout << "Their lowest mutual father is:" << Temp_Ptr_Father->Key_Value << endl;
		else
			cout << "They have no mutual father." << endl;
	};


	cout << "All process is done!Excited!" << endl;

	return 0;
};