#include <iostream>
#include <vector>

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


long long fibonacci_sum_fast(long long n){

    long long  result = get_fibonacci_huge_fast(n + 2, 10) - 1;

    if(result == -1){
	result = 9;
    }

    return result;
}


long long get_fibonacci_partial_sum_fast(long long from, long long to){

    long long sum_to = fibonacci_sum_fast(to);
    long long sum_from = fibonacci_sum_fast(from - 1);
    long long result;
    
    if(sum_to >= sum_from){
      result = sum_to - sum_from;
    }else{
      result = (sum_to + 10) - sum_from;
    }

    return result;  
}


int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_fast(from,to) << '\n';
}
