#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main()
{
    std::string num_1;
    std::string num_2;
    std::string sum = "";
    std::cout << "Enter 2 numbers" << std::endl;
    getline(std::cin, num_1);
    getline(std::cin, num_2);
    int NumberToAdd = 0;
    for (int i = num_1.length() - 1; i >= 0; i--)
    {
        int current_number = 0;

        current_number = (num_1[i] - '0') + (num_2[i] - '0') + NumberToAdd;
        if (current_number > 10)
        {
            current_number = current_number - 10;
            NumberToAdd = 1;
            if (i == 0)
            {
                sum = sum + std::to_string(current_number) + "1";
                break;
            }
        }
        else
        {
            current_number = current_number;
            NumberToAdd = 0;
        }

        sum = sum + std::to_string(current_number);
    }
    std::reverse(sum.begin(), sum.end());
    std::cout << sum << std::endl;
}