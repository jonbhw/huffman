#include "constant.hpp"
#include "encoder.hpp"
#include "decoder.hpp"

#include <iostream>
#include <sstream>

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
  ifstream fin_hcb("a.txt.hcb");
  string cp_original = "";
  if (fin_hcb) {
    ostringstream ss;
    /*
      FIXME:
      这里的 .rdbuf() 有个严重的问题,
      遇到 SUB 字符时(ASCII = 26), 会停下来, 导致其后的字符均无法成功 dump 进 cp_original 内.
      酱瓜临时用加一个 SUB_RDBUF_OFFSET 的方式,
      使得写入 hcb 文件的 ASCII 从 SUB 后开始来解决,
      但这样会浪费相当的存储空间(基本上只用了 7bits/8bits).
      未来可将此处的读入换成 C 语言的 getchar(), 从而可以将 OFFSET 重置为 0, CHAR_ACTUAL_BITS 设为 8,
      充分利用 8 bits 的存储.
     */
    ss << fin_hcb.rdbuf();
    cp_original = ss.str();
  }
  fin_hcb.close();
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