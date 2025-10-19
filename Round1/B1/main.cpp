#include <bits/stdc++.h>
using namespace std;
void solve(){
    int n, a, b;
    cin >> n >> a >> b;
    for(int i = 0 ; i+1 < 2*n; i++){
	    cout << 1 << " ";
    }
    cout << b<<endl;
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
