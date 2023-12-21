#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>

int main()
{
    //  Open the file
    std::ifstream inputFile("day_1\\input.txt");

    // Check if the file is open
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return 1; // Return an error code
    }

    std::unordered_map<std::string, std::string> spelledOutToNumeric;
    spelledOutToNumeric["one"] = "1";
    spelledOutToNumeric["two"] = "2";
    spelledOutToNumeric["three"] = "3";
    spelledOutToNumeric["four"] = "4";
    spelledOutToNumeric["five"] = "5";
    spelledOutToNumeric["six"] = "6";
    spelledOutToNumeric["seven"] = "7";
    spelledOutToNumeric["eight"] = "8";
    spelledOutToNumeric["nine"] = "9";
    std::vector<std::string> nums;
    std::string line;
    std::string next_three;
    std::string next_four;
    std::string next_five;
    std::string str_num;
    std::string part_one_str_num;
    std::vector<std::string> part_one_nums;
    // Read and display the contents of the file
    while (std::getline(inputFile, line))
    {
        part_one_str_num = "";
        str_num = "";
        for (int c = 0; c < line.length(); c++)
        {
            next_three = line.substr(c, 3);
            next_four = line.substr(c, 4);
            next_five = line.substr(c, 5);
            if (std::isdigit(line[c]))
            {
                part_one_str_num += line[c];
                str_num += line[c];
            }
            else if (spelledOutToNumeric.find(next_three) != spelledOutToNumeric.end())
            {
                str_num += spelledOutToNumeric[next_three];
                c += 1;
            }
            else if (spelledOutToNumeric.find(next_four) != spelledOutToNumeric.end())
            {
                str_num += spelledOutToNumeric[next_four];
                c += 2;
            }
            else if (spelledOutToNumeric.find(next_five) != spelledOutToNumeric.end())
            {
                str_num += spelledOutToNumeric[next_five];
                c += 3;
            }
        }
        if (part_one_str_num.length() == 1)
        {
            part_one_str_num += part_one_str_num;
            part_one_nums.push_back(part_one_str_num);
        }
        else if (part_one_str_num.length() == 2)
        {
            part_one_nums.push_back(part_one_str_num);
        }
        else
        {
            part_one_str_num.erase(1, part_one_str_num.length() - 2);
            part_one_nums.push_back(part_one_str_num);
        }
        if (str_num.length() == 1)
        {
            str_num += str_num;
            nums.push_back(str_num);
        }
        else if (str_num.length() == 2)
        {
            nums.push_back(str_num);
        }
        else
        {
            str_num.erase(1, str_num.length() - 2);
            nums.push_back(str_num);
        }
    }

    // Close the file
    inputFile.close();

    int result = 0;
    for (int i = 0; i < part_one_nums.size(); i++)
    {
        result += std::stoi(part_one_nums[i]);
    }
    std::cout << "Part 1: " << result << std::endl;

    result = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        result += std::stoi(nums[i]);
    }
    std::cout << "Part 2: " << result << std::endl;

    return 0;
}