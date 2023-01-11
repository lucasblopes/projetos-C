//McCarthy 91
#include <stdio.h>

int F(int n){
    if (n > 100)
        return n - 10;
    return F(F(n+11));
}

int main(){
    int n;

    printf("n = ");
    scanf("%d", &n);
    printf("McCarthy(%d) = %d\n", n, F(n));
    
    return 0;
}