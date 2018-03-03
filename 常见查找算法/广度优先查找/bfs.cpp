#include<iostream> 
#include<vector> 
#include<map> 
#include<queue> 
#include<set> 
using namespace std;

vector<int> bfs(map<int, vector<int> > link, int top)
{
	queue<int> qe;  //队列用来记录节点的遍历顺序 ，其实入队列的顺序也就是bfs查找的顺序 
	vector<int> order;//bfs查找的最后顺序 
	map<int, int> pre; //找到每个节点的前一个节点，可以根据这个关系算出任意两个节点的最短路径 
	set<int> qeset;  //因为队列不适合于查找，所以用set来记录队列中现存的元素，用于判断新节点是否在队列里 
	map<int, int> vis;  //当元素从队列中弹出，即已经访问过这个节点了，就将其存到map里 

	qe.push(top);  //先将起始点入队列 
	order.push_back(top); //top是bfs查找的第一个元素 
	qeset.insert(top); //给set里添加队列内的元素，set随队列而改变 
	int head, i = 0;
	while (!qe.empty())  //当队列非空时一直遍历该队列 
	{
		head = qe.front();  //取队列的头元素 
		qe.pop();  //将该元素弹出 
		qeset.erase(head); //set随之删除head元素 
		vis[head] = 1;  //此时head元素被访问过，标记为1 
		for (i = 0; i < link[head].size(); i++)  //遍历与head节点相邻的节点 
		{
			if (qeset.find(link[head][i]) == qeset.end() && vis.find(link[head][i]) == vis.end()) //当这个点不在队列里也没有被访问过，则入队列 
			{
				pre[link[head][i]] = head;  //节点link[head][i]的前一个节点为head 
				qe.push(link[head][i]);  //将该节点入队列 
				qeset.insert(top);   //set相应插入对应元素 
				order.push_back(link[head][i]);  //bfs查找顺序添加该元素 
			}
		}

	}

	map<int, int>::iterator it;
	cout << "preorder:" << endl; 
	for (it = pre.begin(); it != pre.end(); it++) 
	{ 
	    cout << it->first << "->" << it->second << " "; 
	} 
	求距离top最远的节点的最大条数 
	head = order[order.size() - 1];
	i = 0;
	while (pre.find(head) != pre.end())
	{
		head = pre[head];
		i++;
	}
	cout << "距离top最远的节点的条数: ";
	cout << i << endl;

	cout << endl;
	return order;
}

int main()
{
	int x, top, m, n, i = 0;
	map<int, vector<int> > link;
	cin >> x; //输入多少组邻接关系 
	for (i = 0; i < x; i++)
	{
		cin >> m >> n;
		link[m].push_back(n); //无向图所以两个方向都添加上关系 
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