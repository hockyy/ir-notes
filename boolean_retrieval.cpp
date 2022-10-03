#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;


int docID(vector<int>::iterator it){
  return *it;
}

void add(vector <int> &v, int i){
  v.push_back(i);
}


// Method untuk print 
void print(vector <int> &v){
  for(auto &cur: v) cout << cur << " ";
    cout << endl;
}

void print(vector<int>::iterator it){
  cout << *it << endl;
}

// returns v1 and v2
// kompleksitas waktu length(v1) + length(v2)
vector <int> Intersect(vector<int> v1, vector<int> v2, bool debug = 1) {
  auto p1 = v1.begin();
  auto p2 = v2.begin();
  vector <int> answer;
  if(debug) print(v1);
  if(debug) print(v2);
  if(debug) cout << "Intersecting..." << endl; 
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
  if(debug) print(answer);
  if(debug) cout << "----" << endl;
  return answer;
}

// returns v1 or v2
// kompleksitas waktu length(v1) + length(v2)
vector <int> Union(vector<int> v1, vector<int> v2) {
  auto p1 = v1.begin();
  auto p2 = v2.begin();
  vector <int> answer;
  print(v1);
  print(v2);
  cout << "Union..." << endl;
  while(p1 != v1.end() || p2 != v2.end()){
    if(p1 == v1.end()){
      add(answer, docID(p2));
      p2 = next(p2);
    } else if(p2 == v2.end()){
      add(answer, docID(p1));
      p1 = next(p1);
    } else if(docID(p1) == docID(p2)){
      add(answer, docID(p1));
      p1 = next(p1);
      p2 = next(p2);
    }else if(docID(p1) < docID(p2)){
      add(answer, docID(p1));
      p1 = next(p1);
    }else{
      add(answer, docID(p2));
      p2 = next(p2);
    }
  }
  print(answer);
  cout << "----" << endl;
  return answer;
}

// Returns v1 and not v2
// kompleksitas waktu length(v1) + length(v2)
vector <int> Difference(vector<int> v1, vector<int> v2) {
  auto p1 = v1.begin();
  auto p2 = v2.begin();
  vector <int> answer;
  print(v1);
  print(v2);
  cout << "Difference..." << endl;
  while(p1 != v1.end() || p2 != v2.end()){
    if(p1 == v1.end()){
      break;
    } else if(p2 == v2.end()){
      add(answer, docID(p1));
      p1 = next(p1);
    } else if(docID(p1) == docID(p2)){
      p1 = next(p1);
      p2 = next(p2);
    }else if(docID(p1) < docID(p2)){
      add(answer, docID(p1));
      p1 = next(p1);
    }else{
      p2 = next(p2);
    }
  }
  print(answer);
  cout << "----" << endl;
  return answer;
}

// returns multiple intersection
// Kompleksitas waktu = Σ length(v), v ∈ vs
vector <int> Intersect(vector<vector<int>> vs){
  sort(begin(vs), end(vs), [](vector <int> &a, vector <int> &b){
    return a.size() < b.size();
  });
  if(vs.size() == 0) return {};
  vector <int> results = vs[0];
  for(auto &v : vs){
    print(v);
    results = Intersect(results, v, 0);
  }
  cout << ("Multiple Intersect") << endl;
  print(results);
  cout << "----" << endl;
  return results;
}

// intersection binary search
// Kompleksitas waktu: min(length(v1), length(v2)) * log(max(length(v1), length(v2)))
vector <int> IntersectBinarySearch(vector <int> v1, vector <int> v2){
  if(v1.size() > v2.size()) swap(v1, v2);
  vector <int> answer;
  print(v1);
  print(v2);
  cout << "Intersecting Binary Search..." << endl; 
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
  print(answer);
  cout << "----" << endl;
  return answer;
}

int main(){
  map <string, vector<int>> table;
  table["hujan"] = {12,34,54,89,101};
  table["langit"] = {10,12,27,34,54,89,132};
  table["sejuk"] = {18,34,89};
  auto v1 = Intersect(table["hujan"], table["sejuk"]);
  auto v2 = Union(table["hujan"], table["sejuk"]);
  auto v3 = Difference(table["hujan"], table["sejuk"]);
  auto v4 = Intersect({table["hujan"], table["sejuk"], table["langit"]});
  auto v5 = IntersectBinarySearch(table["langit"], table["sejuk"]);
  // print(v);
}