#include <iostream>
#include <string>
#include <sstream>
/*
	get:	stringstream
	*/
#include <cstdlib>

using namespace std;
/*
	aclef 1140310316 151102->151103
	ALL HAIL TO THE GOD OF WAR



	*/


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

//=================================================================================================
//===============================STACK DIFINITION END==============================================
//=================================================================================================

int Priority(string op)
/*
	return the priority of operators in number
	need args of string
	*/
{
	int priority;
	if (op == "#")
		priority = 4;
	else if (op == "*" || op == "/" || op == "%")
		priority = 3;
	//else if ()
	//	priority = 2;
	else if (op == "+" || op == "-")
		priority = 1;
	else if (op == "(")
		priority = 0;
	return priority;
};

int isNumber(string token)
/*
	return 1 if this string represents a number
	*/
{
	for (int i = 0; i < (signed int)token.length(); i++)
		if (isdigit(token[i]))
			return 1;
	return 0;
};

int isOperator(string token)
/*
	return 0 if this string represents a operator
	*/
{
	int temp;
	string OperatorStr = "(#)+-*%//";					// a string conatains all operators
	for (int i = 0; i < (signed int)token.length(); i++)
	{
		temp = OperatorStr.find(token[i]);				//if a char in the token is found in OperatorStr
		if (!(temp == string::npos))					//then this token must be a operator
			return 1;
	};
	return 0;
};


