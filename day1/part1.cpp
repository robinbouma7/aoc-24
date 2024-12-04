#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>
#include <algorithm>

std::ifstream datafile;

std::vector<int> list1;
std::vector<int> list2;

int result = 0;

int main(int argc, char *argv[]) {
    if(argc > 1 && (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "--test") == 0)) {
        std::cout << "TEST DATA\n\n";
        datafile.open("testdata.txt");
    }
    else {
        datafile.open("data.txt");
    }

    if (datafile.is_open()) {
        while(datafile.good() ) {
            std::string line;
            getline(datafile, line);
            bool gotfirst = false;
            int num1 = 0;
            int num2 = 0;

            for(int i = 0; i < line.length(); i++) {
                if(isdigit(line[i])) {
                    if(gotfirst) {
                        num2 = num2 * 10 + (line[i] - '0');
                    }
                    else {
                        num1 = num1 * 10 + (line[i] - '0');
                    }
                }
                else {
                    if(gotfirst && isdigit(line[i - 1])) {
                        std::cout << "error: got anothger digit after first\n";
                        break;
                    }
                    gotfirst = true;
                }
            }
            std::cout << "got 2 numbers: " << num1 << " and " << num2 << "\n";
            list1.push_back(num1);
            list2.push_back(num2);
        }
    }
    std::cout << "got all numbers\n";
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());
    if(list1.size() != list2.size()) {
        std::cout << "error: lists are not the same size\n";
        return 1;
    }
    for(int i = 0; i < list1.size(); i++) {
        if(list1[i] >= list2[i]) {
            result += list1[i] - list2[i];
        }
        else {
            result += list2[i] - list1[i];
        }
    }
    std::cout << "result: " << result << "\n";
    return 0;
}