#include <iostream>
#include <vector>
#include <map>

#include "Person.h"
#include "IDictionary.h"

// Функция для создания гистограммы
IDictionary<int, int> createHistogram(const std::vector<Person>& sequence, int minValue, int maxValue, int binSize) {
    std::map<int, int> histogram;

    // Инициализация гистограммы
    for (int i = minValue; i <= maxValue; i += binSize) {
        histogram[i] = 0;
    }

    // Заполнение гистограммы
    for (const Person& person : sequence) {
        int bin = (person.age - minValue) / binSize * binSize + minValue;
        histogram[bin]++;
    }

    return histogram;
}

int main() {
    // Пример входной последовательности
    std::vector<Person> people = {
            {"Alice", 25},
            {"Bob", 30},
            {"Charlie", 22},
            {"David", 35},
            {"Eva", 28}
    };

    // Параметры гистограммы
    int minValue = 20;
    int maxValue = 40;
    int binSize = 5;

    // Создание гистограммы
    std::map<int, int> histogram = createHistogram(people, minValue, maxValue, binSize);

    // Вывод результатов
    std::cout << "Histogram:\n";
    for (const auto& entry : histogram) {
        std::cout << "[" << entry.first << "-" << entry.first + binSize << "]: " << entry.second << " people\n";
    }

    return 0;
}
