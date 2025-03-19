#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cctype>
#include <clocale>

//��� ������ ������ � ����������� OC
#ifdef _WIN32
#include "windows.h"
#endif

/* 
* ����� �������� ���� �������� ����� �� ������� ���������
* ������� ��� ��������� ����������� ������ �������� � ��������� �������
* ������: "69-70-30" (8 ��������: ��� �����, �����, ��� �����, �����, ��� �����)
*/
std::string getValidatedPhone() {
    std::string phone;
    while (true) {
        std::cout << "������� ����� �������� (������: 69-70-30): ";
        getline(std::cin, phone);

        if (phone.empty()) {
            std::cout << "������: ���� �� ����� ���� ������. ���������� ��� ���.\n";
            continue;
        }

        if (phone.size() != 8) {
            std::cout << "������: ����� ������ �������� �� 8 ��������. ���������� ��� ���.\n";
            continue;
        }
        
        // ��������, ��� ������� � ������ �������� ���������:
        if (!isdigit(phone[0]) || !isdigit(phone[1]) ||
            phone[2] != '-' ||
            !isdigit(phone[3]) || !isdigit(phone[4]) ||
            phone[5] != '-' ||
            !isdigit(phone[6]) || !isdigit(phone[7]))
        {
            std::cout << "������: ������ ��������. ����� ������ ���� � ������� \"69-70-30\".\n";
            continue;
        }
        // ���� ��� �������� ��������, ��������� ���������� �����
        break;
    }
    return phone;
}

// ������� ��� ������� ������ � ����������� �� �� (���������� ��������������� ���������)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ������� ��� ����������� ��������� �������� ������ �� ������������ � ������� ���������� ���������
void safeGetline(std::string& input, const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        getline(std::cin, input);
        if (!input.empty())
            break;
        std::cout << "������: ���� �� ����� ���� ������. ���������� ��� ���.\n";
    }
}

// ������� ��� ����������� ����� ����� (������ ������ ����)
int getValidatedChoice() {
    int choice = 0;
    std::string input;
    while (true) {
        std::cout << "������� ����� ��������: ";
        getline(std::cin, input);
        if (input.empty()) {
            std::cout << "������: ���� �� ����� ���� ������.\n";
            continue;
        }
        try {
            choice = stoi(input);
            break;
        }
        catch (const std::exception& e) {
            std::cout << "������: ������� ���������� �����.\n";
        }
    }
    return choice;
}

// ������� ��� ������� ������ � ��������������� ������
void insertSorted(std::vector<std::string>&vec, const std::string& phone) {
    auto pos = lower_bound(vec.begin(), vec.end(), phone);
    vec.insert(pos, phone);
}

int main() {
    // ��������� ������ ��� ����������� ����������� ���������
    setlocale(LC_ALL, "");
#ifdef _WIN32
    // ��������� ������� �������� �������
    SetConsoleCP(866);
    SetConsoleOutputCP(866);
#endif

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // ���������� ��� �������� ������ �����������:
    // phone2surname: ����� -> �������
    // surname2phones: ������� -> ������ �������
    std::map<std::string, std::string> phone2surname;
    std::map<std::string, std::vector<std::string>> surname2phones;

    while (true) {
        clearScreen();
        std::cout << "========================\n";
        std::cout << "  ���������� ����������\n";
        std::cout << "========================\n";
        std::cout << "1. �������� ������ (����� � �������)\n";
        std::cout << "2. ����� ������� �� ������\n";
        std::cout << "3. ����� �����(�) �� �������\n";
        std::cout << "4. �����\n";

        int choice = getValidatedChoice();

        if (choice == 1) {
            // ���������� ������: ������ ����� �������� � �������
            std::string phone = getValidatedPhone();
            std::string surname;
            safeGetline(surname, "������� �������: ");

            // ��������� ������ � ����������
            phone2surname[phone] = surname;
            insertSorted(surname2phones[surname], phone);

            std::cout << "\n������ ������� ���������!\n";
        }
        else if (choice == 2) {
            // ����� ������� �� ������
            std::string phone = getValidatedPhone();
            if (phone2surname.find(phone) != phone2surname.end()) {
                std::cout << "�������: " << phone2surname[phone] << "\n";
            }
            else {
                std::cout << "������ �� �������.\n";
            }
        }
        else if (choice == 3) {
            // ����� ������(��) �� �������
            std::string surname;
            safeGetline(surname, "������� ������� ��� ������: ");
            if (surname2phones.find(surname) != surname2phones.end()) {
                std::cout << "������: ";
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
                std::cout << "������ �� �������.\n";
            }
        }
        else if (choice == 4) {
            std::cout << "�����...\n";
            break;
        }
        else {
            std::cout << "�������� �����. ���������� ��� ���.\n";
        }
        std::cout << "\n������� Enter ��� �����������...";
        std::string dummy;
        getline(std::cin, dummy);
    }

    return 0;
}
