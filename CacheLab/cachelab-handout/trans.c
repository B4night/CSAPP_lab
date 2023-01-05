/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

// 32X32矩阵的转置
void process_32(int A[32][32], int B[32][32]) {
    int t1, t2, t3, t4, t5, t6, t7, t8;
    int i, j, tmp;
    int m, n;
    for (i = 0; i < 32; i += 8) {
        for (j = 0; j < 32; j += 8) {
            if (i != j) {   // 非对角线,映射到不同的cache中
                for (m = i; m < i + 8; m++) {
                    for (n = j; n < j + 8; n++) {
                        B[n][m] = A[m][n];
                    }
                }
            } else {        // 对角线,映射到相同的cache中,会冲突
                // 处理方法:先将8X8的块赋值给B,然后转置
                tmp = i;
                t1 = A[tmp][j]; t2 = A[tmp][j+1]; t3 = A[tmp][j+2]; t4 = A[tmp][j+3];
                t5 = A[tmp][j+4]; t6 = A[tmp][j+5]; t7 = A[tmp][j+6]; t8 = A[tmp][j+7];
                B[tmp][j] = t1; B[tmp][j+1] = t2; B[tmp][j+2] = t3; B[tmp][j+3] = t4;
                B[tmp][j+4] = t5; B[tmp][j+5] = t6; B[tmp][j+6] = t7; B[tmp][j+7] = t8;

                tmp++;
                t1 = A[tmp][j]; t2 = A[tmp][j+1]; t3 = A[tmp][j+2]; t4 = A[tmp][j+3];
                t5 = A[tmp][j+4]; t6 = A[tmp][j+5]; t7 = A[tmp][j+6]; t8 = A[tmp][j+7];
                B[tmp][j] = t1; B[tmp][j+1] = t2; B[tmp][j+2] = t3; B[tmp][j+3] = t4;
                B[tmp][j+4] = t5; B[tmp][j+5] = t6; B[tmp][j+6] = t7; B[tmp][j+7] = t8;

                tmp++;
                t1 = A[tmp][j]; t2 = A[tmp][j+1]; t3 = A[tmp][j+2]; t4 = A[tmp][j+3];
                t5 = A[tmp][j+4]; t6 = A[tmp][j+5]; t7 = A[tmp][j+6]; t8 = A[tmp][j+7];
                B[tmp][j] = t1; B[tmp][j+1] = t2; B[tmp][j+2] = t3; B[tmp][j+3] = t4;
                B[tmp][j+4] = t5; B[tmp][j+5] = t6; B[tmp][j+6] = t7; B[tmp][j+7] = t8;

                tmp++;
                t1 = A[tmp][j]; t2 = A[tmp][j+1]; t3 = A[tmp][j+2]; t4 = A[tmp][j+3];
                t5 = A[tmp][j+4]; t6 = A[tmp][j+5]; t7 = A[tmp][j+6]; t8 = A[tmp][j+7];
                B[tmp][j] = t1; B[tmp][j+1] = t2; B[tmp][j+2] = t3; B[tmp][j+3] = t4;
                B[tmp][j+4] = t5; B[tmp][j+5] = t6; B[tmp][j+6] = t7; B[tmp][j+7] = t8;

                tmp++;
                t1 = A[tmp][j]; t2 = A[tmp][j+1]; t3 = A[tmp][j+2]; t4 = A[tmp][j+3];
                t5 = A[tmp][j+4]; t6 = A[tmp][j+5]; t7 = A[tmp][j+6]; t8 = A[tmp][j+7];
                B[tmp][j] = t1; B[tmp][j+1] = t2; B[tmp][j+2] = t3; B[tmp][j+3] = t4;
                B[tmp][j+4] = t5; B[tmp][j+5] = t6; B[tmp][j+6] = t7; B[tmp][j+7] = t8;

                tmp++;
                t1 = A[tmp][j]; t2 = A[tmp][j+1]; t3 = A[tmp][j+2]; t4 = A[tmp][j+3];
                t5 = A[tmp][j+4]; t6 = A[tmp][j+5]; t7 = A[tmp][j+6]; t8 = A[tmp][j+7];
                B[tmp][j] = t1; B[tmp][j+1] = t2; B[tmp][j+2] = t3; B[tmp][j+3] = t4;
                B[tmp][j+4] = t5; B[tmp][j+5] = t6; B[tmp][j+6] = t7; B[tmp][j+7] = t8;

                tmp++;
                t1 = A[tmp][j]; t2 = A[tmp][j+1]; t3 = A[tmp][j+2]; t4 = A[tmp][j+3];
                t5 = A[tmp][j+4]; t6 = A[tmp][j+5]; t7 = A[tmp][j+6]; t8 = A[tmp][j+7];
                B[tmp][j] = t1; B[tmp][j+1] = t2; B[tmp][j+2] = t3; B[tmp][j+3] = t4;
                B[tmp][j+4] = t5; B[tmp][j+5] = t6; B[tmp][j+6] = t7; B[tmp][j+7] = t8;

                tmp++;
                t1 = A[tmp][j]; t2 = A[tmp][j+1]; t3 = A[tmp][j+2]; t4 = A[tmp][j+3];
                t5 = A[tmp][j+4]; t6 = A[tmp][j+5]; t7 = A[tmp][j+6]; t8 = A[tmp][j+7];
                B[tmp][j] = t1; B[tmp][j+1] = t2; B[tmp][j+2] = t3; B[tmp][j+3] = t4;
                B[tmp][j+4] = t5; B[tmp][j+5] = t6; B[tmp][j+6] = t7; B[tmp][j+7] = t8;

                for (m = i; m < i + 8; m++) {
                    for (n = j; n < m; n++) {
                        tmp = B[m][n];
                        B[m][n] = B[n][m];
                        B[n][m] = tmp;
                    }
                }

            }
        }
    }
}

