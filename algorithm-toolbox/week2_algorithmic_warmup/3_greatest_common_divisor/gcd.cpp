#include <iostream>
#include <algorithm>

using namespace std;

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_fast(int a, int b) {

  int greater = max(a,b);
  int minor = min(a,b);
  int remainder = greater % minor;

  while (remainder != 0) {
    
    greater = minor;
    minor = remainder;
    remainder = greater % minor;
    
  }

  return minor;  
}


int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd_fast(a, b) << std::endl;
  return 0;
}
