#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> //this header may cause problem

//written: aclef 2015 12 17


#define INPUT_FILENAME		"phaedo.txt"		//this place defines the article used to encode
#define MAX_VALUE			2147483647			//max value of int, used to find the lease weight node in the list
#define MAX_CODE_COUNT		300					//max number of type of character
#define MAX_NODE_COUNT		MAX_CODE_COUNT*2-1	//the number of code canbe calculated from code count

using namespace std;

typedef struct
{
	int weight, father, lchild, rchild;
} HTNode;

//struct definition
HTNode	htnode[MAX_NODE_COUNT];				//stores the tree in a array
char	charin[MAX_CODE_COUNT];				//stores all characters read from the text and use their position
int		char_count = 0;						//the actual number of characters.
string	bitstr;								//store the temporary bit string
//definition end----------------------------------

int char_Exist(char chin)
/*
	Judge if a character is existed in the former part of the text
	return position if yes, return -1 otherwise.
	*/
{
	if (!char_count)
		return -1;
	for (int i = 0; i < char_count; i++)
		if (charin[i] == chin)
			return i;
	return -1;
};

void ht_DFS(int pos)
/*
	walk the tree in DFS
	display all codes.
*/
{
	int FLAG_HAVE_CHILD = 0;
	if (htnode[pos].lchild != -1)
	{
		bitstr += '0';
		ht_DFS(htnode[pos].lchild);
		bitstr = bitstr.substr(0, bitstr.length() - 1);
		FLAG_HAVE_CHILD = 1;
	};
	if (htnode[pos].rchild != -1)
	{
		bitstr += '1';
		ht_DFS(htnode[pos].rchild);
		bitstr = bitstr.substr(0, bitstr.length() - 1);
		FLAG_HAVE_CHILD = 1;
	};

	if (FLAG_HAVE_CHILD)		//if a node is a leaf, then reach the end.
		return;
	else
	{
		cout << "Code for '" << charin[pos] << "' ASCII:" << (int)charin[pos] << " is:" << bitstr << endl;
		return;
	};
};

int main()
{
	for (int i = 0; i < MAX_CODE_COUNT; i++)	//initialize the arrays
		charin[i] = 0;
	for (int i = 0; i < MAX_NODE_COUNT; i++)
	{
		htnode[i].father = -1;
		htnode[i].lchild = -1;
		htnode[i].rchild = -1;
		htnode[i].weight = 0;
	};

	cout << "The default filename is:" << INPUT_FILENAME << '.' << endl;

	ifstream fin(INPUT_FILENAME);				//open the file
	if (!fin.is_open())
	{
		cout << "This file doesnt exist, the program will now exit." << endl;
		return 0;
	};


	while (!fin.eof())							//read all characters from the file
	{
		char temp_Char; //store the temporation character
		int temp_Pos;	//store the position of the inputted character

		fin.get(temp_Char);
		temp_Pos = char_Exist(temp_Char);
		if (temp_Pos == -1)
		{
			char_count++;
			charin[char_count - 1] = temp_Char;
			htnode[char_count - 1].weight = 1;
		}
		else
			htnode[temp_Pos].weight++;
	};

	cout << "File reading process end." << endl;
	cout << "There are " << char_count << " kinds of character in the text." << endl;

	for (int i = 0; i < char_count; i++)
		cout << "Char:'" << charin[i] << "' ASCII:" << (int)charin[i] << " weight:" << htnode[i].weight << endl;


	//DATA READING PROCESS END, NOW BUILD THE TREE
	for (int i = 0; i < char_count - 1; i++)
	{
		int w1, w2, p1, p2;
		w1 = w2 = MAX_VALUE;			//w1 w2 store the least small 2 node with no father
		p1 = p2 = 0;					//p1 p2 store the least small 2 node's position
		for (int j = 0; j < char_count + i; j++)
			if (htnode[j].weight < w1 && htnode[j].father == -1)
			{
				w2 = w1;
				p2 = p1;
				w1 = htnode[j].weight;
				p1 = j;
			}
			else if (htnode[j].weight < w2 && htnode[j].father == -1)
			{
				w2 = htnode[j].weight;
				p2 = j;
			};
		//after found the least 2 small weight nodes.
		htnode[p1].father = char_count + i;		//assign 2 father to the 2 node
		htnode[p2].father = char_count + i;
		htnode[char_count + i].weight = htnode[p1].weight + htnode[p2].weight;	//father's weight is childs' sum
		htnode[char_count + i].lchild = p1;		//set child
		htnode[char_count + i].rchild = p2;
	};

	int node_count = char_count * 2 - 1;
	int htroot = node_count - 1;
	int dec_pos = htroot;
	cout << endl << "Tree build successfully with " << node_count << " nodes" << endl;

	//use a recursive function to output all code:
	bitstr = "";
	ht_DFS(htroot);

	cout << "Now input the binary code to decode(input non 01 to exit):" << endl;
	cout << "The code inputted will not be displayed." << endl;
	while (1)
	{
		char temp_char;
		temp_char=_getch();
		if (temp_char != '0' && temp_char != '1')
			break;
		if (temp_char == '0')
			dec_pos = htnode[dec_pos].lchild;
		else
			dec_pos = htnode[dec_pos].rchild;
		if (htnode[dec_pos].lchild == -1)
		{
			cout << charin[dec_pos] << endl;
			dec_pos = htroot;
		};
	};
	return 0;
};