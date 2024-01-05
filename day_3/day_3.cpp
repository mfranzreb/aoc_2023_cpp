#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <chrono>

struct VectorHash
{
    std::size_t operator()(std::vector<int> const &vec) const
    {
        std::size_t seed = 2; // vec size is always 2
        for (int x : vec)
        {
            x = ((x >> 16) ^ x) * 0x45d9f3b;
            x = ((x >> 16) ^ x) * 0x45d9f3b;
            x = (x >> 16) ^ x;
            seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    //  Open the file
    std::ifstream inputFile("day_3\\input.txt");

    // Check if the file is open
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return 1; // Return an error code
    }
    std::string line;
    std::vector<std::string> lines;
    int beg;
    int end;
    unsigned long int result = 0;
    unsigned long long int result2 = 0;
    int line_length;
    int lines_num;
    bool broken;
    unsigned int num;

    std::unordered_map<std::vector<int>, std::vector<unsigned int>, VectorHash> gears;

    while (std::getline(inputFile, line))
    {
        lines.push_back(line);
    }
    inputFile.close();
    lines_num = lines.size();
    line_length = lines[0].length();

    for (int i = 0; i < lines_num; i++)
    {
        for (int j = 0; j < line_length; j++)
        {
            if (std::isdigit(lines[i][j]))
            {
                beg = j;
                do
                {
                    j++;
                } while (j < line_length && std::isdigit(lines[i][j]));
                end = j - 1;
                broken = false;
                num = std::stoi(lines[i].substr(beg, end - beg + 1));
                // if (std::find(nums.begin(), nums.end(), num) != nums.end())
                //{
                //     continue;
                // }
                for (int k = beg - 1; k <= end + 1; k++)
                {
                    if (k >= 0 && k < line_length && ((i > 0 && !(std::isdigit(lines[i - 1][k]) || lines[i - 1][k] == '.')) || (i < lines_num - 1 && !(std::isdigit(lines[i + 1][k]) || lines[i + 1][k] == '.'))))
                    {
                        if (i > 0 && lines[i - 1][k] == '*')
                        {
                            if (gears.find({i - 1, k}) == gears.end())
                            {
                                gears[{i - 1, k}] = {num, 1};
                            }
                            else
                            {
                                gears[{i - 1, k}][0] *= num;
                                gears[{i - 1, k}][1] += 1;
                            }
                        }

                        else if (i < lines_num - 1 && lines[i + 1][k] == '*')
                        {
                            if (gears.find({i + 1, k}) == gears.end())
                            {
                                gears[{i + 1, k}] = {num, 1};
                            }
                            else
                            {
                                gears[{i + 1, k}][0] *= num;
                                gears[{i + 1, k}][1] += 1;
                            }
                        }

                        result += num;
                        broken = true;
                        break;
                    }
                }
                if (!broken && ((beg > 0 && !(std::isdigit(lines[i][beg - 1]) || lines[i][beg - 1] == '.')) || (end < line_length - 1 && !(std::isdigit(lines[i][end + 1]) || lines[i][end + 1] == '.'))))
                {
                    if (beg > 0 && lines[i][beg - 1] == '*')
                    {
                        if (gears.find({i, beg - 1}) == gears.end())
                        {
                            gears[{i, beg - 1}] = {num, 1};
                        }
                        else
                        {
                            gears[{i, beg - 1}][0] *= num;
                            gears[{i, beg - 1}][1] += 1;
                        }
                    }

                    else if (end < line_length - 1 && lines[i][end + 1] == '*')
                    {
                        if (gears.find({i, end + 1}) == gears.end())
                        {
                            gears[{i, end + 1}] = {num, 1};
                        }
                        else
                        {
                            gears[{i, end + 1}][0] *= num;
                            gears[{i, end + 1}][1] += 1;
                        }
                    }
                    result += num;
                }
            }
        }
    }
    for (auto &gear : gears)
    {
        if (gear.second[1] == 2)
        {
            result2 += gear.second[0];
        }
    }
    std::cout << "Part 1: " << result << std::endl;
    std::cout << "Part 2: " << result2 << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "The average exeuction time of AoC day 2 (microseconds): " << ((duration.count() / 1)) << std::endl;
    return 0;
}