// /**
//  * @file luogu3373.cpp
//  * @author HourunLi (HourunLi@github.io)
//  * @brief luogu3373 segment tree template
//  * @version 0.1
//  * @date 2022-08-03
//  * 
//  * @copyright Copyright (c) 2022
//  * 
//  */

// #include"SegmentTree.hpp"
// int main() {
//     freopen("input.txt","r",stdin);
//     int n, m, mod;
//     cin >> n >> m >> mod;
//     SegmentTree solver = SegmentTree(n, mod);

//     solver.inputData(n);
//     solver.buildTree(1, n, 1);
//     int opcode, x, y, k;
//     for(int i = 0; i < m; i++) {
//         cin >> opcode;
//         if (opcode == 1) {
//             cin >> x >> y >> k;
//             solver.mul(x, y, 1, n, k, 1); 
//         } else if (opcode == 2) {
//             cin >> x >> y >> k;
//             solver.add(x, y, 1, n, k, 1); 
//         } else if(opcode == 3) {
//             cin >> x >> y;
//             cout << solver.getSum(x, y, 1, n, 1) << endl;   
//         }
//     }
//     return 0;
// }
/**
 * @file SegmentTree.hpp
 * @author HourunLi
 * @brief segment tree template
 * @version 0.1
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
typedef unsigned int uint32;
typedef long long ll;
typedef unsigned long long uint64;
typedef pair<int, int> Pair;

#ifdef DEBUG
#define print(...) printf(__VA_ARGS__)
#else
#define print(...)
#endif
#ifndef __SEGMENT_TREE_HPP__
#define __SEGMENT_TREE_HPP__
#define lc(i) (i << 1)
#define rc(i) ((i << 1) | 1)

class SegmentTree {
private:
    int n, mod;
    ll *tree, *addLazyTag, *mulLazyTag;
public:
    int *data;
    SegmentTree(int n, int mod = INT_MAX): n(n), mod(mod){
        tree = new ll[4*n]();
        addLazyTag = new ll[4*n]();
        mulLazyTag = new ll[4*n];
        for(int i = 0 ; i < 4*n ; i++) mulLazyTag[i] = 1;
        data = new int[n+5]();
    }

    ~SegmentTree() {
        delete [] tree;
        delete [] addLazyTag;
        delete [] mulLazyTag;
        delete [] data;
    }

    void inputData(int size) {
        for(int i = 1; i <= size ; i++) {
            cin >> data[i];
        }
    }

    void buildTree(int l, int r, int root) {
        if(l == r) {
            tree[root] = data[l]%mod;
            return;
        }

        int m = (l + r) >> 1;
        buildTree(l, m, lc(root));
        buildTree(m+1, r, rc(root));
        tree[root] = (tree[lc(root)] + tree[rc(root)]) % mod;
        return;
    }

    void pushdown(int s, int t, int p) {
        int m = (s + t) >> 1;
        tree[lc(p)] = ( (tree[lc(p)]*mulLazyTag[p])%mod + (addLazyTag[p] * (m-s+1))%mod ) % mod;
        tree[rc(p)] = ( (tree[rc(p)]*mulLazyTag[p])%mod + (addLazyTag[p] * (t-m))%mod ) % mod;
        // tree[rc(p)] += addLazyTag[p] * (t-m);
        addLazyTag[lc(p)] = (addLazyTag[lc(p)] * mulLazyTag[p] + addLazyTag[p]) % mod;
        addLazyTag[rc(p)] = (addLazyTag[rc(p)] * mulLazyTag[p] + addLazyTag[p]) % mod;
        addLazyTag[p] = 0;

        mulLazyTag[lc(p)] = (mulLazyTag[lc(p)] * mulLazyTag[p]) % mod;
        mulLazyTag[rc(p)] = (mulLazyTag[rc(p)] * mulLazyTag[p]) % mod;
        mulLazyTag[p] = 1;
        return;
    }

    void add(int l, int r, int s, int t, int num, int root) {
        if(l > t || r < s) return;
        if(l <= s && r >= t) {
            tree[root] = ( tree[root] + (t-s+1)*num ) % mod;
            addLazyTag[root] = (addLazyTag[root] + num) % mod;
            return;
        }

        int m = (s + t) >> 1;
        if(addLazyTag[root] || mulLazyTag[root] != 1) {
            pushdown(s, t, root);
        }
        if(l <= m) add(l, r, s, m, num, lc(root));
        if(r > m) add(l, r, m+1, t, num, rc(root));
        tree[root] = (tree[lc(root)] + tree[rc(root)]) % mod;
        return;
    }

    void mul(int l, int r, int s, int t, int num, int root) {
        if(l > t || r < s) return;
        if(l <= s && r >= t) {
            tree[root] = (tree[root] * num) % mod;
            addLazyTag[root] = (addLazyTag[root] * num) % mod;
            mulLazyTag[root] =  (mulLazyTag[root] * num) % mod;
            return;
        }
        int m = (s + t) >> 1;
        if(addLazyTag[root] || mulLazyTag[root] != 1) {
            pushdown(s, t, root);
        }
        if(l <= m) mul(l, r, s, m, num, lc(root));
        if(r > m) mul(l, r, m+1, t, num, rc(root));
        tree[root] = (tree[lc(root)] + tree[rc(root)]) % mod;
        return;
    }

    int getSum(uint32 l, uint32 r, uint32 s, uint32 t, uint32 root) {
        if(l > t || r < s) return 0;
        if(l <= s && r >= t) return (tree[root]) % mod;
        int m = (s + t) >> 1;
        // cout << m << endl;
        if(addLazyTag[root] || mulLazyTag[root] != 1) {
            pushdown(s, t, root);
        }
        int sum = 0;
        
        if(l <= m) sum = getSum(l ,r, s, m, lc(root));
        if(r > m) sum += getSum(l, r, m+1, t, rc(root));
        return sum%mod;
    }
};
#endif // ! __SEGMENT_TREE_HPP__

int main() {
    // freopen("input.txt","r",stdin);
    int n, m, mod;
    cin >> n >> m >> mod;
    SegmentTree solver = SegmentTree(n, mod);

    solver.inputData(n);
    solver.buildTree(1, n, 1);
    int opcode, x, y, k;
    for(int i = 0; i < m; i++) {
        cin >> opcode;
        if (opcode == 1) {
            cin >> x >> y >> k;
            solver.mul(x, y, 1, n, k, 1); 
        } else if (opcode == 2) {
            cin >> x >> y >> k;
            solver.add(x, y, 1, n, k, 1); 
        } else if(opcode == 3) {
            cin >> x >> y;
            cout << solver.getSum(x, y, 1, n, 1) << endl;   
        }
    }
    return 0;
}