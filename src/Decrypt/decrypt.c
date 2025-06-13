#include "decrypt.h"
#include <stdlib.h>

char binToChar(int arr[]) {
    int sum = 0, x = 64;
    for (int i = 0; i < 7; i++) {
        if (arr[i] == 1) sum += x;
        x /= 2;
    }
    return sum;
}

void grafToBin(Graph graf, Key koenci, int arr[]) {
    for (int i = 0; i < 7; i++) arr[i] = 0;
    int first = koenci.first;
    int i = koenci.last - 1;
    int prev = first - 1;
    int id = 6;

    if (koenci.first != koenci.last) {
        if (graf.len == 2) {
            int x = graf.matrix[i][prev];
            for (int k = 1; k < x; k++) arr[id--] = 0;
            arr[id--] = 1;
            x = graf.matrix[prev][i];
            for (int k = 1; k < x; k++) arr[id--] = 0;
            arr[id--] = 1;
        } else {
            while (1) {
                int j;
                if (i == koenci.last - 1) {
                    int x = graf.matrix[i][prev];
                    for (int k = 1; k < x; k++) arr[id--] = 0;
                    arr[id--] = 1;
                }
                for (j = 0; j < graf.len && (graf.matrix[i][j] == 0 || j == prev); j++);
                int x = graf.matrix[i][j];
                for (int k = 1; k < x; k++) arr[id--] = 0;
                arr[id--] = 1;
                prev = i;
                i = j;
                if (i == koenci.first - 1) break;
            }
        }
    } else {
        int x = graf.matrix[0][0];
        for (int k = 1; k < x; k++) arr[id--] = 0;
        arr[id--] = 1;
    }
}

char* decrypt(Message msg, keyList kList) {
    char* decryptedMsg = malloc((msg.len + 1) * sizeof(char));
    if (!decryptedMsg) return NULL;

    int xor = 127;
    graphList g = msg.gList;
    keyList k = kList;

    for (int i = 0; i < msg.len; i++) {
        int arr[7];
        grafToBin(g->graf, k->info, arr);
        decryptedMsg[i] = binToChar(arr) ^ xor;
        g = g->next;
        k = k->next;
    }

    decryptedMsg[msg.len] = '\0';  // ? Critical Fix
    return decryptedMsg;
}

