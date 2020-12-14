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

unordered_map<string, char> hct_to_decode_table(string filename) {
  unordered_map<string, char> huffman_decode_table;
  ifstream fin_hct((filename+".hct").c_str());
  char ch, _; string hcode;
  int l;
  fin_hct >> l;
  // 修复无法读取空白字符的问题
  while (fin_hct >> noskipws >> _ >> ch >> _ >> hcode) {
    if (ch == REPLACE_SLASH_N)
      huffman_decode_table[hcode] = '\n';
    else
      huffman_decode_table[hcode] = ch;
  }
  fin_hct.close();
  return huffman_decode_table;
}

string hcb_to_cp_string(string filename, int length) {
  string cp_original = "";
  FILE *fp = fopen((filename+".hcb").c_str(), "rb");  // 使用二进制方式打开才能不在遇到 SUB 时跳回文件开头
  //TODO: 这里读取定长字符串, 不知道在二进制方式下改为 while(!feof()) 能不能正常运作
  for (int i = 0; i < length / CHAR_ACTUAL_BITS + 1; i++) {
    cp_original += fgetc(fp);
  }
  fclose(fp);
#ifdef _DEBUG_CP_STR
      ofstream ob1("a.txt.ob1.txt");
      ob1 << cp_original << endl;
      ob1.close();
#endif
  return cp_original;
}

int valid_bit_length(string filename) {
  ifstream fin_hct((filename+".hct").c_str());  
  int l;
  fin_hct >> l;
  fin_hct.close();
  return l;
}
