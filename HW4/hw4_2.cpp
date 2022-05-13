#include <iostream>

using namespace std;
bool** adj;
bool* isOasis;
bool* vis;
bool dfs(int s, int d, int n) {
    if (s == d) return true;
    vis[s] = true;
    for (int i = 0; i < n; i++) {
        if (adj[s][i] && !(!isOasis[s] && !isOasis[i]) && !vis[i]) {
            if (dfs(i, d, n))return true;
        }
    }
    return false;
}
int main() {
    int n, edges;
    cin >> n >> edges;
    isOasis = new bool[n];
    vis = new bool[n];
    for (int i = 0, t; i < n; i++) {
        cin >> t;
        (t == 1) ? isOasis[i] = true : isOasis[i] = false;
        vis[i] = false;
    }
    adj = new bool* [n]; //adjacency matrix
    for (int i = 0; i < n; i++) {
        adj[i] = new bool[n];
        for (int j = 0; j < n; j++) {
            adj[i][j] = false;
        }
    }
    for (int i = 1, a, b; i <= edges; i++) {
        cin >> a >> b;
        adj[a][b] = true;
        adj[b][a] = true;
    }
    int s, d;
    while (cin >> s >> d) {
        if (dfs(s, d, n))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
        for (int i = 0; i < n; i++)vis[i] = false;
    }
    for (int i = 0; i < n; i++)delete adj[i];
    delete adj;
    delete vis;
    delete isOasis;
    return 0;
}