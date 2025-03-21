%{
    #include <stdio.h>
    #include <string.h>
    
    void print_token(const char *type, const char *value) {
        printf("%s: %s\n", type, value);
    }
%}

%option noyywrap

%%

"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while"   { print_token("Keyword", yytext); }

[0-9]+[a-zA-Z_][a-zA-Z0-9_]*   

[a-zA-Z_][a-zA-Z0-9_]*          { print_token("Identifier", yytext); }

[0-9]+                         { print_token("Constant", yytext); }

\"([^\\\"]|\\.)*\"             { print_token("String", yytext); }

\'([^\\\']|\\.)*\'             { print_token("String", yytext); }

[;,\(\)\{\}\[\]]               { print_token("Punctuation", yytext); }

"=="|"!="|"<="|">="|"++"|"--"|"&&"|"||"|"+"|"-"|"*"|"/"|"="|"<"|">"|"!"  { print_token("Operator", yytext); }

"//".*                        { /* Ignore single-line comments */ }

"/*"([^*]|\*+[^*/])*\*+"/"     { /* Ignore multi-line comments */ }

[ \t\n]+                      { /* Ignore white spaces */ }

.                             { /* Silently ignore any other unmatched characters */ }

%%

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    yyin = file;
    yylex();
    fclose(file);
    
    return 0;
}

