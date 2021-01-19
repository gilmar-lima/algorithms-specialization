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

long long poly_hash(string& text, int& prime_number, int& random_integer){

    long long hash_value = 0;

    for (int i = 0; i < text.length(); i++) {
        hash_value = (random_integer * hash_value + text[i]) % prime_number;        
    }

    return hash_value;
}

vector<long long> pre_compute_hashes(string& text, int length_pattern, int& prime_number, int& random_integer){

    vector<long long> hash_values (text.length() - length_pattern + 1); 
    
    string sub_string = text.substr(text.length() - length_pattern, text.length());
    hash_values[text.length() - length_pattern] = poly_hash(sub_string, prime_number, random_integer);
    
    long long y = 1;
    for (size_t i = 1; i <= length_pattern; i++) {
        y = (y*random_integer)%prime_number;
    }

    for (int i = text.length() - length_pattern - 1; i >= 0; i--)
    {
        int ascii = text[i];
        hash_values[i] = (((random_integer*hash_values[i+1] + text[i] - y*text[i + length_pattern -1]) % prime_number) + prime_number)%prime_number ;
    }

    return hash_values;
}

vector<int> rabin_karp(string text, string pattern)
{
    int prime_number = 7069;
    int random_integer = 7000;

    vector<int> result;
    long long p_hash = poly_hash(pattern, prime_number,random_integer);
    vector<long long> hash_values = pre_compute_hashes(text, pattern.length(), prime_number, random_integer);

    for (size_t i = 0; i <= (text.length() - pattern.length()); i++)
    {
        if(p_hash != hash_values[i]) continue;
        
        if(text.substr(i, pattern.length()) == pattern) result.push_back(i);
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
