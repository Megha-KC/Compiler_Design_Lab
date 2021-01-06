%{
    #include<stdio.h>
    int valid = 1;
%}

%token letter digit

%%
start: letter s
s:  letter s
    | digit s
    | 
    ;
%%

int yyerror() {
    printf("Not a valid variable\n");
    valid = 0;
    return 0;    
}

int main() {
    printf("Input a variable to test for its validility: ");
    yyparse();
    if (valid)
        printf("Valid variable\n");
}