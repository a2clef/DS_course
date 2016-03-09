#include<iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
#define N 40
using namespace std;

typedef struct S
{
	string name;
	int sco[6];
	int num;
	int ss[6];
};
int n, m, w;
S a[N];
string b[N];
int five[6] = { 0, 7, 5, 3, 2, 1 };
int three[4] = { 0, 5, 3, 2 };

void init()
{
	cout << "����ѧԺ��n��������Ŀ��m��Ů����Ŀ��w" << endl;
	cin >> n >> m >> w;
	cout << "������ÿ��ѧԺ�ı�ż�����" << endl;
	int fl;
	for (int i = 1; i <= n; i++)
	{
		cin >> fl;
		cin >> b[fl];
	}
	cout << "������ÿ����Ŀ�ı�ţ����ƣ�ȡ���������������ÿ�����ε�ѧԺ���" << endl;
	for (int i = 0; i < m + w; i++)
	{
		cin >> fl; cin >> a[fl].name; cin >> a[fl].num;
		if (a[fl].num == 3)
			for (int j = 1; j <= 3; j++)
				a[fl].ss[j] = three[j];
		if (a[fl].num == 5)
			for (int j = 1; j <= 5; j++)
				a[fl].ss[j] = five[j];
		for (int j = 1; j <= a[fl].num; j++)
			cin >> a[fl].sco[j];
	}
	char* filename = "file.dat";
	FILE *fp;
	fp = fopen(filename, "wb");
	fwrite(&a, sizeof(S), N, fp);
	fclose(fp);
	return;
}

void sum()
{
	int sco[N];
	char* filename = "file.dat";
	FILE *fp;
	fp = fopen(filename, "rb");

	fread(&a, sizeof(S), N, fp);
	fclose(fp);
	for (int i = 1; i <= n; i++) sco[i] = 0;
	for (int i = 1; i <= m + w; i++)
	{

		for (int j = 1; j <= a[i].num; j++)
		{
			sco[a[i].sco[j]] += a[i].ss[j];
		}
	}
	for (int i = 1; i <= n; i++)
		cout << sco[i] << endl;

}
void sort()
{
	cout << "��������ʽ��" << endl;
	cout << "1��ѧԺ���" << endl;
	cout << "2��ѧԺ����" << endl;
	cout << "3��ѧԺ�ܷ�" << endl;
	cout << "4������" << endl;
	cout << "5��Ů��" << endl;
	int sco[N];
	for (int i = 1; i <= n; i++) sco[i] = 0;
	for (int i = 1; i <= m + w; i++)
	{

		for (int j = 1; j <= a[i].num; j++)
		{
			sco[a[i].sco[j]] += a[i].ss[j];
			//cout<<i<<" "<<j<<" "<<a[i].sco[j]<<" "<<a[i].ss[j]<<" "<<sco[a[i].sco[j]]<<endl;

		}
	}
	int bh;
	cin >> bh;
	if (bh == 1)
	{
		for (int i = 1; i <= n; i++)
			cout << i << ":" << b[i] << " " << sco[i] << endl;
	}
	else if (bh == 2)
	{
		int re[N];
		for (int i = 1; i <= n; i++)
			re[i] = i;
		for (int i = 1; i<n; i++)
			for (int j = i; j <= n; j++)
				if (b[i]>b[j])
				{
					string rec = b[i];
					b[i] = b[j];
					b[j] = rec;
					int rr = re[i];
					re[i] = re[j];
					re[j] = rr;
				}
		for (int i = 1; i <= n; i++)
			cout << i << ":" << b[i] << " " << sco[re[i]] << endl;
	}
	else if (bh == 3)
	{
		int re[N];
		for (int i = 1; i <= n; i++)
			re[i] = i;
		for (int i = 1; i<n; i++)
			for (int j = i; j <= n; j++)
				if (sco[i]<sco[j])
				{
					int rec = sco[i];
					sco[i] = sco[j];
					sco[j] = rec;
					int rr = re[i];
					re[i] = re[j];
					re[j] = rr;
				}
		for (int i = 1; i <= n; i++)
			cout << i << ":" << b[re[i]] << " " << sco[i] << endl;

	}
	else if (bh == 4)
	{
		for (int i = 1; i <= n; i++) sco[i] = 0;
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= a[i].num; j++)
				sco[a[i].sco[j]] += a[i].ss[j];
		int re[N];
		for (int i = 1; i <= n; i++)
			re[i] = i;
		for (int i = 1; i<n; i++)
			for (int j = i; j <= n; j++)
				if (sco[i]<sco[j])
				{
					int rec = sco[i];
					sco[i] = sco[j];
					sco[j] = rec;
					int rr = re[i];
					re[i] = re[j];
					re[j] = rr;
				}
		for (int i = 1; i <= n; i++)
			cout << i << ":" << b[re[i]] << " " << sco[i] << endl;
	};
	if (bh == 5)
	{
		for (int i = 1; i <= n; i++) sco[i] = 0;
		for (int i = m + 1; i <= m + w; i++)
			for (int j = 1; j <= a[i].num; j++)
				sco[a[i].sco[j]] += a[i].ss[j];
		int re[N];
		for (int i = 1; i <= n; i++)
			re[i] = i;
		for (int i = 1; i<n; i++)
			for (int j = i; j <= n; j++)
				if (sco[i]<sco[j])
				{
					int rec = sco[i];
					sco[i] = sco[j];
					sco[j] = rec;
					int rr = re[i];
					re[i] = re[j];
					re[j] = rr;
				}
		for (int i = 1; i <= n; i++)
			cout << i << ":" << b[re[i]] << " " << sco[i] << endl;
	};
	else
	{
		cout << "ERROR" << endl;
		return;
	};
};



