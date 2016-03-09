#include <iostream>
#define MAX_COUNT 100

//written by AClef 2015 12 02


//=================================================================================================
//===============================STACK DEFINITION START============================================
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



class AdjNode
{
public:
	int Key;
	AdjNode * P_Next;
};


using namespace std;
int Count;
AdjNode Table[MAX_COUNT];




void init_visit()
{
	for (int i = 1; i <= Count; i++)
		Table[i].Key = 0;
	return;
};

void init_table()
{
	for (int i = 1; i <= Count; i++)
	{
		Table[i].P_Next = NULL;
		Table[i].Key = 0;
	};
	return;
};

void DFS_Search(int node)
{
	cout << node << " ";
	AdjNode* P_Temp = Table[node].P_Next;
	while (P_Temp)
	{
		if (Table[P_Temp->Key].Key)
		{
			P_Temp = P_Temp->P_Next;
			continue;
		};
		Table[P_Temp->Key].Key = 1;
		DFS_Search(P_Temp->Key);
		P_Temp = P_Temp->P_Next;
	};
	return;
};

void Travel_DFS_Recursive()
{
	init_visit();
	int FLAG_Connected=1;
	for (int k = 1; k <= Count; k++)
	{
		if (Table[k].Key)
			continue;
		cout << "Start from node " << k << endl;
		Table[k].Key = 1;
		DFS_Search(k);
		cout << endl;
		if (k!=1)
			FLAG_Connected=0;
	};
	if (FLAG_Connected)
		cout << "This graph is connected"<<endl;
	else
		cout << "This graph is not connected."<<endl;
	return;
};

void Travel_DFS_Stack()
{
	init_visit();
	Stack<int> stack_i;
	for (int k = 1; k <= Count; k++)
	{
		if (Table[k].Key)
			continue;
		cout << "Start from node " << k << endl;
		Table[k].Key = 1;
		//search start
		stack_i.push(k);
		cout << k << " ";

		while (!stack_i.isEmpty())
		{
			int Temp,Flag_Have_Unvisited_Neighbor=0;
			AdjNode* P_Temp;
			stack_i.peek(Temp);
			P_Temp = Table[Temp].P_Next;
			while (!Flag_Have_Unvisited_Neighbor)
			{
				if (!P_Temp)
					break;
				if (Table[P_Temp->Key].Key)
				{
					P_Temp = P_Temp->P_Next;
					continue;
				};
				Flag_Have_Unvisited_Neighbor = 1;
				cout << P_Temp->Key << " ";
				Table[P_Temp->Key].Key = 1;
				stack_i.push(P_Temp->Key);
			};
			if (!Flag_Have_Unvisited_Neighbor)
				stack_i.pop(Temp);
		};
		//search end
		cout << endl;
	};
	return;
};


void BFS_Search(int node)
{
	int Queue[MAX_COUNT];
	int iq = 1, oq = 0;
	Queue[0] = node;
	while (iq > oq)
	{
		cout << Queue[oq] << " ";
		AdjNode* P_Temp = Table[Queue[oq]].P_Next;
		oq++;
		while (P_Temp)
		{
			if (Table[P_Temp->Key].Key == 0)
			{
				Queue[iq] = P_Temp->Key;
				iq++;
				Table[P_Temp->Key].Key = 1;
			};
			P_Temp = P_Temp->P_Next;
		};
	};
	return;
};

void Travel_BFS()
{
	init_visit();
	for (int k = 1; k <= Count; k++)
	{
		if (Table[k].Key)
			continue;
		cout << "Start from node " << k << endl;
		Table[k].Key = 1;
		BFS_Search(k);
		cout << endl;
	};
	return;
};


int main()
{
	cout << "Please input the number of points(<=100):";
	cin >> Count;
	init_table();

	cout << "Please input the 2 point of edge(enter both 0 to exit)." << endl;
	int a, b;
	while (cin >> a >> b)
	{
		if (a*b == 0)
			break;

		if ((a <= 0 || a > Count) || (b <= 0 || b > Count))
		{
			cout << "Illegal input, Please check." << endl;
			continue;
		};

		AdjNode* P_Temp = Table[a].P_Next; //Temp points to the first adj node of a
		
		int Flag_Edge_Existed = 0;			//set flag to 0
		while (P_Temp)
		{
			if (P_Temp->Key == b)
			{
				Flag_Edge_Existed = 1;
				break;
			};
			P_Temp = P_Temp->P_Next;
		};
		if (Flag_Edge_Existed)
		{
			cout << "This edge already exists. Please check." << endl;
			continue;
		};
		
		//inert the edge into the graph(both link list)
		P_Temp = &Table[a];	//locate the link list
		while (P_Temp->P_Next)	//goto the tail of the list
			P_Temp = P_Temp->P_Next;
		P_Temp->P_Next = new AdjNode;	//add a new AdjNode object
		P_Temp->P_Next->Key = b;
		P_Temp->P_Next->P_Next = NULL;

		P_Temp = &Table[b];
		while (P_Temp->P_Next)
			P_Temp = P_Temp->P_Next;
		P_Temp->P_Next = new AdjNode;
		P_Temp->P_Next->Key = a;
		P_Temp->P_Next->P_Next = NULL;
	};

	cout << "Travel the Graph with DFS" << endl;
	Travel_DFS_Recursive();

	cout << "Travel the Graph with DFS(Non-Recursive)" << endl;
	Travel_DFS_Stack();


	cout << "Travel the Graph with BFS" << endl;
	Travel_BFS();

	return 0;
};