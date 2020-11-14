#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int get_change(int m) {

    const int value [3] = {10,5,1};
    vector<int> number_of_coins;
    int division_result;
    
    for(int i = 0; i <= 2; i++){

      division_result = m / value[i];
      m = m % value[i];
      
      number_of_coins.push_back( division_result ); 
    }
    
    return accumulate(number_of_coins.begin(), number_of_coins.end(),0);
}

int main() {
    int m;
    cin >> m;
    cout << get_change(m) << '\n';
}
