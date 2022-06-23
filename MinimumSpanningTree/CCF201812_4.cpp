#include "MST.hpp"
int main() {
    freopen("input.txt", "r", stdin);
    int n, m, s;
    cin >> n >> m >> s;
    UndirectedGraph graph;
    Kruskal solver = Kruskal(&graph);
    int u, v, t;
    for(int i =1; i<= m; i++) {
        scanf("%d %d %d", &u, &v, &t);
        solver.add(u, v, t);
    }
    Pair ans = solver.solve();
    cout << ans.second << endl;
    return 0;
}