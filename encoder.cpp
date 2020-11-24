#include "encoder.hpp"

#include <iostream>
#include <sstream>
#include <stdio.h>

#include "constant.hpp"

using namespace std;

freq_hashmap text_file_to_frequency_hashmap(string filename) {
  freq_hashmap char_freq;
  char ch;
  ifstream fin;
  fin.open(filename.c_str());

  while (fin.get(ch)) {
    char_freq[ch]++;
  }

  fin.close();
  return char_freq;
}

struct MinHeapNode* frequency_to_huffman_tree(freq_hashmap char_freq) {
  // 先将哈希表的数据转换成一个个叶子节点存入优先队列中, 并把低频的放到前面
  // 然后逐一合并节点, 构建 Huffman 树

  // 先创建所有叶子节点
  struct MinHeapNode *left, *right, *top;
  priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> min_heap;

  // 将哈希表转换成叶子节点
  for (auto itr : char_freq) {
    min_heap.push(new MinHeapNode(itr.first, itr.second));
  }
  
  // 构建 Huffman 树
  while (min_heap.size() != 1) {
    left = min_heap.top();
    min_heap.pop();
    right = min_heap.top();
    min_heap.pop();
    //TODO: 之后这个 dollar 号要换掉的
    top = new MinHeapNode('$', left->freq + right->freq);
    top->left = left;
    top->right = right;
    min_heap.push(top);
  }

  return min_heap.top();
}

void print_codes(struct MinHeapNode *root, std::string str) {
  if (!root) return;
  //TODO: 之后这个 dollar 号要换掉的
  if (root->data != '$')
    cout << root->data << " : " << str << "\n";
  print_codes(root->left, str+"0");
  print_codes(root->right, str+"1");
}

unordered_map<char, std::string> huffman_encode_table(struct MinHeapNode *root) {
  unordered_map<char, std::string> result;
  huffman_encode_table_helper(root, result);
  return result;
}

void huffman_encode_table_helper(struct MinHeapNode *root, unordered_map<char, std::string> &result, std::string str) {
  if (!root) return;
  //TODO: 之后这个 dollar 号要换掉的
  if (root->data != '$')
      result[root->data] = str;
  huffman_encode_table_helper(root->left, result, str+"0");
  huffman_encode_table_helper(root->right, result, str+"1");
}

string huffman_encode_string_to_string(string original) {
  string encoded = "";
  freq_hashmap char_freq = string_to_frequency_hashmap(original);
  struct MinHeapNode* huffman_tree = frequency_to_huffman_tree(char_freq);
  unordered_map<char, std::string> ascii_code_table = huffman_encode_table(huffman_tree);

  for (int i = 0; i < original.size(); i++) {
    encoded += ascii_code_table[original[i]];
  }
  return encoded;
}

freq_hashmap string_to_frequency_hashmap(string text) {
  freq_hashmap char_freq;
  for (int i = 0; i < text.size(); i++) {
    char_freq[text[i]]++;
  }
  return char_freq;
}

void huffman_encode(string filename) {
  string original = "";
  ifstream fin(filename.c_str());
  if (fin) {
    ostringstream ss;
    ss << fin.rdbuf();
    original = ss.str();
  }

  string result = "";
  freq_hashmap char_freq = string_to_frequency_hashmap(original);
  struct MinHeapNode* huffman_tree = frequency_to_huffman_tree(char_freq);
  unordered_map<char, std::string> ascii_code_table = huffman_encode_table(huffman_tree);
  for (int i = 0; i < original.size(); i++) {
    result += ascii_code_table[original[i]];
  }

  ofstream out_huffman_table(filename + ".hct");
  out_huffman_table << result.length() << "\n";
  for (auto i: ascii_code_table) {
    // 写入文件时将换行符用一个约定的不可打印字符替换掉, 方便之后的读入操作
    if (i.first == '\n') {
      out_huffman_table << (char)REPLACE_SLASH_N << " " << i.second << "\n";
    }
    else
      out_huffman_table << i.first << " " << i.second << "\n";
  }
  out_huffman_table.close();

  ofstream out_encoded_string(filename + ".hcs");
  out_encoded_string << result;
  out_encoded_string.close();

  ofstream out_binary(filename + ".hcb");
  string temp = zero_and_one_string_to_compressed_char_string(result);
  FILE *fp = fopen((filename+".hcb").c_str(), "wb");
  for (int i = 0; i < temp.length(); i++) {
    fputc(temp[i], fp);
  }
  fclose(fp);
  out_binary.close();
}

string zero_and_one_string_to_compressed_char_string(string bitstr) {
  /* 
    压缩字符串就是说, 比如一个 char 占 8 bits, 
    那么我就可以把 bitstr 里的 0100 0001 (十进制下是 65) 这 8 bits 转化为 'A', 放入压缩字符串中, 以此类推.
   */
  
  const int CHAR_SIZE = sizeof(char) * CHAR_ACTUAL_BITS;
  // 预处理 bitstr, 使其长度为 CHAR_SIZE 的整数倍
  while (bitstr.length() % CHAR_SIZE) {
    bitstr += "0";
  }
  // 转化开始
  string result = "";
  int j = 0; char ch;
  for (int i = 0; i < bitstr.length(); i += CHAR_SIZE) {
    ch = 0;
    for (j = 0; j < CHAR_SIZE; j++) {
      ch = ch * 2 + bitstr[i+j] - '0';
    }
    result += ch + SUB_RDBUF_OFFSET;
  }
  return result;
}
