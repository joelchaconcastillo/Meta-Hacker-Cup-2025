#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> routev;
vector<vector<pair<int,int>>> occ;
vector<vector<int>> parentv;
vector<int> L;


int findp(int r, int x) {
    if (x > L[r]) return x;
    if (parentv[r][x] == x) return x;
    return parentv[r][x] = findp(r, parentv[r][x]);
}


void union_next(int r, int x) {
    int px = findp(r, x);
    if (px <= L[r]) {
        parentv[r][px] = findp(r, px + 1);
    }
}

void solve(){
    int N, K, M;
    cin >> N >> K >> M;

    routev.assign(M, {});
    L.assign(M, 0);
    occ.assign(N+1, {});
    parentv.assign(M, {});

    for (int i = 0; i < M; i++) {
        int Li;
        cin >> Li;
        L[i] = Li;
        routev[i].assign(Li+1, 0);
        for (int j = 1; j <= Li; j++) {
            int a;
            cin >> a;
            routev[i][j] = a;
            occ[a].push_back({i, j});
        }
    }

    for (int i = 0; i < M; i++) {
        parentv[i].resize(L[i] + 2);
        for (int j = 0; j <= L[i] + 1; j++) parentv[i][j] = j;
    }

    vector<int> dist(N+1, -1);
    deque<int> dq;
    dist[1] = 0;
    dq.push_back(1);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        int du = dist[u];
        for (auto &rp : occ[u]) {
            int r = rp.first;
            int pos = rp.second;
            int start = pos + 1;
            if (start > L[r]) continue;
            int end = pos + K;
            if (end > L[r]) end = L[r];
            int idx = findp(r, start);
            while (idx <= end) {
                int v = routev[r][idx];
                if (dist[v] == -1) {
                    dist[v] = du + 1;
                    dq.push_back(v);
                }
		union_next(r, idx);
                idx = findp(r, idx + 1);
            }
        }
        occ[u].clear();
    }

    long long ans = 0;
    for (int i = 1; i <= N; i++) {
        int d = dist[i];
        if (d == -1) d = -1;
        ans += (long long)i * d;
    }

    cout << ans;
}

int main(){
    int t;
    cin >> t;
    int i = 1;
    while(t--){
        cout << "Case #" << i << ": ";
        solve();
        cout << "\n";
        i++;
    }
    return 0;
}

