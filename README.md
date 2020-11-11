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
