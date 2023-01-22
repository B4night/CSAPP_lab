

需要实现的代码

- `void eval(char *cmdline)`：解析并执行命令。
- `int builtin_cmd(char **argv)`：检测命令是否为内置命令`quit`、`fg`、`bg`、`jobs`。
- `void do_bgfg(char **argv)`：实现`bg`、`fg`命令。
- `void waitfg(pid_t pid)`：等待前台命令执行完成。
- `void sigchld_handler(int sig)`：处理`SIGCHLD`信号，即子进程停止或终止。
- `void sigint_handler(int sig)`：处理`SIGINT`信号，即来自键盘的中断`ctrl-c`。
- `void sigtstp_handler(int sig)`：处理`SIGTSTP`信号，即终端停止信号`ctrl-z`。



# eval

如果是内置命令, 则调用`builtin_cmd`直接执行

否则生成一个子进程, 父进程根据是FG还是BG有不同处理方式

注意屏蔽信号



# builtin_cmd

用strcmp来判断是哪种内置命令, 调用辅助函数执行

注意返回值



# do_bgfg

注意jid和pid格式上的不同

`%5`表示`jid5`, `5`表示`pid5`

一个进程的pid和gid是相同的, 且一个进程组中只有一个进程, 所以使用`kill(-job->pid, ..)`来发送信号



# waitfg

当foreground process在运行的时候调用sigsuspend, 当收到SIGCHLD的时候判断是否是foreground process运行结束, 如果运行结束的话就返回, 不是则继续调用sigsuspend



# sigchld_handler

保存errno值

根据`WIFEXITED, WIFSIGNALED`有不同的处理方法

注意屏蔽信号



# sigint_handler

直接给foreground process发送信号



# sigtstp_handler

直接发送信号即可
