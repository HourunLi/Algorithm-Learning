#include<bits/stdc++.h>
using namespace std;

#define lowbit(x) (x&(-x))

typedef long long ll;

class BinaryIndexedTree {
private:
    ll *tree;
    int size;
public:
    BinaryIndexedTree(int n) {
        size = n;
        tree = new ll[size+1]();
    }

    ~BinaryIndexedTree() {
        delete[] tree;
    }

    void init(int n, ll *list) {
        for(int i = 1; i <=n; i++) {
            tree[i] = list[i];
        }
        return;
    }

    void buildTree() {
        for(int i = 1; i <= size; ++i) {
            int directParent = i + lowbit(i);
            if(directParent <= size) {
                tree[directParent] += tree[i];
            }
        }
        return;
    }

    // update single node
    void add(int p, int k) {
        while(p <= size) {
            tree[p] += k;
            p = p + lowbit(p);
        }
        return;
    }

    // get sum of 1, 2, ...., x 
    ll getSum(int x) {
        ll ans = 0;
        while(x >= 1) {
            ans = ans + tree[x];
            x -= lowbit(x);
        }
        return ans;
    }
    ll getRangeSum(int l, int r) {
        return getSum(r) - getSum(l-1);
    }
    ll *getTree() {
        return tree;
    }
    
    int getSize() {
        return size;
    }
};

int n, m;
int main() {
    cin >> n >> m;
    ll *a = new ll[n+1]();
    BinaryIndexedTree btree = BinaryIndexedTree(n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    btree.init(n, a);
    btree.buildTree();

    for(int i = 0; i < m; i++) {
        int opcode, x, y;
        scanf("%d%d%d", &opcode, &x, &y);
        if (opcode == 1) {
            int k;
            scanf("%d", &k);
            if(k == 1) continue;
            for(int j = x; j <= y; j++) {
                if(a[j] >= k && a[j] % k == 0) {
                    int tmp = a[j]/k;
                    btree.add(j, tmp - a[j]);
                    a[j] = tmp;
                }
            }
        } else {
            cout << btree.getRangeSum(x, y) << endl;   
        }
    }
    delete[] a;
    return 0;
}