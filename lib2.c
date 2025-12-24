#include <math.h>

static int current_e_version = 0; // 0 - предел, 1 - ряд

static long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++)
        result *= i;
    return result;
}

// (1 + 1/x)^x
static float e_limit(int x) {
    if (x <= 0) return 2.0;
    return pow(1.0 + 1.0/x, x);
}

// Сумма ряда 1/n!
static float e_series(int x) {
    float sum = 0.0;
    // Ограничиваем до 20 для безопасности
    int limit = (x > 20) ? 20 : x;
    for (int n = 0; n <= limit; n++) {
        sum += 1.0 / factorial(n);
    }
    return sum;
}

// Основная функция
float E(int x) {
    if (x < 0) return 0;
    if (current_e_version == 0)
        return e_limit(x);
    else
        return e_series(x);
}

// Функция переключения версии (для program2)
void switch_e(int version) {
    if (version == 0 || version == 1)
        current_e_version = version;
}