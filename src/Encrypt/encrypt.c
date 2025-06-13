#include "encrypt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // for getpid()

void charToBinary(char x, int res[7]) {
    int divd = 64;
    for (int i = 0; divd != 0; divd /= 2, i++) {
        res[i] = (x >= divd) ? (x -= divd, 1) : 0;
    }
}

int countOne(int bin[7]) {
    int cnt = 0;
    for (int i = 0; i < 7; i++) {
        if (bin[i] == 1) cnt++;
    }
    return cnt;
}

void shuffle(int arr[], int len) {
    for (int i = 0; i < len; i++) arr[i] = i + 1;
    for (int i = len - 1; i > 0; i--) {
        int ranNum = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[ranNum];
        arr[ranNum] = temp;
    }
}

int countZero(int arr[], int x) {
    int sum = 0, cnt = 0, i = 0;
    while (i < 7 && cnt < x) {
        if (arr[i] == 1) cnt++;
        i++;
    }
    while (i < 7 && arr[i] != 1) {
        sum++;
        i++;
    }
    return sum + 1;
}

void msgToGraf(Graph* graf, int len, int arr[7], keyList* kList) {
    int order[len];
    shuffle(order, len);
    int first = order[0], last = order[len - 1];

    if (len != 2) {
        for (int i = 0; i < len - 1; i++) {
            int val = countZero(arr, i + 1);
            graf->matrix[order[i] - 1][order[i + 1] - 1] = val;
            graf->matrix[order[i + 1] - 1][order[i] - 1] = val;
        }
        int val = countZero(arr, len);
        graf->matrix[first - 1][last - 1] = val;
        graf->matrix[last - 1][first - 1] = val;
    } else {
        graf->matrix[first - 1][last - 1] = countZero(arr, 1);
        graf->matrix[last - 1][first - 1] = countZero(arr, 2);
    }

    Key koenci = {first, last};
    keyAppend(kList, koenci);
}

Message encrypt(char text[], keyList* kList) {
    Message msg = {0, NULL};
    int len = strlen(text);
    msg.len = len;

    int xor = 127;
    srand((unsigned int)(time(NULL)) ^ getpid());

    for (int i = 0; i < len; i++) {
        char karakter = text[i] ^ xor;
        int arr[7];
        charToBinary(karakter, arr);
        int one = countOne(arr);
        Graph graf;
        createGraph(&graf, one);
        msgToGraf(&graf, one, arr, kList);
        graphAppend(&msg.gList, graf);
    }

    return msg;
}

