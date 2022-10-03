#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
  int ch;
  int child[26];
}

TrieNode trie[100005];
int ptr = 1;

void insert(string s, int idx){
  int pos = 0;
  for(auto ch: s){
    int curChar = ch - 'a';
    if(child[curChar] == 0){
      child[curChar] = ptr;
      ptr++;
    } 

  }
}

int main(){
    
}