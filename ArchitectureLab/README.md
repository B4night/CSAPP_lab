# 环境配置

首先通过下面的命令来安装环境, 此命令出自[知乎博客](https://zhuanlan.zhihu.com/p/454779772)

``` shell
wget https://gitee.com/lin-xi-269/csapplab/raw/master/lab4archlab/archlab-handout/installTclTk.sh && bash installTclTk.sh
```

在`sim`文件夹下使用`make clean && make`大概率还是会报错的, 是因为gcc版本过高的原因

此时将`misc`, `pipe`下的`Makefile`对应语句修改为如下形式即可

[原文链接](https://stackoverflow.com/questions/63152352/fail-to-compile-the-y86-simulatur-csapp)

![image-20230117185436523](https://joplin-imgbed-1312299157.cos.ap-nanjing.myqcloud.com/image-20230117185436523.png)

