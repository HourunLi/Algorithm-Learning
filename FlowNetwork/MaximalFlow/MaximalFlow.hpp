#ifndef __MAXIMAL_FLOW_HPP__
#define __MAXIMAL_FLOW_HPP__
#include "../../basic.hpp"
#include "../../graph.hpp"
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
        flow[s] = INF;
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
    int EdmondKarp() {
        int maxFlow = 0;
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
#endif 
