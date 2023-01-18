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
