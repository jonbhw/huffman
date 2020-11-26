#ifndef CHAR_ACTUAL_BITS
#define CHAR_ACTUAL_BITS 8
#endif

#ifndef REPLACE_SLASH_N
#define REPLACE_SLASH_N 7
#endif

// 默认关闭 .hcs 格式输出(即01字符串输出)
#ifndef BITSTR_OUTPUT_FILE
#define BITSTR_OUTPUT_FILE 0
#endif

// 输出 Huffman 树的图形化形式
#ifndef PRINT_HUFFMAN_TREE
#define PRINT_HUFFMAN_TREE 1
#endif

// 用来标记此结点非叶子结点的字符
#ifndef CHAR_NOT_LEAF_NODE
#define CHAR_NOT_LEAF_NODE 26
#endif

// 非叶子结点在输出时的占位符 (此配置项仅在 PRINT_HUFFMAN_TREE 设为非零值时有效)
#ifndef PRINT_CHAR_NOT_LEAF_NODE
#define PRINT_CHAR_NOT_LEAF_NODE "☻"
#endif