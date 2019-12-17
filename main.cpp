#include <iostream>
#include <vector>
#include <fstream>
#include "OpenDataServer.h"
#include "Command.h"
#include <unordered_map>
#include <map>
#include "Parser.h"
#include <thread>

using namespace std;

vector<string> static lexer(const string&);


int main() {

    unordered_map<string, Command *> mapOfCommands;

    vector<string>vectorOfStrings12;
    vectorOfStrings12 = lexer("fly.txt");

    Parser parser(vectorOfStrings12);
    mapOfCommands = parser.action(vectorOfStrings12);



    SymbolTable * st = createSymbolTable();

    OpenDataServer ods(5400);
    ods.setSymbolTable(st);

    //temo vector and iter just to run the functions execute
    vector<string> vec;
    vec.push_back("test");
    vector<string>::iterator it = vec.begin();

    thread t1([&]() {
        return ods.execute(it);});


    string s = "127.0.0.1";

    ConnectCommand cc(s, 5402);
    cc.setSymbolTable(st);
    cc.execute(it);


    t1.join();









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
        bool isVarDec = false;

        for (char& c : line) {
            if (token == ("while") || token == ("if")) {
                isCondition = true;
            }else if (token ==("Print") || token == ("print")) {
                isPrint = true;
            } else if (token == "var") {
                isVarDec = true;
            }
            if (!isEquation && !isPrint && (c == ' ' || c == '\t' || c == '\n' || c == ',')) {
                if (!token.empty()) {
                    lexerVector.push_back(token);
                }
                token = "";
                continue;
            } else if (!isPrint && !isCondition && c == '=') {
                if (!token.empty()) {
                    lexerVector.push_back(token);
                    token = "";
                }
                token.push_back(c);
                lexerVector.push_back(token);
                isEquation = true;
                token = "";
                continue;

            } else if (isEquation) {
                if (c == ' ') {
                    continue;
                }
            } else if (isVarDec && (c == '-' || c == '>'|| c == '<' )) {
                    if (!token.empty() && token != "-" && token != "<" && token != ">") {
                        lexerVector.push_back(token);
                        token = "";
                    }
                    token.push_back(c);

                    if (token.size() == 2) {
                        lexerVector.push_back(token);
                        token = "";
                        isVarDec = false;

                    }
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