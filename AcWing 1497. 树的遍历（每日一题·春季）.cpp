
#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;
const int N = 35;
int Post[N], In[N];
unordered_map<int, int>lChild, rChild, Pos;
int build(int iStart, int iEnd, int pStart, int pEnd) {
    int root = Post[pEnd];
    int k = Pos[root];
    if (iStart < k)lChild[root] = build(iStart, k - 1, pStart, pStart + k - 1 - iStart);
    if (iEnd > k)rChild[root] = build(k + 1, iEnd, pStart + k - iStart, pEnd - 1);
    ///列两个方程
    /*
    *            左子树    根  右子树
      Inorder:|___________ - ___________|
              iSt      k-1 k k+1       iEnd

                  左子树      右子树      根
    Postorder:|____________|____________|
              pSt         X|X+1        pEnd

              得到如下方程
              X - pSt = k - 1 - iSt;
    */
    return root;
}
void bfs(int start) {
    queue<int>q;
    q.push(start);
    while (q.size()) {
        int node = q.front();
        q.pop();
        cout << node << ' ';//弹出队列最末尾
        if (lChild[node])q.push(lChild[node]);
        if (rChild[node])q.push(rChild[node]);
        //在弹出该层时将该节点的左右子树列入，从左到右顺序
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)cin >> Post[i];
    for (int i = 0; i < n; ++i) {
        cin >> In[i];
        Pos[In[i]] = i;//将下标存入哈希表
    }
    int Root = build(0, n - 1, 0, n - 1);
    bfs(Root);
    return 0;
}

