#include <iostream>

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

//Calculate fibonacci last digit
int get_fibonacci_last_digit_fast(int n) {
    
    int sequence[2] = {0, 1};
    int nextNumber = 0;

    if(n <= 1)
	return n;    
    
    for(int i = 2; i <= n; i++){
      
	nextNumber = (sequence[0] + sequence[1]) % 10;
	sequence[0] = sequence[1];
	sequence[1] = nextNumber;
    }
    return nextNumber;
}

int main() {
    int n;
    std::cin >> n;
    //int c = get_fibonacci_last_digit_naive(n);
    int c = get_fibonacci_last_digit_fast(n);
    std::cout << c << '\n';
}
