/**
 * @file luoguP2057.cpp
 * @author HourunLi
 * @brief MinimalCut application: Either or problem. Source: https://www.luogu.com.cn/problem/P2057
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

    void add(int u, int v, int w = 0) {
        if(++tot >= m) {
            edges = (DirectedEdge*)realloc(edges, sizeof(DirectedEdge) * (2*m));
            m *= 2;
        }
        edges[tot].next = head[u];
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

#define getREdge(i) ( ( (i-1) ^ 1) + 1 )
class MinimalCut : DirectedGraph {
private:
    int s, t;
public:
    MinimalCut(int n, int m, int s, int t) : DirectedGraph(n, 2*m), s(s), t(t){
    }

    // add edge
    void add(int u, int v, int cap = 0) {
        DirectedGraph::add(u, v, cap);
        DirectedGraph::add(v, u, 0);
    }

    void add_r(int u, int v, int cap) {
        DirectedGraph::add(u, v, cap);
        DirectedGraph::add(v, u, cap);
    }
    
    /**
     * @brief bfs function for Edmond Karp algorithm
     * 
     * @param last 
     * @param flow 
     * @return true 
     * @return false 
     */
    bool bfs(int *last, int* flow) {
        memset(last, -1, sizeof(int) * (n+5));
        queue<int> q;
        q.push(s);
        flow[s] = INT_MAX;
        while(!q.empty()) {
            int from = q.front();
            q.pop();
            if(from == t) break;
            for(int e = head[from]; e != 0; e = edges[e].next) {
                int to = edges[e].to, vol = edges[e].w;
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
        int *last = new int[n+5]();
        int *flow = new int[n+5]();
        while(bfs(last, flow)) {
            maxFlow += flow[t];
            for(int i = t; i !=s; i = edges[getREdge(last[i])].to) {
                edges[last[i]].w -= flow[t];
                edges[getREdge(last[i])].w += flow[t];
            }
        }
        delete []last;
        delete []flow;
        return maxFlow;
    }

    /**
     * @brief bfs function for dinic algorithm
     * 
     * @param deep 
     * @return true 
     * @return false 
     */
    bool bfs(int *deep) {
        memset(deep, -1, sizeof(int)*(n+5));
        queue<int> q;
        deep[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int from = q.front();
            q.pop();
            for(int e = head[from]; e; e = edges[e].next) {
                if(deep[edges[e].to] == -1 && edges[e].w) {
                    deep[edges[e].to] = deep[from] + 1;
                    q.push(edges[e].to);
                }
            }
        }
        return deep[t] != -1;
    }

    /**
     * @brief 
     * 
     * @param now the current node
     * @param flow the min flow of path from s to current node
     * @return int the sum of all feasible path in residual networks
     */
    uint64 dfs(int *cur, int *deep, int now, int flow) {
        if(!flow || now == t) return flow;
        uint64 ret = 0, f;
        for(int e = cur[now]; e; e = edges[e].next) {
            cur[now] = e;
            if(deep[edges[e].to] == deep[now] + 1 && (f = dfs(cur, deep, edges[e].to, min(flow, edges[e].w)))) {
                ret += f;
                flow -= f;
                edges[e].w -= f;
                edges[getREdge(e)].w += f;
                if(!flow) break;
            }
        }
        return ret;
    }
    
    uint64 Dinic() {
        uint64 maxFlow = 0;
        int *deep = new int[n+5];
        int *cur = new int[n+5]();
        while(bfs(deep)) {
            // cout << "here" << maxFlow << "\n";
            memcpy(cur, head, (n+5)*sizeof(int));
            maxFlow += dfs(cur, deep, s, INT_MAX);
        }
        delete []deep;
        delete []cur;
        return maxFlow;
    }
};
int main() {
    // freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    int s = 1, t = n+2;
    MinimalCut solver(n+2, 2*n+m, s, t);
    int tmp;
    for(int i = 2; i <= n+1; i++) {
        cin >> tmp;
        solver.add(s, i, !tmp);
        solver.add(i, t, tmp);
    }
    int c1, c2;
    for(int i = 0; i < m; i++) {
        cin >> c1 >> c2;
        solver.add(c1+1, c2+1, 1);
        solver.add(c2+1, c1+1, 1);
    }
    cout << solver.Dinic();
}