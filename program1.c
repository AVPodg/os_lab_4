// program1.c - статическое связывание с lib1.c и lib2.c
#include <stdio.h>
#include "lib.h"

int main() {
    int command;
    
    printf("Программа 1 (статическая линковка)\n");
    printf("1 K - вычислить π (K > 0)\n");
    printf("2 x - вычислить e (x >= 0)\n");
    printf("0 - выход\n");
    
    while (1) {
        printf("> ");
        if (scanf("%d", &command) != 1) break;
        
        if (command == 0) break;
        
        if (command == 1) {
            int K;
            if (scanf("%d", &K) != 1) {
                printf("Ошибка ввода\n");
                while (getchar() != '\n');
                continue;
            }
            if (K <= 0) {
                printf("K должно быть > 0\n");
            } else {
                printf("π(%d) = %f\n", K, Pi(K));
            }
        } 
        else if (command == 2) {
            int x;
            if (scanf("%d", &x) != 1) {
                printf("Ошибка ввода\n");
                while (getchar() != '\n');
                continue;
            }
            if (x < 0) {
                printf("x должно быть >= 0\n");
            } else {
                printf("e(%d) = %f\n", x, E(x));
            }
        } 
        else {
            printf("Неизвестная команда\n");
        }
        
        // Очистка буфера
        while (getchar() != '\n');
    }
    
    printf("Выход\n");
    return 0;
}