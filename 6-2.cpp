#include<iostream>
#include "queue"
using namespace std;

const int maxn = 100;
int Map[maxn][maxn];
int m, n, ans;//记录矩阵长宽
int vis[maxn][maxn];//标记已走过的

typedef struct {
	int a, b;
}Node;

bool judge(int a, int b)
{
	if (a >= n || b >= m || b < 0 || a < 0)//位置越界
		return false;
	if (vis[a][b] == 1 || Map[a][b] == 0)//可联通且未访问过
		return false;
	return true;
}

int Z[4] = { 0,0,1,-1 };//遍历元素上下左右四个方向
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
		for (int i = 0; i < 4; i++)//遍历该位置上下左右是否有可联通位置
		{
			int xx = Z[i] + top.a;
			int yy = P[i] + top.b;
			if (judge(xx, yy))
			{
				node.a = xx;
				node.b = yy;
				q.push(node);//当前结点的子项入队
				vis[xx][yy] = 1;
			}
		}
	}
}

int main()
{
	while (scanf("%d%d", &n, &m) != EOF)//矩阵的长和宽
	{
		ans = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> Map[i][j];
		for (int i = 1; i < n; i++)//遍历每一个位置
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
