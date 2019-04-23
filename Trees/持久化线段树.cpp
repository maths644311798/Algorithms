/*
主席树又名持久化线段树。
功能：比线段树多维护若干历史版本。
思路：要维护区间[1,n]上的数据，则对每一个前缀[1,i]都建立一棵线段树，i=1,…n. 共建n棵线段树。如果每棵线段树都有O(n)个结点，其实重复了很多信息。稍微深入思考，发现前缀[1,i+1]建立的线段树和前缀[1,i]的线段树相比，只有某个叶结点到根结点的路径上所有结点信息改变，故只变化O(lgn)个结点。所以每棵线段树应该新建O(lgn)个结点。
 
应用问题：第k小的数。 时间限制:2s，空间限制：64M.
问题描述：给定int a[1...n]，回答m个查询Q(x,y,k)：在线段a[x...y]中的第k小的数是什么？
输入：第一行为整数数组规模n，查询数m。第二行为n个整数。之后m行，每行3个整数: x,y,k，表示Q(x,y,k). 1≤n≤100000，1≤m≤5000. a[i]的绝对值≤10^9. 1≤x≤y≤n，1≤k≤y-x+1.
 
样例输入：
7 3
1 5 2 6 3 7 4
2 5 3
4 4 1
1 7 3
 
样例输出：
5
6
3
*/ 

#include<iostream>
#include<stdio.h>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=1e5+6;
int n,m,cnt(0),root[maxn],a[maxn]; //root[]储存n棵线段树的根结点下标。
struct node{int l,r,sum;}; //默认初始化l,r,sum为0
//l,r是区间左右端点， sum是区间中已经插入多少个数据 
vector<int> v;

//获取x的下标，在下标范围在1~n的情况下 
int getid(int x){return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
 
class PersistentLineSegmentTree
{
public:

    node tnode[maxn*40];  //O(nlgn)个结点
    void update(int l,int r,int &x,int y,int pos)
	{
              //利用tnode[y]的信息新建结点
        tnode[++cnt]=tnode[y];     //tnode[x]和tnode[y]总对应相同的线段（区间）.
        tnode[x=cnt].sum++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(mid>=pos) update(l,mid, tnode[x].l, tnode[y].l, pos);
        else update(mid+1,r, tnode[x].r, tnode[y].r, pos);
    }

    int query(int l,int r,int x,int y,int k)
    {
        if(l==r) return l;
        int mid=(l+r)>>1;
        int sum=tnode[tnode[y].l].sum - tnode[tnode[x].l].sum;
        if(sum>=k) return query(l,mid,tnode[x].l,tnode[y].l,k);
        else return query(mid+1,r,tnode[x].r,tnode[y].r,k-sum);
    }
} T;  //树中有若干根结点，视为多棵线段树
 

int main()
{
    ios::sync_with_stdio(false);
    scanf("%d %d",&n,&m);
    for(int i=1; i<=n; ++i) scanf("%d",&a[i]),v.push_back(a[i]);
    //离散化
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    //根据第i-1棵线段树来建立第i棵线段树，其实只增加O(lgn)个结点
    for(int i=1; i<=n; ++i) T.update(1,n,root[i],root[i-1],getid(a[i]));
    for(int i=1; i<=m; ++i)
    {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        //用区间[1...y]的信息比较区间[1...x-1]，即知[x...y]上的信息
        printf("%d\n",v[T.query(1,n,root[x-1],root[y],k)-1]);
    }
    return 0;
}
