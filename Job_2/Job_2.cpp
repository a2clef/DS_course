#include <iostream>

#define TABLE_SIZE 50

using namespace std;

/*
	A series of stacks storaged in a linear table
	without the aid of pointers

	All free space is collected by a static stack:bin

	a.clef 1140310316
	15.10.30
*/


typedef struct Node
/*
	the basic element of a linear table
	contains 3 integar value, used like a pointer link node
*/
{
	int key;
	int prev, succ;
}Node;


//This is the table that storages all data
static Node table[TABLE_SIZE];


class Stack
/*
	CLASS STACK
	data:
		1.top pointer
		2.root pointer(base)
		3.element count
	function:
		1.Stack_IsEmpty()
		2.Stack_Size()
		3.Stack_Pop()
		4.Stack_Push(position,key)
	static function:
		1.Stack_GetStorage()
			get a free slot from stack:bin
*/
{

private:
	int top, base, count;

public:
	Stack();		//default constructer, initialize a stack
	int Stack_IsEmpty();
	int Stack_Size();
	static int Stack_GetStorage();
	int Stack_Pop();
	void Stack_Push(int pos,int key);


};

Stack::Stack()		//the default constructor
{
	top = -1;
	base = -1;
	count = 0;
};

static Stack bin;	//the free space collector, also a stack


int Stack::Stack_Size()
//return the size of a stack
{
	return (*this).count;
};

int Stack::Stack_IsEmpty()
//return 1 if this stack is empty
{
	if ((*this).count == 0)
		return 1;
	else
		return 0;
};

int Stack::Stack_Pop()
//pop a element from a normal stack
//warning: DO NOT USE THIS FUNCTION TO POP STACK:bin
//			PLEASE USE Stack::Stack_GetStorage only when
//			you need a new slot
{
	int temp;

	if ((*this).Stack_IsEmpty())
	{
		cout << "The Stack Is Empty!" << endl;
		return -1;
	};

	(*this).count--;		//stack not empty,successfully poped
	cout << "The element poped is " << (table[(*this).top]).key << endl;
	temp = (*this).top;		//temp holds the position of the poped element in the table

	(*this).top = table[(*this).top].prev; //exclude the element from the stack

	bin.Stack_Push(temp, -1);	//push the excluded element into the bin stack, collect free spaces.
	if ((*this).Stack_IsEmpty())	//if the stack is empty, then re-initialize the stack.
		(*this).top = (*this).base = -1;
	return temp;			//return the position of poped element, maybe useless
};

void Stack::Stack_Push(int pos, int key)
/*
	This function pushes a element into a stack
	the position of a free slot and the key to be stored is necessary
	***This function is shared by normal stack and bin stack
*/
{
	if (pos == -1)	//if the arg:pos is -1, maybe the Stack::Stack_GetStorage() failed to fetch a free slot
	{
		cout << "Push failed!" << endl; //nothing can be done
		return;
	};


	if ((*this).Stack_IsEmpty())		//if the stack is empty,then the element pushed is the root of the stack
	{
		(*this).base = pos;
		(*this).top = pos;
		table[pos].key = key;
		table[pos].prev = -1;
		table[pos].succ = -1;
		(*this).count = 1;
	}
	else								//Push the element into the stack
	{
		table[(*this).top].succ = pos;

		table[pos].key = key;
		table[pos].prev = (*this).top;
		table[pos].succ = -1;
		
		(*this).top = pos;
		(*this).count++;
	};

	return;
};

int Stack::Stack_GetStorage()
/*
	THIS FUNCTION ONLY APPLYS TO STACK:bin
	No argument is required
*/
{
	if (bin.Stack_IsEmpty())  //if the stack:bin is empty, the table is full
	{
		cout << "There are no spaces to free!" << endl;
		return -1;				//return a impossible value to inform other procedure that Stack_GetStorage failed
	};

	int temp;

	bin.count--;
	if (bin.Stack_IsEmpty())	//reset the bin stack
		bin.top = bin.base = -1;

	temp = bin.top;
	bin.top = table[bin.top].prev;	//exclude the slot from bin stack
	return temp;
};




