#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include<random>
#include <ostream>
std::string to_binar(int a, int bit_size);
int to_dec(std::string& value);
char to_binchar(int a);
int from_binchar(char a);
class data_Func
{
private:
	std::string truth_table;
public:
	//принимаем по целому числу
	int getValue(int input)
	{
		return from_binchar(truth_table.at(input));
	}
	//принимаем по двоичной записи
	int getValue(std::string& input)
	{
		return from_binchar(truth_table.at(to_dec(input)));
	}
	data_Func(std::string& input_func)
	{
		truth_table.clear();
		truth_table = input_func;
	}
	data_Func()
	{
		truth_table.clear();
		truth_table = " ";
	}

};

class Field
{
	int width;
	std::vector<std::vector<int>> game_field;
	data_Func function;
	/*void random_init_field();
	void user_init_field(std::vector<std::string>& user_points);*/
	int check_neighbors(int x, int y);
	int get_future_step(int x, int y);
	bool isEdgeUp(int x)
	{
		if (x == 0) return true;
		else return false;
	}
	bool isEdgeDown(int x)
	{
		if (x == width-1) return true;
		else return false;
	}
public:
	void random_init_field();
	void user_init_field(std::vector<std::string>& user_points);
	void get_new_generation(Field& old_gen);
	friend std::ostream& operator<<(std::ostream& os, const Field& field);
	Field(int i_width, std::string& i_str)
	{
		width = i_width;
		game_field.resize(width, std::vector<int>(i_width,0));
		function = i_str;
	}
};

