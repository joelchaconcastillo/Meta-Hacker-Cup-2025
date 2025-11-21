#include <bits/stdc++.h>
using namespace std;

void solve(){
    long long N, M;
    cin >> N >> M;
    if( N>=M  && N<= 2LL*M - 2){
	    cout << "YES"<<endl;
	    return;
    }
    if(N>=2LL*M && (N%2==0)){
	    cout << "YES"<<endl;
	    return;
    }
    cout << "NO"<<endl;
}

int main(){
    int t;
    cin >> t;
    int i = 1;
    while(t--){
        cout << "Case #" << i << ": ";
        solve();
        i++;
    }
    return 0;
}

