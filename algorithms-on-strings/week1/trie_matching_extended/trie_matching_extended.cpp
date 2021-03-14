#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;
struct node {
	int value;
	bool pattern_end;
};

typedef map<char,node> edges;
typedef vector<edges> trie;

trie build_trie(const vector<string>& patterns) {
  trie t;
  edges new_node;
	vector<string> sorted_patterns = patterns;

  t.push_back(new_node);
	
	auto compare_size = [](string& pattern1, string& pattern2){
		return pattern1.size() < pattern2.size();
	};

  auto have_out_edge = [](const trie& t, const node& current_node, const char& current_symbol){
    return t[current_node.value].find(current_symbol) != t[current_node.value].end();
  };

	auto is_pattern_end = [](const int& position, const auto& pattern){
		return position == pattern.size() - 1;
	};

	sort(sorted_patterns.begin(), sorted_patterns.end(), compare_size);	

  for (auto &&pattern : sorted_patterns)
  {
    node current_node {0,false};
    for (size_t i = 0; i < pattern.size(); i++)
    {
      char current_symbol = pattern[i];
      if(have_out_edge(t,current_node,current_symbol)){
        current_node = t[current_node.value].find(current_symbol)->second;
      }else{
        t.push_back(new_node);
        int new_node_position = t.size() -1;
				node next_node {new_node_position,is_pattern_end(i,pattern)};
        t[current_node.value].insert(std::pair<char,node>(current_symbol,next_node));
        current_node = next_node;			
      }
    }    
  }
  return t;
}

bool prefix_trie_matching(const string& text, const trie& t){
	int symbol_position = 0;
	char symbol = text[symbol_position];
	node v {0,false};

	auto is_pattern = [](const node& v){
		return v.pattern_end;
	};

	auto have_edge = [](const node& v, const trie& t, const char& symbol){
		return t[v.value].find(symbol) != t[v.value].end();
	};

	while(true){
		if(is_pattern(v)) return true;
		
		if(have_edge(v,t,symbol)){
			v = t[v.value].find(symbol)->second;
			symbol_position++;
			symbol = text[symbol_position];
			continue;
		}

		return false;
	}
}

set<int, less<int>> trie_matching(const string& text, const trie& t){
	int text_position = 0;	
	set<int, less<int>> positions;	

	while(text_position < text.size()){
		bool match = prefix_trie_matching(text.substr(text_position,text.size()),t);
		if(match) positions.insert(text_position);
		text_position++;
	}

	return positions;
}

set<int, less<int>> solve (const string& text, int n, const vector <string>& patterns)
{
	set<int, less<int>> result;

	trie t = build_trie(patterns);
	result = trie_matching(text,t);

	return result;
}

int main (void)
{
	string text;
	cin >> text;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	set<int, less<int> > ans;
	set<int, less<int> >::iterator position;
	ans = solve (text, n, patterns);

	for (position = ans.begin(); position != ans.end(); position++)
	{
		cout << *position;
		if (position != ans.end())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
