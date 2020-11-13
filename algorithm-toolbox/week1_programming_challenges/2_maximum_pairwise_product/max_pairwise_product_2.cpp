#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long MaxPairwiseProduct(vector<long long> &numbers) {
    long long max_product = 0;

    sort(numbers.begin(), numbers.end(), greater<int>());
    max_product = numbers[0]*numbers[1];
    
    return max_product;
}


int main(){

    int n;
    cin >> n;
    vector<long long> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    cout << MaxPairwiseProduct(numbers) << "\n";   
    
    return 0;
}
