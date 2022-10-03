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
// returns v1 or v2
// kompleksitas waktu length(v1) + length(v2)
vector <int> Union(vector<int> v1, vector<int> v2) {
  auto p1 = v1.begin();
  auto p2 = v2.begin();
  vector <int> answer;
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

  return answer;
}

// returns v1 or v2
// kompleksitas waktu length(v1) + length(v2)
vector <int> Union2(vector<int> v1, vector<int> v2) {
  auto p1 = v1.begin();
  auto p2 = v2.begin();
  vector <int> answer;
   while(p1 != v1.end() && p2 != v2.end()){
     if(docID(p1) == docID(p2)){
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
   while (p1 != v1.end()) {
     add(answer, docID(p1));
     p1 = next(p1);
   }
   while (p2 != v2.end()) {
     add(answer, docID(p2));
     p2 = next(p2);
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
  // cout << "Union" << endl;
  cout << "Union2" << endl;
  auto start = chrono::steady_clock::now();
  // auto v3 = Union(v1, v2);
  auto v3 = Union2(v1, v2);
  auto end = chrono::steady_clock::now();

  cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;
 
}