#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <thread>
#include "OpenDataServer.h"
#include "CreateSymbolTable.h"

using namespace std;
std::vector<string> static lexer(const std::string&);


int main() {




/*




*/


/*
    std::vector<string> lexerStrings;
    lexerStrings = lexer("fly.txt");


*/



    OpenDataServer openDataServer;
    std::vector<string> vtest;
    vtest.push_back("5400");
    std::vector<string>::iterator it = vtest.begin();

    openDataServer.execute(it);



    std::cout<<"cd"<<endl;


    return 0;

}



std::vector<string> static lexer(const std::string& fileName) {
    std::vector<string> lexerVector;

    ifstream file(fileName);
    if (!file.is_open()) {
        std::cout<<"Error open the file"<<endl;
    }



    std::string line;
    /*
     * reading line by line and check the type of the expression in the line
     * if line is an equation we will put the whole expression, with the parenthesis,
     * in one string and will analyze the expression later
     * if there is a command of print so we copy the string in the (" ... ")
     * we always check if the token that we are going to insert the lexer is not empty
     */
    while(getline(file, line)) {
        std::string token;
        //3 options that the type of the expression in the line might be
        bool isEquation = false;
        bool isPrint = false;
        bool isCondition = false;

        for (char& c : line) {
            if (token == ("while") || token == ("if")) {
                isCondition = true;
            }
            if (token ==("Print") || token == ("print")) {
                isPrint = true;
            }
            if (!isEquation && !isPrint && (c == ' ' || c == '\t' || c == '\n' || c == ',')) {
                if (!token.empty()) {
                    lexerVector.push_back(token);
                }
                token = "";
                continue;
            } else if (!isPrint && !isCondition && c == '=') {
                token.push_back(c);
                lexerVector.push_back(token);
                isEquation = true;
                token = "";
                continue;

            } else if (!isEquation && c == '(') {
                lexerVector.push_back(token);
                token = "";
                continue;
            } else if (!isEquation && c == ')') {
                if (!token.empty()) {
                    lexerVector.push_back(token);
                }
                token = "";
                continue;
            } else if (c == '"') {
                if (!token.empty()) {
                    lexerVector.push_back(token);
                }
                token = "";
                continue;
            }
            token.push_back(c);
        }
        if (!token.empty()) {
            lexerVector.push_back(token);
        }




    }
    return lexerVector;


}