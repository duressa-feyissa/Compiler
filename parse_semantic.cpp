#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <fstream>
#include "lexer.cpp"
#include <cmath>

using namespace std;

enum class DataKind
{
    NUMBER,
    STRING,
    boolean
};

struct Data
{
    DataKind kind;
    float floatValue;
    string stringValue;
    bool booleanValue;
};

unordered_map<string, Data> variables;

class ExpressionParser
{
public:
    ExpressionParser(Tokenizer &tokenizer) : tokenizer(tokenizer) {}

    Data parse()
    {
        Token token = tokenizer.getNextToken();
        if (token.kind == TokenKind::EOF_TOKEN)
        {
            return {DataKind::NUMBER, 0};
        }
        Data result = parseStatement(token);
        return result;
    }

private:
    Data parseStatement(Token &token)
    {
        if (token.kind == TokenKind::PRINT)
        {
            token = tokenizer.getNextToken();
            if (token.kind == TokenKind::LPAREN)
            {
                token = tokenizer.getNextToken();
                if (token.kind == TokenKind::STRING)
                {
                    string value = token.value;
                    token = tokenizer.getNextToken();
                    if (token.kind == TokenKind::RPAREN)
                    {
                        cout << value << endl;
                        token = tokenizer.getNextToken();
                        return {DataKind::NUMBER, 0};
                    }
                    else
                    {
                        cerr << "Error: Invalid print statement" << endl;
                        return {DataKind::NUMBER, 0};
                    }
                }
                else
                {
                    Data value = parseExpression(token);
                    if (token.kind == TokenKind::RPAREN)
                    {
                        if (value.kind == DataKind::NUMBER)
                        {
                            cout << value.floatValue << endl;
                        }
                        else if (value.kind == DataKind::boolean)
                        {
                            if (value.booleanValue)
                            {
                                cout << "True" << endl;
                            }
                            else
                            {
                                cout << "False" << endl;
                            }
                        }
                        else
                        {
                            cout << value.stringValue << endl;
                        }
                        token = tokenizer.getNextToken();
                        return {DataKind::NUMBER, 0};
                    }
                    else
                    {
                        cerr << "Error: Invalid print statement" << endl;
                        return {DataKind::NUMBER, 0};
                    }
                }
            }
            else
            {
                if (token.kind == TokenKind::STRING)
                {
                    string value = token.value;
                    token = tokenizer.getNextToken();
                }
                else
                {
                    Data value = parseExpression(token);
                    if (value.kind == DataKind::NUMBER)
                    {
                        cout << "PRINT: " << value.floatValue << endl;
                    }
                    else
                    {
                        cout << "PRINT: " << value.stringValue << endl;
                    }
                    token = tokenizer.getNextToken();
                }
            }
        }
        else if (token.kind == TokenKind::VARIABLE)
        {

            string variableName = token.value;
            token = tokenizer.getNextToken();

            if (token.kind == TokenKind::ASSIGN)
            {
                token = tokenizer.getNextToken();

                Data value = parseExpression(token);

                variables[variableName] = value;
            }

            else if (token.kind == TokenKind::PLUS || token.kind == TokenKind::MINUS || token.kind == TokenKind::MULTIPLY || token.kind == TokenKind::DIVIDE || token.kind == TokenKind::MODULO || token.kind == TokenKind::LESS || token.kind == TokenKind::GREATER || token.kind == TokenKind::LESS_EQUAL || token.kind == TokenKind::GREATER_EQUAL || token.kind == TokenKind::EQUAL || token.kind == TokenKind::NOT_EQUAL || token.kind == TokenKind::AND || token.kind == TokenKind::OR || token.kind == TokenKind::NOT)
            {
                Data value = parseExpression(token);
                return value;
            }
            else
            {
                cerr << "Error: Invalid variable assignment" << endl;
                return {DataKind::NUMBER, 0};
            }
        }
        else
        {
            return parseExpression(token);
        }

        return {DataKind::NUMBER, 0};
    }

    Data parseExpression(Token &token)
    {

        Data result = parseTerm(token);

        while (token.kind == TokenKind::PLUS || token.kind == TokenKind::MINUS)
        {
            if (token.kind == TokenKind::PLUS)
            {
                token = tokenizer.getNextToken();
                Data value = parseTerm(token);
                if (result.kind == DataKind::NUMBER && value.kind == DataKind::NUMBER)
                {
                    result.floatValue += value.floatValue;
                }
                else
                {
                    result.stringValue += value.stringValue;
                }
            }
            else if (token.kind == TokenKind::MINUS)
            {
                token = tokenizer.getNextToken();
                Data value = parseTerm(token);
                if (result.kind == DataKind::NUMBER && value.kind == DataKind::NUMBER)
                {
                    result.floatValue -= value.floatValue;
                }
                else
                {
                    cerr << "Error: Invalid subtraction" << endl;
                    return {DataKind::NUMBER, 0};
                }
            }
        }

        return result;
    }

