#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

int main()
{
    //  Open the file
    std::ifstream inputFile("day_2\\input.txt");

    // Check if the file is open
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return 1; // Return an error code
    }
    std::string line;
    unsigned char num_red = 12;
    unsigned char num_green = 13;
    unsigned char num_blue = 14;
    int seen_red = 0;
    int seen_green = 0;
    int seen_blue = 0;
    int max_red = 0;
    int max_green = 0;
    int max_blue = 0;
    int game_id;
    unsigned long long int powers = 0;
    std::string temp;
    std::vector<int> ids;
    while (std::getline(inputFile, line))
    {
        line.erase(0, 5);
        game_id = std::stoi(line);
        line.erase(0, 2);

        for (int c = 0; c < line.length(); c++)
        {
            if (std::isdigit(line[c]))
            {
                temp += line[c];
            }
            else if (line[c] == 'r' && line[c - 1] == ' ')
            {
                seen_red = std::stoi(temp);
                if (seen_red > max_red)
                {
                    max_red = seen_red;
                }
                temp = "";
                c += 2;
            }
            else if (line[c] == 'g')
            {
                seen_green = std::stoi(temp);
                if (seen_green > max_green)
                {
                    max_green = seen_green;
                }
                temp = "";
                c += 4;
            }
            else if (line[c] == 'b')
            {
                seen_blue = std::stoi(temp);
                if (seen_blue > max_blue)
                {
                    max_blue = seen_blue;
                }
                temp = "";
                c += 3;
            }
        }
        if (!(max_red > num_red || max_green > num_green || max_blue > num_blue))
        {
            ids.push_back(game_id);
        }
        powers += max_red * max_green * max_blue;
        temp = "";
        max_red = 0;
        max_green = 0;
        max_blue = 0;
    }

    // Close the file
    inputFile.close();

    int result = 0;
    for (int i = 0; i < ids.size(); i++)
    {
        result += ids[i];
    }
    std::cout << "Part 1: " << result << std::endl;
    std::cout << "Part 2: " << powers << std::endl;

    return 0;
}