#include <stdio.h>

void removeSpaces(){
    char c=getchar();
    while(c==' '||c=='\t'){
        c=getchar();
    }
    ungetc(c,stdin);
}

void spamchar(char c,int n){
    for(int i=0;i<n;++i){
        putchar(c);
    }
}

int main(){
    char c=getchar();
    int newLine=0,level=0,escapeC=0,escapeCom1=0,escapeCom2=0,escapeS=0;
    while(c!=EOF){
        switch(c){
            case '/':
                putchar(c);
                c=getchar();
                if(c=='/'){
                    escapeCom1=!escapeCom1;
                    putchar(c);
                }
                else if(c=='*'){
                    escapeCom2=1;
                    putchar(c);
                }
                else ungetc(c,stdin);
                break;
            case '*':
                putchar(c);
                c=getchar();
                if(c=='/'){
                    escapeCom2=0;
                    putchar(c);
                }
                else ungetc(c,stdin);
                break;
            case '\\':
                putchar(c);
                c=getchar();
                putchar(c);
                break;
            case '"':
                putchar(c);
                escapeS=!escapeS;
                break;
            case '\'':
                putchar(c);
                escapeC=!escapeC;
                break;
            case '{':
                if(escapeC||escapeCom1||escapeCom2||escapeS){
                    putchar(c);
                    break;
                }
                ++level;
                putchar(c);
                putchar('\n');
                removeSpaces();
                spamchar(' ',2*level);
                newLine=1;
                break;
            case '}':
                if(escapeC||escapeCom1||escapeCom2||escapeS){
                    putchar(c);
                    break;
                }
                --level;
                if(!newLine){
                    putchar('\n');
                }
                spamchar(' ',2*level);
                putchar(c);
                putchar('\n');
                newLine=1;
                removeSpaces();
                break;
            case '\n':
                putchar(c);
                spamchar(' ',2*level);
                removeSpaces();
                newLine=1;
                escapeCom1=0;
                break;
            default:
                putchar(c);
                newLine=0;
                break;
        }
        c=getchar();
    }
    return 0;
}
