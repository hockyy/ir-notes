#include <iostream>
using namespace std;
typedef long long LL;
#include <vector>
#define pb push_back
#define all(x) begin(x), end(x)
#define trav(a, x) for(auto& a : x)
#define rep(i, a, b) for(int i = a; i < (b); ++i)

inline void fasterios(){
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
}

// Remember to undefine if the problem is interactive
#define endl '\n'

#include <random>
#include <chrono>
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); //For int
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); //For LL
// cout << rng() << endl;
// shuffle(isi.begin(),isi.end(),rng);

LL getRange(LL a, LL b){
   LL ran = b-a+1;
   return (rng()%ran)+a;
}

int main(){
  fasterios();
  int n = 2000000;
  int m = 100000;
  vector <int> v1;
  vector <int> v2;
  rep(i,0,n) v1.pb(getRange(1, 10000000));
  rep(i,0,m) v2.pb(getRange(1, 10000000));
  sort(all(v1));
  v1.erase(unique(all(v1)),v1.end());
  sort(all(v2));
  v2.erase(unique(all(v2)),v2.end());
  cout << v1.size() << endl;
  trav(cur, v1) cout << cur << " ";
  cout << endl;
  cout << v2.size() << endl;
  trav(cur, v2) cout << cur << " ";
  cout << endl;
}