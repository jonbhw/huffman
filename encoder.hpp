#ifndef JONBGUA_UNORDERED_MAP
#define JONBGUA_UNORDERED_MAP
#include <unordered_map>
#endif

#ifndef JONBGUA_FSTREAM
#define JONBGUA_FSTREAM
#include <fstream>
#endif

#ifndef JONBGUA_QUEUE
#define JONBGUA_QUEUE
#include <queue>
#endif

#ifndef JONBGUA_BITSET
#define JONBGUA_BITSET
#include <bitset>
#endif

#ifndef JONBGUA_MINHEAPNODE
#define JONBGUA_MINHEAPNODE
struct MinHeapNode {
  char data;
  unsigned freq;
  MinHeapNode *left, *right;

  MinHeapNode(char data, unsigned freq) {
    left = right = NULL;
    this->data = data;
    this->freq = freq;
  }
};
#endif

struct compare {
  bool operator() (MinHeapNode *left, MinHeapNode *right) {
    return (left->freq > right->freq);
  }
};

#ifndef JONBGUA_FREQ_HASHMAP
#define JONBGUA_FREQ_HASHMAP
typedef std::unordered_map<char, int> freq_hashmap;
#endif

// 从文件流读入文本, 并据此生成一个 "字符-频次" 对应的哈希表 (类似 Python 中的字典)
freq_hashmap text_file_to_frequency_hashmap(std::string filename);

// 输出 Huffman 编码对照表
// 通过前序遍历 Huffman 树的方式
void print_codes(struct MinHeapNode *root, std::string str = "");

// 创建 Huffman 树
struct MinHeapNode* frequency_to_huffman_tree(freq_hashmap char_freq);

// 创建 ASCII 字符 -> Huffman 编码 的一一对应表
std::unordered_map<char, std::string> huffman_encode_table(struct MinHeapNode *root);

// 在 huffman_encode_table() 内实现遍历 Huffman 树的助手函数
//TODO: 事实上应该把这两个打包成一个类
void huffman_encode_table_helper(
                                  struct MinHeapNode *root,
                                  std::unordered_map<char, std::string> &result,
                                  std::string str = ""
                                );

// 将原文字符串转为 Huffman 编码后的字符串(只包含 0 和 1)
std::string huffman_encode_string_to_string(std::string original);

// 从字符串生成 字符-频次 对应表
freq_hashmap string_to_frequency_hashmap(std::string text);

// 执行 Huffman 编码
void huffman_encode(std::string filename);

/* 
  将只含 0 和 1 的字符串转化为「压缩字符串」。
  @param bitstr 只含 0 和 1 的字符串
  @return 压缩字符串
 */
std::string zero_and_one_string_to_compressed_char_string(std::string bitstr);
