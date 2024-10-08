#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD 50

typedef struct keep
{
    char word[MAX_WORD]; //คำศัพท์เดิม
    char sortword[MAX_WORD]; //คำศัพท์เรียง A-Z
} Word_t;

void BubleSortWord(char* word){ //รับคำศัพท์
    int n = strlen(word); //คำนวนตัวอักษร
    for(int i = 0; i < n - 1; i++){ //เรียงจากน้อยไปมาก n^2 A-Z
        for(int j = 0; j < n - i - 1; j++){
            if(word[j] > word[j + 1]){
                char tmp = word[j];
                word[j] = word[j + 1];
                word[j + 1] = tmp;
            }
        }
    }
}

int main(){
    char CurrentWord[MAX_WORD]; //คำศัพท์ปัจจุบัน
    char CurrentSortWord[MAX_WORD]; //คำศัพท์ปัจจุบันที่เรียง A-Z
    int m,n;
    scanf("%d %d",&m,&n);

    Word_t *array = (Word_t*)malloc(m * sizeof(Word_t));

    for(int i = 0; i < m; i++){
        scanf("%s",array[i].word); //รับคำศัพท์ทั้งหมด
        strcpy(array[i].sortword,array[i].word); //คัดลองคำศัพท์ไปเก็บใน SortWord (ยังไม่ BBsort)
        BubleSortWord(array[i].sortword); //BBsort แต่ละคำศัพท์
    }

    for(int i = 0; i < n; i++){
        scanf("%s",CurrentWord); //รับคำศัพท์ปัจจุบัน
        strcpy(CurrentSortWord,CurrentWord); //คัดลองคำศัพท์ไปเก็บใน SortWord (ยังไม่ BBsort)
        BubleSortWord(CurrentSortWord); //BBsort

    int check = 0; 
    for(int i = 0; i < m; i++){
        if(strcmp(CurrentSortWord,array[i].sortword) == 0){ //เปรียบเทียบคำศัพท์ปัจจุบันที่เรียงกับคำศัพท์เดิมที่เรียง
            if(check){
                printf(" ");
            }
            printf("%s",array[i].word);
            check = 1;
        }
    }
    printf("\n");
}
return 0;
}