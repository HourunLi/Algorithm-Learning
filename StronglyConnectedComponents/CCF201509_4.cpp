#include "scc.hpp"
int main() {
    // freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n>> m;
    DirectedGraph graph(n, m);
    int u, v;
    for(int i = 1 ;i <= m; i++) {
        scanf("%d %d",&u,&v);
        graph.add(u, v);
    }
    SCC solver = SCC(&graph);
    auto ret = solver.kosaraju();
    uint64 ans = 0;
    for(int i = 0; i < ret.size(); i++) {
        uint64 size = ret[i].size();
        ans += size * (size-1) / 2;
    }
    cout << ans << endl;
    return 0;
}