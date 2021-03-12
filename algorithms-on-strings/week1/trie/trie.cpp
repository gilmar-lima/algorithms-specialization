#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  edges new_node;
  t.push_back(new_node);
  

  auto have_symbol = [](const trie& t, const int& current_node, const char& current_symbol){
    return t[current_node].find(current_symbol) != t[current_node].end();
  };

  for (auto &&pattern : patterns)
  {
    int current_node = 0;
    for (size_t i = 0; i < pattern.size(); i++)
    {
      char current_symbol = pattern[i];
      if(have_symbol(t,current_node,current_symbol)){
        current_node = t[current_node].find(current_symbol)->second;
      }else{
        t.push_back(new_node);
        int new_node_position = t.size() -1;
        t[current_node].insert(std::pair<char,int>(current_symbol,new_node_position));
        current_node = new_node_position;
      }
    }    
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}