#include <stdio.h>

int palindro(int, int);
int main()
{
    int i, n = 70;
    for(i = 0; ; ++i){
        printf("%d, %d\n", i, palindro(i, n));
        if(i > 150)
            break;
    }
    printf("done.\n");
    return 0;
}


/* 回文数，比如: n = 4,
 * 则生成的回文数序列为：0，1,2,3,2,1,0,1，...
 * 如此循环下去。
 * 其中 i 从0 开始。
 * 
 */
int palindro(int i, int n){ /* 用来生成回文数的函数*/
    if(i < 2*n-1)
        return (i <= n-1) ? (i) : (2*n-2-i);
    else{
        i = i % (2*n-2);
        return (i <= n-1) ? (i) : (2*n-2-i);
    }
}