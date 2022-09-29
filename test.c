#include<stdio.h>
#include <stdlib.h>
int fib(int num,int *count){
    *count += 1;
    if(num == 0)
        return 0;
    if(num == 1)
        return 1;

    return fib(num - 1,count) + fib(num - 2,count);

}
int main(){

    int *count = malloc(sizeof(int));
    *count = 0;
    fib(4,count);
    printf("%d\n",*count);
}
seq 100 | sort -R | /usr/bin/time -f "%U" ./sortIntList > /dev/null