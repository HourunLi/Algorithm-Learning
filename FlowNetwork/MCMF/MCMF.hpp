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
#ifndef __MCMF_HPP__
#define __MCMF_HPP__
#include "../../basic.hpp"
#include "../../graph.hpp"

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

    ll dfs(int *dist, int *cur, int now, int flow) {
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
        int *cur = new int[n+5]();
        bool *inq = new bool[n+5]();
        while(spfa(inq, deep)) {
            memcpy(cur, head, (n+5)*sizeof(uint32));
            ll f = dfs(deep, cur, s, INT_MAX);
            maxFlow += f;
            minCost += f * deep[t];
        }
        delete []deep;
        delete []cur;
        delete []inq;
        return make_pair(maxFlow, minCost);
    }

    bool dijkstra(int *dist, bool *vis, int *deep, MCMFNode *p) {
        memset(dist, 0x7F, sizeof(int) * (n+5));
        memset(vis, 0, sizeof(bool) * (n+5));
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
#endif // !__MCMF_HPP__

// #include <algorithm>
// #include <cstdio>
// #include <cstring>
// #include <queue>
// #define INF 0x3f3f3f3f
// using namespace std;

// struct edge {
//   int v, f, c, next;
// } e[100005];

// struct node {
//   int v, e;
// } p[10005];

// struct mypair {
//   int dis, id;

//   bool operator<(const mypair& a) const { return dis > a.dis; }

//   mypair(int d, int x) { dis = d, id = x; }
// };

// int head[5005], dis[5005], vis[5005], h[5005];
// int n, m, s, t, cnt = 1, maxf, minc;

// void addedge(int u, int v, int f, int c) {
//   e[++cnt].v = v;
//   e[cnt].f = f;
//   e[cnt].c = c;
//   e[cnt].next = head[u];
//   head[u] = cnt;
// }

// bool dijkstra() {
//   priority_queue<mypair> q;
//   for (int i = 1; i <= n; i++) dis[i] = INF;
//   memset(vis, 0, sizeof(vis));
//   dis[s] = 0;
//   q.push(mypair(0, s));
//   while (!q.empty()) {
//     int u = q.top().id;
//     q.pop();
//     if (vis[u]) continue;
//     vis[u] = 1;
//     for (int i = head[u]; i; i = e[i].next) {
//       int v = e[i].v, nc = e[i].c + h[u] - h[v];
//       if (e[i].f && dis[v] > dis[u] + nc) {
//         dis[v] = dis[u] + nc;
//         p[v].v = u;
//         p[v].e = i;
//         if (!vis[v]) q.push(mypair(dis[v], v));
//       }
//     }
//   }
//   return dis[t] != INF;
// }

// void spfa() {
//   queue<int> q;
//   memset(h, 63, sizeof(h));
//   h[s] = 0, vis[s] = 1;
//   q.push(s);
//   while (!q.empty()) {
//     int u = q.front();
//     q.pop();
//     vis[u] = 0;
//     for (int i = head[u]; i; i = e[i].next) {
//       int v = e[i].v;
//       if (e[i].f && h[v] > h[u] + e[i].c) {
//         h[v] = h[u] + e[i].c;
//         if (!vis[v]) {
//           vis[v] = 1;
//           q.push(v);
//         }
//       }
//     }
//   }
// }

// int main() {
//   freopen("input.txt", "r", stdin);
//   scanf("%d%d%d%d", &n, &m, &s, &t);
//   for (int i = 1; i <= m; i++) {
//     int u, v, f, c;
//     scanf("%d%d%d%d", &u, &v, &f, &c);
//     addedge(u, v, f, c);
//     addedge(v, u, 0, -c);
//   }
//   spfa();  // 先求出初始势能
//   while (dijkstra()) {
//     int minf = INF;
//     for (int i = 1; i <= n; i++) h[i] += dis[i];
//     for (int i = t; i != s; i = p[i].v) minf = min(minf, e[p[i].e].f);
//     for (int i = t; i != s; i = p[i].v) {
//       e[p[i].e].f -= minf;
//       e[p[i].e ^ 1].f += minf;
//     }
//     maxf += minf;
//     minc += minf * h[t];
//   }
//   printf("%d %d\n", maxf, minc);
//   return 0;
// }
