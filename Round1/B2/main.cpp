#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1'000'000'007;

// fast pow mod
long long modpow(long long a, long long e){
    long long r = 1 % MOD;
    a %= MOD;
    while(e){
        if(e & 1) r = (__int128)r * a % MOD;
        a = (__int128)a * a % MOD;
        e >>= 1;
    }
    return r;
}
long long inv(long long x){ return modpow((x%MOD+MOD)%MOD, MOD-2); }

// C(n,k) with large n, small k
long long comb_large_n_small_k(long long n, int k){
    if(k==0) return 1;
    long long num = 1;
    for(int i=1;i<=k;i++){
        long long term = ((n - k + i) % MOD + MOD) % MOD;
        num = (__int128)num * term % MOD;
    }
    static vector<long long> fact = {1};
    while((int)fact.size() <= k)
        fact.push_back(fact.back() * (long long)fact.size() % MOD);
    return num * inv(fact[k]) % MOD;
}

// trial factorization of B
vector<pair<long long,int>> factorize(long long B){
    vector<pair<long long,int>> res;
    long long b = B;
    for(long long p = 2; p*p <= b; p++){
        if(b % p == 0){
            int cnt = 0;
            while(b % p == 0){
                b /= p;
                cnt++;
            }
            res.push_back({p, cnt});
        }
    }
    if(b > 1) res.push_back({b, 1});
    return res;
}

// enumerate divisors of B with exponent vectors
void enumerate_divisors(int idx,
                        const vector<pair<long long,int>>& fac,
                        long long cur,
                        vector<int>& expv,
                        vector<pair<long long,vector<int>>>& out)
{
    if(idx == (int)fac.size()){
        out.push_back({cur, expv});
        return;
    }
    long long p = fac[idx].first;
    int e = fac[idx].second;
    long long val = 1;
    for(int k=0;k<=e;k++){
        expv[idx] = k;
        enumerate_divisors(idx+1, fac, cur * val, expv, out);
        val *= p;
    }
    expv[idx] = 0;
}

void solve(){
    long long N, A, B;
    cin >> N >> A >> B;

    auto factors = factorize(B);
    int m = factors.size();

    vector<int> expInv(m,0);
    vector<pair<long long, vector<int>>> divs;
    enumerate_divisors(0, factors, 1LL, expInv, divs);

    long long res = 0;

    for(auto &pr : divs){
        long long u = pr.first;
        if(u > A) continue;
        const vector<int>& a = pr.second;
        long long contrib = 1;

        for(int j=0;j<m;j++){
            int aj = a[j];
            int ej = factors[j].second;
            int bj = ej - aj;
            long long c1 = comb_large_n_small_k(N-1 + aj, aj);
            long long c2 = comb_large_n_small_k(N-1 + bj, bj);
            contrib = (__int128)contrib * c1 % MOD;
            contrib = (__int128)contrib * c2 % MOD;
        }

        res += contrib;
        if(res >= MOD) res -= MOD;
    }

    cout << res << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
