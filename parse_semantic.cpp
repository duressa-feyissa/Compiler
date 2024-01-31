#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <fstream>
#include "lexer.cpp"

using namespace std;

unordered_map<string, int> variables;

unordered_map<string, int> globalVariables;

class ExpressionParser
{
public:
    ExpressionParser(Tokenizer &tokenizer) : tokenizer(tokenizer) {}

    int parse()
    {
        Token token = tokenizer.getNextToken();
        if (token.kind == TokenKind::EOF_TOKEN)
        {
            return 0;
        }
        int result = parseStatement(token);
        return result;
    }

private:
    int parseStatement(Token &token)
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
                        return 0;
                    }
                    else
                    {
                        cerr << "Error: Invalid print statement" << endl;
                        return 0;
                    }
                }
                else
                {
                    int value = parseExpression(token);
                    if (token.kind == TokenKind::RPAREN)
                    {
                        cout << value << endl;
                        token = tokenizer.getNextToken();
                        return 0;
                    }
                    else
                    {
                        cerr << "Error: Invalid print statement" << endl;
                        return 0;
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
                    int value = parseExpression(token);
                    cout << "PRINT: " << value << endl;
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

                int value = parseExpression(token);
                globalVariables[variableName] = value;
            }
            else if (token.kind == TokenKind::PLUS || token.kind == TokenKind::MINUS || token.kind == TokenKind::MULTIPLY || token.kind == TokenKind::DIVIDE || token.kind == TokenKind::MODULO)
            {
                token = tokenizer.getNextToken();
                int value = parseExpression(token);
                return value + globalVariables[variableName];
            }
            else
            {
                cerr << "Error: Invalid variable assignment" << endl;
                return 0;
            }
        }
        else
        {
            return parseExpression(token);
        }

        return 0;
    }

    int parseExpression(Token &token)
    {
        int result = parseTerm(token);

        while (token.kind == TokenKind::PLUS || token.kind == TokenKind::MINUS)
        {
            if (token.kind == TokenKind::PLUS)
            {
                token = tokenizer.getNextToken();
                result += parseTerm(token);
            }
            else if (token.kind == TokenKind::MINUS)
            {
                token = tokenizer.getNextToken();
                result -= parseTerm(token);
            }
        }

        return result;
    }

    int parseTerm(Token &token)
    {
        int result = parseFactor(token);

        while (token.kind == TokenKind::MULTIPLY || token.kind == TokenKind::DIVIDE || token.kind == TokenKind::MODULO)
        {
            if (token.kind == TokenKind::MULTIPLY)
            {
                token = tokenizer.getNextToken();
                result *= parseFactor(token);
            }
            else if (token.kind == TokenKind::DIVIDE)
            {
                token = tokenizer.getNextToken();
                int divisor = parseFactor(token);
                if (divisor != 0)
                {
                    result /= divisor;
                }
                else
                {
                    cerr << "Error: Division by zero" << endl;
                    return 0;
                }
            }
            else if (token.kind == TokenKind::MODULO)
            {
                token = tokenizer.getNextToken();
                int divisor = parseFactor(token);
                if (divisor != 0)
                {
                    result %= divisor;
                }
                else
                {
                    cerr << "Error: Modulo by zero" << endl;
                    return 0;
                }
            }
        }

        return result;
    }

    int parseFactor(Token &token)
    {
        if (token.kind == TokenKind::INTEGER)
        {
            int value = stoi(token.value);
            token = tokenizer.getNextToken();
            return value;
        }
        else if (token.kind == TokenKind::VARIABLE)
        {
            string variableName = token.value;
            token = tokenizer.getNextToken();

            if (globalVariables.find(variableName) != globalVariables.end())
            {
                return globalVariables[variableName];
            }
            else
            {
                cerr << "Error: Variable '" << variableName << "' not found" << endl;
                return 0;
            }
        }
        else if (token.kind == TokenKind::LPAREN)
        {
            token = tokenizer.getNextToken(); // Consume '('
            int result = parseExpression(token);
            if (token.kind == TokenKind::RPAREN)
            {
                token = tokenizer.getNextToken(); // Consume ')'
                return result;
            }
            else
            {
                cerr << "Error: Unmatched parenthesis" << endl;
                return 0;
            }
        }

        cerr << "Error: Invalid factor" << token.value << endl;
        return 0;
    }

    Tokenizer &tokenizer;
};
