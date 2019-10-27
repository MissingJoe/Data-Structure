#include<iostream>
#include "queue"
using namespace std;

const int maxn = 100;
int Map[maxn][maxn];
int m, n, ans;//��¼���󳤿�
int vis[maxn][maxn];//������߹���

typedef struct {
	int a, b;
}Node;

bool judge(int a, int b)
{
	if (a >= n || b >= m || b < 0 || a < 0)//λ��Խ��
		return false;
	if (vis[a][b] == 1 || Map[a][b] == 0)//����ͨ��δ���ʹ�
		return false;
	return true;
}

int Z[4] = { 0,0,1,-1 };//����Ԫ�����������ĸ�����
int P[4] = { 1,-1,0,0 };

void BFS(int x, int y)
{
	queue<Node> q;
	Node node;
	node.a = x;
	node.b = y;
	q.push(node);
	vis[x][y] = 1;
	while (!q.empty())
	{
		Node top = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)//������λ�����������Ƿ��п���ͨλ��
		{
			int xx = Z[i] + top.a;
			int yy = P[i] + top.b;
			if (judge(xx, yy))
			{
				node.a = xx;
				node.b = yy;
				q.push(node);//��ǰ�����������
				vis[xx][yy] = 1;
			}
		}
	}
}

int main()
{
	while (scanf("%d%d", &n, &m) != EOF)//����ĳ��Ϳ�
	{
		ans = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> Map[i][j];
		for (int i = 1; i < n; i++)//����ÿһ��λ��
			for (int j = 1; j < m; j++)
				if (Map[i][j] == 1 && vis[i][j] == 0)
				{
					ans++;
					BFS(i, j);
				}
		cout << ans << endl;
	}
	return 0;
}
