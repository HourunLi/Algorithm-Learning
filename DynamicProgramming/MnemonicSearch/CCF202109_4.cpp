#include <bits/stdc++.h>
using namespace std;

#define N (1<<16)
#define M 81

double a[N][M];
bool vis[N][M];
double p[17];
int n, k;

double dp(int state, int coin, int need) {
    if(coin >= need*k) return 0;
    if(vis[state][coin]) return a[state][coin];
    vis[state][coin] = true;
    double ret = 0;
    for(int i = 0; i < n; i++) {
        bool has = (state >> i) & 1;
        if(has) {
            ret += p[i] * (1 + dp(state, coin+1, need));
        } else {
            ret += p[i] * (1 + dp(state | (1 << i), coin, need -1));
        }
    }
    a[state][coin] = ret;
    return ret;
}

int main() {
    // freopen("input.txt", "r", stdin);
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> p[i];
    }
    printf("%.10llf", dp(0, 0, n));
    return 0;
}