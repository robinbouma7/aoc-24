#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::ifstream datafile;

int main(int argc, char *argv[]) {
    if(argc > 1 && (std::strcmp(argv[1], "-t") == 0 || std::strcmp(argv[1], "--test") == 0)) {
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
            
        }
    }
    return 0;
}