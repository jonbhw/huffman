#include "constant.hpp"
#include "encoder.hpp"
#include "decoder.hpp"

#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    cout << "[ERROR] lack of argument(s)" << endl;
    cout << "Press any key to quit..." << endl;
    getchar();
  }
  string filename = argv[1];
  string extension_name = filename.substr(filename.length()-3, 3);
  if (extension_name == "hcb" || extension_name == "hcs") {
    // 去掉文件名中的后缀
    filename = filename.substr(0, filename.length()-4);
    /* 读取 Huffman 解码表 */
    unordered_map<string, char> huffman_decode_table;
    ifstream fin_hct((filename+".hct").c_str());
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

    if (extension_name == "hcb") {
      string original = "";
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
      original = compressed_char_string_to_zero_and_one_string(cp_original);
      original = original.substr(0, length);
      string result = decode_string(original, huffman_decode_table);
      ofstream ob((filename+".b.txt").c_str());
      ob << result << endl;
      ob.close();
    }
    else if (extension_name == "hcs") {
      ifstream fin_hcs((filename+".hcs").c_str());
      string original = "";      
      original = "";
      fin_hcs >> original;
      fin_hcs.close();
      original = original.substr(0, length);
      string result = decode_string(original, huffman_decode_table);
      ofstream os((filename+".s.txt").c_str());
      os << result << endl;
      os.close();
    }
  }
  else if (extension_name == "hct") {
    cout << "[ERROR] Please drag in *.hcb or *.hcs file" << endl;
    cout << "Press any key to quit..." << endl;
    getchar();
  }
  else {
    huffman_encode(filename.c_str());
  }

  return 0;
}