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
// 通过前序遍历 Huffman Tree 的方式
void print_codes(struct MinHeapNode *root, std::string str = "");

// 创建 Huffman 树
struct MinHeapNode* frequency_to_huffman_tree(freq_hashmap char_freq);
