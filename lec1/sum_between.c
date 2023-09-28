#include <stdio.h>

int sum_between(int x, int y){
    int result = 0;
    for (int i=x; i<=y; i++){
        result += i;
    }
    return result;
}

int main(){
    printf("sum = %d\n", sum_between(1,3));
    return 0;
}