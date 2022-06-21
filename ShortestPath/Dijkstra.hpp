/**
 * @file template.cpp
 * @author HourunLi
 * @brief Dijkstra template
 * @version 0.1
 * @date 2022-06-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __DIJKSTRA_HPP__
#define __DIJKSTRA_HPP__
// #include "E:\CodeLearning\codeLearning\basic.hpp"
// #include "E:\CodeLearning\codeLearning\graph.hpp"
#include "../basic.hpp"
#include "../graph.hpp"
#define INF (1<<31 - 1)

class Dijkstra{
private:
    int n, m; // n is the number of nodes, m is the number of edges
    uint64 *dist;
    bool *vis;
    // for build edges
    uint32 *head, tot;
    DirectedEdge *edges;
    priority_queue<Pair, vector<Pair>, greater<Pair> > q;
public:
    Dijkstra(int n_, int m_): n(n_), m(m_){
        dist = new uint64[n+5]();
        // memset(dist, -1, (n+5) * sizeof(uint32));
        for(int i = 0; i < n+5; i++) {
            dist[i] = INF;
        }
        vis = new bool[n+5]();
        edges = new DirectedEdge[m+5]();
        head = new uint32[n+5]();
        tot = 0;
    }

    ~Dijkstra() {
        delete[] dist;
        delete[] vis;
        delete[] edges;
        delete[] head;
    }
    // add edge
    void add(int u, int v, int w) {
        edges[++tot].next = head[u];
        edges[tot].to = v;
        edges[tot].w = w;
        head[u] = tot; 
    }

    void dijkstra(int s) {
        dist[s] = 0;
        q.push(make_pair(0, s));
        while(!q.empty()) {
            int s = q.top().second;
            q.pop();
            if(vis[s]) continue;
            vis[s] = true;
            for(int e = head[s]; e != 0; e = edges[e].next) {
                int t = edges[e].to;
                dist[t] = min(dist[t], dist[s] + edges[e].w);
                if(!vis[t]) {
                    q.push(make_pair(dist[t], t));
                }
            }
        }
    }

    uint64 getAnswer(int t) {
        // return dist[t] == -1? INF : dist[t];
        return dist[t];
    }
};
#endif // ! __DIJKSTRA_HPP__