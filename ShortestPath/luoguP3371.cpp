/**
 * @file luoguP3371.cpp
 * @author HourunLi
 * @brief p3371 problem from luogu. Source: https://www.luogu.com.cn/problem/P3371
 * @version 0.1
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Dijkstra.hpp"
#include "SPFA.hpp"
int main() {
    freopen("input.txt", "r", stdin);
    int n, m, s;
    cin >> n >> m >> s;
    SPFA solver = SPFA(n, m);
    int u, v, w;
    
    for(int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        solver.add(u, v, w);
    }
    solver.spfa(s);
    
    for(int i = 1; i <= n; i++) {
        cout << solver.getAnswer(i) << " ";
    }
    return 0;
}