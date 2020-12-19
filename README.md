# Huffman 编解码

一个基于 Huffman Tree 的文本文件压缩解压器，系课程「数据结构及其算法」（210070）实验 3 之成品。

[项目地址](https://github.com/JiangGua/210070-huffman) | [国内镜像 (Gitlab@LUG)](https://git.lug.ustc.edu.cn/JiangGua/210070-huffman) | [下载地址](https://github.com/JiangGua/210070-huffman/releases/latest) | [下载地址 (国内)](https://git.lug.ustc.edu.cn/JiangGua/210070-huffman/-/releases)



## 使用方法

### Windows

#### 编码（压缩）

将需要压缩的文本文件拖拽到本程序的程序图标上（比如是 `huffman.exe`），松开鼠标，程序会在文本文件所在目录下生成 `*.hcb` 和 `*.hct` 两个文件，前者为二进制压缩后的文件，后者为 Huffman 解码表。

可能会生成 `*.hct.txt` 文件（随 `constant.hpp` 中的设置不同而变化），此为 Huffman 树的可视化输出。

#### 解码（解压缩）

将 `*.hcb` 和 `*.hct` 两个文件放在同一目录下，将 `*.hcb` 文件拖拽到本程序的程序图标上，程序会在文件所在目录下生成 `*.b.txt` 文件，意即「从二进制压缩后的文件解码而来的文本文件」。

`*.b.txt` 文件内容应与原来的 `*.*` 的内容完全一致。

#### 动图演示

如果您是 PDF 阅读者，可以 [在这里下载 [GIF]](https://cdn.jsdelivr.net/gh/jonbgua/jonbgua-com-picbed@master/20201208215553.gif)。

![Windows 下编解码过程](https://cdn.jsdelivr.net/gh/jonbgua/jonbgua-com-picbed@master/20201208215553.gif)



## 项目结构

本项目依照尽可能模块化的原则构建。

```python
.
├── constant.hpp	# 全局变量
├── main.cpp		# 主程序
├── encoder.hpp		
├── encoder.cpp		# 编码模块
├── decoder.hpp		
├── decoder.cpp		# 解码模块
```



## 实现细节

### 主要数据结构

1. 字符频率表
2. Huffman 树
3. Huffman 编码表
4. Huffman 解码表

#### 字符频率表

```c++
typedef std::unordered_map<char, int> freq_hashmap;
```

一个无序哈希表，类似 Python 的字典。每个字符 `<char>` 对应一个频率 `<int>`。

#### Huffman 树

##### 节点

```c++
struct MinHeapNode {
  // 若为「合成节点」, 则此项为 CHAR_NOT_LEAF_NODE (constant.hpp 中定义)
  char data;
  unsigned freq;
  MinHeapNode *left, *right;

  MinHeapNode(char data, unsigned freq) {
    left = right = NULL;
    this->data = data;
    this->freq = freq;
  }
};
```

##### 节点们

各节点的指针存在一个优先队列中，优先队列按 `freq` 从小到大排序。

#### Huffman 编码表

用于将文本字符串编码为「01 字符串」（只含有 0 和 1 的字符串）。

```c++
std::unordered_map<char, std::string>
```

每个 `<char>` 对应一个只含 0 和 1 的 `<std::string>`（Huffman 编码）。

#### Huffman 解码表

与 Huffman 编码表的作用相反，用于将「01 字符串」解码为文本字符串。

```c++
std::unordered_map<std::string, char>
```



### 运行流程

#### 编码（压缩）

1. 从文件中读入待编码字符串
2. 生成 Huffman 编码表
   1. 生成字符频率表
   2. 生成 Huffman 树
   3. 生成 Huffman 编码表
3. 保存 Huffman 编码表
   1. 将 Huffman 编码表存入文件 `*.hct`（**H**uffman en**C**oding **T**able）
   2. 可视化打印 Huffman 树（`*.hct.txt`）
4. 利用 Huffman 编码表编码
   1. 文本字符串 → 01 字符串
   2. 01 字符串 →「压缩字符串」（01 字符串中每 8 位的 0 和 1 压缩成一个 char 型字符）
5. 保存结果
   1. 「压缩字符串」→ `*.hcb` （**H**uffman en**C**oded **B**inary file）
   2. 「01 字符串」→ `*.hcs` 【默认关闭】（**H**uffman en**C**oded **S**tring file）

#### 解码（解压缩）

从二进制文件 `*.hcb` 解压缩。

1. 从文件中读入
   1. 读取 Huffman 解码表 `*.hct`
   2. 读取 `*.hcb`
2. 利用 Huffman 解码表解码
   1. 「压缩字符串」→ 01 字符串
   2. 01 字符串 → 文本字符串
3. 保存结果
   1. 文本字符串 → `*.b.txt`



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
- [Print binary tree in a pretty way using C++](https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c)
- [几种 MingW 使用记录 - k1988](https://baba.zhaoxiuyuan.com/2017/09/121_mingw_record/)
- [TDM-GCC](https://jmeubank.github.io/tdm-gcc/)
  - 原生支持 32 & 64 位编译，且编译后的程序能在各种平台下运行而不需要配置依赖库。32 位模式编译的程序在 Windows XP SP3 下运行正常。
