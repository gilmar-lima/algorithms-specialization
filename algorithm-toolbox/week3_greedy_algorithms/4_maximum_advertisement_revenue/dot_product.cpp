#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long max_dot_product(vector<int> a, vector<int> b) {

    long long result = 0;    
    int temp_i, temp_j;
    long long temp_value, mult;
    int size = a.size();

    for (int n = 0; n < size; n++) {
	
	temp_value = (long long) a[0]*b[0];

	for (size_t i = 0; i < a.size(); i++){
	    for (size_t j = 0; j < b.size(); j++){
		mult = (long long) a[i]*b[j];

		if(mult >= temp_value){
		    temp_value = mult;
		    temp_i = i;
		    temp_j = j;
		}		
	    }
	}

	result = result + temp_value;
	a.erase(a.begin() + temp_i);
	b.erase(b.begin() + temp_j);
    }

    return result;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n), b(n);
    for (size_t i = 0; i < n; i++) {
	std::cin >> a[i];
    }
    for (size_t i = 0; i < n; i++) {
	std::cin >> b[i];
    }
    std::cout << max_dot_product(a, b) << std::endl;
}
