#include <bits/stdc++.h>
using namespace std;

vector<int> r, p;

int _find(int a){
    return (a!=p[a])? (p[a] = _find(p[a])) : a;
}

bool same(int a, int b){
    return _find(a) == _find(b);
}

void _unite(int a, int b){
    a = _find(a);
    b = _find(b);
    if(a == b) return;
    if(r[a] < r[b]) swap(a,b);
    p[b] = a;
    if(r[a] == r[b]) r[a]++;
}

void solve(){
    int n;
    cin >> n;
    r.assign(n+1, 1);
    p.assign(n+1, 0);
    vector<long long> a(n);
    for(auto &i : a) cin >> i;

    for(int i = 0; i <= n; i++) p[i] = i;

    vector<array<long long,3>> edges;
    edges.reserve(2LL*n);

    for(int i = 0; i < n; i++)
        edges.push_back({a[i], n, i});

    for(int i = 1; i < n; i++)
        edges.push_back({ llabs(a[i] - a[i-1]), i-1, i });

    sort(edges.begin(), edges.end());

    long long res = 0;
    int cont = 0;
    for(auto &e : edges){
        long long w = e[0];
        int u = e[1], v = e[2];
        if(!same(u,v)){
            _unite(u,v);
            res = max(res, w);
            cont++;
            if(cont == n) break;
        }
    }

    cout << res << "\n";
}

int main(){
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++){
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}

