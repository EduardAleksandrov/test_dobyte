#include <iostream>
#include <vector>

int main() {
    const int num_digits = 6; // Количество цифр с каждой стороны
    const int base = 13;      // Система счисления
    const int max_sum = num_digits * (base - 1); // 6 * 12 = 72

    // dp[i][j] — количество способов получить сумму j, используя i цифр
    std::vector<std::vector<long long>> dp(num_digits + 1, std::vector<long long>(max_sum + 1, 0));

    // Базовый случай: 0 цифр могут дать только сумму 0 (1 способ)
    dp[0][0] = 1;

    // Заполнение таблицы DP
    for (int i = 1; i <= num_digits; ++i) {
        for (int s = 0; s <= max_sum; ++s) {
            for (int digit = 0; digit < base; ++digit) {
                if (s >= digit) {
                    dp[i][s] += dp[i - 1][s - digit];
                }
            }
        }
    }

    // Считаем сумму квадратов количеств для каждой возможной суммы
    long long total_combinations_6_digits = 0;
    for (int s = 0; s <= max_sum; ++s) {
        total_combinations_6_digits += (dp[num_digits][s] * dp[num_digits][s]);
    }

    // Умножаем на 13, так как средняя цифра может быть любой (0-12)
    long long final_answer = total_combinations_6_digits * base;

    std::cout << final_answer << std::endl;

    return 0;
}