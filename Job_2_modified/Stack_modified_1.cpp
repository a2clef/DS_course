#define STACK_HEADER_TYPE_1
#include <stdlib.h>

template<class T>
class Stack
/*
	The declaration of template class Stack
	functions:
		1.int isEmpty()
		2.int isFull()
		3.int Size()
		4.*T getData()
		5.push(const T &e)
		6.pop(T &e)
*/
{
public:
	Stack(void);					//default constructor
	~Stack(void);					//default destructor

	int push(const T &e);			//push
	int pop(T &e);					//pop
	int isEmpty() const				//isEmpty
	{
		return top == -1;
	}

	int isFull() const				//isFull
	{
		return top == size - 1;
	}

	T operator [] (int index);		//[] operator reloaded

	int Size() const				//Size
	{
		return top + 1;
	}

	T* getData() const;				//getData


private:
	int size;						//the length of the stack
	int top;						//position of the stack top
	T *stackPtr;					//pointer of the element at the top of the stack
};


template<class T>
Stack<T>::Stack(void)				//default constructor definition
/*
	the default size of a stack is 100
*/
{
	size = 100;
	top = -1;
	stackPtr = new T[size];
}

template<class T>
Stack<T>::~Stack(void)				//destructor definition
{
	delete[] stackPtr;
}

template<class T>
int Stack<T>::push(const T &e)		//push dinifition
/*
	return 1 if push successed
	return 0 if push failed
*/
{
	if (isFull())					//add more space to the stack if the stack is full
	{
		stackPtr = (T *)realloc(stackPtr, (size + 10)*sizeof(T));
		stackPtr[++top] = e;
		size += 10;		
		return 1;
	}
	else
	{
		stackPtr[++top] = e;
		return 1;
	}
	return 0;
}


template<class T>
int Stack<T>::pop(T &e)
/*
	return 1 if pop successed
	return 0 if pop failed
*/
{
	if (!isEmpty())
	{
		e = stackPtr[top--];
		return 1;
	}
	return 0;
}

template <class T>
T Stack<T>::operator[](int index)
{
	return stackPtr[index];
}

template <class T>
T* Stack<T>::getData() const
{
	return stackPtr;
}
