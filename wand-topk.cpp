#include <bits/stdc++.h>
using namespace std;

struct PostingEntry {
  int docID;
  double score;
  PostingEntry(int _docID, double _score): docID(_docID), score(_score){
  }
  // Sort by score first
  bool operator <(const PostingEntry &other)const{
    if(score == other.score) return docID < docID;
    return score < other.score;
  }

  bool operator >(const PostingEntry &other) const {
    return other < *this;
  }
};

struct PostingsList{
    string term;
    vector <PostingEntry> list;
    double upperBoundScore;
    PostingsList (string _term, const vector <PostingEntry> postingsList):
    term(_term),
    list(postingsList),
    upperBoundScore(0){
      for(const auto &cur : list){
        upperBoundScore = max(upperBoundScore, cur.score);
      }
    }
    int size() {
      return (int) list.size();
    }
    PostingEntry &operator[](size_t index) {
      return list[index];
    }
};

// Memetakan dari string ke pointer of vector
map<string, PostingsList*> posting;
typedef priority_queue <PostingEntry, vector <PostingEntry>, greater<PostingEntry>> Heap;
Heap wandTopK(const vector <string> terms, int k){

// Memindahkan PostingsList yang diquery ke list of PostingsList
  vector <PostingsList*> queriedPostingList;
  for(const auto &cur : terms){
    queriedPostingList.push_back(posting[cur]);
  }

  int n = (int)terms.size();
  int curDoc = 0;
  // Set pointernya ke awal
  // Untuk terms[i] posisi pointernya lagi di posisi[i], awalnya 0
  vector <int> posisi(n, 0);
  vector <int> permutationOfTerms(n, 0);
  // iota untuk melakukan assigning serial, yaitu permutationOfTerms[i] = i;
  iota(begin(permutationOfTerms), end(permutationOfTerms), 0);
  // permutationOfTerms digunakan sebagai penanda terms mana yang berada di mana saat disort

  Heap topK;
  for(int i = 0;i < k;i++){
    topK.push(PostingEntry(-1, 0));
  }
  while (true){
    int threshold = topK.top().score;
    sort(begin(permutationOfTerms), end(permutationOfTerms), [&](int idx1, int idx2){
      auto doc1 = (*queriedPostingList[idx1])[posisi[idx1]];
      auto doc2 = (*queriedPostingList[idx2])[posisi[idx2]];
      return doc1.docID < doc2.docID;
    });
    int pivot = -1;
    double curUB = 0;
    for(const auto &idx : permutationOfTerms){
      if(curUB >= threshold){
        pivot = (*queriedPostingList[idx])[posisi[idx]].docID;
        break;
      }
      curUB += (*queriedPostingList[idx]).upperBoundScore;
    }
    if(pivot == -1) return topK;
    if(pivot == n - 1) return topK;
  }
  return topK;
}


int main() {
  return 0;
  PostingsList *hujan = new PostingsList("hujan", {{1, 1.5}, {2, 0.4}, {3, 0.6}, {6, 1.0}, {8, 1.5}, {11, 1.6}});
  posting[hujan->term] = hujan;
  PostingsList *turun = new PostingsList("turun", {{1, 0.7}, {3, 1.0}, {6, 1.5}, {8, 1.5}, {10, 0.3}, {12, 1.1}});
  posting[turun->term] = turun;
  PostingsList *deras = new PostingsList("deras", {{1, 1.2}, {6, 1.0}, {7, 0.5}, {10, 0.6}, {11, 1.8}});
  posting[deras->term] = deras;
  
  wandTopK({"hujan", "turun", "deras"}, 1);
}