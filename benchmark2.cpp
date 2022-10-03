#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


int docID(vector<int>::iterator it){
  return *it;
}

void add(vector <int> &v, int i){
  v.push_back(i);
}
// returns v1 and v2
// kompleksitas waktu length(v1) + length(v2)
vector <int> Intersect(vector<int> v1, vector<int> v2, bool debug = 1) {
  auto p1 = v1.begin();
  auto p2 = v2.begin();
  vector <int> answer;
  while(p1 != v1.end() && p2 != v2.end()){
    if(docID(p1) == docID(p2)){
      add(answer, docID(p1));
      p1 = next(p1);
      p2 = next(p2);
    }else if(docID(p1) < docID(p2)){
      p1 = next(p1);
    }else{
      p2 = next(p2);
    }
  }
  return answer;
}

// intersection binary search
// Kompleksitas waktu: min(length(v1), length(v2)) * log(max(length(v1), length(v2)))
vector <int> IntersectBinarySearch(vector <int> v1, vector <int> v2){
  if(v1.size() > v2.size()) swap(v1, v2);
  vector <int> answer;
  for(auto &value : v1){
    // Binary search apakah ada "value" pada v2
    int lo = 0;
    int hi = (int) v2.size() - 1;
    while(lo < hi){
      int mid = (lo + hi) / 2;
      if(v2[mid] < value) lo = mid + 1;
      else hi = mid;
    }
    if(v2[lo] == value) add(answer, value);
  }
  return answer;
}

int main(){
  int n, m;
  cin >> n;
  vector <int> v1(n);
  for(auto &cur : v1) cin >> cur;
  cin >> m;
  vector <int> v2(m);
  for(auto &cur : v2) cin >> cur;

  cout << n << " " << m << endl;
  cout << "IntersectBinarySearch" << endl;
  // cout << "Intersect" << endl;
  auto start = chrono::steady_clock::now();
  auto v3 = IntersectBinarySearch(v1, v2);
  // auto v3 = Intersect(v1, v2);
  auto end = chrono::steady_clock::now();

  cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;
}