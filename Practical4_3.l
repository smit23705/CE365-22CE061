%{
#include <stdio.h>
#include <string.h>
int charCount = 0;
int wordCount = 0;
int lineCount = 0;
%}

%option noyywrap

%%
\n           { charCount += yyleng; lineCount++; }
[ \t]+       { charCount += yyleng; }
[^ \t\n]+   { charCount += yyleng; wordCount++; }
%%


int main(void)
{
    yylex();
    printf("Characters : %d\n", charCount);
    printf("Words : %d\n", wordCount);
    printf("Line : %d\n", lineCount);
    return 0;
}