    Data parseTerm(Token &token)
    {

        Data result = parseFactor(token);
        bool isLogic = false;

        while (token.kind == TokenKind::AND || token.kind == TokenKind::OR || token.kind == TokenKind::LESS || token.kind == TokenKind::GREATER || token.kind == TokenKind::LESS_EQUAL || token.kind == TokenKind::GREATER_EQUAL || token.kind == TokenKind::EQUAL || token.kind == TokenKind::NOT_EQUAL || token.kind == TokenKind::MULTIPLY || token.kind == TokenKind::DIVIDE || token.kind == TokenKind::MODULO)
        {
            if (token.kind == TokenKind::AND)
            {
                token = tokenizer.getNextToken();
                Data value = parseTerm(token);
                if (result.kind == DataKind::boolean && value.kind == DataKind::boolean)
                {

                    result.booleanValue = result.booleanValue && value.booleanValue;
                    result.kind = DataKind::boolean;
                }
                else
                {
                    cerr << "Error: Invalid and operation" << endl;
                    return {DataKind::boolean, 0, "", false};
                }
            }
            else if (token.kind == TokenKind::OR)
            {
                token = tokenizer.getNextToken();
                Data value = parseTerm(token);
                if ((result.kind == DataKind::boolean || result.kind == DataKind::NUMBER) && (value.kind == DataKind::boolean || value.kind == DataKind::NUMBER))
                {
                    result.booleanValue = (result.booleanValue || result.floatValue) || (value.booleanValue || value.floatValue);
                    result.kind = DataKind::boolean;
                }
                else
                {
                    cerr << "Error: Invalid or operation" << endl;
                    return {DataKind::boolean, 0, "", false};
                }
            }
            else if (token.kind == TokenKind::LESS)
            {
                token = tokenizer.getNextToken();
                Data value = parseFactor(token);
                if (result.kind == DataKind::NUMBER && value.kind == DataKind::NUMBER)
                {
                    result.booleanValue = result.floatValue < value.floatValue;
                    result.kind = DataKind::boolean;
                }
                else
                {
                    cerr << "Error: Invalid less than comparison" << endl;
                    return {DataKind::boolean, 0, "", false};
                }
            }
            else if (token.kind == TokenKind::GREATER)
            {
                token = tokenizer.getNextToken();
                Data value = parseFactor(token);
                if (result.kind == DataKind::NUMBER && value.kind == DataKind::NUMBER)
                {
                    result.booleanValue = result.floatValue > value.floatValue;
                    result.kind = DataKind::boolean;
                }
                else
                {
                    cerr << "Error: Invalid greater than comparison" << endl;
                    return {DataKind::boolean, 0, "", false};
                }
            }
            else if (token.kind == TokenKind::LESS_EQUAL)
            {
                token = tokenizer.getNextToken();
                Data value = parseFactor(token);
                if (result.kind == DataKind::NUMBER && value.kind == DataKind::NUMBER)
                {
                    result.booleanValue = result.floatValue <= value.floatValue;
                    result.kind = DataKind::boolean;
                }
                else
                {
                    cerr << "Error: Invalid less than or equal comparison" << endl;
                    return {DataKind::boolean, 0, "", false};
                }
            }
            else if (token.kind == TokenKind::GREATER_EQUAL)
            {
                token = tokenizer.getNextToken();
                Data value = parseFactor(token);
                if (result.kind == DataKind::NUMBER && value.kind == DataKind::NUMBER)
                {
                    result.booleanValue = result.floatValue >= value.floatValue;
                    result.kind = DataKind::boolean;
                }
                else
                {
                    cerr << "Error: Invalid greater than or equal comparison" << endl;
                    return {DataKind::boolean, 0, "", false};
                }
            }
            else if (token.kind == TokenKind::EQUAL)
            {
                token = tokenizer.getNextToken();
                Data value = parseFactor(token);
                if (result.kind == DataKind::NUMBER && value.kind == DataKind::NUMBER)
                {
                    result.booleanValue = result.floatValue == value.floatValue;
                    result.kind = DataKind::boolean;
                }
                else
                {
                    cerr << "Error: Invalid equal comparison" << endl;
                    return {DataKind::boolean, 0, "", false};
                }
            }
            else if (token.kind == TokenKind::NOT_EQUAL)
            {
                token = tokenizer.getNextToken();
                Data value = parseFactor(token);
                if (result.kind == DataKind::NUMBER && value.kind == DataKind::NUMBER)
                {
                    result.booleanValue = result.floatValue != value.floatValue;
                    result.kind = DataKind::boolean;
                }
                else
                {
                    cerr << "Error: Invalid not equal comparison" << endl;
                    return {DataKind::boolean, 0, "", false};
                }
            }

            else if (token.kind == TokenKind::MULTIPLY)
            {
                token = tokenizer.getNextToken();
                Data value = parseFactor(token);
                if (result.kind == DataKind::NUMBER && value.kind == DataKind::NUMBER)
                {
                    result.floatValue *= value.floatValue;
                }
                else
                {
                    cerr << "Error: Invalid multiplication" << endl;
                    return {DataKind::NUMBER, 0};
                }
            }
            else if (token.kind == TokenKind::DIVIDE)
            {
                token = tokenizer.getNextToken();
                Data value = parseFactor(token);
                if (result.kind == DataKind::NUMBER && value.kind == DataKind::NUMBER)
                {
                    if (value.floatValue != 0)
                    {
                        result.floatValue /= value.floatValue;
                    }
                    else
                    {
                        cerr << "Error: Division by zero" << endl;
                        return {DataKind::NUMBER, 0};
                    }
                }
                else
                {
                    cerr << "Error: Invalid division" << endl;
                    return {DataKind::NUMBER, 0};
                }
            }
            else if (token.kind == TokenKind::MODULO)
            {
                token = tokenizer.getNextToken();
                Data value = parseFactor(token);
                if (result.kind == DataKind::NUMBER && value.kind == DataKind::NUMBER)
                {
                    if (value.floatValue != 0)
                    {
                        result.floatValue = fmod(result.floatValue, value.floatValue);
                    }
                    else
                    {
                        cerr << "Error: Modulo by zero" << endl;
                        return {DataKind::NUMBER, 0};
                    }
                }
                else
                {
                    cerr << "Error: Invalid modulo" << endl;
                    return {DataKind::NUMBER, 0};
                }
            }
        }

        return result;
    }

