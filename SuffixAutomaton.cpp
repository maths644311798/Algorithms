//给定一个只包含小写字母的字符串 input_str。
//求出 input_str的所有出现次数不为 1 的子串的出现次数乘上该子串长度的最大值。
//参考《陈立杰讲稿后缀自动机》
//OI中对堆区有限制，所以这个做法容易内存溢出。
//用全局变量的做法随处可见
#include<cstdio>
#include<algorithm>
#include<memory.h>
#include<vector>
using namespace std;

const int N = 1e6 + 10;
char input_str[N];
long long int res = 0;

//后缀自动机的状态其实是下标集合
class SuffixAutomaton
{
public:
	//先构造状态机，再据此构造parent树(字典树的变形)
	struct Node
	{
		int len; //此等价类中子串最长长度
		int size; //子树规模
		Node* fa; //用于构造parent树
		Node* child[30];//26个字母就是状态机有26个转移函数
		vector<Node*> tree_edge;
		bool visited;

		Node() : len(0), size(0), fa(NULL), visited(false)
		{
			memset(child, 0, sizeof(child));
			tree_edge.clear();
		}

		Node(Node* out_node)
		{
			if (out_node)
			{
				len = out_node->len;
				size = out_node->size;
				fa = out_node->fa;
				visited = out_node->visited;
				for (int i = 1; i <= 26; ++i)
					child[i] = out_node->child[i];
				tree_edge = out_node->tree_edge;
			}
		}
	} *root, * last;


	SuffixAutomaton()
	{
		last = root = new Node();
	}

	inline void add(Node* u, Node* v)
	{
		(u->tree_edge).push_back(v);
	}
	//构造后缀自动机 : 插入字符c，暂定状态为{pos}
	inline void ins(int c, int pos)
	{
		Node* p = last;
		last = new Node();
		last->len = pos;
		last->size = 1;
		//顺着parent树的路径向上找
		for (; p && (p->child[c] == NULL); p = p->fa)
		{
			p->child[c] = last;
		}
		if (p == NULL)
		{
			last->fa = root;
			return;
		}

		Node* q = p->child[c];
		if (p->len + 1 == q->len)
		{
			last->fa = q;
			return;
		}
		// nq的状态集合包含last的状态集合
		Node* nq = new Node(q);
		nq->size = 0;
		nq->len = p->len + 1;
		q->fa = nq;
		last->fa = nq;
		for (Node* i = p; i && (i->child[c] == q); i = i->fa)
		{
			i->child[c] = nq;
		}
	}

	//建树，用fa和p连
	void build_tree(Node* p)
	{
		if (p == NULL) return;
		if (p->visited) return;
		p->visited = true;
		if (p->fa)
		{
			add(p->fa, p);
		}
		for (int i = 1; i <= 26; i++)
			if (p->child[i])
			{
				build_tree(p->child[i]);
			}
	}

	void dfs(Node* u)
	{
		if (u == NULL) return;
		for (auto i = u->tree_edge.begin(); i != u->tree_edge.end(); ++i)
		{
			dfs(*i);
			u->size += (*i)->size;
		}
		if (u->size != 1)
		{
			res = max(res, (long long int) u->size * u->len);
		}
	}
} sam;

int main()
{
	scanf("%s", input_str + 1);
	for (int i = 1; i<=1100000 && input_str[i] != '\0'; i++)
	{
		sam.ins(input_str[i] - 'a' + 1, i);
	}
	sam.build_tree(sam.root);
	sam.dfs(sam.root);
	printf("%lld", res);
	return 0;
}
