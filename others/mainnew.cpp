#include <iostream>
#include <vector>

using namespace std;

const int MAX_SUM = 72; // Максимальная сумма для 6 цифр в 13-ти значной системе

// Функция для подсчета количества способов получить каждую возможную сумму
vector<long long> countWays(int digits) {
    vector<long long> ways(MAX_SUM + 1, 0);
    ways[0] = 1; // Один способ получить сумму 0, используя 0 цифр

    for (int d = 0; d < digits; ++d) {
        vector<long long> newWays(MAX_SUM + 1, 0);
        for (int sum = 0; sum <= MAX_SUM; ++sum) {
            for (int digit = 0; digit < 13; ++digit) {
                if (sum + digit <= MAX_SUM) {
                    newWays[sum + digit] += ways[sum];
                }
            }
        }
        ways = newWays; // Обновляем количество способов
    }
    
    return ways;
}

int main() {
    // Получаем количество способов для 6 цифр
    vector<long long> ways = countWays(6);

    long long beautifulCount = 0;

    // Считаем количество "красивых" чисел
    for (int sum = 0; sum <= MAX_SUM; ++sum) {
        beautifulCount += ways[sum] * ways[sum]; // квадрат числа способов
    }

    // Вывод результата
    cout << beautifulCount << endl;
    return 0;
}