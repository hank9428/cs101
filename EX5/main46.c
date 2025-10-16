#include <stdio.h>
void towerofhano(int n,char from_rod, char to_rod, char aux_rod){
    if (n==1){
        printf("\n move disk 1 from rod %c to rod %c",from_rod, to_rod);
        return;
    }
    towerofhano(n-1,from_rod,aux_rod,to_rod);
    printf("\n move disk 1 from rod %c to rod %c",from_rod, to_rod);
    towerofhano(n-1,aux_rod,to_rod,from_rod);
    
}
int main(){
    int n=3;
    towerofhano(n,'A','B','C');
    return 0;
}
