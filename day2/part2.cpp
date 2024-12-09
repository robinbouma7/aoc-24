#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>

std::ifstream datafile;

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
            int lastnum = -1;
            int tempnum = 0;
            bool isvalid = true;
            int increasing = -1;
            int mistakes = 0;
            //TODO: the mistake can be the second because it increases but the rest decreases. 
            //this does not account for that because it sets increasing with number 1 and 2.
            //maybe fix it by adding everything to a vector and creating a function that checks if its valid
            //then you can check if its valid if you remove the second number and check if its valid if you remove the first number
            for(int i = 0; i < line.length(); i++) {
                if(isdigit(line[i])) {
                    tempnum = (tempnum * 10) + line[i] - '0';
                }
                else {
                    if(lastnum < 0) {
                        lastnum = tempnum;
                        tempnum = 0;
                        continue;
                    }
                    else {
                        if(increasing == -1) {
                            if(tempnum - lastnum > 0 && tempnum - lastnum <= 3) {
                                increasing = 1;
                                //std::cout << "increasing " << tempnum - lastnum << std::endl;
                                lastnum = tempnum;
                                tempnum = 0;
                            }
                            else if(tempnum - lastnum < 0 && tempnum - lastnum >= -3) {
                                increasing = 0;
                                //std::cout << "decreasing" << tempnum - lastnum << std::endl;
                                lastnum = tempnum;
                                tempnum = 0;
                            }
                            else {
                                if(mistakes == 0) {
                                    mistakes++;
                                    tempnum = 0;
                                    continue;
                                }
                                else {
                                    isvalid = false;
                                    break;
                                }
                            }
                        }
                        else if(increasing == 0) {
                            if(tempnum - lastnum < 0 && tempnum - lastnum >= -3) {
                                //std::cout << "decreasing " << tempnum - lastnum << std::endl;
                                lastnum = tempnum;
                                tempnum = 0;
                                continue;
                            }
                            else {
                                //std::cout << "decrease test: " << lastnum << " " << tempnum << std::endl;
                                //std::cout << tempnum - lastnum << std::endl;
                                if(mistakes == 0) {
                                    mistakes++;
                                    tempnum = 0;
                                    continue;
                                }
                                else {
                                    isvalid = false;
                                    break;
                                }
                            }
                        }
                        else if(increasing == 1) {
                            if(tempnum - lastnum > 0 && tempnum - lastnum <= 3) {
                                //std::cout << "increasing " << tempnum - lastnum << std::endl;
                                lastnum = tempnum;
                                tempnum = 0;
                                continue;
                            }
                            else {
                                //std::cout << "increase test: " << lastnum << " " << tempnum << std::endl;
                                //std::cout << tempnum - lastnum << std::endl;
                                if(mistakes == 0) {
                                    mistakes++;
                                    tempnum = 0;
                                    continue;
                                }
                                else {
                                    isvalid = false;
                                    break;
                                }
                            }
                        }
                    }
                   
                }
            }

            if(isvalid) {
                std::cout << "valid: " << line << std::endl;
                validcount++;
            }
            else {
                std::cout << "invalid: " << line << std::endl;
            }
        
           
        }
         std::cout << "result: " << validcount << std::endl;
    }
    return 0;
}