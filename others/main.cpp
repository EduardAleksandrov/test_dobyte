/*
    Полный перебор 
    
    Ключевая идея заключается в том, чтобы перебрать все возможные комбинации 13-ти 
    значных чисел и проверить, являются ли они красивыми. Мы будем использовать рекурсивный 
    или переборный метод для генерации всех комбинаций, поскольку максимальное количество 
    комбинаций будет допустимым для современных компьютеров.
*/
#include <iostream>
#include <string>

using namespace std;

// Функция для преобразования символа в соответствующее числовое значение
int charToValue(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0'; // Преобразование символа в число (0-9)
    } else if (c >= 'A' && c <= 'C') {
        return c - 'A' + 10; // Преобразование символа в число (A=10, B=11, C=12)
    }
    return 0; // Для безопасности
}

// Проверка, является ли число красивым
bool isBeautiful(const string& number) {
    int firstHalfSum = 0, secondHalfSum = 0;
    
    // Суммируем первую и вторую половины
    for (int i = 0; i < 6; i++) {
        firstHalfSum += charToValue(number[i]);
    }
    for (int i = 6; i < 13; i++) {
        secondHalfSum += charToValue(number[i]);
    }
    
    return firstHalfSum == secondHalfSum;
}

// Рекурсивная функция для генерации всех 13-значных чисел
void generateNumbers(string current, int pos, long long& count) {
    if (pos == 13) {
        if (isBeautiful(current)) {
            count++;
        }
        return;
    }
    
    // Перебираем все возможные символы (0-9, A-C)
    for (char c : "0123456789ABC") {
        generateNumbers(current + c, pos + 1, count);
    }
}

int main() {
    long long count = 0;
    generateNumbers("", 0, count); // Начинаем генерацию начиная с пустой строки
    cout << count << endl; // Выводим количество красивых чисел
    return 0;
}