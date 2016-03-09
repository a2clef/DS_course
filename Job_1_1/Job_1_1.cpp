#include <iostream>
#include <string>

/*
由于元素数量并不多，可以直接用数组元素存储并排序
其他方式：链表，开放寻址哈希表等


*/


using namespace std;
string arr[8] = { "PAB" ,"5C","PABC" ,"CXY","CRSI", "7","B899", "B9" };

int is_alpha(char ch)
/*
	该函数判断一个字符是否是大写字母

*/
{
	if (ch >= 'A'&& ch <= 'Z')
		return 1;
	else return 0;
};

int compare(string a, string b)
/*
	该函数对两个字符串的字典序大小进行比较，如果前者比后者靠前，则返回0，否则返回1
*/
{
	int m_len = 0,flag=0;

	if (a.length() > b.length())		//取出长度比较小的一个字符串的长度
	{
		m_len = b.length();
	}
	else
	{
		m_len = a.length();
		flag = 1;
	};
	for (int i = 0; i < m_len; i++)
	{
		if (is_alpha(a[i]) && is_alpha(b[i]))		//如果该位置的两个字符都是字母，进行判断
		{
			if (a[i] < b[i])
				return 0;
			if (a[i] > b[i])
				return 1;
			continue;
		}
		else if (is_alpha(a[i]))					//如果a字符串该位置是字母而b不是，则a靠前
		{
			return 0;
		}
		else if (is_alpha(b[i]))					//与上相反
		{
			return 1;
		}
		else
		{
			if (a[i] < b[i])						//如果a和b在这个位置都是数字，进行比较
				return 0;
			if (a[i] > b[i])
				return 1;
			continue;
		}
	};
	if (flag)										//如果在共同长度范围内都相等，则长度比较短的字符串字典序较前
		return 0;
	else
		return 1;

};

int main()
{
	for (int i = 0; i < 8; i++)				//插入排序法排序，使用函数来比较
	{
		for (int j = i + 1; j < 8; j++)
		{
			if (compare(arr[i], arr[j]))
			{
				string	temp;
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			};
		};
	};

	for (int i = 0; i < 8; i++)			//输出所有元素
	{
		cout << arr[i] << endl;
	}
	getchar();
	return 0;	 

}