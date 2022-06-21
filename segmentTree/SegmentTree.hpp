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
#ifndef __SEGMENT_TREE_HPP__
#define __SEGMENT_TREE_HPP__
#include "../basic.hpp"
#define lc(i) (i << 1)
#define rc(i) ((i << 1) | 1)

class SegmentTree {
private:
    int n;
    int *tree, *lazyMark;
public:
    int *data;
    SegmentTree(int n): n(n) {
        tree = new int[3*n]();
        lazyMark = new int[3*n]();
        data = new int[n+5]();
    }
    ~SegmentTree() {
        delete [] tree;
        delete [] lazyMark;
        delete [] data;
    }

    void buildTree(uint32 l, uint32 r, uint32 p) {
        if(l == r) {
            tree[p] = data[l];
            return;
        }

        uint32 m = (l + r) >> 1;
        buildTree(l, m, lc(p)), buildTree(m+1, r, rc(p));
        tree[p] = tree[lc(p)] + tree[rc(p)];
        return;
    }

    void pushdown(uint32 s, uint32 t, uint32 p) {
        uint32 m = (s + t) >> 1;
        tree[lc(p)] += lazyMark[p] * (m-s+1);
        tree[rc(p)] += lazyMark[p] * (t-m);
        lazyMark[lc(p)] += lazyMark[p], lazyMark[rc(p)] += lazyMark[p];
        lazyMark[p] = 0;
        return;
    }

    void update(uint32 l, uint32 r, uint32 s, uint32 t, uint32 c, uint32 p) {
        if(l <= s && r >= t) {
            tree[p] += (t-s+1)*c;
            lazyMark[p] += c;
            return;
        }

        uint32 m = (s + t) >> 1;
        if(lazyMark[p]) {
            pushdown(s, t, p);
        }
        if(l <= m) update(l, r, s, m, c, lc(p));
        if(r > m) update(l, r, m+1, t, c, rc(p));
        tree[p] = tree[lc(p)] + tree[rc(p)];
        return;
    }

    int getSum(uint32 l, uint32 r, uint32 s, uint32 t, uint32 p) {
        if(l <= s && r >= t) return tree[p];
        uint32 m = (s + t) >> 1;
        // cout << m << endl;
        if(lazyMark[p]) {
            pushdown(s, t, p);
        }
        int sum = 0;
        
        if(l <= m) sum = getSum(l ,r, s, m, lc(p));
        if(r > m) sum += getSum(l, r, m+1, t, rc(p));
        return sum;
    }
};
#endif // ! __SEGMENT_TREE_HPP__