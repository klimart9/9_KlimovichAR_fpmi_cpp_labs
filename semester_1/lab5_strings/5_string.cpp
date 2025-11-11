#include <iostream>
#include <string>
#include <cctype>
#include <cmath>

int main()
{
	std::string str;
	std::string new_str;
	std::cout << "Write your string" << std::endl;
	getline(std::cin, str);
	if (str == "")
	{
		std::cout << "Write not null  string" << std::endl;
		return 1;
	}
	for (int i = 0; i < str.length(); i++)
	{
		while (std::isdigit(str[i]))
		{
			new_str = new_str + str[i];
			i = i + 1;
			if (!(std::isdigit(str[i])))
			{
				new_str = new_str + " ";
			}
		}
	}
	if (new_str == "")
	{
		std::cout << "Your sring doesn't contain numbers" << std::endl;
		return 1;
	}
	std::cout << "\nNumbers:" << new_str << std::endl;
	std::string current_number;
	std::string answer;
	for (int i = 0; i < new_str.length(); i++)
	{
		while (std::isdigit(new_str[i]))
		{
			current_number = current_number + new_str[i];
			i = i + 1;
			if (!(std::isdigit(new_str[i])))
			{
				bool is_simple = true;
				int number = std::stoi(current_number);
				for (int i = 2; i < sqrt(number); i++)
				{
					if (number % i == 0)
					{
						is_simple = false;
					}
				}
				if (is_simple)
				{
					answer = answer + current_number + " ";
				}
				current_number = "";
			}
		}
	}
	if (answer == "")

	{
		std::cout << "String doesn't contain simple numbers" << std::endl;
		return 1;
	}
	std::cout << "\nSimple numbers in your string: " << answer << std::endl;

	return 0;
}
