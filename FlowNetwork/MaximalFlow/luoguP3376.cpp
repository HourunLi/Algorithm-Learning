/**
 * @file luoguP3376.cpp
 * @author HourunLi
 * @brief Maximal Flow example. Source: https://www.luogu.com.cn/problem/P3376
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "MaximalFlow.hpp"
int main() {
    freopen("input.txt", "r", stdin);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    MaximalFlow solver(n, m, s, t);
    int u, v, w;
    for(int i = 1; i <= m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        solver.add(u, v, w);
    }
    cout << solver.Dinic() << endl;
    return 0;
}