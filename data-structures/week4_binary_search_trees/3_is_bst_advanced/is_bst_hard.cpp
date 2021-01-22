#include <algorithm>
#include <iostream>
#include <vector>
#include <cstddef>

using namespace std;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool check_node(int node_index, const vector<Node>& tree){

    if(node_index == -1){
      return true;
    }
    

    if(tree[node_index].left == -1 && tree[node_index].right == -1){
      return true;
    }else if(tree[node_index].left == -1 && tree[node_index].right != -1){
      if(tree[node_index].key > tree[tree[node_index].right].key) return false;
    }else if(tree[node_index].left != -1 && tree[node_index].right == -1){
      if(tree[tree[node_index].left].key >= tree[node_index].key) return false;
    }else{
      if(tree[node_index].key > tree[tree[node_index].right].key || tree[tree[node_index].left].key >= tree[node_index].key) return false;
    }  

    return (check_node(tree[node_index].left, tree) && check_node(tree[node_index].right, tree));

}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  

  if(tree.size() == 0) return true; 

  return check_node(0,tree);
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
