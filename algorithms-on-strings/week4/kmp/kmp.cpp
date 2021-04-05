#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.

vector<int>	compute_prefix_function(const string& pattern){
	vector<int> s (pattern.size(),0);
	int border = 0;

	for(int i = 1; i < pattern.size(); i++){
		while(border > 0 && pattern[i] != pattern[border])
			border = s[border - 1];
		
		if(pattern[i] == pattern[border])
			border = border + 1;
		else
			border = 0;

		s[i] = border;
	}

	return s;
}

vector<int> find_occurrences(const string& pattern, const string& text){
	string S = pattern + '$' + text;
	vector<int> s = compute_prefix_function(S);
	vector<int> result;

	for(int i = pattern.size() + 1; i < S.size(); i++){
		if(s[i] == pattern.size())
			result.push_back(i - 2*pattern.size());
	}

	return result;
}

vector<int> find_pattern(const string& pattern,  const string& text) {
  return find_occurrences(pattern, text);
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
