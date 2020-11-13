#include <iostream>

long long pisano_period(long long m){

    long long currentFib = 1;
    long long previousFib = 0;
    long long pisanoPeriod = 0;

    do{
	long long temp;

	temp = (currentFib + previousFib) % m;
	previousFib = currentFib;
	currentFib = temp;
	
	pisanoPeriod++;
	
    }while(previousFib != 0 || currentFib != 1);
  
    return pisanoPeriod;
}

long long fibonacci_fast(long long n, long long m) {
    
    long long sequence[2] = {0, 1};
    long long nextNumber = 0;

    if(n <= 1)
	return n;    
    
    for(int i = 2; i <= n; i++){
	nextNumber = (sequence[0] + sequence[1]) % m;
	sequence[0] = sequence[1];
	sequence[1] = nextNumber;
    }
  
    return nextNumber;
}


long long get_fibonacci_huge_fast(long long n, long long m) {

    long long result = 0;
    
    n = n % pisano_period(m);
    result = fibonacci_fast(n, m);
    
    return result;
}

long long fibonacci_sum_squares_fast(long long  n) {

    long long fib_current = get_fibonacci_huge_fast(n,10);
    long long fib_next = get_fibonacci_huge_fast(n+1,10);
     
    return (fib_next*fib_current) % 10;
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_squares_fast(n);
}
