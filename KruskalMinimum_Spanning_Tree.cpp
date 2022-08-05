#include<iostream>//��С������
#include<algorithm>
using namespace std;
int a, b;
struct node 
{
    int x, y, val;//������һ��
}edge[200005];
int parent[5005];

bool cmp(node a, node b)//�Զ����������
{
    return a.val < b.val;
}
int find(int x) 
{
    while (parent[x] != x) 
    {
        x = parent[x] = parent[parent[x]];//·��ѹ��
    }
    return x;
}

void root(int x, int y) 
{
    int x_root = find(x);
    int y_root = find(y);
    if (x_root != y_root)parent[x_root] = y_root;//�ϲ�����
}

int main()
{
    int n, m, ans = 0, cnt = 0;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) 
    {//����
        scanf("%d %d %d", &edge[i].x, &edge[i].y, &edge[i].val);
    }
    for (int i = 1; i <= n; i++)parent[i] = i;//��ʼ��
    sort(edge + 1, edge + m + 1, cmp);//����
    for (int i = 1; i <= m; i++) 
    {
        int x_root = find(edge[i].x);
        int y_root = find(edge[i].y);
        if (x_root == y_root)continue;//���ڵ���ͬ��˵���Ѿ���һ��������
        else
        {
            //root(edge[i].x,edge[i].y);
            parent[x_root] = y_root;//�ϲ�
            ans += edge[i].val;//ans��Ȩֵ
            cnt++;//cnt:����
        }
        if (cnt == n - 1) 
        {
            printf("%d", ans);
            return 0;
        }
    }
    printf("orz");
}