void search()
{
	char* filename = "file.dat";
	FILE *fp;
	fp = fopen(filename, "rb");

	fread(&a, sizeof(S), N, fp);
	fclose(fp);
	cout << "1����ѯѧԺ" << endl;
	cout << "2����ѯ��Ŀ" << endl;
	int ch;
	cin >> ch;
	if (ch == 1)
	{
		int bh;
		cout << "����ѧԺ���" << endl;
		cin >> bh;
		cout << "������Ŀ���" << endl;
		int bh2;
		int flag = 0;
		cin >> bh2;
		for (int i = 1; i <= a[bh2].num; i++)
			if (a[bh2].sco[i] == bh)
			{
				cout << "no." << i << endl;
				flag = 1;
				break;
			}
		if (flag == 0) cout << "no prize" << endl;
	}
	else if (ch == 2)
	{
		int bh;
		cout << "������Ŀ���" << endl;
		cin >> bh;
		for (int i = 1; i <= a[bh].num; i++)
			cout << "no." << i << ":" << a[bh].sco[i] << " :" << b[a[bh].sco[i]] << endl;
	}
	else
	{
		cout << "ERROR" << endl;
		return;
	}
}


void doit(int n)
{
	switch (n)
	{
	case 1:init();	return;
	case 2:sum(); return;
	case 3:sort();	return;
	case 4:search();	return;
	default: {cout << "ERROR"; return; }
	}
}
void printmenu()
{
	cout << "����ѡ��" << endl;
	cout << "1)������Ŀ��ǰ������ǰ�����ĳɼ�" << endl;
	cout << "2)ͳ���ܷ�" << endl;
	cout << "3)�������" << endl;
	cout << "4)��ȷ��ѯ" << endl;
	cout << "5)�˳�" << endl;
}



int main()
{
	printmenu();
	int count;
	cin >> count;
	while (count != 5)
	{
		doit(count);
		printmenu();
		cin >> count;
		getchar();
	}
	getchar();
	return 0;

}
