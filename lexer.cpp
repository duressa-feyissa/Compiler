#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <fstream>

using namespace std;

enum class TokenKind
{
    INTEGER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,
    EOF_TOKEN,
    LPAREN,
    RPAREN,
    ASSIGN,
    VARIABLE,
    PRINT,
    STRING
};

struct Token
{
    TokenKind kind;
    string value;
};

class Tokenizer
{
public:
    Tokenizer(const string &input) : input(input), position(0) {}

    Token getNextToken()
    {
        while (position < input.length() && isspace(input[position]))
        {
            position++;
        }

        if (position >= input.length())
        {
            return {TokenKind::EOF_TOKEN, ""};
        }

        if (isdigit(input[position]))
        {
            return getIntegerToken();
        }

        switch (input[position])
        {
        case '+':
            position++;
            return {TokenKind::PLUS, "+"};
        case '-':
            position++;
            return {TokenKind::MINUS, "-"};
        case '*':
            position++;
            return {TokenKind::MULTIPLY, "*"};
        case '/':
            position++;
            return {TokenKind::DIVIDE, "/"};
        case '%':
            position++;
            return {TokenKind::MODULO, "%"};
        case '(':
            position++;
            return {TokenKind::LPAREN, "("};
        case ')':
            position++;
            return {TokenKind::RPAREN, ")"};
        case '#':
            position++;
            while (position < input.length() && input[position] != '\n')
            {
                position++;
            }
            return getNextToken();
        case '=':
            position++;
            return {TokenKind::ASSIGN, "="};
        }

        if (isalpha(input[position]))
        {
            return getIdentifierToken();
        }

        if (input[position] == '"')
        {
            return getStringToken();
        }

        return {TokenKind::EOF_TOKEN, ""};
    }

private:
    Token getIntegerToken()
    {
        string value;
        while (position < input.length() && isdigit(input[position]))
        {
            value += input[position];
            position++;
        }
        return {TokenKind::INTEGER, value};
    }

    Token getStringToken()
    {
        string value;
        position++;
        while (position < input.length() && (input[position] != '"' || input[position] == '\''))
        {
            value += input[position];
            position++;
        }
        position++;
        return {TokenKind::STRING, value};
    };

    Token getIdentifierToken()
    {
        string value;
        while (position < input.length() && (isalnum(input[position]) || input[position] == '_'))
        {
            value += input[position];
            position++;
        }

        if (value == "print")
        {
            return {TokenKind::PRINT, value};
        }

        return {TokenKind::VARIABLE, value};
    }

    string input;
    size_t position;
};
