#include<iostream>
using namespace std;

struct Node {
	int data;
	Node *next;
};

class Queue {
private:
	Node *front;
	Node *rear;
public:
	Queue()
	{
		Node *p = new Node();
		p->data = NULL;
		p->next = NULL;
		front = p;
		rear = p;
	}

	~Queue()
	{
		Node *p = front;
		Node *q;
		while (p != NULL) {
			q = p;
			p = p->next;
			delete q;
		}
	}

	void push(Node *p) { //指针的next领记得赋空值
		p->next = NULL;
		rear->next = p;
		rear = p;
	}

	void push(int a) {
		Node *p = new Node();
		p->data = a;
		p->next = NULL;
		rear->next = p;
		rear = p;
	}

	//寻找最大位数
	int lengthData() {
		int length = 0;	//数据长度（最大位数）
		int n = 0;	//单个数据的位数
		int d = 0;	//数据元素
		Node *p = front->next;
		while (p != NULL) {
			d = p->data;
			while (d > 0) {
				d /= 10;
				n++;
			}
			p = p->next;
			if (length < n)
				length = n;

			n = 0;
		}
		return length;
	}

	bool empty() {
		if (rear == front)
			return true;
		else return false;
	}

	void clear() {
		front->next = NULL;
		rear = front;
	}

	void print(Queue &que) {
		Node *p = que.front->next;
		while (p != NULL) {
			cout << p->data << " ";
			p = p->next;
		}
	}

	//两个容器里面反复倒
	void RadixSort(Queue &que) {
		Queue *arr[10];
		for (int i = 0; i < 10; i++)
		{
			arr[i] = new Queue;
		}
		int maxlen = que.lengthData();
		int d = 1;
		for (int i = 0; i < maxlen; i++)
		{
			Node *p = que.front->next;
			Node *q;
			int k = 0;
			while (p != NULL) {
				k = ((p->data) / d) % 10;
				q = p->next;
				arr[k]->push(p);//先加入每个指针数组形成10个链表队列
				p = q;
			}
			que.clear();
			for (int i = 0; i < 10; i++)
			{
				if (!arr[i]->empty()) {
					Node *p = arr[i]->front->next;
					Node *q;
					while (p != NULL) {
						q = p->next;
						que.push(p);//在新建一个链表队列存入
						p = q;
					}
				}
			}
			for (int i = 0; i < 10; i++)
			{
				arr[i]->clear();
			}
			d *= 10;
			que.print(que);
			cout << endl;
		}
		que.print(que);
	}
};

int main(void)
{
	Queue oldque;
	int i;

	cout << "输入 int 类型的待排序的整数序列：输入 ctrl+z 结束输入，再回车即可" << endl;
	//顺序输入元素
	while (cin >> i)
	{
		oldque.push(i);
	}
	//基数排序
	oldque.RadixSort(oldque);
	system("pause");
	return 0;
}

