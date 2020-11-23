#include <iostream>
#include <vector>

using namespace std;

vector<int> optimal_summands(int n) {
    vector<int> summands;
    int current_number = 1;
    int remainder;

    while (n != 0) {
	remainder = n - current_number;
	if(remainder > current_number || remainder == 0){

	    summands.push_back(current_number);
	    n = n - current_number;
	}

	current_number++;	
    }
	
      
    return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