    Data parseFactor(Token &token)
    {
        if (token.kind == TokenKind::NOT)
        {
            token = tokenizer.getNextToken();
            Data value = parseFactor(token);
            if (value.kind == DataKind::boolean || value.kind == DataKind::NUMBER)
            {
                value.booleanValue = !(value.booleanValue || value.floatValue);
                return value;
            }
            else
            {
                cerr << "Error: Invalid not operation" << endl;
                return {DataKind::boolean, 0, "", false};
            }
        }
        else if (token.kind == TokenKind::BOOLEAN)
        {
            bool value = token.value == "True";
            token = tokenizer.getNextToken();
            return {DataKind::boolean, 0, "", value};
        }
        else if (token.kind == TokenKind::STRING)
        {
            string value = token.value;
            token = tokenizer.getNextToken();
            return {DataKind::STRING, 0, value, false};
        }
        else if (token.kind == TokenKind::INTEGER)
        {
            float value = stoi(token.value);
            token = tokenizer.getNextToken();
            return {DataKind::NUMBER, value, "", false};
        }
        else if (token.kind == TokenKind::VARIABLE)
        {
            string variableName = token.value;
            token = tokenizer.getNextToken();
            if (variables.find(variableName) != variables.end())
            {
                return variables[variableName];
            }
            else
            {
                cerr << "Error: Variable '" << variableName << "' not found" << endl;
                return {DataKind::NUMBER, 0, "", false};
            }
        }
        else if (token.kind == TokenKind::LPAREN)
        {

            token = tokenizer.getNextToken();
            Data result = parseExpression(token);
            if (token.kind == TokenKind::RPAREN)
            {
                token = tokenizer.getNextToken();
                return result;
            }
            else
            {
                cerr << "Error: Unmatched parenthesis" << endl;
                return {DataKind::NUMBER, 0, "", false};
            }
        }

        cerr << "Error: Invalid factor occur" << token.value << endl;
        return {DataKind::NUMBER, 0, "", false};
    }
    Tokenizer &tokenizer;
};
