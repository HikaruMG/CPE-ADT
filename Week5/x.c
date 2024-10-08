#include <stdio.h>
#include <string.h>
#define MAX 10
int main(){
    char d[MAX];
    char ans[MAX+1];
    fgets(d,sizeof(d),stdin);

    int size = sizeof(d) / sizeof(d[0]);
    d[1]=d[-2];
    // Print the array elements
    printf("Array elements:\n");
    for(int i = 0; i < size; i++) {
        printf("%c ",d[i]);
    }
}