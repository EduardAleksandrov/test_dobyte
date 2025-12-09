/*
    Разделение по суммам

    Суммирование: Генерируются все возможные суммы для 6 цифр (для первой и второй половин) с помощью generateSums().
    Сохранение результатов: Используется map для хранения количества способов для каждой суммы, 
    что позволяет быстро проверить, сколько различных комбинаций повторяются.
    Комбинирование результатов: Для каждой уникальной суммы первой половины ищется соответствующая 
    сумма во второй половине и учитывается общее количество "красивых" чисел.

    Результат: 707_972_099_627
*/

#include <iostream>
#include <vector>
#include <map>
#include <omp.h>
#include <cmath>

using namespace std;

// Функция для преобразования символа в соответствующее числовое значение
// int charToValue(char c) {
//     return (c >= '0' && c <= '9') ? (c - '0') : (c - 'A' + 10); // A=10, B=11, C=12
// }

// Генерация всех возможных сумм для 6 цифр с использованием OpenMP
void generateSums(map<int, long long>& sumCount, int digitCount) {
    long long totalComb = 1; // общее количество возможных комбинаций 6-значных чисел в тринадцатиричной системе счисления
    for (int d = 0; d < digitCount; d++) {
        totalComb *= 13; // Перебираем 13^digitCount
    }

    #pragma omp parallel
    {
        // Локальная таблица для хранения сумм в каждом потоке
        map<int, long long> localSumCount;

        #pragma omp for
        for (long long i = 0; i < totalComb; ++i) {
            int sum = 0;
            int temp = i;
            // преобразование числа из десятичной системы счисления в тринадцатиричную, 
            // при этом одновременно рассчитывается сумма его разрядов.
            for (int j = 0; j < digitCount; ++j) {
                int digit = temp % 13; // Получаем текущий разряд
                sum += digit; // К сумме добавляем разряд
                temp /= 13; // Уменьшаем число
            }
            localSumCount[sum]++; // Увеличиваем количество раз для каждой суммы
        }

        // Объединение локальных счетчиков в глобальный
        #pragma omp critical
        {
            for (const auto& entry : localSumCount) {
                sumCount[entry.first] += entry.second;
            }
        }
    }
}

int main() {
    // Словарь для хранения количества комбинаций по каждой вероятной сумме
    map<int, long long> sumCountFirstHalf, sumCountSecondHalf;

    // Генерируем суммы для первых и вторых половин с использованием OpenMP
    generateSums(sumCountFirstHalf, 6);
    generateSums(sumCountSecondHalf, 6);

    long long count = 0;

    // Считаем количество "красивых" чисел
    for (const auto& entry : sumCountFirstHalf) {
        int sumValue = entry.first; // Сумма для первой половины
        long long waysFirst = entry.second; // Количество комбинаций для данной суммы

        // Если есть соответствующая сумма во второй половине
        if (sumCountSecondHalf.find(sumValue) != sumCountSecondHalf.end()) {
            long long waysSecond = sumCountSecondHalf[sumValue]; // Количество способов для второй половины

            // Умножаем, чтобы получить количество красивых комбинаций
            count += waysFirst * waysSecond;
        }
    }

    cout << count << endl; // Выводим количество красивых чисел
    return 0;
}