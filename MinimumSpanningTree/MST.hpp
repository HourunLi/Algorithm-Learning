/**
 * @file template.hpp
 * @author HourunLi
 * @brief MST template
 * @version 0.1
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __MINIMUM_SPANNING_TREE__
#define __MINIMUM_SPANNING_TREE__
#include "../basic.hpp"
#include "../graph.hpp"
#include "../UnionFind/UnionFind.hpp"
class Kruskal {
private:
    UndirectedGraph *graph;
    UnionFind *unionFind;
public:
    Kruskal(int n, int m) {
        graph = new UndirectedGraph(n, m);
        unionFind = new UnionFind(n);
    }

    ~Kruskal() {
        delete graph;
        delete unionFind;
    }

    void add(int u, int v, int w) {
        graph->add(u, v, w);
        return;
    }

    // bool cmp(const int a, const int b) {
    //     return graph->edge(a).w < graph->edge(b).w;
    // }

    // return <min weight of MST, max edge weight>
    Pair solve() {
        int cnt = 0, ans = 0;
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        graph->edgesSort();
        for(int i = 1; i <= m; i++) {
            int u = graph->edge(i).u;
            int v = graph->edge(i).v;
            int w = graph->edge(i).w;
            if(unionFind->find(u) != unionFind->find(v)) {
                unionFind->merge(u, v);
                ans += w;
                cnt++;
            }
            if(cnt == n-1) {
                return make_pair(ans, w);
            }
        }
        return make_pair(-1, -1);
    }
};
#endif // !__MINIMUM_SPANNING_TREE__