int main()
{
	static string KnownCh = "1234567890(#.)+-*%//";		//this string contains all valid character in a expression
	//note:'#'symbol is later used to represent negative number			
	Stack<string>	OPTStack;		//stack of operators
	string input_raw, input;		//the original line inputed / the cleaned input
	string token[300];				//stores all tokens splitted from the input
	string token_suffix[300];		//stores all tokens in order of suffix expression

	int EXPR_TYPE_INT = 0;			//FLAGS:TYPE OF EXPRESSION
	int EXPR_TYPE_FLOAT = 0;
	int i = 0, token_count = 0;

	cout << "Please input the infix expression" << endl;
	getline(cin, input_raw);
	input = "";




	//split the string
	for (int i = 0; i < (signed)input_raw.length(); i++)		//input is the processed string without white space
	{
		int temp = KnownCh.find(input_raw[i]);						//Check if this input contains illegal character
		if (temp == string::npos)
		{
			cout << "This input contains unknown character" << endl;
			cout << "Which can't be calculated." << endl;
			cout << "Please check your input" << endl;
			cout << "The program will now exit" << endl;
			getchar();
			return 0;
		}
		else
			input += input_raw[i];

	};

	for (int i = 1; i < (signed)input.length(); i++)			//let '#' represent the negative operator
		if (input[i] == '-')
			if (!(isdigit(input[i - 1]) || (input[i - 1] == ')')))
				input[i] = '#';

	if (input[0] == '-')								//if the '-' symbol appear at the begin of a string 
		input[0] = '#';									//then it must be a negative symbol

	//TEST START
	cout << endl << "The pre-processed input is:" << endl;
	cout << "(The '#' in the expression represents negative operator.)" << endl;
	cout << input << endl;
	//TEST END



	//judge the type of the expression
	for (int i = 0; i < (signed int)input.length(); i++)			//if this expression contains '.'->float expression
		if (input[i] == '.')
		{
			EXPR_TYPE_FLOAT = 1;
			break;
		};
	for (int i = 0; i < (signed int)input.length(); i++)			//if this expression contains '%'->int expression
		if (input[i] == '%')
		{
			EXPR_TYPE_INT = 1;
			break;
		};
	if ((EXPR_TYPE_FLOAT + EXPR_TYPE_INT) == 0)			//default EXPR_TYPR_INT
		EXPR_TYPE_INT = 1;

	if ((EXPR_TYPE_FLOAT*EXPR_TYPE_INT) == 1)			//float expression cant have mod operator
	{
		cout << "This expression contains both real number and mod operator" << endl;
		cout << "which can't be calculated." << endl;
		cout << "The program will now exit" << endl;
		getchar();
		return 0;
	};


	if (EXPR_TYPE_FLOAT)
	{
		cout << endl << "This is a float expression!" << endl;
	}
	else
	{
		cout << endl << "This is an integer expression!" << endl;
	};







	while (i < (signed)input.length())							//split the input into tokens
	{
		string token_temp = "";
		if (isdigit(input[i]))							//process the postive number
		{
			//j = i;
			while ((isdigit(input[i]) || input[i] == '.') && (i < (signed)input.length()))
			{
				token_temp += input[i];
				i++;
			};
			token[token_count] = token_temp;
			token_count++;
			continue;
		};

		if (input[i] == '#')							//process the negative number
		{
			token_temp += input[i];
			i++;
			while ((isdigit(input[i]) || input[i] == '.') && (i < (signed)input.length()))
			{
				token_temp += input[i];
				i++;
			};
			token[token_count] = token_temp;
			token[token_count][0] = '-';					//change the'#' symbol back to '-'
			token_count++;
			continue;
		};
		if (input[i] == '+')							//process the '+' sign
		{
			if (token[token_count - 1] == "+")				//if there are too much '+' symbol
			{
				i++;
				continue;
			};
			token_temp += input[i];
			i++;
			token[token_count] = token_temp;
			token_count++;
			continue;
		};

		if ((input[i] == '-') || (input[i] == '*') || (input[i] == '/') || (input[i] == '%') || (input[i] == '(') || (input[i] == ')'))	//process the '-' '*' '/' sign
		{
			token_temp += input[i];
			i++;
			token[token_count] = token_temp;
			token_count++;
			continue;
		};
	};
	//TEST START
	cout << endl << "There are " << token_count << " tokens." << endl;
	cout << "The splitted tokens is:" << endl;
	for (int i = 0; i < token_count; i++)
	{
		cout << token[i] << ' ';
	};
	cout << endl;

	//TEST END

	//___________________________________________TURN INTO SUFFIX EXPRESSION
	string tempOpt = "";
	int token_suffix_count = 0;
	for (int i = 0; i < token_count; i++)
	{
		if (isNumber(token[i]))
		{
			token_suffix[token_suffix_count] = token[i];
			token_suffix_count++;
			continue;
		};
		if (isOperator(token[i]))
		{
			if (OPTStack.isEmpty())
			{
				OPTStack.push(token[i]);
				continue;
			};

			if (token[i] == "(")
			{
				OPTStack.push(token[i]);
				continue;
			};

			if (token[i] == ")")
			{
				while (OPTStack.pop(tempOpt))
				{
					if (tempOpt == "(")
						break;
					token_suffix[token_suffix_count] = tempOpt;
					token_suffix_count++;
				};
				continue;
			};
			while (OPTStack.peek(tempOpt))
			{
				if (Priority(tempOpt) >= Priority(token[i]))
				{
					OPTStack.pop(tempOpt);
					token_suffix[token_suffix_count] = tempOpt;
					token_suffix_count++;
				}
				else
					break;
			};
			OPTStack.push(token[i]);
			continue;
		};
	};
	while (!OPTStack.isEmpty())
	{
		OPTStack.pop(tempOpt);
		token_suffix[token_suffix_count] = tempOpt;
		token_suffix_count++;
	};
	cout << endl << "The suffix expression is:" << endl;
	for (int i = 0; i < token_suffix_count; i++)
		cout << token_suffix[i] << " ";
	cout << endl;


	if (EXPR_TYPE_INT)
	{
		Stack<int>		NIIStack;
		int temp, tileft, tiright;
		for (int i = 0; i < token_suffix_count; i++)
		{
			if (isNumber(token_suffix[i]))
			{
				stringstream(token_suffix[i]) >> temp;
				NIIStack.push(temp);
				continue;
			};
			if (isOperator(token_suffix[i]))
			{
				NIIStack.pop(tiright);
				NIIStack.pop(tileft);
				if (token_suffix[i] == "+")
					NIIStack.push(tileft + tiright);
				if (token_suffix[i] == "-")
					NIIStack.push(tileft - tiright);
				if (token_suffix[i] == "*")
					NIIStack.push(tileft * tiright);
				if (token_suffix[i] == "%")
					NIIStack.push(tileft % tiright);

				if (token_suffix[i] == "/")
				{
					if (tiright == 0)
					{
						cout << "Something is divided by zero" << endl;
						cout << "The program will now exit" << endl;
						return 0;
					};
					NIIStack.push(tileft / tiright);
				};
			};

		};
		cout << endl << "The result of calculation is:";
		NIIStack.pop(temp);
		cout << temp << endl;
	}
	else if (EXPR_TYPE_FLOAT)
	{
		Stack<double>	NRDStack;
		double temp, tdleft, tdright;
		for (int i = 0; i < token_suffix_count; i++)
		{
			if (isNumber(token_suffix[i]))
			{
				stringstream(token_suffix[i]) >> temp;
				NRDStack.push(temp);
				continue;
			};
			if (isOperator(token_suffix[i]))
			{
				NRDStack.pop(tdright);
				NRDStack.pop(tdleft);
				if (token_suffix[i] == "+")
					NRDStack.push(tdleft + tdright);
				if (token_suffix[i] == "-")
					NRDStack.push(tdleft - tdright);
				if (token_suffix[i] == "*")
					NRDStack.push(tdleft * tdright);
				if (token_suffix[i] == "/")
				{
					if (tdright == 0)
					{
						cout << "Something is divided by zero" << endl;
						cout << "The program will now exit" << endl;
						return 0;
					};
					NRDStack.push(tdleft / tdright);
				};
			};

		};
		cout << endl << "The result of calculation is:";
		NRDStack.pop(temp);
		cout.setf(ios_base::fixed, ios_base::floatfield);
		cout << temp << endl;
	}
	else
	{
		return 0;
	};
	getchar();
	return 0;
};