#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

vector<int> rabin_karp(string text, string pattern) {
    int prime_number = 13;
    int random_integer = 10;

    vector<int> result;
    int pattern_length = pattern.length();
    int text_length = text.length();
    int i, j;
    long long pattern_hash = 0;
    long long text_hash = 0;
    int h = 1;

    for (i = 0; i < pattern_length - 1; i++)
        h = (h * random_integer) % prime_number;

    // Calculate hash value for pattern and text
    for (i = 0; i < pattern_length; i++) {
        pattern_hash = (random_integer * pattern_hash + pattern[i]) % prime_number;
        text_hash = (random_integer * text_hash + text[i]) % prime_number;
    }

    // Find the match
    for (i = 0; i <= text_length - pattern_length; i++) {
        if (pattern_hash == text_hash) {
        for (j = 0; j < pattern_length; j++) {
            if (text[i + j] != pattern[j]) break;
        }

        if (j == pattern_length)
            result.push_back(i);
        }

        if (i < text_length - pattern_length) {
        text_hash = (random_integer * (text_hash - text[i] * h) + text[i + pattern_length]) % prime_number;

        if (text_hash < 0)
            text_hash = (text_hash + prime_number);
        }
    }

    return result;
}


void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    cout << "\n";
}

vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    vector<int> ans;

    ans = rabin_karp(t, s);
    
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
