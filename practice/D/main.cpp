/*
 * Author: Joel Chacón Castillo
 * Description: Eulerian traversal + alternate edge coloring solution
 * 
 * This program finds an Eulerian traversal through a possibly disconnected graph.
 * It adds an auxiliary node S to connect components and handle odd-degree vertices,
 * ensuring every vertex has even degree. Then it performs Hierholzer's algorithm 
 * using an edge-indexed approach for O(E) complexity.
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> p, sz;
    DSU(int n): p(n), sz(n,1) { iota(p.begin(), p.end(), 0); }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    void unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b];
    }
};

void solve(){
    int T; 
    if(!(cin>>T)) return;
    for(int tc=1; tc<=T; ++tc){
        int n,m; 
        cin>>n>>m;
        vector<int> A(m),B(m);
        for(int i=0;i<m;i++){ cin>>A[i]>>B[i]; --A[i]; --B[i]; }

        DSU dsu(n);
        vector<int> deg(n);
        for(int i=0;i<m;i++){ 
            deg[A[i]]++; 
            deg[B[i]]++; 
            dsu.unite(A[i],B[i]); 
        }

        int S = n; // extra node
        vector<vector<int>> adj(n+1);
        vector<int> eu, ev, rid;

        auto add_edge = [&](int u,int v,int id){
            int idx = eu.size();
            eu.push_back(u); 
            ev.push_back(v); 
            rid.push_back(id);
            adj[u].push_back(idx); 
            adj[v].push_back(idx);
        };

        // original edges
        for(int i=0;i<m;i++) add_edge(A[i],B[i],i);
        // connect odd-degree vertices to S
        for(int v=0;v<n;v++) if(deg[v]&1) add_edge(v,S,-1);

        // ensure each component is connected to S evenly
        vector<int> rep(n,-1), hasEdge(n,0), hasOdd(n,0);
        for(int v=0;v<n;v++) if(deg[v]>0){
            int r=dsu.find(v);
            hasEdge[r]=1;
            if(rep[r]==-1) rep[r]=v;
            if(deg[v]&1) hasOdd[r]=1;
        }
        for(int r=0;r<n;r++) if(hasEdge[r]&&!hasOdd[r]){
            int v=rep[r];
            add_edge(v,S,-1);
            add_edge(v,S,-1);
        }

        // Eulerian traversal
        int E=eu.size();
        vector<char> used(E);
        vector<int> it(n+1), stV{S}, stE, res;
        while(!stV.empty()){
            int v=stV.back();
            while(it[v]<adj[v].size() && used[adj[v][it[v]]]) it[v]++;
            if(it[v]==adj[v].size()){
                stV.pop_back();
                if(!stE.empty()){ 
                    res.push_back(stE.back()); 
                    stE.pop_back(); 
                }
            }else{
                int ei=adj[v][it[v]++];
                if(used[ei]) continue;
                used[ei]=1;
                int to=eu[ei]^ev[ei]^v;
                stV.push_back(to);
                stE.push_back(ei);
            }
        }

        // alternate coloring
        vector<int> color(E);
        for(int i=res.size()-1,cur=0;i>=0;i--,cur++)
            color[res[i]] = (cur%2 ? 2 : 1);

        // assign back to real edges
        vector<int> day(m,1);
        for(int i=0;i<E;i++) if(rid[i]>=0) day[rid[i]] = color[i];

        // compute answer
        vector<int> d1(n), d2(n);
        for(int i=0;i<m;i++){
            int u=A[i],v=B[i];
            if(day[i]==1){ d1[u]++; d1[v]++; }
            else{ d2[u]++; d2[v]++; }
        }
        ll ans=0;
        for(int i=0;i<n;i++) ans += 1LL*d1[i]*d1[i] + 1LL*d2[i]*d2[i];

        string s;
        for(int i=0;i<m;i++) s.push_back('0'+day[i]);
        cout<<"Case #"<<tc<<": "<<ans<<" "<<s<<"\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}

