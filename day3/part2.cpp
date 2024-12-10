#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>

std::ifstream datafile;
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
            //alles lezen, als je mul( vind begin met nummers vinden todat het klaar is of als het invalid is.
            bool mulfound = false;
            int num1 = -1;
            int num2 = -1;
            int tempnum = 0;
            bool enabled = true;
            for(int i = 0; i < line.length(); i++) {
                if(!enabled) {
                    if(line[i] == 'd' && line[i + 1] == 'o' && line[i + 2] == '(' && line[i + 3] == ')') {
                        std::cout << "found do()" << std::endl;
                        i += 3;
                        enabled = true;
                    }
                    else {
                        continue;
                    }
                }
                if(line[i] == 'd' && line[i + 1] == 'o' && line[i + 2] == 'n' && line[i + 3] == '\'' && line[i + 4] == 't' && line[i + 5] == '(' && line[i + 6] == ')') {
                    std::cout << "found don't()" << std::endl;
                    i += 6;
                    enabled = false;
                    continue;
                }
                if(mulfound) {
                    if(isdigit(line[i])) {
                        //std::cout << "adding digit: " << line[i] << std::endl;
                        tempnum = (tempnum * 10) + line[i] - '0';
                    }
                    else if(line[i] == ',') {
                        if(num1 >= 0) {
                            //std::cout << ",error\n";
                            num1 = -1;
                            num2 = -1;
                            tempnum = 0;
                            mulfound = false;
                        }
                        else {
                            num1 = tempnum;
                            tempnum = 0;
                        }
                    }
                        
                    else if(line[i] == ')') {
                        //std::cout << "found ) " << std::endl;
                        num2 = tempnum;
                        if(num1 >= 0 && num2 >= 0) {
                            //std::cout << "num1: " << num1 << " num2: " << num2 << std::endl;
                            int oldresult = result;
                            result += num1 * num2;
                            //std::cout << "oldresult: " << oldresult << " newresult: " << result << std::endl;
                            if(oldresult > result) {
                                std::cout << "overflow" << std::endl;
                            }
                            num1 = -1;
                            num2 = -1;
                            tempnum = 0;
                            mulfound = false;
                        }
                        else {
                            std::cout << "invalid" << std::endl;
                            num1 = -1;
                            num2 = -1;
                            tempnum = 0;
                            mulfound = false;
                        }
                    }
                    else {
                        //std::cout << "message failed because of character: " << line[i] << std::endl;
                        num1 = -1;
                        num2 = -1;
                        tempnum = 0;
                        mulfound = false;
                    }
                }
                else if(line[i] == 'm' && line[i + 1] == 'u' && line[i + 2] == 'l' && line[i + 3] == '(') {
                    //std::cout << "found mul" << std::endl;
                    i += 3;
                    mulfound = true;
                }
            }
            
        }
    }
    std::cout << "result: " << result << std::endl;
    return 0;
}