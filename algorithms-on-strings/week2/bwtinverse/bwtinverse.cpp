#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> parse_column(const string& text){

  unordered_map<char,int> occurrence;
  vector<string> column (text.size(),"#");

  for (size_t i = 0; i < text.size(); i++)
  {
    int count  = 1;
    if(occurrence.count(text[i]) != 0){
      count = occurrence.find(text[i])->second;
      count++;           
    }
    occurrence[text[i]] = count;
    column.push_back(text[i] + to_string(count));
  }
  

  for (auto &&element : text)
  {
    int count  = 1;
    if(occurrence.count(element) != 0){
      count = occurrence.find(element)->second;
      count++;           
    }
    occurrence[element] = count;
    column.push_back(element + to_string(count));
  }

  return column;  
}

unordered_map<string,string> map_column(vector<string> column1, vector<string> column2)
{
  unordered_map<string,string> mapping;  
  for (size_t i = 0; i < column1.size(); i++)
    mapping.insert(pair<string,string> (column1[i],column2[i]));
  return mapping;  
} 

string InverseBWT(const string& bwt) {
  string text = "";
  string bwt_ordered = bwt;
  sort(bwt_ordered.begin(), bwt_ordered.end());

  vector<string> last_column =  parse_column(bwt);
  vector<string> first_column =  parse_column(bwt_ordered);

  unordered_map<string,string> first_to_last = map_column(first_column,last_column);
  string first_match = first_column[0];
    
  for (size_t i = 0; i < bwt_ordered.size(); i++)
  {
    text = text + first_match[0];
    first_match = first_to_last.find(first_match)->second;    
  }

  reverse(text.begin(),text.end());  
    
  return text;
}




int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