void process_64(int A[64][64], int B[64][64]) {
    int i, j, x, y;
    int t1, t2, t3, t4, t5, t6, t7, t8;

    //处理对角线,下面说的图x是对角线部分中的图的编号
    for (i = 0; i < 8; i++) {	
    //(i * 8, i * 8)为对角线块的左上角坐标
    //当处理第1个对角线块时,备用块为第一行从左往右数第三个块,其他时间则为第一行从左往右数第二个块
    //(x,y)为备用块的左上角坐标
        if (i == 1)
            x = 0, y = 16;
        else
            x = 0, y = 8;
        j = 8*i;
        for (t1 = j + 4; t1 < j + 8; t1++)		//将A的下半部分转移到借用块
            for (t2 = j; t2 < j + 8; t2++)
                B[x + t1-j-4][y+t2-j] = A[t1][t2];

        //避免行冲突，用变量存储
        //将A上半部分的每一行复制到B的上半部分
        t1=A[j][j], t2=A[j][j+1], t3=A[j][j+2], t4=A[j][j+3], 
        t5=A[j][j+4], t6=A[j][j+5], t7=A[j][j+6], t8=A[j][j+7];
        B[j][j]=t1, B[j][j+1]=t2, B[j][j+2]=t3, B[j][j+3]=t4, 
        B[j][j+4]=t5, B[j][j+5]=t6, B[j][j+6]=t7, B[j][j+7]=t8;

        t1=A[j+1][j], t2=A[j+1][j+1], t3=A[j+1][j+2], t4=A[j+1][j+3], 
        t5=A[j+1][j+4], t6=A[j+1][j+5], t7=A[j+1][j+6], t8=A[j+1][j+7];
        B[j+1][j]=t1, B[j+1][j+1]=t2, B[j+1][j+2]=t3, B[j+1][j+3]=t4, 
        B[j+1][j+4]=t5, B[j+1][j+5]=t6, B[j+1][j+6]=t7, B[j+1][j+7]=t8;

        t1=A[j+2][j], t2=A[j+2][j+1], t3=A[j+2][j+2], t4=A[j+2][j+3], 
        t5=A[j+2][j+4], t6=A[j+2][j+5], t7=A[j+2][j+6], t8=A[j+2][j+7];
        B[j+2][j]=t1, B[j+2][j+1]=t2, B[j+2][j+2]=t3, B[j+2][j+3]=t4, 
        B[j+2][j+4]=t5, B[j+2][j+5]=t6, B[j+2][j+6]=t7, B[j+2][j+7]=t8;

        t1=A[j+3][j], t2=A[j+3][j+1], t3=A[j+3][j+2], t4=A[j+3][j+3], 
        t5=A[j+3][j+4], t6=A[j+3][j+5], t7=A[j+3][j+6], t8=A[j+3][j+7];
        B[j+3][j]=t1, B[j+3][j+1]=t2, B[j+3][j+2]=t3, B[j+3][j+3]=t4, 
        B[j+3][j+4]=t5, B[j+3][j+5]=t6, B[j+3][j+6]=t7, B[j+3][j+7]=t8;
        //到此时实现了图3

        //下边需要实现图4,即转置四个4×4的子矩阵
        t7 = x;
        t8 = y;

        //下列四个循环是转置四个子矩阵
        for (x = j; x < j + 4; x++) {	//B上半部分的左半
            for (y = j; y < j + (x - j); y++) {
                t1 = B[x][y];
                B[x][y] = B[y][x];
                B[y][x] = t1;
            }
        }
        for (x = j; x < j + 4; x++) {	//B上半部分的右半
            for (y = j + 4; y < j + 4 + (x - j); y++) {
                t1 = B[x][y];
                B[x][y] = B[y-4][x+4];
                B[y-4][x+4] = t1;
            }
        }
        for (x = t7; x < t7 + 4; x++) {		//备用块的左半
            for (y = t8; y < t8 + (x - t7); y++) {
                t1 = B[x][y];
                B[x][y] = B[y-t8][x+t8];
                B[y-t8][x+t8] = t1;
            }
        }
        for (x = t7; x < t7 + 4; x++) {		//备用块的右半
            for (y = t8 + 4; y < t8 + 4 + (x - t7); y++) {
                t1 = B[x][y];
                B[x][y] = B[y-t8-4][x+t8+4];
                B[y-t8-4][x+t8+4] = t1;
            }
        }

        //下面一个循环实现图5
        for (x = j, t1 = t7; x < j + 4; x++, t1++)
            for (y = j + 4, t2 = t8; y < j + 8; y++, t2++) {
                t3 = B[x][y];
                B[x][y] = B[t1][t2];
                B[t1][t2] = t3;
            }

        //将备用块的上半复制到B的下半中
        for (x = j + 4, t1 = t7; x < j + 8; x++, t1++)
            for (y = j, t2 = t8; y < j + 8; y++, t2++)
                B[x][y] = B[t1][t2];

    }

        //非对角线部分,下面说的图x是非对角线部分中的图的编号
    for (i = 0; i < 64; i += 8) {
        for (j = 0; j < 64; j += 8) {
            if (i != j) {	//因为对角线上的块需要特判处理,所以只执行非对角线块

                //下面两个for实现图4
                for (x = i, t1 = i; x < i + 4; x++, t1++) {
                    for (y = j, t2 = j; y < j + 4; y++, t2++) {
                        B[t2][t1] = A[x][y];    						
                    }
                }
                for (x = i, t1 = i + 4; x < i + 4; x++, t1++) {
                    for (y = j + 4, t2 = j; y < j + 8; y++, t2++) {
                        B[t2][t1] = A[x][y];    						
                    }
                }

                //下面四行实现图5
                t1 = B[j][i+4]; t2 = B[j][i+5]; t3 = B[j][i+6]; t4 = B[j][i+7];
                B[j][i+4] = A[i+4][j]; B[j][i+5] = A[i+5][j]; 
                B[j][i+6] = A[i+6][j]; B[j][i+7] = A[i+7][j];
                B[j+4][i] = t1; B[j+4][i+1] = t2; B[j+4][i+2] = t3; B[j+4][i+3] = t4;

                //下面四行实现图6
                t1 = B[j+1][i+4]; t2 = B[j+1][i+5]; t3 = B[j+1][i+6]; t4 = B[j+1][i+7];
                B[j+1][i+4] = A[i+4][j+1]; B[j+1][i+5] = A[i+5][j+1];
                B[j+1][i+6] = A[i+6][j+1]; B[j+1][i+7] = A[i+7][j+1];
                B[j+5][i] = t1; B[j+5][i+1] = t2; B[j+5][i+2] = t3; B[j+5][i+3] = t4;

                //...
                t1 = B[j+2][i+4]; t2 = B[j+2][i+5]; t3 = B[j+2][i+6]; t4 = B[j+2][i+7];
                B[j+2][i+4] = A[i+4][j+2]; B[j+2][i+5] = A[i+5][j+2]; 
                B[j+2][i+6] = A[i+6][j+2]; B[j+2][i+7] = A[i+7][j+2];
                B[j+6][i] = t1; B[j+6][i+1] = t2; B[j+6][i+2] = t3; B[j+6][i+3] = t4;

                t1 = B[j+3][i+4]; t2 = B[j+3][i+5]; t3 = B[j+3][i+6]; t4 = B[j+3][i+7];
                B[j+3][i+4] = A[i+4][j+3]; B[j+3][i+5] = A[i+5][j+3]; 
                B[j+3][i+6] = A[i+6][j+3]; B[j+3][i+7] = A[i+7][j+3];
                B[j+7][i] = t1; B[j+7][i+1] = t2; B[j+7][i+2] = t3; B[j+7][i+3] = t4;
                //执行至此,已到图7

                //for循环将转置后的A的右下部分复制到B的右下部分
                for (x = i + 4, t1 = i + 4; x < i + 8; x++, t1++) {
                    for (y = j + 4, t2 = j + 4; y < j + 8; y++, t2++) {
                        B[t2][t1] = A[x][y];    						
                    }
                }
            }
        }
    }
}

