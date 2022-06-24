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
#ifndef __SHORTEST_PATH__HPP
#define __SHORTEST_PATH__HPP
// #include "E:\CodeLearning\codeLearning\basic.hpp"
// #include "E:\CodeLearning\codeLearning\graph.hpp"
#include "../basic.hpp"
#include "../graph.hpp"

class Dijkstra{
private:
    uint32 *dist;
    bool *vis;
    DirectedGraph *graph;
public:
    Dijkstra(DirectedGraph *graph_) {
        graph = graph_;
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        dist = new uint32[n+5]();
        memset(dist, INF, (n+5) * sizeof(uint32));
        vis = new bool[n+5]();
    }

    ~Dijkstra() {
        delete[] dist;
        delete[] vis;
    }
    // add edge
    void add(int u, int v, int w = 0) {
        graph->add(u, v, w);
    }

    void dijkstra(int source) {
        priority_queue<Pair, vector<Pair>, greater<Pair> > q;
        dist[source] = 0;
        q.push(make_pair(0, source));
        while(!q.empty()) {
            int s = q.top().second;
            q.pop();
            if(vis[s]) continue;
            vis[s] = true;
            for(int e = graph->begin(s); e != graph->end(); e = graph->next(e)) {
                int t = graph->edge(e).to;
                if(vis[t]) continue;
                if(dist[s] + graph->edge(e).w < dist[t]){
                    dist[t] = dist[s] + graph->edge(e).w;
                    q.push(make_pair(dist[t], t));
                }
            }
        }
    }

    uint32 getAnswer(int t) {
        // return dist[t] == -1? INF : dist[t];
        return dist[t];
    }
};

class SPFA {
private:
    uint32 *dist;
    bool *inqueue;
    DirectedGraph *graph;
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
        queue<int> q;
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
    uint32 getAnswer(int t) {
        // return dist[t] == -1? INF : dist[t];
        return dist[t];
    }
};

#endif // ! __SHORTEST_PATH__HPP