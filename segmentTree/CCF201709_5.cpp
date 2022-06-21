/**
 * @file CCF201709_5.cpp
 * @author HourunLi
 * @brief 5th problem of CCF 2017 9 exam. source: http://118.190.20.162/view.page?gpid=T59
 * @version 0.1
 * @date 2022-06-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<bits/stdc++.h>
using namespace std;
#define lc(i) (i << 1)
#define rc(i) ((i << 1) | 1)
int n, m;
typedef long long ll;
ll d[300000];
int a[100005];

void buildTree(int l, int r, int p) {
    if(l == r) {
        d[p] = a[l];
        return;
    }

    int m = (l + r) >> 1;
    int lc = lc(p), rc = rc(p);
    buildTree(l, m, lc);
    buildTree(m+1, r, rc);
    d[p] = d[lc] + d[rc];
    return;
}

void update(int id, int s, int t, int p) {
    if(s == t) {
        d[p] = a[id];
        return;
    }

    int m = (s + t) >> 1;
    int lc = lc(p), rc = rc(p);
    if(id <= m) update(id, s, m, lc);
    if(id > m) update(id, m+1, t, rc);
    d[p] = d[lc] + d[rc];
    return;
}

ll getSum(int l, int r, int s, int t, int p) {
    if(l <= s && r >= t) return d[p];
    int m = (s + t) >> 1;
    
    ll sum = 0;
    int lc = lc(p), rc = rc(p);
    if(l <= m) sum += getSum(l ,r, s, m, lc);
    if(r > m) sum += getSum(l, r, m+1, t, rc);
    return sum;
}

int main() {
    scanf("%d%d", &n, &m);
    // cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        // cin >> a[i];
        scanf("%d", &a[i]);
    }
    buildTree(1, n, 1);
    for(int i = 0; i < m; i++) {
        int opcode, x, y;
        scanf("%d%d%d", &opcode, &x, &y);
        if (opcode == 1) {
            int k;
            scanf("%d", &k);
            if(k == 1) continue;
            for(int j = x; j <= y; j++) {
                if(a[j] >= k && a[j] % k == 0) {
                    a[j] /= k;
                    update(j, 1, n, 1);
                }
            }
        } else {
            cout << getSum(x, y, 1, n, 1) << "\n";   
        }
    }
    return 0;
}

