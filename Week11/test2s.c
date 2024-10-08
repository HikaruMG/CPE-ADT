#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 20
#define MAX_USERS 100000
#define HASH_SIZE 200003 // A prime number for better distribution

typedef struct User {
    char name[MAX_NAME_LENGTH + 1];
    int count;
    struct User *next;
} User;

User *hash_table[HASH_SIZE];

unsigned int hash(char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str++;
    }
    return hash % HASH_SIZE;
}

User* find_user(char *name) {
    unsigned int index = hash(name);
    User *current = hash_table[index];
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void register_user(char *name) {
    User *user = find_user(name);
    if (!user) {
        unsigned int index = hash(name);
        user = (User *)malloc(sizeof(User));
        strcpy(user->name, name);
        user->count = 1;
        user->next = hash_table[index];
        hash_table[index] = user;
        printf("OK\n");
    } else {
        char base_name[MAX_NAME_LENGTH + 1];
        int num = 0;
        int len = strlen(name);
        for (int i = len - 1; i >= 0; i--) {
            if (name[i] >= '0' && name[i] <= '9') {
                num = num * 10 + (name[i] - '0');
            } else {
                strncpy(base_name, name, i + 1);
                base_name[i + 1] = '\0';
                break;
            }
        }
        if (num == 0) {
            strcpy(base_name, name);
        }
        int new_num = user->count;
        char new_name[MAX_NAME_LENGTH + 1];
        do {
            sprintf(new_name, "%s%d", base_name, new_num);
            new_num++;
        } while (find_user(new_name) != NULL);
        unsigned int index = hash(new_name);
        User *new_user = (User *)malloc(sizeof(User));
        strcpy(new_user->name, new_name);
        new_user->count = 1;
        new_user->next = hash_table[index];
        hash_table[index] = new_user;
        user->count = new_num;
        printf("Change to %s\n", new_name);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    char name[MAX_NAME_LENGTH + 1];
    for (int i = 0; i < n; i++) {
        scanf("%s", name);
        register_user(name);
    }
    return 0;
}
