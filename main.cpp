#include <iostream>
#include <fstream>
#include <string>
#include "parse_semantic.cpp"
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file '" << argv[1] << "'" << endl;
        return 1;
    }

    string source;
    string line;
    while (getline(file, line))
    {
        Tokenizer lexer(line);
        ExpressionParser parser(lexer);
        parser.parse();
    }

    return 0;
}