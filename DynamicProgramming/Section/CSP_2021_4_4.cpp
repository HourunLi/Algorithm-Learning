/**
 * @file CSP_2021_4_4.cpp
 * @author HourunLi
 * @brief  Section DP. reference: https://www.cnblogs.com/lipoicyclic/p/15020078.html
 * @version 0.1
 * @date 2022-06-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mod 1000000007
int a[1005], dp[1005];
vector<int> fac[100005];
set<int> s;
int n;
ll cal(int l, int r) {
    int dis = a[r]-a[l];
    ll ret = 0;
    s.insert(dis);
    for(auto factor : fac[dis]) {
        if(s.find(factor) != s.end()) continue;
        s.insert(factor);
        ret++;
    }
    // cout << ret << endl;
    return ret;
}
int main() {
    // freopen("input.txt", "r", stdin);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int factor = 1; factor <= a[n]/2; factor++) {
        for(int num = 2*factor; num <= a[n]; num += factor) {
            fac[num].push_back(factor);
        }
    }

    dp[1] = 1;
    for(int i = 1; i <= n; i++) {
        s.clear();
        for(int j = i - 1; j >= 1; j--) {
            dp[i] = (dp[i] + dp[j] *cal(j, i) % mod)%mod;
        }
    }
    cout << dp[n];
    return 0;
}