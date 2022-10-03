#include <vector>
#include <cassert>
#include <map>
#include <deque>
#include <iostream>
#define fi first
#define se second
using namespace std;
struct ListNode {
  int val;
  ListNode *nextNode;
  ListNode (int value) {
    val = value;
  }
};

ListNode *next(ListNode *current) {
  return current->nextNode;
}

// Mengubah vector ke list untuk kepentingan insertion
ListNode *vectorToList(const vector <int> v) {
  assert(v.size() > 0);
  ListNode *head = new ListNode(v[0]);
  ListNode *currentNode = head;
  for (int i = 1; i < (int) v.size(); i++) {
    currentNode->nextNode = new ListNode(v[i]);
    currentNode = next(currentNode);
  }
  return head;
}

int docID(ListNode *node) {
  return node->val;
}

int pos(ListNode *node) {
  return node->val;
}

template<class T>
void add(vector <T> &v, T value) {
  v.push_back(value);
}

typedef pair<int, pair<int, int>> PositionalPair;
map <int, ListNode*> mapBe, mapTo;

void Proximity(ListNode *pp1,
               ListNode *pp2,
               int k, int docId,
               vector <PositionalPair> &answer) {

  deque <int> l;
  while (pp1 != NULL) {
    while (pp2 != NULL && pos(pp2) - pos(pp1) <= k) {
      if (abs(pos(pp1) - pos(pp2)) <= k) l.push_back(pos(pp2));
      pp2 = next(pp2);
    }
    while (!l.empty() && abs(l.front() - pos(pp1)) > k) {
      l.pop_front();
    }
    for (auto &ps : l) {
      add(answer, (PositionalPair) {docId, {pos(pp1), ps}});
    }
    pp1 = next(pp1);
  }
}

vector <PositionalPair> PositionalIntersect(ListNode *p1, ListNode *p2, int k) {
  vector <PositionalPair> answer;
  while (p1 != NULL && p2 != NULL) {
    if (docID(p1) == docID(p2)) {
      Proximity(mapTo[docID(p1)], mapBe[docID(p2)], k, docID(p1), answer);
      p1 = next(p1);
      p2 = next(p2);
    } else if (docID(p1) < docID(p2)) {
      p1 = next(p1);
    } else {
      p2 = next(p2);
    }
  }
  return answer;
}


int main() {
  auto nodeBe = vectorToList({23, 31, 56});
  auto nodeTo = vectorToList({31, 35, 45, 56});

  mapBe[23] = vectorToList({32, 56, 78, 99});
  mapBe[31] = vectorToList({46, 50});
  mapBe[56] = vectorToList({12, 34, 56, 58, 94});

  mapTo[31] = vectorToList({45, 49});
  mapTo[35] = vectorToList({3, 12, 45});
  mapTo[45] = vectorToList({4, 33, 34, 87});
  mapTo[56] = vectorToList({93});

  cout << "k = 2" << endl;
  auto res = PositionalIntersect(nodeBe, nodeTo, 2);
  for(auto &cur: res) cout << cur.fi << " " << cur.se.fi << " " << cur.se.se << endl;
  cout << "k = 3" << endl;
  res = PositionalIntersect(nodeBe, nodeTo, 3);
  for(auto &cur: res) cout << cur.fi << " " << cur.se.fi << " " << cur.se.se << endl;
}