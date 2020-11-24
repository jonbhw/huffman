#include "constant.hpp"
#include "encoder.hpp"
#include "decoder.hpp"

#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;

int main(int argc, char const *argv[]) {
  huffman_encode("a.txt");
  unordered_map<string, char> huffman_decode_table;
  ifstream fin_hct("a.txt.hct");
  char ch, _; string hcode;
  int length;
  fin_hct >> length;
  // 修复无法读取空白字符的问题
  while (fin_hct >> noskipws >> _ >> ch >> _ >> hcode) {
    if (ch == REPLACE_SLASH_N)
      huffman_decode_table[hcode] = '\n';
    else
      huffman_decode_table[hcode] = ch;
  }
  fin_hct.close();

  string original = "";
  string cp_original = "";
  FILE *fp = fopen("a.txt.hcb", "rb");  // 使用二进制方式打开才能不在遇到 SUB 时跳回文件开头
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
  original = compressed_char_string_to_zero_and_one_string(cp_original);
  original = original.substr(0, length);
  string result = decode_string(original, huffman_decode_table);
  ofstream ob("a.txt.ob.txt");
  ob << result << endl;
  ob.close();

  ifstream fin_hcs("a.txt.hcs");
  original = "";
  fin_hcs >> original;
  fin_hcs.close();
  original = original.substr(0, length);
  result = "";
  result = decode_string(original, huffman_decode_table);
  ofstream os("a.txt.os.txt");
  os << result << endl;
  os.close();

  return 0;
}