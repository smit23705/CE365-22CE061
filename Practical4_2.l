%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%option noyywrap

%%
([cC][hH][aA][rR][uU][sS][aA][tT])  { printf("university"); }
.|\n                                { printf("%s", yytext); }
%%

int main(void)
{
    char input[1000];
    printf("Enter string:\n");
    if(fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        exit(1);
    }
    yy_scan_string(input);
    yylex();
    return 0;
}
