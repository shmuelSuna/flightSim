#include <iostream>
#include <vector>
#include <fstream>
#include "OpenDataServer.h"
#include "Command.h"
#include <unordered_map>
#include <map>
#include "Parser.h"

using namespace std;
bool isScript = true;

mutex mtx;

vector<string> static lexer(const string&);
string removeSpaces(string);

/*
 * when the user run the program he puts an argument that it is
 * the path to the text file.
 */
int main(int argc, char* argv[]) {

    string input = argv[1];

    unordered_map<string, Command *> mapOfCommands;

    vector<string>vectorOfStrings12;
    try {
        vectorOfStrings12 = lexer(input);
    } catch (const char* e) {
        cerr<<e<<endl;
        return 0;
    }

    vector<string>::iterator it = vectorOfStrings12.begin();

    Parser parser(vectorOfStrings12);
    mapOfCommands = parser.action(vectorOfStrings12);





    parser.operateCommands();



    return 0;

}



vector<string> static lexer(const string& fileName) {
    vector<string> lexerVector;

    ifstream file(fileName);
    if (!file.is_open()) {
        throw("Error open the file");
    }


    string line;

    while(getline(file, line)) {
        std::string token;
        bool isEquation = false;
        bool isVarDec = false;
        int n = line.size();
        int found;



        for (char& c : line) {
            if (token == "var") {
                if (line.find('=') != string::npos) {
                    lexerVector.push_back(token);
                    token = "";
                    continue;
                } else {
                    isVarDec = true;
                }
            }
            if (!isVarDec && c == ' ') {
                continue;
            }
            if (token == ("while") || token == ("if")) {
                if (token == "while") {
                    lexerVector.push_back(token);
                    line = line.substr(6,n-5);
                } else if (token == "if") {
                    lexerVector.push_back(token);
                    line = line.substr(3, n-2);
                }
                token = "";
                int i = 0;
                line = removeSpaces(line);
                n = line.size();
                for (i = 0; i < n; i++) {
                    if (line[i] == '=' || line[i] == '<' || line[i] == '>' || line[i] == '!') {
                        lexerVector.push_back(token);
                        token = "";
                        token.push_back(line[i]);
                        i++;
                        if (line[i] == '=' || line[i] == '<' || line[i] == '>' || line[i] == '!') {
                            token.push_back(line[i]);
                        } else {
                            i--;
                        }
                        lexerVector.push_back(token);
                        token = "";
                        continue;
                    } else if (line[i] == '{') {
                        lexerVector.push_back(token);
                        token = "{";
                        lexerVector.push_back(token);
                        token = "";
                        break;
                    }
                    token.push_back(line[i]);
                }
                break;
            } else if (token ==("Print") || token == ("print")) {
                token = "Print";
                lexerVector.push_back(token);
                token = "";
                found = line.find('(');
                line = line.substr(found+1,n-(found+1));
                token = line.substr(0, line.size()-1);
                if (line[0] != '"') {
                    token = removeSpaces(token);
                }
                lexerVector.push_back(token);
                token = "";
                break;
            } else if (token == "openDataServer") {
                lexerVector.push_back(token);
                token = "";
                token = line.substr(15, n-16);
                token = removeSpaces(token);
                lexerVector.push_back(token);
                token = "";
                break;
            } else if (token == "connectControlClient") {
                lexerVector.push_back(token);
                token = "";
                found = line.find('"');
                line = line.substr(found+1, n-(found+1));
                found = line.find('"');
                token = line.substr(0, found);
                lexerVector.push_back(token);
                token = "";
                token = line.substr(found+2, line.size() - (found + 3));
                token = removeSpaces(token);
                lexerVector.push_back(token);
                token = "";
                break;

            } else if (token == "sleep" || token == "Sleep") {
                token = "Sleep";
                lexerVector.push_back(token);
                token = "";
                found = line.find('(');
                token = line.substr(found+1, n-(found+2));
                token = removeSpaces(token);
                lexerVector.push_back(token);
                token = "";
                break;
            }
            if (!isEquation && (c == ' ' || c == '\t' || c == '\n' || c == ',')) {
                if (!token.empty()) {
                    lexerVector.push_back(token);
                }
                token = "";
                continue;
            } else if (c == '=') {
                lexerVector.push_back(token);
                token = "";
                token.push_back(c);
                lexerVector.push_back(token);
                token = "";
                found = line.find('=');
                token = line.substr(found+1, n-(found+1));
                token = removeSpaces(token);
                lexerVector.push_back(token);
                token = "";
                break;

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
string removeSpaces(string str)
{
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str = str.substr(0, j);
    return str;
}