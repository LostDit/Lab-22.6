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
	// Установил кодовую страницу консоли
	SetConsoleCP(866);
	SetConsoleOutputCP(866);
#endif

	std::map<std::string, int> queue;
	std::string input;

	std::cout << "Регистратура\n";
	std::cout << "Введите фамилию или \"Next\" для вызова следующего пациента.";
	std::cout << "\nВведите пациента: ";

	while (getline(std::cin, input)) {
		//Если получаю команду вызова след пациента
		if (input == "Next") {
			if (queue.empty()) {
				std::cout << "Очередь пуста.\n";
			}else {
				//Первый в лексиккографическом порядке пациент
				auto it = queue.begin();
				std::cout << "Вызван: " << it->first << "\n";
				//Уменьшаем счётчик вызова
				if (--(it->second) == 0) {
					queue.erase(it);
				}
			}
		}else {
			//При добавлении пациента, фамилия может повторяться
			queue[input]++;
			std::cout << "Добавлено: " << input << "\n";
		}
	}
	return 0;
}
