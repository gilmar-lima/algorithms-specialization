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

    //cout << "Pisano period: " << pisanoPeriod << endl;
    
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


int fibonacci_sum_fast(long long n){

    int result = get_fibonacci_huge_fast(n + 2, 10) - 1;

    if(result == -1){
	result = 9;
    }

    return result;
}

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_fast(n);
}
