#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string InverseBWT(const string& bwt) {
  string text = "";
  string sample (bwt.size(),'x');
  vector<string> M (bwt.size(), sample);

  for (size_t i = 0; i < bwt.size(); i++)
  {
    for (auto &&str : M) rotate(str.begin(), str.begin()+str.size()-1, str.end());
    for (size_t j = 0; j < bwt.size(); j++) M[j][0] = bwt[j];    
    sort(M.begin(), M.end());    
  }

  text = M.front();
  rotate(text.begin(), text.begin()+1, text.end());

  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
