#include "decoder.hpp"

#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
  ifstream fin_hcs("a.txt.hcs");
  string original = "";
  fin_hcs >> original;
  fin_hcs.close();

  unordered_map<string, char> huffman_decode_table;
  ifstream fin_hct("a.txt.hct");
  char ch; string hcode;
  int length;
  fin_hct >> length;
  while (fin_hct >> ch >> hcode) {
    huffman_decode_table[hcode] = ch;
  }
  fin_hct.close();

  string result = decode_string(original, huffman_decode_table);
  cout << result;

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
