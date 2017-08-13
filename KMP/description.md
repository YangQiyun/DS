# Data-Structure-KMP

参考[KMP算法的Next数组详解](http://www.cnblogs.com/tangzhengyue/p/4315393.html)



- 外层的遍历KMP的函数 KMP(string str,string key);
- 核心是失败函数的建立过程
	- 个人理解：某一位置的失败数组的值k，表示当前位置不相等的时候，跳转到key[k]重新进行判断，这样节约了中间j-k判断时间
	- 编写失败数组的时候，相当于进行数学归纳的过程，通过key[j]和key[k]进行判断，则可以改写j+1的失败数值。这是第一步比较概括，第二步可以进行优化失败函数，当Key[j+1]==key[k+1]则j+1的失败数值按第一步计算出来后实际还是会造成无用功，所以该值替换为k+1的失败数值。
	- 这个图会很好的理解![](http://i.imgur.com/5W1IiB6.png)