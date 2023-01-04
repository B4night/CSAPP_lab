# Part A

用到的数据结构如下

``` C++
struct config {
    int verbose;
    int s;      int set_num;       // 2^s is the number of sets
    int E;      int line_num;      // a set has E lines
    int b;      int block_size;    // a line's data block has 2^b bytes
    int traces; char path[256];
} global_config;
	
struct record {		// 记录下hit, miss, eviction数
    int hits;		
    int misses;
    int evitions;
} global_record;

struct Line {	// set中的一行
    int valid;
    int time_tag;
    unsigned int start_addr;
};

struct Set {	// 一个set包含多个(或一个)line
    struct Line* lines;
};

struct Cache {	// cache中有多个set
    struct Set* sets;
} cache;
// 一个cache中有2^s个set,一个set有E行

int isInit = 0;		// 记录下cache是否初始化
int time_step = 0;	// 时间戳,用于给line赋值
```

L(load)操作, S(store)操作都是对内存的一次读取, M(modify)操作是一次L加一次S

内存访问的流程(假设访问内存地址为X的数据)

1. 根据X, 得到其对应的set的坐标
2. 在set包含的line中寻找
   - 如果有line的的数据区包含了X, 则hit
   - 如果没有hit
     - 如果此set已满, 需要eviction
     - 否则找到一个有效值为0的line, 插入即可

代码在`csim.c`和`csim_header.h`中



注: 执行评价程序`./test-csim`的时候有时候会扣分, 目前还没找到是什么原因