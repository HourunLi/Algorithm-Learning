/**
 * @file CCF201812_5.cpp
 * @author HourunLi
 * @brief MCMF and lower bounded flow.
 * @version 0.1
 * @date 2022-06-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "MCMF.hpp"
using namespace std;

int node[205];
int main() {
    // freopen("input.txt", "r", stdin);
    int t,s,e;
    cin >> t >> s >> e;
    int n, m;
    int u, v, w;
    while(t--) {
        cin >> n >> m;
        memset(node, 0, sizeof(node));
        int sum = 0;
        int st = 1, ed = n+2;
        MCMF solver(n+2, 3*m, st, ed);
        for(int k = 0; k < m; k++) {
            scanf("%d %d %c", &u, &v, &w);
            switch(w) {
                case 'A':
                    solver.add(u+1, v+1, INF, e);
                    node[u]++;
                    node[v]--;
                    sum += e;
                    break;
                case 'B':
                    // solver.add(u+1, v+1, 0, e);
                    node[u]++;
                    node[v]--;
                    sum += e;
                    break;
                case 'C':
                    solver.add(u+1, v+1, INF, e);
                    break;
                case 'D':
                    solver.add(u+1, v+1, 1, e);
                    break;
            }
        }
        int flow = 0;
        for(int i = 1; i <= n; i++) {
            if(node[i] > 0) {
                solver.add(i+1, ed, node[i], 0);
                flow += node[i];
            } else if(node[i] < 0) {
                solver.add(st, i+1, -node[i], 0);
            }
        }
        auto ans = solver.PrimalDual();
        if (ans.first != flow) {
            cout << -1 << endl;
        } else {
            cout << ans.second + sum << endl;
        }
    }
    return 0;
}