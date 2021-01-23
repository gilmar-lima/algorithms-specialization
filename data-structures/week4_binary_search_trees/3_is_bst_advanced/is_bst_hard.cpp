#include <algorithm>
#include <iostream>
#include <vector>
#include <cstddef>
#include <climits>

using namespace std;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

struct Boundaries
{
  int min;
  int max;

  Boundaries(int min_, int max_) : min(min_), max(max_) {}
};


bool check_node(int node_index, const vector<Node>& tree, Boundaries node_limits){

    if(node_index == -1){
      return true;
    }

    //check wether the current node respect the limits of its branch
    if(tree[node_index].key > node_limits.max) return false;
    if(tree[node_index].key < node_limits.min) return false;

    //check if the current node children respect the rules
    if(tree[node_index].left == -1 && tree[node_index].right == -1){
      return true;
    }else if(tree[node_index].left == -1 && tree[node_index].right != -1){
      if(tree[node_index].key > tree[tree[node_index].right].key) return false;
    }else if(tree[node_index].left != -1 && tree[node_index].right == -1){
      if(tree[tree[node_index].left].key >= tree[node_index].key) return false;
    }else{
      if(tree[node_index].key > tree[tree[node_index].right].key || tree[tree[node_index].left].key >= tree[node_index].key) return false;
    }

    Boundaries left_limits = node_limits;
    Boundaries right_limits = node_limits;

    if(tree[node_index].key > node_limits.min){
      right_limits.min = tree[node_index].key;
    }

    if(tree[node_index].key < node_limits.max){
      left_limits.max = tree[node_index].key;
    }     

    return (check_node(tree[node_index].left, tree, left_limits) && check_node(tree[node_index].right, tree, right_limits));

}

bool IsBinarySearchTree(const vector<Node>& tree) {
  if(tree.size() == 0) return true; 

  Boundaries node_limits(INT_MIN, INT_MAX) ;

  return check_node(0,tree, node_limits);
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
