# Data-Structure-BM

参考[grep之字符串搜索算法Boyer-Moore由浅入深（比KMP快3-5倍）](http://www.cnblogs.com/lanxuezaipiao/p/3452579.html)
[Boyer-Moore algorithm](http://www-igm.univ-mlv.fr/~lecroq/string/node14.html)


在用于查找子字符串的算法当中，BM（Boyer-Moore）算法是目前相当有效又容易理解的一种，一般情况下，比KMP算法快3-5倍。
BM算法在移动模式串的时候是从左到右，而进行比较的时候是从右到左的。


BM的主要思想是运用了两个规则
1. 坏字符
2. 好后缀

每一步的向后移动是通过这两个规则中最大的一种来进行的，其中坏字符比较简单，就是直接利用一个256的字符数组存储出现该字符的最后一次离m-1的位置距离，其中不计算模式串的最后一个字符因为会产生负数。

好后缀主要三种情况，一种是没有出现好后缀，第二种是好后缀出现在开头，第三种是出现的中间，由于我们移动的时候是移动最近的一个好后缀出现的位置，同时第三种具有特殊性，只针对某一个位置失配的时候才有，所以求好后缀的数组的时候先是计算第一种，然后是第二种，第三种可以对前面计算出来的值进行覆盖，它只是针对特殊的相关的位置。

最后进行移动的过程，外层是便利j对测试串进行++，然后每一步进行从后面开始匹配，当有匹配到-1时找到，没有到达-1停止的时候进行根据BM的最大移动距离进行移动。
