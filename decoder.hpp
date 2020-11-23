#ifndef JONBGUA_UNORDERED_MAP
#define JONBGUA_UNORDERED_MAP
#include <unordered_map>
#endif

#ifndef JONBGUA_BITSET
#define JONBGUA_BITSET
#include <bitset>
#endif

#ifndef JONBGUA_FSTREAM
#define JONBGUA_FSTREAM
#include <fstream>
#endif

/* 
  从 .hct 文件中读取 Huffman 解码表
  @param filename 不包含 .hct 的文件名
  @return 字符串->字符对应表
 */
std::unordered_map<std::string, char> huffman_decode_table(std::string filename);

/* 
  读取二进制 .hcb 文件并将其转换为字符串
  @param filename 不包含 .hcb 的文件名
  @return 只包含 0 和 1 的字符串
 */
std::string hcb_to_string(std::string filename);

/* 
  利用 Huffman 解码表解码字符串
  @param encoded Huffman 编码后的字符串(只包含 0 和 1)
  @param table Huffman 解码表
  @return 解码后的文本字符串
 */
std::string decode_string(std::string encoded, std::unordered_map<std::string, char> table);

/* 
  执行 Huffman 解码，并将结果写入文件
  @param filename 不包含 .hcb 或 .hct 后缀的文件名
 */
void huffman_decode(std::string filename);