void process_61_67(int A[67][61], int B[61][67]) {
    //16 X 16 blocking
    //注意A[N][M], B[M][N]
    int i, j, x;
    int tmpN = 67 / 16 * 16;
    int tmpM = 61 / 16 * 16;
    int t1, t2, t3, t4, t5, t6, t7, t8;
    
    //下面一个循环处理16×16的块,使用变量来减少cache冲突
    for (i = 0; i < tmpN; i += 16) {
        for (j = 0; j < tmpM; j += 16) {
            for (x = i; x < i + 16; x++) {
                t1 = A[x][j], t2 = A[x][j+1], t3 = A[x][j+2], t4 = A[x][j+3], 
                t5 = A[x][j+4], t6 = A[x][j+5], t7 = A[x][j+6], t8 = A[x][j+7];
                B[j][x] = t1, B[j+1][x] = t2, B[j+2][x] = t3, B[j+3][x] = t4, 
                B[j+4][x] = t5, B[j+5][x] = t6, B[j+6][x] = t7, B[j+7][x] = t8;

                t1 = A[x][j+8], t2 = A[x][j+9], t3 = A[x][j+10], t4 = A[x][j+11], 
                t5 = A[x][j+12], t6 = A[x][j+13], t7 = A[x][j+14], t8 = A[x][j+15];
                B[j+8][x] = t1, B[j+9][x] = t2, B[j+10][x] = t3, B[j+11][x] = t4,
                B[j+12][x] = t5, B[j+13][x] = t6, B[j+14][x] = t7, B[j+15][x] = t8;
            }
        }
    }

    //下列两个循环处理不使用分块的部分
    for (i = 0; i < tmpN; i++)
        for (j = tmpM; j < 61; j++)
            B[j][i] = A[i][j];

    for (i = tmpN; i < 67; i++)
        for (j = 0; j < 61; j++)
            B[j][i] = A[i][j];
}

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 32 && N == 32) {
        process_32(A, B);
    }
    if (M == 64 && N == 64) {
        process_64(A, B);
    }
    if (M == 61 && N == 67) {
        process_61_67(A, B);
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

