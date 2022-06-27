#include "MCMF.hpp"
int main() {
    freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m; 
    int s = 1, t = 7*n+2;
    MCMF solver(t, 7*n + 3*m, s, t);
    int a[7], b[7], u, v, w;
    for(int k = 1; k <= n; k++) {
        for(int i = 0; i < 7; i++) {
            scanf("%d", &a[i]);
            if(a[i]) {
                solver.add(s, i*n+k+1, a[i], 0);
            }
        }
        for(int i = 0; i < 7; i++) {
            scanf("%d", &b[i]);
            if(b[i]) {
                solver.add(i*n+k+1, t, b[i], 0);
            }
        }
        cin >> v >> w;
        for(int i = 0; i < 7; i++) {
            int next = (i+1)%7;
            solver.add(i*n+k+1, next*n+k+1, v, w);
        }
    }
    for(int k = 0; k < m; k++) {
        scanf("%d %d %d", &u, &v, &w);
        for(int i = 0; i < 7; i++) {
            solver.add(i*n+u+1, i*n+v+1, INF, w);
            solver.add(i*n+v+1, i*n+u+1, INF, w);
        }
    }
    cout << solver.PrimalDual().second << endl;
    return 0;
}