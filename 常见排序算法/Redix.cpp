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

	void push(Node *p) { //ָ���next��ǵø���ֵ
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

	//Ѱ�����λ��
	int lengthData() {
		int length = 0;	//���ݳ��ȣ����λ����
		int n = 0;	//�������ݵ�λ��
		int d = 0;	//����Ԫ��
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

	//�����������淴����
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
				arr[k]->push(p);//�ȼ���ÿ��ָ�������γ�10���������
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
						que.push(p);//���½�һ��������д���
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

	cout << "���� int ���͵Ĵ�������������У����� ctrl+z �������룬�ٻس�����" << endl;
	//˳������Ԫ��
	while (cin >> i)
	{
		oldque.push(i);
	}
	//��������
	oldque.RadixSort(oldque);
	system("pause");
	return 0;
}

