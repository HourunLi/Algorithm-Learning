/**
 * @file luoguP1048.cpp
 * @author HourunLi
 * @brief Mnemonic Search example. Source: https://www.luogu.com.cn/problem/P1048
 * @version 0.1
 * @date 2022-06-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<bits/stdc++.h>
using namespace std;
int t[105], m[105];
int main() {
    // freopen("input.txt", "r", stdin);
    int T, M;

    cin >> T >> M;
    for(int i = 1; i <= M; i++) {
        cin >> t[i] >> m[i];
    }
    int a[1005][105];
    memset(a, 0, sizeof(a));
    for(int i = 1; i <=T; i++) {
        for(int j = 1; j <= M; j++) {
            a[i][j] = a[i][j-1];
            if(i < t[j]) continue;
            a[i][j] = max(a[i][j], a[i-t[j]][j-1] + m[j]);
        }
    }
    cout << a[T][M];
    return 0;
}