#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;
std::vector<string> static lexer(const std::string&);


int main() {
    lexer("fly.txt");


    return 0;
}



std::vector<string> static lexer(const std::string& fileName) {
    std::vector<string> lexerVector;

    ifstream file(fileName);
    if (!file.is_open()) {
        std::cout<<"Error open the file"<<endl;
    }



    std::string line;
    while(getline(file, line)) {
        std::string token;
        for (char& c : line) {
            if (c == '(' || c == ')' || c == ' ') {
                lexerVector.push_back(token);
                token = "";
                continue;
            }
            token.push_back(c);
        }



    }
    return lexerVector;


}