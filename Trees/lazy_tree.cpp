/*
	lazy tree is a segment tree that put the summation to a lazy mark instead add to every element.
	when we need to get the sum, we put the lazy mark to a child node, and get the sum of the current node.
*/
#include<iostream>
using namespace std;

struct TreeNode
{  
	long l, r;	//Left and Right Endpoints of Line Segment 
    long long sum, cnt;	//sum is the Summation of interval elements
    //cnt is the lazy mark
};

long a[100000];
TreeNode tree[300000];
long n, m;

void build(long i, long l, long r)
{  
	tree[i].l = l;
   	tree[i].r = r;
   	tree[i].cnt = 0;
   	tree[i].sum = 0;
   	if (l == r)
   	{  
		tree[i].sum = a[l];
      	return;
   	}
   	long mid = (l+r)/2;
   	build(i*2, l, mid);
   	build(i*2+1, mid+1, r);
   	tree[i].sum = tree[i*2].sum + tree[i*2+1].sum;
}

void update(long i)
{ 
	if (tree[i].cnt != 0)
	{  
		tree[i].sum= tree[i].sum+(tree[i].r-tree[i].l+1)*tree[i].cnt;
    	tree[i*2].cnt = tree[i*2].cnt+tree[i].cnt;
    	tree[i*2+1].cnt = tree[i*2+1].cnt+tree[i].cnt;
    	tree[i].cnt = 0;
	}
}

void ins(long i, long x, long y, long now)	//all elements in [x,y] increase
{  
	update(i);
	if (x <= tree[i].l && y >= tree[i].r)
	{  
		tree[i].cnt = now;
    	return;
	}
	long mid = (tree[i].l+tree[i].r)/2;
	if (x <= mid) ins(i*2, x, y, now);
	if (y > mid) ins(i*2+1, x, y, now);
	update(i*2); update(i*2+1);
	tree[i].sum = tree[i*2].sum+tree[i*2+1].sum;
}

long long cal(long i, long x, long y)
{  
	update(i);
	if (x <= tree[i].l && y >= tree[i].r) return tree[i].sum;
	long mid = (tree[i].l+tree[i].r)/2;
	long long ans = 0;
	if (x <= mid) ans+=cal(i*2, x, y);
	if (y > mid) ans+=cal(i*2+1, x, y);
	update(i*2); update(i*2+1);
	tree[i].sum = tree[i*2].sum+tree[i*2+1].sum;
	return ans;
}

int main()
{   cin>> n;
    for(long i = 1; i <= n; i++) cin>> a[i];
    build(1, 1, n);
    cin>> m;
    for(long i = 1; i <= m; i++)
    {  
		long k, x, y, z;
    	cin>> k;
    	if (k == 0)
    	{ 
			cin >> x >> y >> z;
			//increase a[x..y] by z
        	ins(1, x, y, z);
    	}
	    else
	    {  
			cin >> x >> y;
			//to get the sum of a[x]+a[x+1]+...a[y]
	       	cout << cal(1, x, y) << endl;
	    }
 	}
    return 0;
} 
