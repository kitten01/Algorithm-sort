#include <iostream> 
#include <stdlib.h>   
#include <time.h>  
using namespace std;

int random(int min = 1, int max = 100);
void bubbleSort(int a[], int size);
void insertSort(int a[], int size);
void shellSort(int a[], int size);
void print(int *array);
void adjustHeap(int * arrs, int p, int len);
void heapSort(int * arrs, int len);
void quickSort(int a[], int head, int tail);

const int NUM = 50;
typedef long clock_t;



int main() {
	int array[NUM];


	for (int i = 0; i < NUM ; i++)//���ȡ100����,��[1-100]֮��(�п����ظ�)  
		array[i] = random();
	print(array);
	//ð������
	bubbleSort(array, NUM);
	cout << endl << "ð����������" << endl;
	print(array);
	cout << "--------------------------------------�ָ���-----------------------------------------"<<endl<<endl<<endl<< endl <<endl;


	for (int i = 0; i < NUM; i++)//���ȡ100����,��[1-100]֮��(�п����ظ�)  
		array[i] = random();
	print(array);
	//��������
	insertSort(array, NUM);
	cout <<endl<< "������������" << endl;
	print(array);
	cout << "--------------------------------------�ָ���-----------------------------------------" << endl << endl << endl << endl << endl;

		


	for (int i = 0; i < NUM; i++)//���ȡ100����,��[1-100]֮��(�п����ظ�)  
		array[i] = random();
	print(array);
	//ϣ������
	shellSort(array, NUM);
	cout << endl << "ϣ����������" << endl;
	print(array);
	cout << "--------------------------------------�ָ���-----------------------------------------" << endl << endl << endl << endl << endl;




	for (int i = 0; i < NUM; i++)//���ȡ100����,��[1-100]֮��(�п����ظ�)  
		array[i] = random();
	print(array);
	//������
	heapSort(array, NUM);
	cout << endl << "����������" << endl;
	print(array);
	cout << "--------------------------------------�ָ���-----------------------------------------" << endl << endl << endl << endl << endl;




	for (int i = 0; i < NUM; i++)//���ȡ100����,��[1-100]֮��(�п����ظ�)  
		array[i] = random();
	print(array);
	quickSort(array, 0, NUM-1);
	cout << endl << "������������" << endl;
	print(array);
	cout << "--------------------------------------�ָ���-----------------------------------------" << endl << endl << endl << endl << endl;




	system("pause");
}

void bubbleSort(int a[], int size) {
	int temp;
	bool flag=true;
	for (int i = 1; i < size && flag; i++)
	{
		flag = false;
		for (int j = 0; j < size-i; j++)
		{
			if (a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				flag=true;
			}
		}
	}
}


void insertSort(int a[], int size) {
	for (int i = 1; i < size; i++)
	{
		int key = a[i];
		int j = i - 1;
		while (j >=0 && key<a[j]) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}


void shellSort(int a[], int size) {
	for (int gap = size/2; gap >= 1; gap/=2)
	{
		for (int j = gap; j < size; j++)
		if(a[j] < a[j-gap]){
			int temp = a[j];	//�ڱ�
			int k = j - gap;
			while (k >= 0 && temp < a[k]) {
				a[k + gap] = a[k];
				k -= gap;
			}
			a[k+gap] = temp;
		}
	}
}


int random(int min, int max)
{
	return min + (max - min + 1) * rand() / RAND_MAX;
}


void print(int *array) {
	for (int i = 0; i < NUM; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}



void quickSort(int a[], int head, int tail) {
	int pivotkey = a[head];
	int i = head, j = tail;
	while (head > tail) return;
	while (i < j) {
		while (i < j && a[j] >= pivotkey) j--;
		a[i] = a[j];
		while (i < j && a[i] <= pivotkey) i++;
		a[j] = a[i];
	}
	a[i] = pivotkey;
	quickSort(a, head, i - 1);
	quickSort(a, j + 1, tail);

}


void adjustHeap(int * arrs, int p, int len) {
	int curParent = arrs[p];
	int child = 2 * p + 1;   //����
	while (child < len) {     //û�к���
		if (child + 1<len&&arrs[child]<arrs[child + 1]) {
			child++;    //�ϴ��ӵ��±�
		}
		if (curParent<arrs[child]) {
			arrs[p] = arrs[child];
			//û�н�curParent��ֵ����������Ϊ��Ҫ����������
			//����亢�����д�ģ������ƣ�curParent��Ҫ�������ơ�
			p = child;
			child = 2 * p + 1;
		}
		else
			break;
	}
	arrs[p] = curParent;
}

void heapSort(int * arrs, int len) {
	//�����ѣ�����ײ�ĸ��ڵ㿪ʼ
	for (int i = NUM / 2 - 1; i >= 0; i--)
		adjustHeap(arrs, i, NUM);
	//�������
	for (int i = NUM - 1; i >= 0; i--) {
		int maxEle = arrs[0];
		arrs[0] = arrs[i];
		arrs[i] = maxEle;

		adjustHeap(arrs, 0, i);
	}
}
