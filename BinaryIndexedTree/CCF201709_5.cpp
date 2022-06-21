#include "BinaryIndexedTree.hpp"

#define lowbit(x) (x&(-x))

int main() {
    int n, m;
    cin >> n >> m;
    ll *a = new ll[n+1]();
    BinaryIndexedTree solver = BinaryIndexedTree(n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        solver.setVal(i, a[i]);
    }
    solver.buildTree();

    for(int i = 0; i < m; i++) {
        int opcode, x, y;
        scanf("%d%d%d", &opcode, &x, &y);
        if (opcode == 1) {
            int k;
            scanf("%d", &k);
            if(k == 1) continue;
            for(int j = x; j <= y; j++) {
                if(a[j] >= k && a[j] % k == 0) {
                    int tmp = a[j]/k;
                    solver.add(j, tmp - a[j]);
                    a[j] = tmp;
                }
            }
        } else {
            cout << solver.getRangeSum(x, y) << endl;   
        }
    }
    delete[] a;
    return 0;
}