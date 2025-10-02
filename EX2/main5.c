/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/#include <stdio.h>

#include <stdio.h>

int main() {
    char grade = 'B';
    printf("Your grade is %c\n", grade);
    switch (grade) {
        case 'A':
            printf("Excellent\n");
            break;
        case 'B':
        case 'C':
            printf("Well done!\n");
            break;
        case 'D':
        case 'F':
            printf("Better try again!\n");
            break;
        default:
            printf("Invali grade\n");
    }
    return 0;
}
