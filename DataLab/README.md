# Data Lab

位运算中几个巧妙的方法



有一个数x, 当x为0的时候返回0, 不为0的时候返回一

``` C++
return !!x;
```



用一位来表示多个位的信息

``` C++
x = x & (x >> 16);	// x0 = x0 & x16
x = x & (x >> 8);	// x0 = x0 & x16 & x8 & x24
x = x & (x >> 4);	// x0 = x0 & x16 & x8 & x24 & x4 & x 12 & x20 & 28
x = x & (x >> 2);
x = x & (x >> 1);
```



表示两个数相同, 如判断x和0xff是否相同, 相同的话返回1

``` C++
return !(x ^ 0xff);
```

