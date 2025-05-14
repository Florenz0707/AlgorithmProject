# 文件读取提示

以**c**开头的行表示注释（comment），在读取时可以忽略。

以**p edge**开头的行含有两个参数（preamble），先后表示点数和边数。

以**e**开头的行含有两个参数（edge），表示a和b之间有一条无向边。

# 示例

```
c File:  hamming8-4.clq
c
c Source: Panos Pardalos pardalos@math.ufl.edu
c
c Reference: hamminga-b is a Hamming graph on a-bit words with
c            an edge if and only if the two words are at least
c            hamming distance b apart
c
p edge 256 20864
e 9 8
e 10 7
e 11 6
e 12 5
e 13 4
e 14 3
e 15 2
e 16 1
e 17 8
```
