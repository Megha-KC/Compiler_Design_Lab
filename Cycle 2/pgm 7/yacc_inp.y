%{
    #include<stdio.h>
    #include<stdlib.h>
    extern FILE *yyin;
%}

%token FOR RELOP LOGOP ID NUM INC DEC;
%right '='  
%left LOGOP 
%left RELOP
%left '+' '-'
%left '*' '/'
%left INC DEC

%%
start:           st                                                      { printf("Input Accepted!\n"); exit(0); } 
st:              FOR '(' loop_expr ';' condition ';' loop_expr ')' block ;      
loop_expr:          E | ;
block:           '{' code '}' | statement ;
code:           statement code | statement ;
statement:      E ';' | st ;
    
E:               ID '=' E
                 |E '+' E
                 | E '-' E
                 | E '*' E
                 | E '/' E
                 | E RELOP E
                 | E LOGOP E
                 |ID INC
                 | ID DEC
                 | ID
                 | NUM
                 ;

condition:       E RELOP E
                 | E LOGOP E 
                 |;

%%

int yyerror(char* s) {
    fprintf(stderr, "%s\n", s);
}

int main(int argc, char* argv[]) {
    FILE *fp;
    if(argc>1) {
        fp=fopen(argv[1],"r");
        if(!fp) {
            perror(fp);
            printf("%s not found", argv[1]);
            exit(0);
        }
        yyin=fp;
    }
    printf("Checking the validity of for loop...\n");
    yyparse();
}