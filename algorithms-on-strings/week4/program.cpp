#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> sort_characters(string S){
	vector<int> order (S.size(),0);
	unordered_map<char,int> num_occurrence;
	const string alphabet  = "$ABCDEFGHIJKLMNOPQRSTUVWXYZ";  

	for (size_t i = 0; i < S.size(); i++)
  {
    int count  = 1;
    if(num_occurrence.count(S[i]) != 0){
      count = num_occurrence.find(S[i])->second;
      count++;           
    }    
		num_occurrence[S[i]] = count;
  }

	for (size_t i = 1; i <= alphabet.size() - 1 ; i++){
		num_occurrence[alphabet[i]] = num_occurrence[alphabet[i]] + num_occurrence[alphabet[i-1]]; 
	}

	for (int i = S.size() - 1; i >= 0; i--)
	{
		char c = S[i];
		num_occurrence[c] = num_occurrence[c] - 1;
		order[num_occurrence[c]] = i;
	}

	return order;
}

vector<int> compute_char_classes(string S, vector<int> order){
	vector<int> classy (S.size(),0);
	classy[order[0]] = 0;

	for(int i = 1; i <= S.size() - 1; i++){
		if(S[order[i]] != S[order[i-1]]){
			classy[order[i]] = classy[order[i-1]] + 1;
		}else{
			classy[order[i]] = classy[order[i-1]];
		}
	}
	return classy;
}

vector<int> sort_doubled(string S, int L, vector<int> order, vector<int> classy){
	vector<int> new_order (S.size(),0);
	vector<int> num_occurrence (S.size(),0);

	for (size_t i = 0; i < S.size(); i++){
		num_occurrence[classy[i]] = num_occurrence[classy[i]] + 1;
	}

	for (size_t i = 1; i < S.size(); i++){
		num_occurrence[i] = num_occurrence[i] + num_occurrence[i-1];
	}

	for (int i = S.size() - 1; i >= 0; i--){
		int start = (order[i] - L + S.size()) % S.size();
		int cl = classy[start];
		num_occurrence[cl] = num_occurrence[cl] - 1;
		new_order[num_occurrence[cl]] = start;
	}

	return new_order;
}

vector<int> update_classes(vector<int> new_order, vector<int> classy, int L){
	int n = new_order.size();
	vector<int> new_class (n,0);
	new_class[new_order[0]] = 0;

	for (size_t i = 1; i < n; i++){
		int cur = new_order[i];
		int prev = new_order[i-1];
		int mid = cur + L;
		int mid_prev = (prev + L) % n;

		if(classy[cur] != classy[prev] || classy[mid] != classy[mid_prev]){
			new_class[cur] = new_class[prev] + 1;
		}else{
			new_class[cur] = new_class[prev];
		}
	}

	return new_class;

}

vector<int> build_suffix_array(string S){
	vector<int> order = sort_characters(S);
	vector<int> classy = compute_char_classes(S, order);

	int L = 1;

	while(L < S.size()){
		order = sort_doubled(S,L,order,classy);
		classy = update_classes(order,classy,L);
		L = 2*L;
	}

	return order;
}

void print_vector(vector<int> vec){
	std::cout << "[ ";
	for (auto &&element : vec) std::cout << element << " ";	
	std::cout << "]" << endl;
}

int main(){

	string s = "AACGATAGCGGTAGA$";

	std::transform(s.begin(), s.end(), s.begin(), std::ptr_fun<int, int>(std::toupper));
	
	vector<int> order = sort_characters(s);
	vector<int> classy = compute_char_classes(s, order);
	vector<int> doubled_sorted = sort_doubled(s,1,order,classy);
	vector<int> new_class = update_classes(doubled_sorted,classy,1);

	vector<int> suffix_array = build_suffix_array(s);
	

	print_vector(order);	
	print_vector(classy);
	print_vector(doubled_sorted);
	print_vector(new_class);
	print_vector(suffix_array);

}