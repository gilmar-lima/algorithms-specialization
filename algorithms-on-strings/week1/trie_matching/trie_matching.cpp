#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(const vector<string>& patterns) {
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

bool prefix_trie_matching(const string& text, const trie& t){
	int symbol_position = 0;
	char symbol = text[symbol_position];
	int v = 0;

	auto is_leaf = [](const int& v, const trie& t){
		return t[v].size() == 0;
	};

	auto have_edge = [](const int& v, const trie& t,const char& symbol){
		return t[v].find(symbol) != t[v].end();
	};

	while(true){
		if(is_leaf(v,t)){
			return true;
		}else if(have_edge(v,t,symbol)){
			v = t[v].find(symbol)->second;
			symbol_position++;
			symbol = text[symbol_position];
		}else{
			return false;
		}
	}
}

vector<int> trie_matching(const string& text, const trie& t){
	int text_position = 0;
	vector<int> match_position;

	while(text_position < text.size()){
		bool match = prefix_trie_matching(text.substr(text_position,text.size()),t);
		if(match) match_position.push_back(text_position);
		text_position++;
	}

	return match_position;
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;

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

	vector <int> ans;
	ans = solve (text, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
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
