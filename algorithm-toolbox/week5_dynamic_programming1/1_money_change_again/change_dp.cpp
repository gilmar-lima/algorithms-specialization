#include <iostream>
#include <vector>

using namespace std;

int get_change(int money) {
    
    vector<int> coins = {1,3,4};
    vector<int> min_num_coins (money + 1,0);
    int num_coins = 0;
    
    for(int m = 1; m <= money; m++){
	min_num_coins[m] = money + 1;

	for(int coin : coins){
	    if (m >= coin){
		num_coins = min_num_coins[m - coin] + 1;
		if (num_coins < min_num_coins[m]){
		    min_num_coins[m] = num_coins;
		}
	    }	    
	}

    }
        
    return min_num_coins[money];
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
