#include <stdio.h>
#include <stdbool.h>
#define NMAX 1000000
bool cdigi(int number, int k) {
    while (number > 0) {
        if (number % 10 == k) {
            return true;
        }
        number /= 10;
    }
    return false;
}
int main() {
    int n, k,x;
    int Mdrink[NMAX];
    bool exit[NMAX] = {false};
    scanf("%d %d", &n, &k);
    if (n>=2){
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        if (x>100){
            return 0;
        }else{
            
        }
    }
    int re_player = n , player = 0, count = 1,t;
    /*
        1.รอบที่หารด้วย K
        2.รอบที่มีเลขโดด K
    */
    while (re_player > 1) {  //หาคนยังมากกว่า่ 1 คน
        bool drink = (count % k == 0) || cdigi(count, k); // จะเป็นจริงเมื่อ count หาร k ลงตัว หรือ มีเลขโดด
        if (drink && !exit[player]) { //จะดื่มเมื่อ เป็นจริง และ ยังอยู่ในเกม
            Mdrink[player]--; //ลดจำนวนเครื่องดื่มที่ดื่มได้
            if (Mdrink[player] == 0) { //ถ้าจำนวนที่ดื่มได้เป็นศูนย์
                exit[player] = true; // ออกจากเกม
                re_player--; //จำนวนผู้เล่นที่เหลืออยู่ลดลง
            }
        }
        count++;//คนถัดไป
        player = (player + 1) % n; //คนที่
        /*
        ex.5
        1%5 = 1
        2%5 = 2
        3%5 = 3
        4%5 = 4
        5%5 = 0
        */
    }
    // True in Exit
    for (int i = 0; i < n; i++) {
        if (!exit[i]) {
            printf("%d\n", i + 1);
            break;
        }
    }
    }
    return 0;
}
