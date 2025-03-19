#include <iostream>
#include <map>
#include <string>
#include <clocale>

#ifdef _WIN32
#include "windows.h"
#endif

// Функция для приведения символа к нижнему регистру (онли английская раскладка)
char toLower(char ch) {
    if (ch >= 'A' && ch <= 'Z')
        return ch + ('a' - 'A');
    return ch;
}

// Функция нормализации строки и приведение к нижнему регистру
std::string normalize(const std::string& s) {
    std::string res;
    for (char ch : s) {
        if (ch == ' ') continue;
        res.push_back(toLower(ch));
    }
    return res;
}

bool isAnagram(const std::string& s1, const std::string& s2) {

    std::string str1 = normalize(s1);
    std::string str2 = normalize(s2);

    // Если длины строк различаются, то уже не анаграмма
    if (str1.size() != str2.size()) return false;

    std::map<char, int> freq1;
    std::map<char, int> freq2;

    // Подсчёт количества символов в первой строке
    for (char ch : str1) {
        freq1[ch]++;
    }

    // Подсчёт количества символов во второй строке
    for (char ch : str2) {
        freq2[ch]++;
    }

    // Сравниваю два отображения
    return freq1 == freq2;
}

int main() {
    setlocale(LC_ALL, "");
#ifdef _WIN32
    SetConsoleCP(866);
    SetConsoleOutputCP(866);
#endif

    std::string str1, str2;

    std::cout << "Введите первую строку: ";
    getline(std::cin, str1);
    std::cout << "Введите вторую строку: ";
    getline(std::cin, str2);

    if (isAnagram(str1, str2))
        std::cout << "Строки являются анаграммами.\n";
    else
        std::cout << "Строки НЕ являются анаграммами.\n";

    return 0;
}
