#ifndef __BINARY_INDEXED_TREE__
#define __BINARY_INDEXED_TREE__
#include "basic.hpp"

#define lowbit(x) (x&(-x))
class BinaryIndexedTree {
private:
    ll *tree;
    int size;
public:
    BinaryIndexedTree(int n) {
        size = n;
        tree = new ll[size+1]();
    }

    void input(int n) {
        for(int i = 1; i <=n; i++) {
            scanf("%d", &tree[i]);
        }
        return;
    }

    void buildTree(int n) {
        for(int i = 1; i <= n; ++i) {
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

    ll *getTree() {
        return tree;
    }
    
    int getSize() {
        return size;
    }
};

#endif // !__BINARY_INDEXED_TREE__
