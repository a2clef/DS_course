/* By Leafy
2015/11/2 */
#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;

union NUMORSIGN
{
	float n;
	char c;
};
int Get(char a)                                      //用于返回该操作符的优先级
{
	if (a == '+' || a == '-')                       //+43;-45;
	{
		return 1;
	}
	else if (a == '*' || a == '/' || a == '%')      //*42;/47;%37;
	{
		return 2;
	}
	else if (a == 40 || a == 41)                     //()40,41;
	{
		return 3;
	}
	return -1;
}
void convert(string line, int len)
{

	int i = 0,
		j = 0,
		k = 0;

	int x = 0;
	int flag = 1;                                  //若前一位是符号或为空，则为1；

	char sign[50];                                  //用来存储运算符
	for (i = 0; i<50; i++)
	{
		sign[i] = '\0';
	}

	NUMORSIGN nors[50];                            //用于储存中间结果
	int    norsdef[50];                            //用来协助判断nors存储的类型，n为0，c为1；

	int  a = 0, b = 0;                                //分别用来标注两个数组存储的元素的个数,同时指明了下一个元素存储的下标
	char  ctof[10];
	char     tempc;


	for (i = 0; i < len;)
	{
		if ((line[i] == '-') && flag)                //用于判断负号是相反数还是减法的作用
		{
			nors[b].c = 0;
			norsdef[b] = 1;
			cout << "judge";

			b++;
			i++;
		}
		else if (line[i] <= '9' && line[i] >= '0')            //操作数压入nors；
		{
			j = i;
			while ((j <= len) && ((line[j]<'9' && line[j]>'0') || line[j] == '.'))
			{
				j++;
			}
			j--;
			x = 0;
			for (k = i; k <= j; k++)
			{
				ctof[x] = line[k];
				x++; 
			}
			ctof[x] = '\0';
			nors[a].n = atof(ctof);
			norsdef[a] = 0;
			a++;
			i = j + 1;
			cout << nors[a - 1].n << endl;
			flag = 0;
		}
		else if (a == 0 || line[i] == '(' || sign[a - 1] == '(' || (Get(line[i]) > Get(sign[a - 1])))
		{
			sign[a] = line[i];
			a++;
			i++;
			cout << "FLAGspe" << sign[a - 1];  //error case 1
		}
		else if (line[i] == ')')
		{
			nors[b].c = sign[a - 1];
			norsdef[b] = 1;
			b++;
			sign[a - 1] = '\0';
			a--;
			tempc = sign[a - 1];
			while (tempc != '(' && a > 0)
			{
				nors[b].c = sign[a - 1];
				norsdef[b] = 1;
				b++;
				sign[a - 1] = '\0';
				a--;
				tempc = sign[a-1];
			}
		}
		else if (Get(line[i]) <= Get(sign[a - 1]))
		{
			nors[b].c = sign[a - 1];
			norsdef[b] = 1;
			b++;
			sign[a - 1] = '\0';
			a--;
			tempc = sign[a - 1];
			while (Get(tempc) <= Get(sign[a - 1]) && a > 0)
			{
				nors[b].c = sign[a - 1];
				norsdef[b] = 1;
				b++;
				sign[a - 1] = '\0';
				a--;
				tempc = sign[a-1];
			}
		}
	}


	for (i = 0; i<2; i++)
	{
		if (norsdef[i] == 1)
		{
			cout << nors[i].c;
		}
		else
		{
			cout << nors[i].n;
		}
	}


}
int main()
{
	string line;

	char input;

	getline(cin, line);
	cout << "已读入算式：" << line << endl;

	int len = line.length();
	cout << "有效字符的个数为：" << len << endl;

	int i, j = 0;
	for (i = 0; i<len; i++)                              //除掉字符串里所有的空格
	{
		if (line[i] != ' ')
		{
			line[j] = line[i];
			j++;
		}
	}
	line[j] = '\0';
	len = j - 1;
	cout << line << "#" << endl;


	convert(line, len);

	return 0;

}
