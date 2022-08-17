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
#include"SegmentTree.hpp"
int main() {
    freopen("input.txt","r",stdin);
    int n, m;
    cin >> n >> m;
    SegmentTree solver = SegmentTree(n);

    solver.inputData(n);
    solver.buildTree(1, n, 1);
    int opcode, x, y, k;
    for(int i = 0; i < m; i++) {
        cin >> opcode;
        if (opcode == 1) {
            cin >> x >> y >> k;
            solver.add(x, y, 1, n, k, 1); 
        } else if (opcode == 2) {
            cin >> x >> y;
            cout << solver.getSum(x, y, 1, n, 1) << endl;   
        }
    }
    return 0;
}
