#include <iostream>
#include <climits>
#include <map>
using namespace std;

#define pb push_back
#define sz(x) (int)(x.size())
typedef long long LL;

string S, T;
int memo[5005][5005];``
map <char, int> nextCharS, nextCharT;

const int kSubstitutionCost = 1;
const int kDeleteCost = 1;
const int kInsertCost = 1;
const int kTransitionCost = 1;

// Lowrance-Wagner Algorithm
int dp(int posS, int posT){
  // No more edit case
  int &ret = memo[posS][posT];
  if(~ret) return ret;
  ret = INT_MAX;
  if(posS == sz(S) && posT == sz(T)) return ret = 0;
  if(posS == sz(S)) return ret = sz(T) - posT; // Add the rest of the T characters
  if(posT == sz(T)) return ret = sz(S) - posS; // Remove the rest of the S characters
  // Insert T[posT] in posS
  ret = min(ret, dp(posS, posT + 1) + kInsertCost);
  // Remove S[posS] in S
  ret = min(ret, dp(posS + 1, posT) + kDeleteCost);
  // substitution S[posS] with T[posT]
  ret = min(ret, dp(posS + 1, posT + 1) + kSubstitutionCost * (S[posS] != T[posT]));
  {
    // transposition
    int nextS = lastFindS[posS];
    int nextT = lastFindT[posT];
    if(nextS != -1 && nextT != -1){
      int costS = nextS - posS - 1;
      int costT = nextT - posT - 1;
      // cout << costS << " " << costT << endl;
      ret = min(ret, dp(nextS + 1, nextT + 1) + kTransitionCost + costS + costT);
    }
  }
  return ret;
}

int main(){
  int t = 1;
  while(t--){
    nextCharS.clear();
    nextCharT.clear();
    getline(cin, S);
    getline(cin, T);
    int n = sz(S);
    int m = sz(T);
    for(int i = n - 1;i >= 0;i--){
      lastFindS[i] = -1;
      if(nextCharS.count(S[i])) lastFindS[i] = nextCharS[S[i]];
      nextCharS[S[i]] = i;
    }
    for(int i = m - 1;i >= 0;i--){
      lastFindT[i] = -1;
      if(nextCharT.count(T[i])) lastFindT[i] = nextCharT[T[i]];
      nextCharT[T[i]] = i;
    }
    cout << "\"" << S << "\"" << endl;
    cout << "\"" << T << "\"" << endl;
    cout << n << " " << m << endl;
    for(int i = 0;i < n + 1; i++) for(int j = 0;j < m + 1;j++) memo[i][j] = -1;
    cout << dp(0, 0) << endl;
    for(int i = n;i >= 0; i--){ for(int j = m;j >= 0;j--) cout << memo[i][j] << " ";  cout << endl;}
  }
}