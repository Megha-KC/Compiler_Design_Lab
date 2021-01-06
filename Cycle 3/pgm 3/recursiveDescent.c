/*Recursive decent parser
Grammar:
E -> iZ
Z -> +iZ|e
Write one program for each non-terminal.
*/
#include<stdio.h>

char input[100];
int i = 0;
int curr = 0;

int E();
int Z();

int main() {
    printf("Enter input:\n");
    scanf("%s", input);
    while(input[i] != '\0')
        i++;
    // i contains length of the input.

    int res = E();
    if(res == 1 && curr == i)
        printf("Input has been accepted.\n");
    else    
        printf("Input has been rejected.\n");
}

int E() {
    int res;
    // E -> iZ
    if(input[curr] == 'i') {
        curr++;
        res = Z();
        if(res == 1)    
            return 1;
        else
            return -1;
    }
}

int Z() {
    int res;
    // Z -> +iZ
    if(input[curr] == '+' && input[curr + 1] == 'i') {
        curr += 2;
        res = Z();
        if(res == 1) 
            return 1;
    }
    //Z -> e
    //not incrementing curr
    return 1;
}