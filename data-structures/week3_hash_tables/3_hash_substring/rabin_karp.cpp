// Rabin-Karp algorithm in C++

#include <string.h>

#include <iostream>
using namespace std;

#define random_integer 10

void rabinKarp(char pattern[], char text[], int prime_number) {
  int pattern_length = strlen(pattern);
  int text_length = strlen(text);
  int i, j;
  int pattern_hash = 0;
  int text_hash = 0;
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
        cout << "Pattern is found at position: " << i << endl;
    }

    if (i < text_length - pattern_length) {
      text_hash = (random_integer * (text_hash - text[i] * h) + text[i + pattern_length]) % prime_number;

      if (text_hash < 0)
        text_hash = (text_hash + prime_number);
    }
  }
}

int main() {
  char text[] = "testTesttesT";
  char pattern[] = "Test";
  int prime_number = 13;
  rabinKarp(pattern, text, prime_number);
}