#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void inorder_order_traversal(int node_index, const vector<Node>& tree, vector<int>& result){
    if(node_index == -1){
      return;
    }

    inorder_order_traversal(tree[node_index].left, tree, result);
    result.push_back(tree[node_index].key);
    inorder_order_traversal(tree[node_index].right, tree, result);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  vector<int> result;

  if(tree.size() == 0) return true;

  inorder_order_traversal(0, tree, result);

  for (size_t i = 0; i < result.size()-1; i++)
  {
    if(result[i] > result[i+1]) return false;
  }  

  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
