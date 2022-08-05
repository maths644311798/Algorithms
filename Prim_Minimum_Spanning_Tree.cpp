#include<algorithm>
#include<iostream>
#include<cstring>
#include<stdio.h>
#include<math.h>
#include<string>
#include<stdio.h>
#include<queue>
#include<stack>
#include<map>
#include<deque>
using namespace std;

struct edge//����ߵ������toΪͨ���ıߣ�����Ҫ����from
{
    int to;
    int v;
    friend bool operator<(const edge& x, const edge& y)//���ȶ��м���С��
    {
        return x.v > y.v;
    }
};

priority_queue<edge>q;
int vis[105];//�ж��Ƿ�������
int p[105][105];//��ͼ
int n;
int main()
{
    int i, j, s, key;
    edge now;
    while (scanf("%d", &n) != EOF)
    {
        for (i = 0; i < n; i++)
        {
            vis[i] = 0;//��ʼ��һ��
            for (j = 0; j < n; j++)
            {
                scanf("%d", &p[i][j]);
            }
        }
        s = 0;
        vis[0] = 1;//�����ʼ��
        key = 0;//�������ʼ��
        while (!q.empty())q.pop();
        for (i = 0; i < n - 1; i++)//n-1��
        {
            for (j = 0; j < n; j++)//�����¼��������
            {
                if (!vis[j])//û��ǹ��ĵ�ͼ���ȫ��Ͱ�ײ�
                {
                    now.to = j;
                    now.v = p[key][j];
                    q.push(now);
                }
            }
            while (!q.empty() && vis[q.top().to])//��С�ߵ��Ǳ�ǹ��ͷ���
            {
                q.pop();
            }
            if (q.empty())
                break;
            now = q.top();
            key = now.to;
            s += now.v;//�ۼ���С�ߵĺ�
            vis[key] = 1;
            q.pop();
        }
        printf("%d\n", s);
    }
    return 0;
}