int main()
{
	cout << "Initializing the table for stacks..." << endl;
	for (int i = 0; i < 50; i++)		//initialize the table
	{
		table[i] = { -1, -1, -1 };
		bin.Stack_Push(i, 0);			//Push all elements into bin
	};
	cout << "Table initialized, the size of the table is " <<TABLE_SIZE<<"."<<endl;
	Stack stack1, stack2, stack3;
	cout << "3 stacks created!" << endl;
	cout << "Now push 9 elements into stack1" << endl;
	cout << "The elements is 998,12,432,5345,2,5243,925,84,15"<<endl;
	stack1.Stack_Push(Stack::Stack_GetStorage(), 998);
	stack1.Stack_Push(Stack::Stack_GetStorage(), 12);
	stack1.Stack_Push(Stack::Stack_GetStorage(), 432);
	stack1.Stack_Push(Stack::Stack_GetStorage(), 5345);
	stack1.Stack_Push(Stack::Stack_GetStorage(), 2);
	stack1.Stack_Push(Stack::Stack_GetStorage(), 5243);
	stack1.Stack_Push(Stack::Stack_GetStorage(), 925);
	stack1.Stack_Push(Stack::Stack_GetStorage(), 84);
	stack1.Stack_Push(Stack::Stack_GetStorage(), 15);
	cout << "Now push 9 elements into stack2" << endl;
	cout << "The elements is 998,12,412,513,5634,26,986,5637,6"<<endl;
	stack2.Stack_Push(Stack::Stack_GetStorage(), 998);
	stack2.Stack_Push(Stack::Stack_GetStorage(), 12);
	stack2.Stack_Push(Stack::Stack_GetStorage(), 412);
	stack2.Stack_Push(Stack::Stack_GetStorage(), 513);
	stack2.Stack_Push(Stack::Stack_GetStorage(), 5634);
	stack2.Stack_Push(Stack::Stack_GetStorage(), 26);
	stack2.Stack_Push(Stack::Stack_GetStorage(), 986);
	stack2.Stack_Push(Stack::Stack_GetStorage(), 5637);
	stack2.Stack_Push(Stack::Stack_GetStorage(), 6);
	cout << "Now push 8 elements into stack3" << endl;
	cout << "The elements is 412,123,73564,42435,132,47352,41452,413542"<<endl;
	stack3.Stack_Push(Stack::Stack_GetStorage(), 412);
	stack3.Stack_Push(Stack::Stack_GetStorage(), 123);
	stack3.Stack_Push(Stack::Stack_GetStorage(), 73654);
	stack3.Stack_Push(Stack::Stack_GetStorage(), 42435);
	stack3.Stack_Push(Stack::Stack_GetStorage(), 132);
	stack3.Stack_Push(Stack::Stack_GetStorage(), 47352);
	stack3.Stack_Push(Stack::Stack_GetStorage(), 41452);
	stack3.Stack_Push(Stack::Stack_GetStorage(), 413542);

	cout << "Now stack1 have " << stack1.Stack_Size() << " elements." << endl;
	cout << "There are " << bin.Stack_Size() << " free slots." << endl;
	cout << "Now pop some of the elements in stack1:" << endl;
	stack1.Stack_Pop();
	stack1.Stack_Pop();
	stack1.Stack_Pop();
	stack1.Stack_Pop();
	stack1.Stack_Pop();
	cout << "Now stack1 have " << stack1.Stack_Size() << " elements." << endl;
	cout << "There are " << bin.Stack_Size() << " free slots." << endl;

	cout << "Now stack2 have " << stack2.Stack_Size() << " elements." << endl;
	cout << "Now pop some of the elements in stack2:" << endl;
	stack2.Stack_Pop();
	stack2.Stack_Pop();
	stack2.Stack_Pop();
	stack2.Stack_Pop();
	cout << "Now stack2 have " << stack2.Stack_Size() << " elements." << endl;
	cout << "There are " << bin.Stack_Size() << " free slots." << endl;

	cout << "Now stack3 have " << stack3.Stack_Size() << " elements." << endl;
	cout << "Now pop some of the elements in stack3:" << endl;
	stack3.Stack_Pop();
	stack3.Stack_Pop();
	stack3.Stack_Pop();
	cout << "Now stack3 have " << stack3.Stack_Size() << " elements." << endl;
	cout << "There are " << bin.Stack_Size() << " free slots." << endl << endl;

	cout << "Now pop all elements out." << endl;
	cout << "Clearing elements in stack1." << endl;
	while (!stack1.Stack_IsEmpty())
		stack1.Stack_Pop();
	cout << "Clearing elements in stack2." << endl;
	while (!stack2.Stack_IsEmpty())
		stack2.Stack_Pop();
	cout << "Clearing elements in stack3." << endl;
	while (!stack3.Stack_IsEmpty())
		stack3.Stack_Pop();


	cout << "Now stack1 have " << stack1.Stack_Size() << " elements." << endl;
	cout << "Now stack2 have " << stack2.Stack_Size() << " elements." << endl;
	cout << "Now stack3 have " << stack3.Stack_Size() << " elements." << endl;
	cout << "There are " << bin.Stack_Size() << " free slots." << endl << endl;

	cout << "All precess finished, excited!" << endl;
	return 0;
}