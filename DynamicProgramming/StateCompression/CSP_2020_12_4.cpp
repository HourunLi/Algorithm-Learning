/**
 * @file CSP_2020_12_4.cpp
 * @author HorunLi
 * @brief tree dp. reference material:https://blog.csdn.net/weixin_44627639/article/details/115052571?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-115052571-blog-114414840.pc_relevant_antiscanv2&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-115052571-blog-114414840.pc_relevant_antiscanv2&utm_relevant_index=2
 * 
 * @version 0.1
 * @date 2022-06-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<bits/stdc++.h>
using namespace std;

#define N 105
#define M 12 
#define K 12

struct DirectedEdge {
    int next, from, to, w;
};

// for graph
int tot,head[N];
DirectedEdge edges[2*N];

int n, m, k;
int need[N][K], parent[N], dp[N];
int one[N][K], f[M][(1<<K)];

int dfs(int k, int from) {
    int ret = 0;
    for(int e = head[from]; e; e = edges[e].next) {
        int to = edges[e].to, w = edges[e].w;
        if(parent[from] == to) continue;
        parent[to] = from;
        int t = dfs(k, to);
        if(dp[to] || need[to][k]) {
            dp[from] += dp[to] + (w << 1);
            ret = max(t + w, ret);
        }
    }
    return ret;
}

void add(int u, int v, int weight = 0) {
    edges[++tot].next = head[u];
    edges[tot].from = u;
    edges[tot].to = v;
    edges[tot].w = weight;
    head[u] = tot; 
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> m >> k;
    for(int i = 1; i<= n; i++) 
        for(int j = 1; j <= k; j++) {
            cin >> need[i][j];
        }

    int u, v, w;
    for(int i = 1; i <= n-1; i++) {
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }

    for(int i = 1; i <= k; i++) {
        for(int j = 1; j <= n; j++) {
            memset(dp, 0, sizeof(dp));
            memset(parent, 0, sizeof(parent));
            int t = dfs(i, j);
            one[j][i] = dp[j] - t;
        }
    }

    for(int i = 1; i < (1 << k); i++) {
        int t1 = INT_MAX;
        for(int j = 1; j <= n; j++) {
            int t2 = 0;
            for(int l = 0; l < k; l++) {
                if(i & (1 << l)) {
                    t2 = max(one[j][l+1], t2);
                }
            }
            t1 = min(t1, t2);
        }
        f[1][i] = t1;
    }

    for(int i = 2; i <= m; i++) {
        for(int j = 0; j < (1<<k); j++) {
            int t = INT_MAX;
            for(int l = j; l; l = (l-1)&j) {
                t = min(max(f[1][l], f[i-1][j ^l]), t);
            }
            f[i][j] = t;
        }
    }
    cout << f[m][(1<<k)-1];
    return 0;
}