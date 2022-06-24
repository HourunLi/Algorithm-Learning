#ifndef __MINIMAL_CUT_HPP__
#define __MINIMAL_CUT_HPP__
#include "../../basic.hpp"
#include "../../graph.hpp"
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
#endif 
