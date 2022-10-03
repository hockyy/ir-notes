#include <iostream>
#include <climits>
#include <map>
using namespace std;

#define pb push_back
#define sz(x) (int)(x.size())
typedef long long LL;

string S, T;
int memo[5005][5005];
map <char, int> lastOccurenceS;

const int kSubstitutionCost = 1;
const int kDeleteCost = 1;
const int kInsertCost = 1;
const int kTranspositionCost = 1;

int main(){
  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  while(cin >> S >> T){
    if(S == "*" || T == "*") return 0;
    lastOccurenceS.clear();
    int n = sz(S);
    int m = sz(T);
    // Definisikan memo[i][j] adalah cost yang diperlukan untuk
    // menjadikan S[1, i] menjadi T[1, j]
    // Perhatikan bahwa S[1, i] berarti substring dengan index yang
    // dimulai dari 1 dan diakhiri i secara inklusif
    S = "-" + S;
    T = "-" + T;
    memo[0][0] = 0;
    for(int i = 1;i <= n;i++){
      // Lakukan deletion sebanyak i kali pada S
      memo[i][0] = i;
    }
    for(int j = 1;j <= m;j++){
      // Lakukan insertion sebanyak j kali pada S
      memo[0][j] = j;
    }
    for(int i = 1;i <= n;i++){
      int lastOccurenceT = -1;
      for(int j = 1;j <= m;j++){
        memo[i][j] = INT_MAX;
        memo[i][j] = min(memo[i][j], memo[i - 1][j] + kDeleteCost);
        memo[i][j] = min(memo[i][j], memo[i][j - 1] + kInsertCost);
        memo[i][j] = min(memo[i][j], memo[i - 1][j - 1] + kSubstitutionCost * (S[i] != T[j]));
        {
          int previousSameCharacterS = (lastOccurenceS.count(T[j]) ? lastOccurenceS[T[j]] : -1);
          int previousSameCharacterT = lastOccurenceT;
          if(previousSameCharacterS != -1 && previousSameCharacterT != -1 && (i - previousSameCharacterS - 1 == 0 || j - previousSameCharacterT - 1 == 0)){
            memo[i][j] = min(memo[i][j],
                             memo[previousSameCharacterS - 1][previousSameCharacterT - 1]
                              + kTranspositionCost
                              + i - previousSameCharacterS - 1
                              + j - previousSameCharacterT - 1);
          }
        }
        if(S[i] == T[j]){
          lastOccurenceT = j;
        }
      }
      lastOccurenceS[S[i]] = i;
    }
    for(int i = 0;i <= n;i++){
      for(int j = 0;j <= m;j++){
        cout << memo[i][j] << " ";
      }
      cout << endl;
    }
    cout << memo[n][m] << endl;
  }
}