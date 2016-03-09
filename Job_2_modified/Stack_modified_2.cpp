/*
	a more powerful Stack realization using pointers

*/



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
	Node<T> *ptr = new Node < T > ;
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
	Node<T> *copyPtr = top = new Node < T > ;
	copyPtr->info = oriPtr->info;
	while (oriPtr->next != NULL)
	{
		copyPtr->next = new Node < T > ;     
		copyPtr = copyPtr->next;
		oriPtr = oriPtr->next;
		copyPtr->info = oriPtr->info;
	}
	copyPtr->next = NULL;
}
