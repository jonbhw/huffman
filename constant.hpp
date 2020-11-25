#ifndef CHAR_ACTUAL_BITS
#define CHAR_ACTUAL_BITS 8
#endif

#ifndef REPLACE_SLASH_N
#define REPLACE_SLASH_N 7
#endif

//TODO: 历史遗留问题, 可以删去, 详见 Commit ID: ee9a6dfe0f01931c70d0d0d85b00a7f86edab554
#ifndef SUB_RDBUF_OFFSET
#define SUB_RDBUF_OFFSET 0
#endif

// 默认关闭 .hcs 格式输出(即01字符串输出)
#ifndef BITSTR_OUTPUT_FILE
#define BITSTR_OUTPUT_FILE 0
#endif