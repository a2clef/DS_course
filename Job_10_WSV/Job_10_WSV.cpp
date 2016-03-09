#include <iostream>
using namespace std;
void output_Name(int num)
{
	if (num == 0)
		cout << "Wolf ";
	else if (num == 1)
		cout << "Sheep ";
	else if (num == 2)
		cout << "Vegetable ";
	return;
};
int main()		//0=wolf 1=sheep 2=vegetable
{
	int map[3][3] = { { 0, 1, 0 }, { 1, 0, 1 }, { 0, 1, 0 } }; 	//if map[i][j], then i and j cant be together
	for (int i = 0; i < 3; i++)
		if (!map[(i + 1) % 3][(i + 2) % 3])
		{
			int j = (i + 1) % 3, k = (i + 2) % 3;
			cout << "Order1:";
			output_Name(i);
			output_Name(j);
			output_Name(k);
			cout <<endl<< "Order2:";
			output_Name(i);
			output_Name(k);
			output_Name(j);
		};
	return 0;
};