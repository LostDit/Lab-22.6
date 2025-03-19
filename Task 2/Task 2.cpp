#include <iostream>
#include <string>
#include <map>
#include <clocale>

#ifdef _WIN32
#include "windows.h"
#endif

int main() {
	setlocale(LC_ALL, "");

#ifdef _WIN32
	// ��������� ������� �������� �������
	SetConsoleCP(866);
	SetConsoleOutputCP(866);
#endif

	std::map<std::string, int> queue;
	std::string input;

	std::cout << "������������\n";
	std::cout << "������� ������� ��� \"Next\" ��� ������ ���������� ��������.";
	std::cout << "\n������� ��������: ";

	while (getline(std::cin, input)) {
		//���� ������� ������� ������ ���� ��������
		if (input == "Next") {
			if (queue.empty()) {
				std::cout << "������� �����.\n";
			}else {
				//������ � ������������������� ������� �������
				auto it = queue.begin();
				std::cout << "������: " << it->first << "\n";
				//��������� ������� ������
				if (--(it->second) == 0) {
					queue.erase(it);
				}
			}
		}else {
			//��� ���������� ��������, ������� ����� �����������
			queue[input]++;
			std::cout << "���������: " << input << "\n";
		}
	}
	return 0;
}