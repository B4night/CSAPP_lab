/*
* author: B4night
* date:   2023-1-4
*/

#include "csim_header.h"
#include "cachelab.h"

int main(int argc, char** argv)
{
    parseArguments(argc, argv);
    // for debug
    // global_config.b = 3;
    // global_config.block_size = 8;
    // global_config.E = 2;
    // global_config.line_num = 2;
    // global_config.s = 2;
    // global_config.set_num = 4;
    // strcpy(global_config.path, "traces/tmp.trace");
    executeFile();
    printSummary(global_record.hits, global_record.misses, global_record.evitions);
    destroyCache();
    return 0;
}