#include <bits/stdc++.h>
using namespace std;

double rbp(vector <int> relevance, double p = 0.8){
  double sum = 0;
  int K = relevance.size();
  for(int i = 0;i < K;i++){
    sum += pow(p, i) * relevance[i];
  }
  sum *= (1 - p);
  return sum;
}

int main(){
  cout << fixed << setprecision(7);
  vector <int> docs = {1, 1, 0, 0, 1, 0, 1, 0, 0, 1};
  vector <int> query = docs;
  query.resize(5);
  cout << rbp(query) << endl;
}