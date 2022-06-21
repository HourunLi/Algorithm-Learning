/**
 * @file template.hpp
 * @author HourunLi
 * @brief Union Find template
 * @version 0.1
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __UNION_FIND___
#define __UNION_FIND___

#include "../basic.hpp"
class UnionFind {
private: 
    int n;
    uint32 *parent;
public:
    UnionFind() {

    }

    UnionFind(int n): n(n) {
        parent = new uint32[n+5];
        for(int i = 0; i < n+5; i++) {
            parent[i] = i;
        }
    }
    ~UnionFind() {
        delete[] parent;
    }

    inline void merge(const int x, const int y) {
        parent[find(x)] = find(y);
    }

    uint32 find(const int x) {
        if(parent[x] == x) return x;
        parent[x] = find(parent[x]);
        return parent[x];
    }
};
#endif