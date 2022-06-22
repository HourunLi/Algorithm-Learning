/**
 * @file scc.hpp
 * @author HourunLi
 * @brief strongly connected components solve method template
 * @version 0.1
 * @date 2022-06-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __SCC_HPP__
#define __SCC_HPP__

#include "../basic.hpp"
#include "../graph.hpp"

class SCC {
private:
    int sccCnt;
    DirectedGraph *graph, *rgraph;
    bool *vis;
    vector<int> order;
    vector<vector<int> > ret;
public:
    SCC(DirectedGraph *graph_) {
        graph = graph_;
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        sccCnt = 0;
        vis = new bool[n + 5]();
        
        rgraph = new DirectedGraph(n, m);
        for(int i = 1; i <= m; i++) {
            rgraph->add(graph->edge(i).to, graph->edge(i).from);
        }
    }
    ~SCC() {
        delete []vis;
        delete rgraph;
    }   

    void dfs(int p) {
        vis[p] = true;
        for(int e = graph->begin(p); e != graph->end(); e = graph->next(e)) {
            int v = graph->edge(e).to;
            if(vis[v]) continue;
            dfs(v);
        }
        order.push_back(p);
        return;
    }

    void rdfs(int p) {
        vis[p] = true;
        for(int e = rgraph->begin(p); e != rgraph->end(); e = rgraph->next(e)) {
            int v = rgraph->edge(e).to;
            if(vis[v]) continue;
            rdfs(v);
        }
        ret[sccCnt-1].push_back(p);
        return;
    }

    vector<vector<int> > kosaraju() {
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        TopoSort solver = TopoSort(graph);
        for(int i = 1; i <= n; i++) {
            if(vis[i]) continue;
            dfs(i);
        }
        reverse(order.begin(), order.end());
        memset(vis, 0, n+5);
        for(int i = 0; i < n; i++) {
            if(vis[order[i]]) continue;
            ++sccCnt;
            ret.push_back({});
            rdfs(order[i]);
        }
        return ret;
    }

};

#endif // ! __SCC_HPP__
