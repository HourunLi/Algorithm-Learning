#include "MST.hpp"
int main() {
    freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    UndirectedGraph graph(n, m);
    Kruskal solver(&graph);
    int u, v, w;
    for(int i = 1; i <= m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        solver.add(u, v, w);
    }
    Pair ans = solver.solve();
    cout << ans.first << endl;
    return 0;
}