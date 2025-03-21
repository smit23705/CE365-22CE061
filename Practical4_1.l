%{
#include <stdio.h>
%}

%option noyywrap

%%
[0-9]+      { printf("%s\n", yytext); }
[ \t\n]+    { /* Skip whitespace */ }
.           { /* Skip any other character */ }

%%

int main(void)
{
    printf("Enter string:\n");
    yylex();
    return 0;
}
