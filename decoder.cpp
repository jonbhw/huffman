#include "decoder.hpp"

#include <iostream>

#include "constant.hpp"

using namespace std;

string decode_string(string encoded, unordered_map<string, char> table) {
  string result = "";
  int i = 0;
  for (int j = 0; j < encoded.length(); j++) {
    string substr = encoded.substr(i, j-i+1);
    if (table.find(substr) == table.end()) {
      continue;
    }
    // 此01串有对应的字符
    else {
      result += table[substr];
      i = j + 1;
    }
  }
  return result;
}

string compressed_char_string_to_zero_and_one_string(string cstr) {
  string result = "";
  for (int i = 0; i < cstr.length(); i++) {
    result += char_to_zero_and_one_string(cstr[i]);
  }
  return result;
}

string char_to_zero_and_one_string(char ch) {
  bitset<sizeof(char)*CHAR_ACTUAL_BITS> b(ch);
  return b.to_string();
}
