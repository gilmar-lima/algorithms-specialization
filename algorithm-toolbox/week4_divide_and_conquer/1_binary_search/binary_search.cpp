#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int binary_search(const vector<int> &a,int left ,int right ,int key) {
    int mid;
    
    if(right < left){
	return -1;
    }

    mid = left + (right - left)/2;

    if(key == a[mid]){
	return mid;
    }else if(key < a[mid]){
	return binary_search(a,left, mid - 1, key);
    }else{
	return binary_search(a, mid + 1, right, key);
    }
}
int linear_search(const vector<int> &a, int x) {
    for (size_t i = 0; i < a.size(); ++i) {
	if (a[i] == x) return i;
    }
    return -1;
}

int main() {
    int n, m;
    int left = 0, right;
    
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
	std::cin >> a[i];
    }

    right = (int)a.size() - 1;
    
    std::cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
	std::cin >> b[i];
    }
    
    for (int i = 0; i < m; ++i) {
	cout << binary_search(a, left, right, b[i]) << ' ';
    }
}
