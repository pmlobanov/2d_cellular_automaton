#include "Field.h"

void Field::random_init_field()
{
	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->game_field[i][j] = rand() % (1 - 0+ 1);
		}
	}
}

void Field::user_init_field(std::vector<std::string>& user_points)
{
	//game_field.clear();
	for (int i = 0; i < user_points.size(); i++) 
	{
		for (int j =0; j < user_points.at(i).size(); j++)
		game_field[i][j] = from_binchar(user_points.at(i).at(j));
	}
}

int Field::check_neighbors(int x, int y)
{
	std::string result;
	result += to_binchar(isEdgeUp(x) ? game_field[width - 1][y] : game_field[x - 1][y]); // s1
	result += to_binchar(isEdgeDown(x) ? game_field[0][y] : game_field[x + 1][y]); // s2
	result += to_binchar(isEdgeUp(y) ? game_field[width - 1][y] : game_field[x][y - 1]); // s3
	result += to_binchar(isEdgeDown(y) ? game_field[0][y] : game_field[x][y +1]); // s4
	result += to_binchar(game_field[x][y]); // s5
	return to_dec(result);
}

std::ostream& operator<<(std::ostream& os, const Field& field)
{
	int sum = 0;
	for (int i = 0; i < field.width; i++)
	{
		os << " ";
		for (int j = 0; j < field.width; j++)
		{
			os << (field.game_field.at(i).at(j) == 1 ? "*" : " ");
			if (field.game_field.at(i).at(j) == 1) sum++;
		}
		os << "\n";
		
	}
	os << " Живых: << " << sum <<"\n";
	return os;
}

int Field::get_future_step(int x, int y)
{
	int status = check_neighbors(x, y);
	return function.getValue(status);
}

void Field::get_new_generation(Field& old_gen)
{
	std::vector<std::vector<int>> tmp;
	tmp.resize(width, std::vector<int>(width, 0));
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < width; j++) {
			int new_state = get_future_step(i, j);
			tmp[i][j] = new_state;
		}
	}
	game_field = tmp;
	std::cout << *this << std::endl;
}

std::string to_binar(int a, int bit_size = 5)
{
	std::string s;
	int mx = bit_size;
	int num = a, bin;
	while (mx > 0)
	{
		bin = pow(2, --mx);
		if (num < bin)
			s += '0';
		else
		{
			s += '1';
			num -= bin;
		}
	}
	return s;
}

char to_binchar(int a)
{
	if (a == 1) return '1';
	else return '0';
}

int from_binchar(char a)
{
	if (a == '1') return 1;
	else return 0;
}


int to_dec(std::string& value)
{
	int result = 0;
	for (int i = value.size() - 1; i >= 0; i--)
	{
		if (value[i] == '1')
		{
			result += pow(2, (value.size() - 1) - i);
		}
	}
	return result;
}