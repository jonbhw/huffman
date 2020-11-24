#include "decoder.hpp"

#include <iostream>

#include "constant.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  unordered_map<string, char> huffman_decode_table;
  ifstream fin_hct("a.txt.hct");
  char ch; string hcode;
  int length;
  fin_hct >> length;
  while (fin_hct >> ch >> hcode) {
    huffman_decode_table[hcode] = ch;
  }
  fin_hct.close();

  string original = "";
  ifstream fin_hcb("a.txt.hcb");
  string cp_original = "";
  fin_hcb >> cp_original;
  fin_hcb.close();
  original = compressed_char_string_to_zero_and_one_string(cp_original);
  original = original.substr(0, length);
  string result = decode_string(original, huffman_decode_table);
  cout << "FROM binary: " << result << "\n";  

  ifstream fin_hcs("a.txt.hcs");
  original = "";
  fin_hcs >> original;
  fin_hcs.close();
  original = original.substr(0, length);
  result = "";
  result = decode_string(original, huffman_decode_table);
  cout << "FROM string: " << result << "\n";

  return 0;
}

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
