#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void move_rest(vector<int> &destination, int i_destination, vector<int> &source, int i_source){

    while (i_destination < destination.size()){
	destination[i_destination] = source[i_source];
	i_destination++;
	i_source++
    }
}


vector<int> merge(vector<int> b, vector<int> c){
    vector<int> d (b.size() + c.size(), 0);
    int i_c = 0, i_b = 0, i_d = 0;

    while ((i_c <= c.size()-1) && (i_b <= b.size()-1) ) {

	if(b[i_b] <= c[i_c]){

	    d[i_d] = b[i_b];
	    i_b++;
	    i_d++;
	    
	}else{

	    d[i_d] = c[i_c];
	    i_c++;
	    i_d++;
	    
	}
    }

    if(i_c <= c.size()-1){
	move_rest(d, i_d, c, i_c);
    }else if(i_b <= b.size()-1){
	move_rest(d, i_d, b, i_b);
    }

    return d;
}

vector<int> merge_sort(vector<int> &a, int left, int right){

    if(right == 1){
	return a;
    }
    int mid = right/2;
    vector<int> b = merge_sort(a, left, mid);
    vector<int> c = merge_sort(a, mid + 1, right);
    vector<int> a_prime = merge(b, c);

    return a_prime;   
}

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return a[left];
  
  
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
