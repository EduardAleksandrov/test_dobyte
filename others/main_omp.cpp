/*
    Полный перебор с многопоточностью
*/
#include <iostream>
#include <omp.h>
#include <cmath>
#include <string>

using namespace std;

// Функция для преобразования символа в соответствующее числовое значение
int charToValue(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'C') {
        return c - 'A' + 10;
    }
    return 0;
}

// Проверка, является ли число красивым
bool isBeautiful(const string& number) {
    int firstHalfSum = 0, secondHalfSum = 0;
    
    for (int i = 0; i < 6; i++) {
        firstHalfSum += charToValue(number[i]);
    }
    for (int i = 6; i < 13; i++) {
        secondHalfSum += charToValue(number[i]);
    }
    
    return firstHalfSum == secondHalfSum;
}

int main() {
    long long count = 0;
    const int totalDigits = 13;
    const int base = 13;
    
    // Общее количество комбинаций
    long long totalCombinations = pow(base, totalDigits);
    
    // Параллельный расчет
    #pragma omp parallel
    {
        long long localCount = 0;

        #pragma omp for
        for (long long i = 0; i < totalCombinations; i++) {
            string number(totalDigits, '0');
            long long temp = i;

            // Преобразуем i в тринадцатиричное число
            for (int j = totalDigits - 1; j >= 0; j--) {
                int digit = temp % base;
                number[j] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
                temp /= base;
            }
            
            // Проверяем, является ли число красивым
            if (isBeautiful(number)) {
                localCount++;
            }
        }

        // Объединение локальных подсчетов
        #pragma omp atomic
        count += localCount;
    }

    cout << count << endl; // Выводим количество красивых чисел
    return 0;
}