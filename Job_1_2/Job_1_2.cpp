#include <iostream>
using namespace std;
/*
	��Ϊֻ��һ�ٸ�Ԫ�أ�û��ʹ�ø��Ӹ��ӵ��㷨�����塣ȡ�����Ԫ�ص��㷨������Order(n)�����
	���������������������ͨ�����Ѿ��㹻ʹ�á�
*/
int main()
{
	double arr[998],temp;
	int n,pos=0;
	cout << "Please input the number of numbers:";
	cin >> n;
	cout << "Please input the numbers in order:" << endl;
	cin >> temp;
	arr[0] = temp;
	for (int i = 1; i < n; i++)
	{
		cin >> arr[i];
		if (arr[i]>temp)		//�������ʱ��Ϳ���ֱ���ҵ�������
		{
			temp = arr[i];
			pos = i;
		}
	};
	cout << "The max number is " << temp << " , it's position is " << pos + 1 << endl;

	getchar();

	return 0;
}