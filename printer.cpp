#include "printer.h"
#include <string>
using namespace std;

void printer::menulog(string& func)
{
	space;
	printf("\n----------------------{Лабораторная работа по Теории Алгоритмов №1}---------------------- \n");
	bool exit1 = true;
	int window_iterator = 0;
	while (exit1)
	{
		switch (window_iterator)
		{
		case 0:
			printAvt(window_iterator, func);
			break;
		case 1:
			ContinueOrFallBack(window_iterator);
			break;
		case 2:
			exit1 = false;
				//setOperationsWindow(exit1, window_iterator);
			break;
		default:
			printf("\n Произошла ошибка");
			break;
		}
	}
}

int printer::intinput()
{
	int val;
	while (true)
	{
		std::cin >> val;
		if (std::cin.peek() != '\n')
		{
			std::cin.clear(); // reset failbit
			std::cin.ignore(std::cin.rdbuf()->in_avail()); // избавление от мусора в буфере
			printf("\n");
			printf("\n Вы ввели некорректное значение, попробуйте заново \n ");
			printf("\n Введите число: ");
		}
		else break;
	}
	return val;
}

void printer::ContinueOrFallBack(int& window_iterator1)
{
	while (true)
	{
		printf("\n Завершить или начать заново?\n");
		printf("\n \t[0] - Заврешить\n \t[1] - Пересоздать автомат\n");
		//if (window_iterator1 > 0) printf("\t[2] - Пересоздать множества\n");
		printf("\n Введите значение: ");
		int i = intinput();
		if (i == 0)
		{
			if (window_iterator1 < 2) window_iterator1++; // идем дальше 
			break;
		}

		else if (i == 1)
		{
			window_iterator1 = 0; // возвращаемся на юниверсум
			break;
		}
		printf("\n Введено число, которое находится за пределами списка команд, введите число от [0 -- %d]\n", (window_iterator1 > 0 ? 2 : 1));
	}
}
std::string printer::string_input(int width)
{
	std::string val;
	bool sign = false;
	bool exit1 = false;
	std::vector<int> rule = { '0','1' };
	while (!exit1)
	{
	in:
		getline(std::cin, val);
		if (((val.size() == 0)) and (val[0] != '0'))
		{
			//printf("Ошибка ввода, попробуйте заново: ");
			goto in;
		}
		if (val.size() > width)
		{
			printf("\n Введено больше символов,чем требуется, попробуйте заново: ");
			goto in;
		}
		for (int i = 0; i < val.size(); i++)
		{
			if (find(rule.begin(), rule.end(), val[i]) == rule.end())
			{
				printf("\n Элемента %c нет в используемом алфавите", val[i]);
				printf("\n Введите слово: ");
				goto in;
			}
		}
		exit1 = true;
	}
	while (val.size() != width)
	{
		val = '0' + val;
	}
	return val;
}

void printer::createManually(vector<string>& i_set, int width)
{
	string set_multiplicity;
	bool exit1 = true;
	while (exit1)
	{
		int currentPower = 0;
		i_set.clear();
		exit1 = false;
		for (int i = 0; i < width; i++)
		{
			std::cout << "\n Введите строку #" << i + 1 << ": ";
			set_multiplicity = string_input(width);
			i_set.push_back(set_multiplicity);
		}
	}
	printf("\n ----Создание заврешено----------- \n");
}



void printAvt(int& window_iterator1, string& func)
{
	int val = 0;
	int width = 0;
	int iterations = 0;
	int powerOfsecondSet = 0;
	bool exit1;
	printer P;
	//printf("\n Лабораторная работа по теории алгоритмов \n ");
	printf("\n Введите ширину поля от 1 до 100: ");
	while (true)
	{
		width = P.intinput();
		if ((width >= 1) and (width <= 100))
		{
			break;
		}
		printf("\n Введенная ширина находится за границами промежутка [1, 100]. Попробуйте заново: ");
	}
	printf("\n Введите количество итераций от 1 до 100: ");
	while (true)
	{
		iterations = P.intinput();
		if ((iterations >= 1) and (iterations <= 100))
		{
			break;
		}
		printf("\n Введенное количество итераций находится за границами промежутка [1, 100]. Попробуйте заново: ");
	}
	printf("\n Введите значение: ");
	
	Field field(width, func);
	while(true)
	{
	chooseWay:
		printf("\n Как вы хотите задать поле: ");
		printf("\n \t[0] - Автоматически\n \t[1] - Вручную\n");
		printf("\n Введите значение: ");
		val = P.intinput();
		if (val == 0) //Создаем автоматически
		{
			srand(time(NULL));
			field.random_init_field();
			break;
		}
		if (val == 1) // Создаем вручную
		{
			//printf("\n Создается первое множество...\n");
			vector<string> i_set;
			P.createManually(i_set, width);
			field.user_init_field(i_set);
			break;
		}
		else
		{
			printf("\n Введено число, которое находится за пределами списка команд, введите число от [0 -- 1]\n");
			goto chooseWay;
		}
	}
	cout << field << endl;
	for (int i = 0; i < iterations; i++)
	{
		cout << "--------- Итерация #" << i <<" ------" << endl;
		
		Field newfied = field;
		newfied.get_new_generation(field);
		field = newfied;
	}
	window_iterator1++;
}
