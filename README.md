> 目录
- [编程与测试要求](#编程与测试要求)
- [开发手册](#开发手册)
  - [算法说明](#算法说明) 
  - [接口说明](#接口说明)
- [用户指南](#用户指南)
  - [概述](#概述)
  - [操作指南](#操作指南)

# 编程与测试要求  
## 第一关-基本测试
根据S-DES算法编写和调试程序，提供GUI解密支持用户交互。输入可以是8bit的数据和10bit的密钥，输出是8bit的密文。

## 第二关-交叉测试 
考虑到是算法标准，所有人在编写程序的时候需要使用相同算法流程和转换单元(P-Box、S-Box等)，以保证算法和程序在异构的系统或平台上都可以正常运行。设有A和B两组位同学(选择相同的密钥K)；则A、B组同学编写的程序对明文P进行加密得到相同的密文C；或者B组同学接收到A组程序加密的密文C，使用B组程序进行解密可得到与A相同的P。

## 第三关-扩展功能  
考虑到向实用性扩展，加密算法的数据输入可以是ASII编码字符串(分组为1 Byte)，对应地输出也可以是ACII字符串(很可能是乱码)。

## 第四关-暴力破解 
假设你找到了使用相同密钥的明、密文对(一个或多个)，请尝试使用暴力破解的方法找到正确的密钥Key。在编写程序时，你也可以考虑使用多线程的方式提升破解的效率。请设定时间戳，用视频或动图展示你在多长时间内完成了暴力破解。

## 第五关-封闭测试  
根据第4关的结果，进一步分析，对于你随机选择的一个明密文对，是不是有不止一个密钥Key？进一步扩展，对应明文空间任意给定的明文分组P_{n}，是否会出现选择不同的密钥K_{i}\ne K_{j}加密得到相同密文C_n的情况？

# 开发手册
## 算法说明
1.初始置换（IP）: 使用初始置换表（IP）对输入的8位明文进行置换，得到置换后的8位序列。

2.密钥生成: 使用P10对输入的10位密钥进行置换，然后对得到的结果分别进行1位和2位的左移，生成两个子密钥k1和k2。

3.拓展置换（EP-Box）: 对右半部分8位密文进行拓展置换，扩展为12位。 子密钥加轮: 将拓展置换后的12位结果与k1进行异或运算，得到12位结果。

4.S盒置换: 将上一步结果分为两组，分别进行S盒置换。

5.压缩置换: 对S盒置换后的结果进行压缩置换，得到4位结果。

6.直接置换（SP-Box）: 对压缩置换后的4位结果进行直接置换。

7.最终置换（IP^-1）: 将上述结果与初始置换后的4位结果进行异或运算，得到8位加密结果。

3.2解密过程详解

1.初始置换（IP^-1）: 使用逆初始置换表（IP^-1）对输入的8位密文进行置换，得到置换后的8位序列。

2.密钥生成: 使用P10对输入的10位密钥进行置换，然后对得到的结果分别进行1位和2位的左移，生成两个子密钥k1和k2。

3.拓展置换（EP-Box）: 对右半部分8位密文进行拓展置换，扩展为12位。 子密钥加轮: 将拓展置换后的12位结果与k2进行异或运算，得到12位结果。

4.S盒置换: 将上一步结果分为两组，分别进行S盒置换。

5.压缩置换: 对S盒置换后的结果进行压缩置换，得到4位结果。

6.直接置换（SP-Box）: 对压缩置换后的4位结果进行直接置换。

7.最终置换（IP）: 将上述结果与初始置换后的4位密文进行异或运算，得到8位解密结果。

3.3破解过程详解

破解过程是通过暴力破解的方式，尝试所有可能的密钥，直到找到正确的密钥，从而解密密文。具体步骤如下：

1.输入明文和密文。 2.对于每个可能的密钥，使用SDES解密算法对密文进行解密。 3.将解密后的明文与输入的明文进行比较，如果相同，则找到了正确的密钥。 4.输出找到的密钥。

由于SDES算法的密钥长度较短，只有10位，因此可以通过暴力破解的方式尝试所有可能的密钥。但是，随着计算机运算能力的提高，暴力破解的难度也在增加，因此需要使用更加安全的加密算法来保护数据的安全性。

## 接口说明

# 用户指南
## 概述
重庆大学大数据与软件学院信息安全导论作业：S-DES算法的实现，根据老师课堂内容，使用CPP语言完成。
实现了二进制加解密和ASCLL码字符串加解密，以及在已知明密文的前提下暴力破解出密钥等功能。

## 操作指南

