#include <iostream>
#include <string>

/*
����Ԫ�����������࣬����ֱ��������Ԫ�ش洢������
������ʽ����������Ѱַ��ϣ���


*/


using namespace std;
string arr[8] = { "PAB" ,"5C","PABC" ,"CXY","CRSI", "7","B899", "B9" };

int is_alpha(char ch)
/*
	�ú����ж�һ���ַ��Ƿ��Ǵ�д��ĸ

*/
{
	if (ch >= 'A'&& ch <= 'Z')
		return 1;
	else return 0;
};

int compare(string a, string b)
/*
	�ú����������ַ������ֵ����С���бȽϣ����ǰ�߱Ⱥ��߿�ǰ���򷵻�0�����򷵻�1
*/
{
	int m_len = 0,flag=0;

	if (a.length() > b.length())		//ȡ�����ȱȽ�С��һ���ַ����ĳ���
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
		if (is_alpha(a[i]) && is_alpha(b[i]))		//�����λ�õ������ַ�������ĸ�������ж�
		{
			if (a[i] < b[i])
				return 0;
			if (a[i] > b[i])
				return 1;
			continue;
		}
		else if (is_alpha(a[i]))					//���a�ַ�����λ������ĸ��b���ǣ���a��ǰ
		{
			return 0;
		}
		else if (is_alpha(b[i]))					//�����෴
		{
			return 1;
		}
		else
		{
			if (a[i] < b[i])						//���a��b�����λ�ö������֣����бȽ�
				return 0;
			if (a[i] > b[i])
				return 1;
			continue;
		}
	};
	if (flag)										//����ڹ�ͬ���ȷ�Χ�ڶ���ȣ��򳤶ȱȽ϶̵��ַ����ֵ����ǰ
		return 0;
	else
		return 1;

};

int main()
{
	for (int i = 0; i < 8; i++)				//������������ʹ�ú������Ƚ�
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

	for (int i = 0; i < 8; i++)			//�������Ԫ��
	{
		cout << arr[i] << endl;
	}
	getchar();
	return 0;	 

}