#include <math.h>

static int current_pi_version = 0; // 0 - Лейбниц, 1 - Валлис

// Ряд Лейбница
static float pi_leibniz(int K) {
    float sum = 0.0;
    for (int i = 0; i < K; i++) {
        if (i % 2 == 0) 
            sum += 1.0 / (2*i + 1);
        else 
            sum -= 1.0 / (2*i + 1);
    }
    return 4 * sum;
}

// Формула Валлиса
static float pi_wallis(int K) {
    float product = 1.0;
    for (int i = 1; i <= K; i++) {
        product *= (4.0*i*i) / (4.0*i*i - 1);
    }
    return 2 * product;
}

// Основная функция 
float Pi(int K) {
    if (K <= 0) return 0;
    if (current_pi_version == 0)
        return pi_leibniz(K);
    else
        return pi_wallis(K);
}

// Функция переключения версии (для program2)
void switch_pi(int version) {
    if (version == 0 || version == 1)
        current_pi_version = version;
}