#include "constant.hpp"
#include "encoder.hpp"
#include "decoder.hpp"

#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;

int main(int argc, char const *argv[]) {
  // 命令行参数错误
  if (argc != 2) {
    cout << "[ERROR] Argument Error: expected 1 but received " << argc-1 << endl;
    cout << "Press any key to quit..." << endl;
    getchar();
    return 0;
  }
  string filename = argv[1];  // 待操作的文件名(包括扩展名)
  string extension_name = filename.substr(filename.length()-3, 3);  // 提取文件扩展名(认为扩展名长度为 3)
  if (extension_name == "hcb" || extension_name == "hcs") {
    // 去掉文件名中的后缀
    filename = filename.substr(0, filename.length()-4);

    /* 读取 Huffman 解码表 */
    int length = valid_bit_length(filename);
    unordered_map<string, char> huffman_decode_table = hct_to_decode_table(filename, length);

    /* 解码二进制存储的压缩文件 */
    if (extension_name == "hcb") {
      string cpstr = hcb_to_cp_string(filename);
      string bitstr = compressed_char_string_to_zero_and_one_string(cpstr);
      bitstr = bitstr.substr(0, length);  // 截取有效比特
      string result = decode_string(bitstr, huffman_decode_table);
      /* 解码结果写入文件 */
      ofstream ob((filename+".b.txt").c_str());
      ob << result;
      ob.close();
    }
    /* 解码 01 字符串存储的压缩文件 */
    else if (extension_name == "hcs") {
      ifstream fin_hcs((filename+".hcs").c_str());
      string bitstr = "";
      fin_hcs >> bitstr;
      fin_hcs.close();
      bitstr = bitstr.substr(0, length);
      string result = decode_string(bitstr, huffman_decode_table);
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