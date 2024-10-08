#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 50

// ฟังก์ชันสำหรับเรียงลำดับตัวอักษรในคำ (ใช้ bubble sort)
void sortWord(char* word) {
    int len = strlen(word);
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (word[j] > word[j+1]) {
                char temp = word[j];
                word[j] = word[j+1];
                word[j+1] = temp;
            }
        }
    }
}

typedef struct {
    char original[MAX_WORD_LEN + 1];
    char sorted[MAX_WORD_LEN + 1];
} Word;

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    Word* dictionary = (Word*)malloc(m * sizeof(Word));
    
    // รับคำในคลังคำศัพท์
    for (int i = 0; i < m; i++) {
        scanf("%s", dictionary[i].original);
        strcpy(dictionary[i].sorted, dictionary[i].original);
        sortWord(dictionary[i].sorted);  // จัดเรียงตัวอักษรในคำ
    }

    // ตรวจสอบคำที่ต้องการค้นหา
    for (int i = 0; i < n; i++) {
        char query[MAX_WORD_LEN + 1];
        char sortedQuery[MAX_WORD_LEN + 1];
        
        // รับคำที่ต้องการตรวจสอบ
        scanf("%s", query);
        strcpy(sortedQuery, query);
        sortWord(sortedQuery);  // จัดเรียงตัวอักษรในคำที่ต้องการค้นหา
        
        // ค้นหาอนาแกรมในคลังคำศัพท์ตามลำดับที่ป้อนเข้า
        int found = 0;
        for (int j = 0; j < m; j++) {
            if (strcmp(sortedQuery, dictionary[j].sorted) == 0) {
                if (found) {
                    printf(" ");
                }
                printf("%s", dictionary[j].original);
                found = 1;
            }
        }
        printf("\n");
    }
    
    // ปล่อยหน่วยความจำที่จองไว้
    free(dictionary);
    
    return 0;
}
