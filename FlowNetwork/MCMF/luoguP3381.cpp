/**
 * @file MCMF.hpp
 * @author HourunLi
 * @brief MCMF template
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
    int next, from, to, w, cost;
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

    ~DirectedGraph() {
        delete []edges;
        delete []head;
    }
    void add(int u, int v, int weight = 0, int cost = 0) {
        if(++tot >= m) {
            edges = (DirectedEdge*)realloc(edges, sizeof(DirectedEdge) * (2*m));
            m *= 2;
        }
        edges[tot].next = head[u];
        edges[tot].from = u;
        edges[tot].to = v;
        edges[tot].w = weight;
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
    ~UndirectedGraph() {
        delete []edges;
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

#define getREdge(i) ( ( (i-1) ^ 1) + 1 )

struct MCMFNode {
    int pre, e;
};

class MCMF : DirectedGraph {
private:
    int s, t;
public:
    MCMF(int n, int m, int s, int t) : DirectedGraph(n, 2*m), s(s), t(t) {

    }

    // add edge
    void add(int u, int v, int cap, int cost) {
        DirectedGraph::add(u, v, cap, cost);
        DirectedGraph::add(v, u, 0, -cost);
    }

    bool spfa(bool* inq, int *deep) {
        queue<int> q;
        memset(deep, 0x7F, sizeof(int) * (n+5));
        deep[s] = 0;
        q.push(s);
        inq[s] = true;
        while(!q.empty()) {
            int from = q.front();
            q.pop();
            inq[from] = false;
            for(int e = head[from]; e; e = edges[e].next) {
                int to = edges[e].to, vol = edges[e].w;
                if(vol && deep[to] > deep[from] + edges[e].cost) {
                    deep[to] = deep[from] + edges[e].cost;
                    if(!inq[to]) {
                        q.push(to);
                        inq[to] = true;
                    }
                }
            }
        }
        return deep[t] != 0x7F7F7F7F;
    }

    ll dfs(int *dist, uint32 *cur, int now, int flow) {
        if(!flow || now == t) return flow;
        uint64 ret = 0, f;
        for(int e = cur[now]; e; e = edges[e].next) {
            cur[now] = e;
            if(dist[edges[e].to] == dist[now] + edges[e].cost && (f = dfs(dist, cur, edges[e].to, min(flow, edges[e].w)))) {
                ret += f;
                flow -= f;
                edges[e].w -= f;
                edges[getREdge(e)].w += f;
                if(!flow) break;
            }
        }
        return ret;
    }

    pair<ll, ll> SSP() {
        ll minCost = 0, maxFlow = 0;
        int *deep = new int[n+5];
        uint32 *cur = new uint32[n+5]();
        bool *inq = new bool[n+5]();
        while(spfa(inq, deep)) {
            memcpy(cur, head, (n+5)*sizeof(uint32));
            ll f = dfs(deep, cur, s, INT_MAX);
            maxFlow += f;
            minCost += f * deep[t];
        }
        // delete []deep;
        // delete []cur;
        // delete []inq;
        return make_pair(maxFlow, minCost);
    }

    bool dijkstra(int *dist, bool *vis, int *deep, MCMFNode *p) {
        memset(dist, 0x7F, sizeof(int) * (n+5));
        memset(vis, 0, sizeof(int) * (n+5));
        priority_queue<Pair, vector<Pair>, greater<Pair> > q;
        dist[s] = 0;
        q.push(make_pair(0, s));
        while(!q.empty()) {
            auto top = q.top();
            q.pop();
            int d = top.first, from = top.second;
            if(vis[from]) continue;
            vis[from] = 1;
            for(int e = head[from]; e; e = edges[e].next) {
                int to = edges[e].to, c = edges[e].cost + deep[from]- deep[to];
                if(edges[e].w && dist[to] > dist[from] + c) {
                    dist[to] = dist[from] + c;
                    p[to].pre = from;
                    p[to].e = e;
                    if(!vis[to]) {
                        q.push(make_pair(dist[to], to));
                    }
                }
            }
        }
        return dist[t] != 0x7F7F7F7F;
    }

    pair<ll, ll> PrimalDual() {
        ll minCost = 0, maxFlow = 0;
        int *dist = new int[n+5]();
        int *deep = new int[n+5];
        bool *vis = new bool[n+5]();
        MCMFNode *p = new MCMFNode[n+5]();
        spfa(vis, deep);
        while(dijkstra(dist, vis, deep, p)) {
            // cout << "here\n";
            int minf = INF;
            for (int i = 1; i <= n; i++) deep[i] += dist[i];
            for (int i = t; i != s; i = p[i].pre) minf = min(minf, edges[p[i].e].w);
            for (int i = t; i != s; i = p[i].pre) {
                edges[p[i].e].w -= minf;
                edges[getREdge(p[i].e)].w += minf;
            }
            maxFlow += minf;
            minCost += minf * deep[t];
        }
        // cout << "kkk\n";
        // delete []dist;
        // delete []deep;
        // delete []vis;
        // delete []p;
        return make_pair(maxFlow, minCost);
    }
};
// #include "MCMF.hpp"

int main() {
    // freopen("input.txt", "r", stdin);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    MCMF solver(n, m, s, t);
    int u, v, w, c;
    for(int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &u, &v, &w, &c);
        solver.add(u, v, w, c);
    }
    auto ans = solver.PrimalDual();
    // cout <<"getAns\n";
    cout << ans.first << " " << ans.second << endl;
    return 0;
}
