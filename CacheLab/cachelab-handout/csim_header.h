#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include <stdlib.h>

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

void initCache() {
    if (isInit) {
        return;
    }
    // 一个cache有2^s个set,一个set有E行
    cache.sets = (struct Set*)malloc(global_config.set_num * sizeof(struct Set));
    for (int i = 0; i < global_config.set_num; i++) {
        cache.sets[i].lines = (struct Line*)malloc(global_config.line_num * sizeof(struct Line));
        for (int j = 0; j < global_config.line_num; j++) {
            cache.sets[i].lines[j].valid = 0;
        }
    }
}

void destroyCache() {   // 归还malloc的空间
    if (!isInit) {
        return;
    }
    for (int i = 0; i < global_config.set_num; i++) {
        free(cache.sets[i].lines);
    }
    free(cache.sets);
    isInit = 0;
}

void memoryAccess(unsigned int addr, int setIdx) {
    int isFull = 1; // 查看此set是否满(即line的有效位是否都为1)
    int efficient_addr = (addr >> global_config.b) << global_config.b;
    for (int i = 0; i < global_config.line_num; i++) {
        if (cache.sets[setIdx].lines[i].valid == 0) {
            isFull = 0; // 未满
            continue;
        }
        if (cache.sets[setIdx].lines[i].start_addr == efficient_addr) { // 此时hit
            global_record.hits++;
            cache.sets[setIdx].lines[i].time_tag = time_step++;
            if (global_config.verbose) {
                fprintf(stdout, " hit");
            }
            return;
        }
    }
    if (global_config.verbose) {
        fprintf(stdout, " miss");
    }
    global_record.misses++;
    if (isFull) {   // set已满,此时需要evict
        if (global_config.verbose) {
            fprintf(stdout, " eviction");
        }
        global_record.evitions++;
        int min_val = cache.sets[setIdx].lines[0].time_tag;
        int tmpIdx = 0;
        for (int i = 1; i < global_config.line_num; i++) {  // LRU算法,找到时间戳最小(距离上次访问时间最长)的line
            if (cache.sets[setIdx].lines[i].time_tag <=  min_val) {
                min_val = cache.sets[setIdx].lines[i].time_tag;
                tmpIdx = i;
            }
        }
        cache.sets[setIdx].lines[tmpIdx].time_tag = time_step++;    // 替换
        cache.sets[setIdx].lines[tmpIdx].start_addr = efficient_addr;
    } else {    // 此时往空的line加入即可
        int tmpIdx;
        for (int i = 0; i < global_config.line_num; i++) {  // 找到有效位为0的line
            if (cache.sets[setIdx].lines[i].valid == 0) {
                tmpIdx = i;
                break;
            }
        }
        cache.sets[setIdx].lines[tmpIdx].time_tag = time_step++;
        cache.sets[setIdx].lines[tmpIdx].valid = 1;
        cache.sets[setIdx].lines[tmpIdx].start_addr = efficient_addr;
    }
}

void executeFile() {
    if (!isInit) {
        initCache();
    }
    FILE* f =fopen(global_config.path, "r");
    if (f == NULL) {
        exit(1);
    }

    char buffer[256];
    while (fgets(buffer, 256, f) != NULL) { // 读入一行
         if (buffer[0] != ' ') {
            continue;
        }
        char op;
        unsigned addr;
        unsigned size;
        sscanf(buffer, " %c %x,%d", &op, &addr, &size); // 格式化scan
        buffer[strlen(buffer) - 1] = 0;     // 去掉换行
        if (global_config.verbose) {
            fprintf(stdout, "%s", buffer + 1);
        }

        int set_idx = (addr >> global_config.b) & ((1 << global_config.s) - 1); // 得到内存地址addr所属的set的坐标
        switch (op) {
        case 'L':
        case 'S':
            memoryAccess(addr, set_idx);    // Load和Store为一次memoryAccess
            break;
        case 'M':                           // Modify为一次Load+一次Store
            memoryAccess(addr, set_idx);
            memoryAccess(addr, set_idx);
            break;
        }
        if (global_config.verbose) {
            fprintf(stdout, " \n");
        }
    }

    fclose(f);
}

void parseArguments(int argc, char** argv) {
    global_config.b = global_config.E = global_config.s = global_config.traces = global_config.verbose = 0;
    global_record.hits = global_record.misses = global_record.evitions = 0;

    int opt;
    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch (opt) {
        case 'h':
            fprintf(stdout, "Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
            exit(0);
            break;
        case 'v':
            global_config.verbose = 1;
            break;
        case 's':
            global_config.s = atoi(optarg);
            global_config.set_num = 1 << atoi(optarg);
            break;
        case 'E':
            global_config.E = atoi(optarg);
            global_config.line_num = atoi(optarg);
            break;
        case 'b':
            global_config.b = atoi(optarg);
            global_config.block_size = 1 << atoi(optarg);
            break;
        case 't':
            global_config.traces = 1;
            strcpy(global_config.path, optarg);
            break;
        default:
            exit(1);
            break;
        }
    }
    if (!(global_config.b && global_config.E && global_config.s && global_config.traces)) {
        exit(1);
    }
}
