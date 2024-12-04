#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>

std::ifstream datafile;

std::vector<int> list1;
std::map<int, int> list2;

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
            if(list2.count(num2) > 0) {
                list2[num2]++;
            }
            else {
                list2[num2] = 1;
            }
            
        }
    }
    std::cout << "got all numbers\n";
    for(int i = 0; i < list1.size(); i++) {
        if(list2.count(list1[i]) == 0) {
            //std::cout << "number " << list1[i] << " \n";
           continue;
        }
        else {
            result += list1[i] * list2[list1[i]];
        }
    }
    std::cout << "result: " << result << "\n";
    return 0;
}