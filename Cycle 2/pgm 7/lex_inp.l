%{
    #include "y.tab.h"
%}

%%
for                                 return FOR;
\< |
\<= |
== |
\>= |
\> |
!=                                  return RELOP;
\+\+                                return INC;
--                                  return DEC;
\|\| |
&&                                  return LOGOP; 
[a-zA-Z_][a-zA-Z_0-9]*              return ID;
[0-9]+                              return NUM;
[\t\n ]                             ;
.                                   return yytext[0];
%%

int yywrap() {}