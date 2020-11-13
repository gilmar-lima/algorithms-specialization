#include <iostream>
#include <algorithm>

using namespace std;

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

long gcd_fast(long a, long b) {

  long greater = max(a,b);
  long minor = min(a,b);
  long remainder = greater % minor;

  while (remainder != 0) {
    
    greater = minor;
    minor = remainder;
    remainder = greater % minor;
    
  }

  return minor;  
}

long long lcm_fast(long a, long b){

  long long multiplied = a * b;

  return (multiplied / gcd_fast(a, b));
}

int main() {
  long a, b;
  std::cin >> a >> b;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
