// program2.c - динамическая загрузка двух библиотек
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

int main() {
    void *lib1, *lib2;
    float (*Pi)(int);
    float (*E)(int);
    void (*switch_pi)(int);
    void (*switch_e)(int);
    
    char input[100]; // буфер для ввода 
    int cmd, arg;
    
    printf("Программа 2 (динамическая загрузка)\n");
    printf("0 - переключить реализации\n");
    printf("1 K - вычислить π (K > 0)\n");
    printf("2 x - вычислить e (x >= 0)\n");
    printf("exit - выход\n\n");
    
    // Загружаем первую библиотеку (π)
    // lib1 - дескриптор загруженной библиотеки
    lib1 = dlopen("./lib1.so", RTLD_LAZY); // dlopen() - функция динамической загрузки библиотеки
    if (!lib1) {
        printf("Ошибка загрузки lib1.so: %s\n", dlerror()); // dlerror() - возвращает строку с описанием последней ошибки dl-функций
        return 1;
    }
    
    // Загружаем вторую библиотеку (e)
    lib2 = dlopen("./lib2.so", RTLD_LAZY); // RTLD_LAZY - ленивая загрузка, значит что ОС не проверяет все функции библиотеки
    if (!lib2) {
        printf("Ошибка загрузки lib2.so: %s\n", dlerror());
        dlclose(lib1); // dlclose() - освобождает ресурсы, связанные с библиотекой
        return 1;
    }
    
    // Загружаем функции из lib1.so (π)
    Pi = (float (*)(int))dlsym(lib1, "Pi"); // dlsym() - ищет символ (функцию) в загруженной библиотеке(возвращает void* - адрес начала машинного кода)
    switch_pi = (void (*)(int))dlsym(lib1, "switch_pi");
    
    // Загружаем функции из lib2.so (e)
    E = (float (*)(int))dlsym(lib2, "E");
    switch_e = (void (*)(int))dlsym(lib2, "switch_e");
    
    if (!Pi || !E || !switch_pi || !switch_e) {
        printf("Ошибка загрузки функций\n");
        dlclose(lib1);
        dlclose(lib2);
        return 1;
    }
    
    // Текущие версии
    int pi_version = 0; // 0 - Лейбниц, 1 - Валлис
    int e_version = 0;  // 0 - предел, 1 - ряд
    
    while (1) {
        printf("> ");
        
        // Читаем строку
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        // Удаляем символ новой строки
        input[strcspn(input, "\n")] = 0;
        
        // Проверка на выход
        if (strcmp(input, "exit") == 0) break;
        
        // Парсим команду
        int parsed = sscanf(input, "%d %d", &cmd, &arg);
        
        if (parsed < 1) {
            printf("Неверная команда\n");
            continue;
        }
        
        if (cmd == 0) {
            pi_version = !pi_version;
            e_version = !e_version;
            
            switch_pi(pi_version);
            switch_e(e_version);
            
            printf("Реализации переключены:\n");
            printf("  π: %s\n", pi_version == 0 ? "Лейбниц" : "Валлис");
            printf("  e: %s\n", e_version == 0 ? "(1+1/x)^x" : "сумма ряда");
        }
        else if (cmd == 1) {
            if (parsed < 2) {
                printf("Использование: 1 K\n");
            } else if (arg <= 0) {
                printf("K должно быть > 0\n");
            } else {
                printf("π(%d) = %f\n", arg, Pi(arg));
            }
        }
        else if (cmd == 2) {
            if (parsed < 2) {
                printf("Использование: 2 x\n");
            } else if (arg < 0) {
                printf("x должно быть >= 0\n");
            } else {
                printf("e(%d) = %f\n", arg, E(arg));
            }
        }
        else {
            printf("Неизвестная команда\n");
        }
    }
    
    dlclose(lib1);
    dlclose(lib2);
    
    printf("Выход\n");
    return 0;
}