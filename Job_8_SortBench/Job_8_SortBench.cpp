#include <iostream>
#include <stdlib.h>
#include <time.h>

#define MAX_COUNT 50000
#define BENCH_ROUND 10

using namespace std;


void ArrRand(int arr[])
{
	for (int i = 0; i < MAX_COUNT; i++)
		arr[i] = rand();
};

void quickSort(int s[], int l, int r)
{
	if (l< r)
	{
		int i = l, j = r, x = s[l];
		while (i < j)
		{
			while (i < j && s[j] >= x) 
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && s[i]< x) 
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		quickSort(s, l, i - 1); 
		quickSort(s, i + 1, r);
	}
}

void sort_Bubble(int arr[])
{
	int temp;
	for (int i = 0; i < MAX_COUNT; i++)
	{
		for (int j = i; j < MAX_COUNT; j++)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
};

void sort_Insertion(int arr[])
{
	for (int i = 1; i < MAX_COUNT; i++)
	{
		if (arr[i - 1] > arr[i])
		{
			int temp = arr[i];
			int j = i;
			while (j > 0 && arr[j - 1] > temp)
			{
				arr[j] = arr[j - 1];
				j--;
			}
			arr[j] = temp;
		}
	}
};

void sort_Selection(int arr[])
{
	int temp, b;
	for (int i = 0; i < MAX_COUNT - 1; i++)
	{
		temp = i;
		for (int j = i + 1; j<MAX_COUNT; j++)
		{
			if (arr[temp]>arr[j])
				temp = j;
		}
		if (i != temp)
		{
			b = arr[temp];
			arr[temp] = arr[i];
			arr[i] = b;
		}
	}
};


void sort_Quick(int arr[])
{
	quickSort(arr, 0, MAX_COUNT - 1);
};

int main()
{
	cout << "Data size is " << MAX_COUNT << endl;
	cout << "Bench round is " << BENCH_ROUND << endl;
	srand((unsigned)time(0));
	int arr[MAX_COUNT];
	double temp_Avg;

	cout << "Testing bubble Sort:" << endl;
	temp_Avg = 0;
	for (int i = 0; i < BENCH_ROUND; i++)
	{
		ArrRand(arr);
		clock_t start_Time = clock();
		//=====bench start
		sort_Bubble(arr);
		//=====bench end
		clock_t end_Time = clock();
		temp_Avg += (static_cast<double>(end_Time - start_Time) / CLOCKS_PER_SEC * 1000) / BENCH_ROUND;
		cout << "Running time " << i << " is: " << static_cast<double>(end_Time - start_Time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	};
	cout << "Average time is:" << temp_Avg << endl;
	cout << "---------------------------------------------------------------" << endl;

	cout << "Testing insertion Sort:" << endl;
	temp_Avg = 0;
	for (int i = 0; i < BENCH_ROUND; i++)
	{
		ArrRand(arr);
		clock_t start_Time = clock();
		//=====bench start
		sort_Insertion(arr);
		//=====bench end
		clock_t end_Time = clock();
		temp_Avg += (static_cast<double>(end_Time - start_Time) / CLOCKS_PER_SEC * 1000) / BENCH_ROUND;
		cout << "Running time " << i << " is: " << static_cast<double>(end_Time - start_Time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	};
	cout << "Average time is:" << temp_Avg << endl;
	cout << "---------------------------------------------------------------" << endl;

	cout << "Testing selection Sort:" << endl;
	temp_Avg = 0;
	for (int i = 0; i < BENCH_ROUND; i++)
	{
		ArrRand(arr);
		clock_t start_Time = clock();
		//=====bench start
		sort_Selection(arr);
		//=====bench end
		clock_t end_Time = clock();
		temp_Avg += (static_cast<double>(end_Time - start_Time) / CLOCKS_PER_SEC * 1000) / BENCH_ROUND;
		cout << "Running time " << i << " is: " << static_cast<double>(end_Time - start_Time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	};
	cout << "Average time is:" << temp_Avg << endl;
	cout << "---------------------------------------------------------------" << endl;

	cout << "Testing quick Sort:" << endl;
	temp_Avg = 0;
	for (int i = 0; i < BENCH_ROUND; i++)
	{
		ArrRand(arr);
		clock_t start_Time = clock();
		//=====bench start
		sort_Quick(arr);
		//=====bench end
		clock_t end_Time = clock();
		temp_Avg += (static_cast<double>(end_Time - start_Time) / CLOCKS_PER_SEC * 1000) / BENCH_ROUND;
		cout << "Running time " << i << " is: " << static_cast<double>(end_Time - start_Time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	};
	cout << "Average time is:" << temp_Avg << endl;
	cout << "---------------------------------------------------------------" << endl;


	return 0;
};