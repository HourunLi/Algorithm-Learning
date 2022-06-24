/**
 * @file luoguP3376.cpp
 * @author HourunLi
 * @brief Maximal Flow example. Source: https://www.luogu.com.cn/problem/P3376
 * @version 0.1
 * @date 2022-06-24
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

struct DirectedEdge {
    int next, from, to, w;
};

struct UndirectedEdge {
    int u, v, w;
    bool operator < (const UndirectedEdge &other) const {
        return w < other.w;
    }
};

class DirectedGraph {
private:
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

    void add(int u, int v, int w = 0) {
        edges[++tot].next = head[u];
        edges[tot].from = u;
        edges[tot].to = v;
        edges[tot].w = w;
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
        return m;
    }

    uint32 getNodeNum() {
        return n;
    }
};

class UndirectedGraph {
private:
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
        edges[++tot].u = u;
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
        return m;
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

#define getREdge(i) ( ( (i-1) ^ 1) + 1 )

class MaximalFlow {
private:
    int s, t;
    DirectedGraph *graph;
public:
    MaximalFlow(DirectedGraph *graph_, int s, int t) : s(s), t(t){
        graph = graph_;
    }

    // add edge
    void add(int u, int v, int cap = 0) {
        graph->add(u, v, cap);
        graph->add(v, u, 0);
    }

    bool bfs(int *last, int* flow) {
        int n = graph->getNodeNum();
        memset(last, -1, sizeof(int) * (n+5));
        queue<int> q;
        q.push(s);
        flow[s] = INT_MAX;
        while(!q.empty()) {
            int from = q.front();
            q.pop();
            if(from == t) break;
            for(int e = graph->begin(from); e != graph->end(); e = graph->next(e)) {
                int to = graph->edge(e).to, vol = graph->edge(e).w;
                if(vol > 0 & last[to] == -1) {
                    flow[to] = min(flow[from], vol);
                    last[to] = e;
                    q.push(to);
                }
            }
        }
        return last[t] != -1;
    }
    uint64 EdmondKarp() {
        uint64 maxFlow = 0;
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        int *last = new int[n+5]();
        int *flow = new int[n+5]();
        while(bfs(last, flow)) {
            maxFlow += flow[t];
            for(int i = t; i !=s; i = graph->edge(getREdge(last[i])).to) {
                graph->modW(last[i], -flow[t]);
                graph->modW(getREdge(last[i]), flow[t]);
            }
        }
        delete []last;
        delete []flow;
        return maxFlow;
    }
};

int main() {
    // freopen("input.txt", "r", stdin);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    DirectedGraph graph(n, 2*m);
    MaximalFlow solver(&graph, s, t);
    int u, v, w;
    for(int i = 1; i <= m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        solver.add(u, v, w);
    }
    cout << solver.EdmondKarp() << endl;
    return 0;
}