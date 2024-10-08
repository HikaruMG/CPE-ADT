#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ID 100000 //รับค้าข้อมูลมากสุด 100000
#define MAX_NAME 21 //รับค้าชื่อมากสุด 20
#define HASH_SIZE 100003 // จำนวนช่องเก็บข้อมูล

typedef struct User {
    int count; //จำนวนชื่อที่ซ้ำ
    char name[MAX_NAME]; //ชื่อ
    struct User *next; //Linked List
} User;
User *HashArray[HASH_SIZE]; //Table ช่องเก็บข้อมูล Node User

unsigned int hash(char *str) { //Hash Function รับชื่อมาแล้วคืน Hash
    unsigned int hash = 0; //เริ่มที่ 0
    while (*str) { //ลูปตามจำนวนตัวอักษรในสตริง
        hash = (hash * 31) + *str++; //วคิด hash ของตัวอักษร ASCII
    }
    return hash % HASH_SIZE; //คืน Hash Index Table
}

User* Check_ID(char *name) { //ตรวจสอบว่ามีชื่ออยู่ใน HashArray หรือไม่
    unsigned int index = hash(name); //หา index จากชื่อที่ Hash ออกมา
    User *current = HashArray[index]; //เข้าไปใน Array ที่ตรงกับ index ของชื่อที่ผ่านการ Hash แล้ว
    while (current) { //ลูปไปจนถึงชื้อสุดท้าย
        if (strcmp(current->name, name) == 0) { //ถ้าชื่อตรงกัน
            return current; //คืน Node ID ของชื่อ
        }
        current = current->next; //ไปต่อชื่อตัวถัดไป
    }
    return NULL; //ไม่พบชื่อ
}

void Add_ID(char *name) {
    User *user = Check_ID(name); //ตรวจสอบว่ามีชื่ออยู่ใน HashArray หรือไม่
    if (!user) { //ถ้าไม่มี
        unsigned int index = hash(name); //หา index จากชื่อที่ Hash ออกมา
        user = (User *)malloc(sizeof(User)); //สร้าง Node ID ใหม่
        strcpy(user->name, name); //เก็บชื่อลงใน Node Name
        user->count = 1; //เก็บจำนวนชื่อลงใน Node Count
        user->next = HashArray[index]; //เก็บชื่อลงใน Linked List
        HashArray[index] = user; //เก็บชื่อลงใน Array
        printf("OK\n");
    } else { //ถ้ามี
        int num = 0; //เลขต่อท้ายชื่อ
        char New_name[MAX_NAME];  //ชื่อใหม่
        int len = strlen(name); //ความยาวของชื่อ
        for (int i = len - 1; i >= 0; i--) { //ลูปตามจำนวนตัวอักษรจากข้างหลังไปข้างหน้า
            if (name[i] >= '0' && name[i] <= '9') { //ถ้ามีตัวเลขตจะเก็บค่าไว้ก่อน
                num = num * 10 + (name[i] - '0'); //แปลง ASCII เป็นตัวเลขโดยลบด้วย '0' และต่อไปที่ละหลัก
            } else {
                strncpy(New_name, name, i + 1); //ไม่ใช่ตัวเลขก็จะเอาตัวอักษรถึง i
                New_name[i + 1] = '\0'; //ตัวท้าย เป็น \0 จบ string
                break;
            }
        }
        if (num == 0) {
            strcpy(New_name, name); //ถ้าไม่มีตัวเลขให้เป็นชื่อเดิม
        }
        int new_num = user->count; //เลขจำนวนข้อมูลใน Linked list
        char new_name[MAX_NAME]; //ชื่อใหม่
        do {
            sprintf(new_name, "%s%d", New_name, new_num); //สร้างชื่อใหม่ที่เอาชื่อหลักมาต่อเลขข้างหลัง
            new_num++;
        } while (Check_ID(new_name) != NULL); //ถ้าชื่อที่สร้างใหม่มีอยู่ใน HashArray ก่อนจะเพิ่มเลขต่อท้ายไปเรื่อยๆ
        unsigned int index = hash(new_name); //หา index จากชื่อที่ Hash ออกมา
        User *New_ID = (User *)malloc(sizeof(User)); //สร้าง Node ID ใหม่
        strcpy(New_ID->name, new_name); //เก็บชื่อลงใน Node Name
        New_ID->count = 1; //เก็บจำนวนชื่อลงใน Node Count
        New_ID->next = HashArray[index]; //เก็บชื่อลงใน Linked List
        HashArray[index] = New_ID; //เก็บ Node ลงใน Array
        user->count = new_num;  
        printf("Change to %s\n", new_name);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    char name[MAX_NAME + 1];
    for (int i = 0; i < n; i++) {
        scanf("%s", name);
        Add_ID(name);
    }
    return 0;
}
