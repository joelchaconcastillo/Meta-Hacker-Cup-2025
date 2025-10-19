#include <bits/stdc++.h>
using namespace std;
void solve(){
    int n;cin>>n;
    vector<int>a(n);
    for(auto &i:a)cin>>i;
    long long res = 0, prev=a[0];
    for(int i = 1 ; i < n; i++){
	    res = max(res, abs(a[i]-prev));
	    prev = a[i];
    }
    cout << res<<endl;
}
int main(){
	int t;
	cin>>t;
	int i = 1;
	while(t--){
		cout << "Case #"<<i<<": ";
		solve();
		i++;
	}
	return 0;
}
/*
   1 2 3 4
   3 4 4 4
   
   0 1 2


 * */
