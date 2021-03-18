#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(string& text) {
  string result = "";
  vector<string> M;

  for (size_t i = 0; i < text.size(); i++)
  {
    M.push_back(text);
    rotate(text.begin(), text.begin()+text.size()-1, text.end());
  }
  sort(M.begin(), M.end());
  for (auto &&str : M) result.push_back(str.back());

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}