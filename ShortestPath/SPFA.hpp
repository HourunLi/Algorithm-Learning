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
#include "../basic.hpp"
#include "../graph.hpp"
#define INF 0x3f3f3f3f

class SPFA {
private:
    uint32 *dist;
    bool *inqueue;
    DirectedGraph *graph;
    queue<int> q;
public:
    SPFA(DirectedGraph *graph_) {
        graph = graph_;
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        dist = new uint32[n+5]();
        memset(dist, INF, (n+5) * sizeof(uint32));
        inqueue = new bool[n+5]();
    }
    ~SPFA() {
        delete[] dist;
        delete[] inqueue;
    }

    // add edge
    void add(int u, int v, int w = 0) {
        graph->add(u, v, w);
    }

    void spfa(int source) {
        dist[source] = 0;
        q.push(source);
        inqueue[source] = true;
        while(!q.empty()) {
            int s = q.front();
            q.pop();
            inqueue[s] = false;
            for(int e = graph->begin(s); e != graph->end(); e = graph->next(e)) {
                int t = graph->edge(e).to;
                if(dist[t] > dist[s] + graph->edge(e).w) {
                    dist[t] = dist[s] + graph->edge(e).w;
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

