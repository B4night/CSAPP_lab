# 环境配置

首先通过下面的命令来安装环境, 此命令出自[知乎博客](https://zhuanlan.zhihu.com/p/454779772)

``` shell
wget https://gitee.com/lin-xi-269/csapplab/raw/master/lab4archlab/archlab-handout/installTclTk.sh && bash installTclTk.sh
```

在`sim`文件夹下使用`make clean && make`大概率还是会报错的, 是因为gcc版本过高的原因

此时将`misc`, `pipe`下的`Makefile`对应语句修改为如下形式即可	[原文链接](https://stackoverflow.com/questions/63152352/fail-to-compile-the-y86-simulatur-csapp)

![image-20230117185436523](https://joplin-imgbed-1312299157.cos.ap-nanjing.myqcloud.com/image-20230117185436523.png)

# Part A

`.ys`文件的运行方式

```shell
./yas xxx.ys	# 生成xxx.yo
./yis xxx.yo	# 会输出模拟的结果
```

本部分代码格式与书上`图4-7`结构类似, 中文版在第252页

## Iteratively sum linked list elements

代码在`sim/misc/sum.ys`

## Recursively sum linked list elements

代码在`sim/misc/rsum.ys`

注意: 需要保存**被调用者保存寄存器**的值

## Copy a source block to a destination block

代码在`sim/misc/copy.ys`

注意:

- C语句需要被拆分为最小执行单位, 如`val = *src++`
- 可以使用`./seq/ssim ./misc/copy.yo > procedure.txt`来得到执行的日志



# Part B

以下是`IADDQ`的分段表示

| Fetch      | icode:ifun <- M1[PC]<br/>rA:rB <- M1[PC + 1]<br/>valC <- M8[PC + 2]<br/>valP <- PC + 10 |
| ---------- | ------------------------------------------------------------ |
| Decode     | valB <- R[rB]                                                |
| Execute    | valE <- valB + valC                                          |
| Memory     |                                                              |
| Write Back | R[rB] <- valB                                                |
| Update PC  | PC <- valP                                                   |

`seq-full.hcl`中包含了每一段要往流水线寄存器中添加的标记值, 如instr_valid, need_regids等, 指导下一个段应该怎么做.

要添加`IADDQ`, 就要把它的影响加入到每一个标记值中

如下, 由于`IADDQ`需要寄存器, 所以其对应的标记`need_regids`为真, 将`IIADDQ`加入到大括号中.

``` 
# Does fetched instruction require a regid byte?
bool need_regids =
	icode in { IRRMOVQ, IOPQ, IPUSHQ, IPOPQ, 
		     IIRMOVQ, IRMMOVQ, IMRMOVQ, IIADDQ };
```



添加完毕后在`sim`文件夹下执行如下两条指令判断是否成功

``` shell
> make VERSION=full
> ./seq/ssim -t ./y86-code/asumi.yo
```

如果最后输出`ISA Check Succeeds`则说明没问题



# Part C

本部分参考了[知乎专栏](https://zhuanlan.zhihu.com/p/454779772)

本部分需要实现一个拷贝长度为n的数组的功能, 未优化过的代码如下

``` C++
word_t ncopy(word_t *src, word_t *dst, word_t len)
{
    word_t count = 0;
    word_t val;

    while (len > 0) {
        val = *src++;
        *dst++ = val;
        if (val > 0)
            count++;
        len--;
    }
    return count;
}
```

可以看到, 每复制一个数组元素有一次`len>0`和`val>0`的判断

判断跳转对流水线有着很大的性能影响, 可以使用循环展开来减少判断的次数

``` C++
typedef int word_t;
word_t ncopy2(word_t *src, word_t *dst, word_t len)
{
    word_t count = 0;
    word_t val1;
    word_t val2;

    while (len > 1) {	// 一次赋值两个
        val1 = *src++;
        val2 = *src++;
        *dst++ = val1;
        *dst++ = val2;
        if (val1 > 0)
            count++;
        if (val2 > 0)
            count++;
        len-=2;
    }
    while (len>0){		// 边界条件
        val1 = *src;
        *dst = val1;
        if (val>0)
        	count++;
        len--;
    }
    return count;
}
```

并且可以优化一下, 使用`IADDQ`来直接进行立即数和寄存器之间的加法, 减少指令的个数



我使用了4x1的循环展开, 对应C代码如下

``` C++
typedef int word_t;
word_t ncopy4(word_t *src, word_t *dst, word_t len)
{
    word_t count = 0;
    word_t val1;
    word_t val2;
    word_t val3;
    word_t val4;

    while (len > 3) {	// 一次赋值4个
        val1 = *src++;
        val2 = *src++;
        val3 = *src++;
        val4 = *src++;
        *dst++ = val1;
        *dst++ = val2;
        *dst++ = val3;
        *dst++ = val4;
        
        if (val1 > 0)
            count++;
        if (val2 > 0)
            count++;
        if (val3 > 0)
            count++;
        if (val4 > 0)
            count++;
        len -= 4;
    }
    while (len>0){		// 边界条件,最多执行三次
        val1 = *src;
        *dst = val1;
        if (val1>0)
        	count++;
        len--;
    }
    return count;
}
```

**有个BUG没有解决, 挖个坑先, 以后有空再回来**



# Appendix

## 循环展开

以下资料来自[维基百科](https://zh.m.wikipedia.org/zh-hans/%E5%BE%AA%E7%8E%AF%E5%B1%95%E5%BC%80)

**循环展开**（Loop unwinding或loop unrolling），是一种牺牲程序的大小来加快程序执行速度的优化方法。可以由程序员完成，也可由[编译器](https://zh.m.wikipedia.org/wiki/编译器)自动优化完成。

循环展开最常用来降低循环开销，为具有多个功能单元的处理器提供[指令级并行](https://zh.m.wikipedia.org/wiki/指令级并行)。也有利于[指令流水线](https://zh.m.wikipedia.org/wiki/指令流水线)的调度。

![image-20230119152617574](https://joplin-imgbed-1312299157.cos.ap-nanjing.myqcloud.com/image-20230119152617574.png)

循环展开可以减少分支预测失败的次数
