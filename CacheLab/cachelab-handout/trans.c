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

void process_32(int A[32][32], int B[32][32]) {
    int i, j, x, y;
    int t1, t2, t3, t4, t5, t6, t7, t8;
    //(i, j)为每个块左上角的元素的坐标
    for (i = 0; i < 32; i += 8) {
        for (j = 0; j < 32; j += 8) {
            if (i != j) {	//处理非对角线上的块
                for (x = i; x < i + 8; x++) {
                    for (y = j; y < j + 8; y++) {
                        B[y][x] = A[x][y];
                    }
                }
            } else {
                //处理对角线上的块
                x = i;	//一次性复制A[i][j]这一块到B[i][j]这一块上
                t1 = A[x][j]; t2 = A[x][j+1]; t3 = A[x][j+2]; t4 = A[x][j+3]; 
                t5 = A[x][j+4]; t6 = A[x][j+5]; t7 = A[x][j+6]; t8 = A[x][j+7];
                B[x][j] = t1; B[x][j+1] = t2; B[x][j+2] = t3; B[x][j+3] = t4; 
                B[x][j+4] = t5; B[x][j+5] = t6; B[x][j+6] = t7; B[x][j+7] = t8;

                x++; 	//一次性复制A[i+1][j]这一块到B[i+1][j]这一块上
                t1 = A[x][j]; t2 = A[x][j+1]; t3 = A[x][j+2]; t4 = A[x][j+3]; 
                t5 = A[x][j+4]; t6 = A[x][j+5]; t7 = A[x][j+6]; t8 = A[x][j+7];
                B[x][j] = t1; B[x][j+1] = t2; B[x][j+2] = t3; B[x][j+3] = t4; 
                B[x][j+4] = t5; B[x][j+5] = t6; B[x][j+6] = t7; B[x][j+7] = t8;

                x++; 	//...
                t1 = A[x][j]; t2 = A[x][j+1]; t3 = A[x][j+2]; t4 = A[x][j+3]; 
                t5 = A[x][j+4]; t6 = A[x][j+5]; t7 = A[x][j+6]; t8 = A[x][j+7];
                B[x][j] = t1; B[x][j+1] = t2; B[x][j+2] = t3; B[x][j+3] = t4; 
                B[x][j+4] = t5; B[x][j+5] = t6; B[x][j+6] = t7; B[x][j+7] = t8;

                x++; 
                t1 = A[x][j]; t2 = A[x][j+1]; t3 = A[x][j+2]; t4 = A[x][j+3]; 
                t5 = A[x][j+4]; t6 = A[x][j+5]; t7 = A[x][j+6]; t8 = A[x][j+7];
                B[x][j] = t1; B[x][j+1] = t2; B[x][j+2] = t3; B[x][j+3] = t4; 
                B[x][j+4] = t5; B[x][j+5] = t6; B[x][j+6] = t7; B[x][j+7] = t8;

                x++; 
                t1 = A[x][j]; t2 = A[x][j+1]; t3 = A[x][j+2]; t4 = A[x][j+3]; 
                t5 = A[x][j+4]; t6 = A[x][j+5]; t7 = A[x][j+6]; t8 = A[x][j+7];
                B[x][j] = t1; B[x][j+1] = t2; B[x][j+2] = t3; B[x][j+3] = t4; 
                B[x][j+4] = t5; B[x][j+5] = t6; B[x][j+6] = t7; B[x][j+7] = t8;

                x++; 
                t1 = A[x][j]; t2 = A[x][j+1]; t3 = A[x][j+2]; t4 = A[x][j+3]; 
                t5 = A[x][j+4]; t6 = A[x][j+5]; t7 = A[x][j+6]; t8 = A[x][j+7];
                B[x][j] = t1; B[x][j+1] = t2; B[x][j+2] = t3; B[x][j+3] = t4;
                B[x][j+4] = t5; B[x][j+5] = t6; B[x][j+6] = t7; B[x][j+7] = t8;

                x++; 
                t1 = A[x][j]; t2 = A[x][j+1]; t3 = A[x][j+2]; t4 = A[x][j+3]; 
                t5 = A[x][j+4]; t6 = A[x][j+5]; t7 = A[x][j+6]; t8 = A[x][j+7];
                B[x][j] = t1; B[x][j+1] = t2; B[x][j+2] = t3; B[x][j+3] = t4; 
                B[x][j+4] = t5; B[x][j+5] = t6; B[x][j+6] = t7; B[x][j+7] = t8;

                x++; 	////一次性复制A[i+7][j]这一块到B[i+7][j]这一块上
                t1 = A[x][j]; t2 = A[x][j+1]; t3 = A[x][j+2]; t4 = A[x][j+3]; 
                t5 = A[x][j+4]; t6 = A[x][j+5]; t7 = A[x][j+6]; t8 = A[x][j+7];
                B[x][j] = t1; B[x][j+1] = t2; B[x][j+2] = t3; B[x][j+3] = t4; 
                B[x][j+4] = t5; B[x][j+5] = t6; B[x][j+6] = t7; B[x][j+7] = t8;
	
                //此时,B中的黄色块上的元素和A中的完全相同,现在需要将这一部分转置
                for (x = i; x < i + 8; x++) {
                    for (y = j; y < j + (x - i); y++) {
                        t1 = B[x][y];
                        B[x][y] = B[y][x];
                        B[y][x] = t1;
                    }
                }
            }
        }
    }
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
    if (M == 32) {
        process_32(A, B);
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

