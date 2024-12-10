#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>

std::ifstream datafile;

std::vector<std::vector<int>> numbers;

bool isvalid(std::vector<int> vec, int maxmistakes) {
    bool increasing;
    int mistakes = 0;
    int lastwasmistake = false;
    if(vec[0] > vec[1]) {
       increasing = false;
    }
    else if(vec[0] < vec[1]) {
        increasing = true;
    }
    else {
        std::cout << "first two are the same" << std::endl;
        return false;
    }
    int difference;
    for(int i = 1; i < vec.size(); i++) {
        if(lastwasmistake) {
            lastwasmistake = false;
            difference = vec[i] - vec[i - 2];
        } 
        else {
            difference = vec[i] - vec[i - 1];
        }
        if(increasing) {
            if(difference <= 0 || difference > 3) {
                if(mistakes < maxmistakes) {
                    mistakes++;
                    lastwasmistake = true;
                }
                else {
                    std::cout << "increase fail " << i << std::endl;
                    std::cout << "difference: " << difference << std::endl;
                    return false;
                }
            }
        }
        else {
            if(difference >= 0 || difference < -3) {
                if(mistakes < maxmistakes) {
                    std::cout << "decrease fail " << i << std::endl;
                    std::cout << "difference: " << difference << std::endl;
                    mistakes++;
                    lastwasmistake = true;
                }
                else {
                    return false;
                }
            }
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    if(argc > 1 && (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "--test") == 0)) {
        std::cout << "TEST DATA\n\n";
        datafile.open("testdata.txt");
    }
    else {
        datafile.open("data.txt");
    }

    if (datafile.is_open()) {
        int validcount = 0;
        while(datafile.good() ) {
            std::string line;
            getline(datafile, line);
            line = line + " ";
            int tempnum = 0;
            bool isvalid = true;
            int increasing = -1;
            int mistakes = 0;
            std::vector<int> tempvec;
            //TODO: the mistake can be the second because it increases but the rest decreases. 
            //this does not account for that because it sets increasing with number 1 and 2.
            //maybe fix it by adding everything to a vector and creating a function that checks if its valid
            //then you can check if its valid if you remove the second number and check if its valid if you remove the first number
            for(int i = 0; i < line.length(); i++) {
                if(isdigit(line[i])) {
                    tempnum = (tempnum * 10) + line[i] - '0';
                }
                else {
                    if(tempnum != 0) {
                        tempvec.push_back(tempnum);
                        tempnum = 0;
                    }
                }
            }
            numbers.push_back(tempvec);        
        }
        for(int i = 0; i < numbers.size(); i++) {
            
            if(isvalid(numbers[i], 1)) {
                std::cout << i << " is valid" << std::endl;
                validcount++;
                continue;
            }
            else {
                for(int j = 0; j < numbers[i].size(); j++) {
                    std::vector<int> tempvec = numbers[i];
                    tempvec.erase(tempvec.begin() + j);
                    if(isvalid(tempvec, 0)) {
                        std::cout << i << " is valid by removing " << j << std::endl;
                        validcount++;
                        break;
                    }
                }
                /*std::vector<int> tempvec = numbers[i];
                tempvec.erase(tempvec.begin());
                if(isvalid(tempvec, 0)) {
                    std::cout << i << " is valid by removing 1" << std::endl;
                    validcount++;
                    continue;
                }
                else {
                    tempvec = numbers[i];
                    tempvec.erase(tempvec.begin() + 1);
                    if(isvalid(tempvec, 0)) {
                        std::cout << i << " is valid by removing 2" << std::endl;
                        validcount++;
                        continue;
                    }
                }*/
            }
            
        }
        std::cout << "result: " << validcount << std::endl;
    }
    return 0;
}