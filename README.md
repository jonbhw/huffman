# Huffman 编解码

一个基于 Huffman Tree 的文本文件压缩解压器，系课程「数据结构及其算法」（210070）实验 3 之成品。

## 附录

### 致谢

感谢 [@hexclover](https://github.com/hexclover) 耐心解答数个有关 C++ 语言的疑问，部分有意思的讨论附在下方。

#### 对于 C++ 一些特性的讨论/记录

> [@hexclover](https://github.com/hexclover)：将函数返回值（unordered_map 类型）作为变量的初始值时，编译器会做相应优化，避免复制一份 unordered_map。

<small>下图由 @hexclover 提供。</small>

<img src="https://cdn.jsdelivr.net/gh/jonbgua/jonbgua-com-picbed@master/20201030203935.jpg" style="zoom:33%;" />

> 含有默认参数的形参在声明中必须放最后，且在 声明 / 定义 中选其一定义默认参数即可。

- [C++ 函数的默认参数补充 - cnblogs](https://www.cnblogs.com/chenke1731/p/9651275.html)
- [解决 Error: default argument given for parameter 2 of {FUNCTION}... 错误 - CSDN](https://blog.csdn.net/weixin_36888577/article/details/79872036)

### 参考资料

- [实验 3：Huffman 编码和解码 - 数据结构及其算法实验](http://staff.ustc.edu.cn/~dongeliu/dsa/exp3.html)
- [Huffman Coding | Greedy Algo-3 - GeeksforGeeks](https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/)
- [unordered_map in C++ STL - GeeksforGeeks](https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/)
- [priority_queue - C++ Reference](http://www.cplusplus.com/reference/queue/priority_queue/)
- 《C++ Primer Plus（第6版）中文版》
- [maxtors / Huffman - GitHub](https://github.com/maxtors/Huffman/blob/master/Huffman.cpp#L182)
- [C++ 将一个数值转化为二进制字符串 - CSDN](https://blog.csdn.net/chuoyunfei4184/article/details/100980312)
- [Read whole ASCII file into C++ std::string](https://www.tutorialspoint.com/Read-whole-ASCII-file-into-Cplusplus-std-string)
- [ASCII - Wikipedia](https://zh.wikipedia.org/wiki/ASCII)
- [C++ “noskipws” is not working as expected, How to properly allow whitespace in string?](https://stackoverflow.com/questions/59904251/c-noskipws-is-not-working-as-expected-how-to-properly-allow-whitespace-in-s)
- [C 语言 getchar() 与 EOF 的关系究竟是怎样的？- 邱昊宇的回答 - 知乎](https://www.zhihu.com/question/278363419/answer/401653803)
- [How can we detect SUB character in a file?](https://stackoverflow.com/questions/23632640/how-can-we-detect-sub-character-in-a-file)
