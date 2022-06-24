/**
 * @file graph.hpp
 * @author HorunLi
 * @brief grpah template
 * @version 0.1
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__
#include "basic.hpp"
struct DirectedEdge {
    int next, from, to, weight, cost;
};

struct UndirectedEdge {
    int u, v, w;
    bool operator < (const UndirectedEdge &other) const {
        return w < other.w;
    }
};

class DirectedGraph {
protected:
    int n, m;
    uint32 *head, tot;
    DirectedEdge *edges;
public:
    DirectedGraph() {

    }
    DirectedGraph(int n_, int m_): n(n_), m(m_){
        edges = new DirectedEdge[m+5]();
        head = new uint32[n+5]();
        tot = 0;
    }

    void add(int u, int v, int weight = 0, int cost = 0) {
        if(++tot >= m) {
            edges = (DirectedEdge*)realloc(edges, sizeof(DirectedEdge) * (2*m));
            m *= 2;
        }
        edges[tot].next = head[u];
        edges[tot].from = u;
        edges[tot].to = v;
        edges[tot].weight = weight;
        edges[tot].cost = cost;
        head[u] = tot; 
    }

    uint32 begin(uint32 u) {
        return head[u];
    }

    uint32 next(uint32 e) {
        return edges[e].next;
    }

    uint32 end() {
        return 0;
    }

    DirectedEdge edge(uint32 e) {
        return edges[e];
    }

    void setW(int e, int w) {
        edges[e].w = w;
        return;
    }
    void modW(int e, int delta) {
        edges[e].w += delta;
        return;
    }
    uint32 getEdgeNum() {
        return tot;
    }

    uint32 getNodeNum() {
        return n;
    }
};

class UndirectedGraph {
protected:
    int n, m;
    uint32 tot;
    UndirectedEdge *edges;
public:
    UndirectedGraph() {
        
    }
    UndirectedGraph(int n_, int m_): n(n_), m(m_){
        edges = new UndirectedEdge[m+5]();
        tot = 0;
    }

    void add(int u, int v, int w = 0) {
        if(++tot >= m) {
            edges = (UndirectedEdge*)realloc(edges, sizeof(UndirectedEdge) * (2*m));
            m *= 2;
        }
        edges[tot].u = u;
        edges[tot].v = v;
        edges[tot].w = w;
    }

    void edgesSort() {
        sort(edges+1, edges+m+1);
    }

    UndirectedEdge edge(uint32 e) {
        return edges[e];
    }

    uint32 getEdgeNum() {
        return tot;
    }

    uint32 getNodeNum() {
        return n;
    }
};

class TopoSort {
private:
    DirectedGraph *graph;
    bool *vis;
    vector<int> topo;

    bool dfs(int p) {
        vis[p] = -1;
        for(int e = graph->begin(p); e != graph->end(); e = graph->next(e)) {
            int v = graph->edge(e).to;
            if(vis[v]) continue;
            if(vis[v] < 0 || !dfs(v)) return false;
        }
        vis[p] = 1;
        topo.push_back(p);
        return true;
    }
public:
    TopoSort(DirectedGraph *graph_) {
        graph = graph_;
        vis = new bool[graph->getNodeNum() + 5]();
    }
    ~TopoSort() {
        delete []vis;
    }

    vector<int> topoSort() {
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        for(int i = 1; i <= n; i++) {
            if(vis[i]) continue;
            if(!dfs(i)) return {};
        }
        reverse(topo.begin(), topo.end());
        return topo;
    }
};
#endif // !__GRAPH_HPP__