#include <iostream>
#include "tape_sort.h"
#include <exception>

bool isEmpty(std::string& filename);
Config conf;

int main()
{
    try {
        std::string input, output, config;
        std::cout << "Enter file with input data" << '\n';
        std::cin >> input;
        if (!std::filesystem::exists(input)) {
            std::cout << "Invalid input data";
            return 1;
        }

        std::cout << "Enter file for output data" << '\n';
        std::cin >> output;

        std::cout << "Enter configuration file" << '\n';
        std::cin >> config;

        std::cout << "Enter amount of RAM" << '\n';
        int ram; std::cin >> ram;

        std::fstream file;
        file.open(config, std::fstream::in);

        if (file.is_open()) 
            conf.setConfig(file);

        if (isEmpty(input)) {
            file.open(output, std::fstream::app);
            return 0;
        }

        Tape inputTape(input, conf);
        TapeSort tape_sort(ram);
        tape_sort.tapeSort(inputTape, output);
    }

    catch (std::exception& err) {
        std::cerr << err.what();
    }

    return 0;
}

bool isEmpty(std::string& filename) {
    std::ifstream file(filename);
    return file.peek() == EOF;
}