#include <iostream>
using namespace std;
/*
	因为只有一百个元素，没有使用更加复杂的算法的意义。取出最大元素的算法可以在Order(n)内完成
	对于这个数量级的输入普通数组已经足够使用。
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
		if (arr[i]>temp)		//在输入的时候就可以直接找到该数字
		{
			temp = arr[i];
			pos = i;
		}
	};
	cout << "The max number is " << temp << " , it's position is " << pos + 1 << endl;

	getchar();

	return 0;
}