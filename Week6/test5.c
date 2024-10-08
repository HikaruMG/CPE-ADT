#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100000

typedef struct {
    int length;
    char side;
} Cars;
Cars LandQueue[MAX];
Cars IslandQueue[MAX];
int frontL = 0, rearL = 0;
int frontR = 0, rearR = 0;
void enqueueL(int l) {
    LandQueue[rearL].length = l;
    LandQueue[rearL].side = 'L';
    rearL++;
}
void enqueueR(int l) {
    IslandQueue[rearR].length = l;
    IslandQueue[rearR].side = 'R';
    rearR++;
}
Cars dequeueR() {
    return IslandQueue[frontR++];
}
bool iscarr() {
    return frontR == rearR;
}
bool iscarl() {
    return frontL == rearL;
}
Cars dequeueL() {
    return LandQueue[frontL++];
}
int main() {
    int l, n;
    scanf("%d", &l);
    l *= 100; 
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int l;
        char side;
        scanf("%d %c", &l, &side);
        if (side == 'L') {
            enqueueL(l);
        } else {
            enqueueR(l);
        }
    }

    int rounds= 0;
    bool onFerry = true;  //ออกจากฝั่ง
    int currentLength;

    while (!iscarl() || !iscarr()) {
        currentLength = 0;
        rounds++;
        if (onFerry) { //อยู่ฝัง
            while (!iscarl() && currentLength + LandQueue[frontL].length <= l) {
                currentLength += dequeueL().length;
            }
        } else {
            //เกาะ
            while (!iscarr() && currentLength + IslandQueue[frontR].length <= l) {
                currentLength += dequeueR().length;
            }
        }
        onFerry = !onFerry;
    }
    printf("%d\n",rounds);

    return 0;
}
