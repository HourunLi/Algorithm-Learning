/**
 * @file luoguP3372.cpp
 * @author HourunLi
 * @brief Basic segement tree template(P3372 problem from luogu). source: https://www.luogu.com.cn/problem/P3372
 * @version 0.1
 * @date 2022-06-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<bits/stdc++.h>
using namespace std;

int n, m;
typedef long long int ll;
ll d[300000], b[300000], a[100005];

void buildTree(ll l, ll r, ll p) {
    if(l == r) {
        d[p] = a[l];
        return;
    }

    ll m = (l + r) >> 1;
    buildTree(l, m, 2*p), buildTree(m+1, r, 2*p+1);
    d[p] = d[2*p] + d[2*p+1];
    return;
}

void pushdown(ll s, ll t, ll p) {
    ll m = (s + t) >> 1;
    d[2*p] += b[p] * (m-s+1);
    d[2*p+1] += b[p] * (t-m);
    b[2*p] += b[p], b[2*p+1] += b[p];
    b[p] = 0;
    return;
}

void update(ll l, ll r, ll s, ll t, ll c, ll p) {
    if(l <= s && r >= t) {
        d[p] += (t-s+1)*c;
        b[p] += c;
        return;
    }

    ll m = (s + t) >> 1;
    if(b[p]) {
        pushdown(s, t, p);
    }
    if(l <= m) update(l, r, s, m, c, 2*p);
    if(r > m) update(l, r, m+1, t, c, 2*p+1);
    d[p] = d[2*p] + d[2*p+1];
    return;
}

ll getSum(ll l, ll r, ll s, ll t, ll p) {
    if(l <= s && r >= t) return d[p];
    ll m = (s + t) >> 1;
    // cout << m << endl;
    if(b[p]) {
        pushdown(s, t, p);
    }
    ll sum = 0;
    
    if(l <= m) sum = getSum(l ,r, s, m, 2*p);
    if(r > m) sum += getSum(l, r, m+1, t, 2*p+1);
    return sum;
}
int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    buildTree(1, n, 1);
    int opcode, x, y, k;
    for(int i = 0; i < m; i++) {
        cin >> opcode;
        if (opcode == 1) {
            cin >> x >> y >> k;
            update(x, y, 1, n, k, 1); 
        } else if (opcode == 2) {
            cin >> x >> y;
            cout << getSum(x, y, 1, n, 1) << endl;   
        }
    }
    return 0;
}
