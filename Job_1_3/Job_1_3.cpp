#include<iostream>
using namespace std;

struct Node
{
	Node * prev;
	int num;
	Node * succ;
};

int main()
{
	int n = 0;
	int score[101][101];
	cout << "Please input the number of teams:";
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		score[i][i] = -1;
		for (int j = i + 1; j <= n; j++)
		{
			cout <<"Please input the game result of team "<<i<<" and "<<j<<", 1(win)/0(lose):";
			cin >> score[i][j];
		}
	}
	for (int i = 0; i <= n; i++)
		score[i][i] = -1;

	Node	pLink;
	Node	*tail = &pLink,*head = &pLink;
	pLink.prev = pLink.succ = NULL;
	pLink.num = 1;
	Node	*now	=	tail;
	Node	*sv		=	NULL;


	cout << "The result is: ";
	for (int i = 2; i <= n; i++)
	{
		now = tail;								//scan the table from tail to head
		while (score[i][now->num] == 1)			//if beat by tail, then insert after the tail
		{										//if beat by element in the middle, then insert  after the element
			if (now->prev != NULL)				//if no element in the list so far can beat this element, insert it at the head
				now = now->prev;
			else
				break;
		};
		if (now->prev == NULL && score[i][now->num] == 1) 
		{
			now->prev = new Node;
			head = now->prev;
			now->prev->num = i;
			now->prev->succ = now;
			now->prev->prev = NULL;
		}
		else
		{
			sv = now->succ;
			now->succ = new Node;
			now->succ->num = i;
			now->succ->prev = now;
			now->succ->succ = sv;
			if (sv == NULL)
				tail = now->succ;
		};
		now = tail;
	};
	now = head;
	while (now->succ != NULL)
	{
		cout << now->num << " ";
		now = now->succ;
	};
	cout << now->num << endl;
	getchar();
	return 0;
};
