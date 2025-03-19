#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cctype>
#include <clocale>

//Для работы локали и определения OC
#ifdef _WIN32
#include "windows.h"
#endif

/* 
* Решил добавить кучу проверок чтобы не сломать программу
* Функция для получения корректного номера телефона с проверкой формата
* Формат: "69-70-30" (8 символов: две цифры, дефис, две цифры, дефис, две цифры)
*/
std::string getValidatedPhone() {
    std::string phone;
    while (true) {
        std::cout << "Введите номер телефона (формат: 69-70-30): ";
        getline(std::cin, phone);

        if (phone.empty()) {
            std::cout << "Ошибка: ввод не может быть пустым. Попробуйте ещё раз.\n";
            continue;
        }

        if (phone.size() != 8) {
            std::cout << "Ошибка: номер должен состоять из 8 символов. Попробуйте ещё раз.\n";
            continue;
        }
        
        // Проверяю, что символы в нужных позициях корректны:
        if (!isdigit(phone[0]) || !isdigit(phone[1]) ||
            phone[2] != '-' ||
            !isdigit(phone[3]) || !isdigit(phone[4]) ||
            phone[5] != '-' ||
            !isdigit(phone[6]) || !isdigit(phone[7]))
        {
            std::cout << "Ошибка: формат неверный. Номер должен быть в формате \"69-70-30\".\n";
            continue;
        }
        // Если все проверки пройдены, возвращаю корректный номер
        break;
    }
    return phone;
}

// Функция для очистки экрана в зависимости от ОС (подсмотрел препроцессорные директивы)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Функция для безопасного получения непустой строки от пользователя с выводом указанного сообщения
void safeGetline(std::string& input, const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        getline(std::cin, input);
        if (!input.empty())
            break;
        std::cout << "Ошибка: ввод не может быть пустым. Попробуйте ещё раз.\n";
    }
}

// Функция для корректного ввода числа (выбора пункта меню)
int getValidatedChoice() {
    int choice = 0;
    std::string input;
    while (true) {
        std::cout << "Введите номер действия: ";
        getline(std::cin, input);
        if (input.empty()) {
            std::cout << "Ошибка: ввод не может быть пустым.\n";
            continue;
        }
        try {
            choice = stoi(input);
            break;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: введите корректное число.\n";
        }
    }
    return choice;
}

// Функция для вставки номера в отсортированный вектор
void insertSorted(std::vector<std::string>&vec, const std::string& phone) {
    auto pos = lower_bound(vec.begin(), vec.end(), phone);
    vec.insert(pos, phone);
}

int main() {
    // Установил локаль для корректного отображения кириллицы
    setlocale(LC_ALL, "");
#ifdef _WIN32
    // Установил кодовую страницу консоли
    SetConsoleCP(866);
    SetConsoleOutputCP(866);
#endif

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Контейнеры для хранения данных справочника:
    // phone2surname: номер -> фамилия
    // surname2phones: фамилия -> вектор номеров
    std::map<std::string, std::string> phone2surname;
    std::map<std::string, std::vector<std::string>> surname2phones;

    while (true) {
        clearScreen();
        std::cout << "========================\n";
        std::cout << "  Телефонный справочник\n";
        std::cout << "========================\n";
        std::cout << "1. Добавить запись (номер и фамилия)\n";
        std::cout << "2. Найти фамилию по номеру\n";
        std::cout << "3. Найти номер(а) по фамилии\n";
        std::cout << "4. Выход\n";

        int choice = getValidatedChoice();

        if (choice == 1) {
            // Добавление записи: читаем номер телефона и фамилию
            std::string phone = getValidatedPhone();
            std::string surname;
            safeGetline(surname, "Введите фамилию: ");

            // Добавляем запись в справочник
            phone2surname[phone] = surname;
            insertSorted(surname2phones[surname], phone);

            std::cout << "\nЗапись успешно добавлена!\n";
        }
        else if (choice == 2) {
            // Поиск фамилии по номеру
            std::string phone = getValidatedPhone();
            if (phone2surname.find(phone) != phone2surname.end()) {
                std::cout << "Фамилия: " << phone2surname[phone] << "\n";
            }
            else {
                std::cout << "Запись не найдена.\n";
            }
        }
        else if (choice == 3) {
            // Поиск номера(ов) по фамилии
            std::string surname;
            safeGetline(surname, "Введите фамилию для поиска: ");
            if (surname2phones.find(surname) != surname2phones.end()) {
                std::cout << "Номера: ";
                bool first = true;
                for (const auto& phone : surname2phones[surname]) {
                    if (!first)
                        std::cout << " ";
                    std::cout << phone;
                    first = false;
                }
                std::cout << "\n";
            }
            else {
                std::cout << "Запись не найдена.\n";
            }
        }
        else if (choice == 4) {
            std::cout << "Выход...\n";
            break;
        }
        else {
            std::cout << "Неверный выбор. Попробуйте ещё раз.\n";
        }
        std::cout << "\nНажмите Enter для продолжения...";
        std::string dummy;
        getline(std::cin, dummy);
    }

    return 0;
}
