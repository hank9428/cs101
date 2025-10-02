/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

int main()
{
    int n=6;
    for(int x = 1; x <=n ; x++){
        for(int y=1; y <=n ; y++){
            if(y<=n-x){
                printf(" ");
            }
                else{
                printf("%d ",x);
            }
        }
        printf("\n");
        }
    return 0;
}
