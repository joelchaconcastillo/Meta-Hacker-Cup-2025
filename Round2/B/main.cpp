#include <bits/stdc++.h>
using namespace std;

vector<int> A, B;
vector<int> groups;
vector<long long> prefGroups;
vector<long long> capacity;

bool feasible_k(int k){
    if(k == 0) return true;
    long long P = prefGroups[k];
    long long demand_prefix = 0;
    int s = 0;
    for(int r = 0; r < k; r++){
        int val = k - r;
        int cnt = groups[r];
        for(int t = 0; t < cnt; t++){
            s++;
            demand_prefix += val;
            if(demand_prefix > capacity[s])
                return false;
        }
    }
    return true;
}

void solve(){
    int N, M;
    cin >> N >> M;

    A.resize(N);
    for(int i = 0; i < N; i++) cin >> A[i];

    B.resize(M);
    for(int i = 0; i < M; i++) cin >> B[i];

    sort(A.begin(), A.end(), greater<int>());

    groups.clear();
    for(int i = 0; i < N; ){
        int j = i + 1;
        while(j < N && A[j] == A[i]) j++;
        groups.push_back(j - i);
        i = j;
    }

    int G = groups.size();

    prefGroups.assign(G + 1, 0);
    for(int i = 0; i < G; i++)
        prefGroups[i + 1] = prefGroups[i] + groups[i];

    sort(B.begin(), B.end());
    capacity.assign(N + 1, 0);

    long long prefSum = 0;
    int ptr = 0;

    for(int s = 1; s <= N; s++){
        while(ptr < M && B[ptr] <= s){
            prefSum += B[ptr];
            ptr++;
        }
        capacity[s] = prefSum + (long long)(M - ptr) * (long long)(s);
    }

    int lo = 0, hi = G, best_k = 0;
    while(lo <= hi){
        int mid = (lo + hi) / 2;
        if(feasible_k(mid)){
            best_k = mid;
            lo = mid + 1;
        } else hi = mid - 1;
    }

    cout << prefGroups[best_k];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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

