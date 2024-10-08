#include <stdio.h>
#include <string.h>
#define MAX 100000
int main(){
    int len = 0,indx=0;
    char text[MAX+1];
    char ans[MAX+1];

    fgets(text,sizeof(text),stdin);

    for(int i = 0; text[i] != '\0';i++){
        if(text[i]=='<'){
            indx = 0;
        }else if(text[i]=='>'){
            
            indx = len;
        }else{
            // printf("index is %d\n",indx);
            // printf("len is %d\n",len);
            for(int j = len;j>indx;j--){
                printf("j is %d\n",j);
                ans[j]=ans[j-1];
                // printf("%c\n",ans[j-1]);
            }
            ans[indx]=text[i];
            indx++;
            len++;
        }
    }
    ans[len]='\0';
    printf("%s\n",ans);
    return 0;
}