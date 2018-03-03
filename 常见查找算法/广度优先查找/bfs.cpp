#include<iostream> 
#include<vector> 
#include<map> 
#include<queue> 
#include<set> 
using namespace std;

vector<int> bfs(map<int, vector<int> > link, int top)
{
	queue<int> qe;  //����������¼�ڵ�ı���˳�� ����ʵ����е�˳��Ҳ����bfs���ҵ�˳�� 
	vector<int> order;//bfs���ҵ����˳�� 
	map<int, int> pre; //�ҵ�ÿ���ڵ��ǰһ���ڵ㣬���Ը��������ϵ������������ڵ�����·�� 
	set<int> qeset;  //��Ϊ���в��ʺ��ڲ��ң�������set����¼�������ִ��Ԫ�أ������ж��½ڵ��Ƿ��ڶ����� 
	map<int, int> vis;  //��Ԫ�شӶ����е��������Ѿ����ʹ�����ڵ��ˣ��ͽ���浽map�� 

	qe.push(top);  //�Ƚ���ʼ������� 
	order.push_back(top); //top��bfs���ҵĵ�һ��Ԫ�� 
	qeset.insert(top); //��set����Ӷ����ڵ�Ԫ�أ�set����ж��ı� 
	int head, i = 0;
	while (!qe.empty())  //�����зǿ�ʱһֱ�����ö��� 
	{
		head = qe.front();  //ȡ���е�ͷԪ�� 
		qe.pop();  //����Ԫ�ص��� 
		qeset.erase(head); //set��֮ɾ��headԪ�� 
		vis[head] = 1;  //��ʱheadԪ�ر����ʹ������Ϊ1 
		for (i = 0; i < link[head].size(); i++)  //������head�ڵ����ڵĽڵ� 
		{
			if (qeset.find(link[head][i]) == qeset.end() && vis.find(link[head][i]) == vis.end()) //������㲻�ڶ�����Ҳû�б����ʹ���������� 
			{
				pre[link[head][i]] = head;  //�ڵ�link[head][i]��ǰһ���ڵ�Ϊhead 
				qe.push(link[head][i]);  //���ýڵ������ 
				qeset.insert(top);   //set��Ӧ�����ӦԪ�� 
				order.push_back(link[head][i]);  //bfs����˳����Ӹ�Ԫ�� 
			}
		}

	}

	map<int, int>::iterator it;
	cout << "preorder:" << endl; 
	for (it = pre.begin(); it != pre.end(); it++) 
	{ 
	    cout << it->first << "->" << it->second << " "; 
	} 
	�����top��Զ�Ľڵ��������� 
	head = order[order.size() - 1];
	i = 0;
	while (pre.find(head) != pre.end())
	{
		head = pre[head];
		i++;
	}
	cout << "����top��Զ�Ľڵ������: ";
	cout << i << endl;

	cout << endl;
	return order;
}

int main()
{
	int x, top, m, n, i = 0;
	map<int, vector<int> > link;
	cin >> x; //����������ڽӹ�ϵ 
	for (i = 0; i < x; i++)
	{
		cin >> m >> n;
		link[m].push_back(n); //����ͼ����������������Ϲ�ϵ 
		link[n].push_back(m);
	}
	cout << "top:" << endl;
	cin >> top;
	vector<int> order;
	order = bfs(link, top);
	cout << "order:" << endl;
	for (i = 0; i < order.size(); i++)
	{
		cout << order[i] << " ";
	}
	cout << endl;
	system("pause");
}