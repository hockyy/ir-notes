struct ListNode {
  int val;
  ListNode *nextNode;
  ListNode *next() {
    return nextNode;
  }
};

int docID(ListNode *node){
  return node->val;
}

int pos(ListNode *node){
  return node->val;
}

int main(){


}