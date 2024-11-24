#pragma once
#include "Field.h"
#define space printf("\n ")
void printAvt(int& window_iterator1, std::string& func);
class printer
{
public:
	void menulog(std::string& func);
	int intinput();
	std::string string_input(int width);
	void ContinueOrFallBack(int& window_iterator1);
	void createSetsWindow(int& window_iterator);
	void createManually(std::vector<std::string>& i_set, int width);
	template <class T> void printSet(T& v/*, std::string s*/)
	{

		//cout << "\n" << s << "\n Члены множества:\n";

		/*if (v.empty())
		{
			cout << "\n -Пустое множество- \n ";
			return;
		}*/
		// Итератор любого контейнера
		typename T::iterator p;
		int i;

		for (p = v.begin(), i = 0; p != v.end(); p++, i++)
			std::cout << std::endl << " " << i + 1 << ". " << *p;
		std::cout << '\n';
	}
};

