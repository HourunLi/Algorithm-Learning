/**
 * @file SPFA.hpp
 * @author HourunLi
 * @brief SPFA template
 * @version 0.1
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef  __SPFA_HPP__
#define __SPFA_HPP__
// #include "E:\CodeLearning\codeLearning\basic.hpp"
// #include "E:\CodeLearning\codeLearning\graph.hpp"
#include "../basic.hpp"
#include "../graph.hpp"
#define INF (1<<31 - 1)

class SPFA {
private:
    int n, m; // n is the number of nodes, m is the number of edges
    uint64 *dist;
    bool *inqueue;
    // for build edges
    uint32 *head, tot;
    DirectedEdge *edges;
    queue<int> q;
public:
    SPFA(int n_, int m_): n(n_), m(m_) {
        dist = new uint64[n+5]();
        // memset(dist, -1, (n+5) * sizeof(uint32));
        for(int i = 0; i < n+5; i++) {
            dist[i] = INF;
        }
        inqueue = new bool[n+5]();
        edges = new DirectedEdge[m+5]();
        head = new uint32[n+5]();
        tot = 0;
    }
    ~SPFA() {
        delete[] dist;
        delete[] inqueue;
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

    void spfa(int source) {
        dist[source] = 0;
        q.push(source);
        inqueue[source] = true;
        while(!q.empty()) {
            int s = q.front();
            q.pop();
            inqueue[s] = false;
            for(int e = head[s]; e !=0 ; e = edges[e].next) {
                int t = edges[e].to;
                if(dist[t] > dist[s] + edges[e].w) {
                    dist[t] = dist[s] + edges[e].w;
                    if(!inqueue[t]) {
                        inqueue[t] = true;
                        q.push(t);
                    }
                }
            }
        }
    }
    uint64 getAnswer(int t) {
        // return dist[t] == -1? INF : dist[t];
        return dist[t];
    }
};
#endif // ! __SPFA_HPP__

