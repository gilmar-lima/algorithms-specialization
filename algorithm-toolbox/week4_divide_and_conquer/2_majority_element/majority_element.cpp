#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int get_majority_element(vector<int> &a, int left, int right) {
    if (left == right) return -1;
    if (left + 1 == right) return a[left];

    sort(a.begin(), a.end());

    int current_element = a[left];
    int counter = 0;
    int half = right/2;
    
    while(left < right){

	if(current_element == a[left]){
	    counter++;
	    if(counter > half) return current_element;
	}else{
	    current_element = a[left];
	    counter = 1;	    
	}

	left++;	    
    }
      
    return -1;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
	cin >> a[i];
    }
    cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
