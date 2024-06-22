#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <Windows.h>
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

unordered_map<char, vector<vector<bool>>>charToPixelMap
{
    {'A', {{0, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {1, 1, 1, 1, 1},
           {1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1}}},
    {'B', {{1, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {1, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {1, 1, 1, 1, 0}}},
    {'C', {{0, 1, 1, 1, 1},
           {1, 0, 0, 0, 0},
           {1, 0, 0, 0, 0},
           {1, 0, 0, 0, 0},
           {0, 1, 1, 1, 1}}},
    {'D', {{1, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1},
           {1, 1, 1, 1, 0}}},
    {'E', {{1, 1, 1, 1, 1},
           {1, 0, 0, 0, 0},
           {1, 1, 1, 1, 0},
           {1, 0, 0, 0, 0},
           {1, 1, 1, 1, 1}}},
    {'F', {{1, 1, 1, 1, 1},
           {1, 0, 0, 0, 0},
           {1, 1, 1, 1, 0},
           {1, 0, 0, 0, 0},
           {1, 0, 0, 0, 0}}},
    {'G', {{0, 1, 1, 1, 1},
           {1, 0, 0, 0, 0},
           {1, 0, 0, 1, 1},
           {1, 0, 0, 0, 1},
           {0, 1, 1, 1, 1}}},
    {'H', {{1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1},
           {1, 1, 1, 1, 1},
           {1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1}}},
    {'I', {{1, 1, 1, 1, 1},
           {0, 0, 1, 0, 0},
           {0, 0, 1, 0, 0},
           {0, 0, 1, 0, 0},
           {1, 1, 1, 1, 1}}},
    {'J', {{0, 0, 0, 1, 1},
           {0, 0, 0, 0, 1},
           {0, 0, 0, 0, 1},
           {1, 0, 0, 0, 1},
           {0, 1, 1, 1, 0}}},
    {'K', {{1, 0, 0, 0, 1},
           {1, 0, 0, 1, 0},
           {1, 1, 1, 0, 0},
           {1, 0, 0, 1, 0},
           {1, 0, 0, 0, 1}}},
    {'L', {{1, 0, 0, 0, 0},
           {1, 0, 0, 0, 0},
           {1, 0, 0, 0, 0},
           {1, 0, 0, 0, 0},
           {1, 1, 1, 1, 1}}},
    {'M', {{1, 0, 0, 0, 1},
           {1, 1, 0, 1, 1},
           {1, 0, 1, 0, 1},
           {1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1}}},
    {'N', {{1, 0, 0, 0, 1},
           {1, 1, 0, 0, 1},
           {1, 0, 1, 0, 1},
           {1, 0, 0, 1, 1},
           {1, 0, 0, 0, 1}}},
    {'O', {{0, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1},
           {0, 1, 1, 1, 0}}},
    {'P', {{1, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {1, 1, 1, 1, 0},
           {1, 0, 0, 0, 0},
           {1, 0, 0, 0, 0}}},
    {'Q', {{0, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1},
           {1, 0, 0, 1, 1},
           {0, 1, 1, 1, 1}}},
    {'R', {{1, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {1, 1, 1, 1, 0},
           {1, 0, 1, 0, 0},
           {1, 0, 0, 1, 0}}},
    {'S', {{0, 1, 1, 1, 1},
           {1, 0, 0, 0, 0},
           {0, 1, 1, 1, 0},
           {0, 0, 0, 0, 1},
           {1, 1, 1, 1, 0}}},
    {'T', {{1, 1, 1, 1, 1},
           {0, 0, 1, 0, 0},
           {0, 0, 1, 0, 0},
           {0, 0, 1, 0, 0},
           {0, 0, 1, 0, 0}}},
    {'U', {{1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1},
           {0, 1, 1, 1, 0}}},
    {'V', {{1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1},
           {0, 1, 0, 1, 0},
           {0, 0, 1, 0, 0}}},
    {'W', {{1, 0, 0, 0, 1},
           {1, 0, 0, 0, 1},
           {1, 0, 1, 0, 1},
           {1, 1, 0, 1, 1},
           {1, 0, 0, 0, 1}}},
    {'X', {{1, 0, 0, 0, 1},
           {0, 1, 0, 1, 0},
           {0, 0, 1, 0, 0},
           {0, 1, 0, 1, 0},
           {1, 0, 0, 0, 1}}},
    {'Y', {{1, 0, 0, 0, 1},
           {0, 1, 0, 1, 0},
           {0, 0, 1, 0, 0},
           {0, 0, 1, 0, 0},
           {0, 0, 1, 0, 0}}},
    {'Z', {{1, 1, 1, 1, 1},
           {0, 0, 0, 1, 0},
           {0, 0, 1, 0, 0},
           {0, 1, 0, 0, 0},
           {1, 1, 1, 1, 1}}},
    {'0', {{0, 1, 1, 1, 0},
           {1, 0, 1, 0, 1},
           {1, 0, 1, 0, 1},
           {1, 0, 1, 0, 1},
           {0, 1, 1, 1, 0}}},
    {'1', {{0, 0, 1, 0, 0},
           {0, 1, 1, 0, 0},
           {0, 0, 1, 0, 0},
           {0, 0, 1, 0, 0},
           {1, 1, 1, 1, 1}}},
    {'2', {{0, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {0, 0, 0, 1, 0},
           {0, 0, 1, 0, 0},
           {1, 1, 1, 1, 1}}},
    {'3', {{0, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {0, 0, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {0, 1, 1, 1, 0}}},
    {'4', {{1, 0, 0, 1, 0},
           {1, 0, 0, 1, 0},
           {1, 1, 1, 1, 1},
           {0, 0, 0, 1, 0},
           {0, 0, 0, 1, 0}}},
    {'5', {{1, 1, 1, 1, 1},
           {1, 0, 0, 0, 0},
           {1, 1, 1, 1, 0},
           {0, 0, 0, 0, 1},
           {1, 1, 1, 1, 0}}},
    {'6', {{0, 1, 1, 1, 0},
           {1, 0, 0, 0, 0},
           {1, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {0, 1, 1, 1, 0}}},
    {'7', {{1, 1, 1, 1, 1},
           {0, 0, 0, 0, 1},
           {0, 0, 0, 1, 0},
           {0, 0, 1, 0, 0},
           {0, 0, 1, 0, 0}}},
    {'8', {{0, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {0, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {0, 1, 1, 1, 0}}},
    {'9', {{0, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {0, 1, 1, 1, 1},
           {0, 0, 0, 0, 1},
           {0, 1, 1, 1, 0}}},
    {'.', {{0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 1, 0}}},
    {',', {{0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 1, 0},
           {0, 0, 1, 0, 0}}},
    {';', {{0, 0, 0, 0, 0},
           {0, 0, 0, 1, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 1, 0},
           {0, 0, 1, 0, 0}}},
    {':', {{0, 0, 0, 0, 0},
           {0, 0, 0, 1, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 1, 0},
           {0, 0, 0, 0, 0}}},
    {'-', {{0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0},
           {0, 1, 1, 1, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0}}},
    {'+', {{0, 0, 0, 0, 0},
           {0, 0, 1, 0, 0},
           {0, 1, 1, 1, 0},
           {0, 0, 1, 0, 0},
           {0, 0, 0, 0, 0}}},
    {' ', {{0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0}}},
    {'<', {{0, 0, 0, 0, 1},
            {0, 0, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 1}}},
    {'=', {{0, 0, 0, 0, 0},
           {0, 1, 1, 1, 0},
           {0, 0, 0, 0, 0},
           {0, 1, 1, 1, 0},
           {0, 0, 0, 0, 0}}},
    {'>', {{1, 0, 0, 0, 0},
           {0, 1, 0, 0, 0},
           {0, 0, 1, 0, 0},
           {0, 1, 0, 0, 0},
           {1, 0, 0, 0, 0}}},
    {'!', {{0, 0, 1, 0, 0},
           {0, 0, 1, 0, 0},
           {0, 0, 1, 0, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 1, 0, 0}}},
    {'?', {{0, 1, 1, 1, 0},
           {1, 0, 0, 0, 1},
           {0, 0, 0, 1, 0},
           {0, 0, 1, 0, 0},
           {0, 0, 1, 0, 0}}},
    {'&', {{0, 1, 1, 1, 0},
           {1, 0, 0, 0, 0},
           {0, 1, 1, 1, 0},
           {1, 0, 0, 1, 0},
           {0, 1, 1, 0, 1}}},
    {'#', {{0, 1, 0, 1, 0},
           {1, 1, 1, 1, 1},
           {0, 1, 0, 1, 0},
           {1, 1, 1, 1, 1},
           {0, 1, 0, 1, 0}}},
    {'%', {{1, 0, 0, 0, 1},
           {0, 0, 0, 1, 0},
           {0, 0, 1, 0, 0},
           {0, 1, 0, 0, 0},
           {1, 0, 0, 0, 1}}},
    {'$', {{0, 1, 1, 1, 1},
           {1, 0, 0, 1, 0},
           {0, 1, 1, 0, 0},
           {0, 0, 1, 0, 1},
           {1, 1, 1, 1, 0}}},
    {'£', {{0, 1, 1, 1, 1},
           {0, 1, 0, 0, 0},
           {1, 1, 1, 0, 0},
           {0, 1, 0, 0, 0},
           {1, 1, 1, 1, 1}}},
    {'^', {{0, 0, 1, 0, 0},
           {0, 1, 0, 1, 0},
           {1, 0, 0, 0, 1},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0}}},
    {'_', {{0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0},
           {0, 0, 0, 0, 0},
           {1, 1, 1, 1, 1}}},
    {'\\', {{1, 0, 0, 0, 0},
           {0, 1, 0, 0, 0},
           {0, 0, 1, 0, 0},
           {0, 0, 0, 1, 0},
           {0, 0, 0, 0, 1}}},
    {'/', {{0, 0, 0, 0, 1},
           {0, 0, 0, 1, 0},
           {0, 0, 1, 0, 0},
           {0, 1, 0, 0, 0},
           {1, 0, 0, 0, 0}}},
    {'|', {{0, 1, 0, 0, 0},
           {0, 1, 0, 0, 0},
           {0, 1, 0, 0, 0},
           {0, 1, 0, 0, 0},
           {0, 1, 0, 0, 0}}}
};

class instr
{
    vector<bool>instructions[5];
public:
    size_t size()
    {
        return instructions[0].size();
    }
    auto at(int i, int j)
    {
        return instructions[i][j];
    }
    auto at(int param)
    {
        return instructions[param];
    }
    void push(int pos, bool _X)
    {
        instructions[pos].push_back(_X);
    }
    void invertf()
    {
        if (!this->at(0, 0)) for (int i = 0; i < 5; i++)
            for (int j = 0; j < this->size(); j++)
                this->at(i, j) = !this->at(i, j);
    }
    void AutoPrint()
    {
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        int sizemax = csbi.dwSize.X;
        int low{}, high;
        int size = this->size();
        const int background = 160;
        while (true) {
            high = low + min(sizemax, size);

            for (int i = 0; i < 5; i++) {
                for (int j = low; j < high; j++) {
                    if (this->at(i, j)) SetConsoleTextAttribute(hConsole, 112);
                    else SetConsoleTextAttribute(hConsole, background);
                    cout << ' ';
                    SetConsoleTextAttribute(hConsole, background);
                }
                SetConsoleTextAttribute(hConsole, 15);
                cout << '\n';
            }
            cout << '\n';
            size -= sizemax;
            low += sizemax;
            if (size <= 0) break;
        }
    }
    string sum()
    {
        string _sum{};
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < this->size(); j++) {
                if (this->at(i, j)) _sum += '1';
                else _sum += '0';
            }
        return _sum;
    }
};

int main()
{
    while (true) 
    {
        string word;
        SetConsoleTextAttribute(hConsole, 4);
        cout << "inserisci una stringa da codificare\n\n";
        SetConsoleTextAttribute(hConsole, 15);
        getline(cin, word);
        cout << '\n';
        if (word.empty()) return 0;
        if (word.at(0) == '/' and word.at(word.size() - 1) == '/') 
        {
            word.pop_back();
            word.erase(0, 1);

            string invsum{};
            bool do_continue{ false };
            
            for (char c : word) {
                int decimal;
                c = toupper(c);
                if (isdigit(c)) decimal = c - '0';
                else decimal = c - 'A' + 10;
                if (decimal > 15) {
                    do_continue = 1;
                    break;
                }

                string bin{ string(4, '0') };
                for (int i = 0, binpow = 8; i < 4; i++, binpow /= 2)
                {
                    if (decimal >= binpow) {
                        decimal -= binpow;
                        bin.at(i) = '1';
                    }
                }
                invsum += bin;
            }
            if (do_continue) continue;

            SetConsoleTextAttribute(hConsole, 4);
            cout << "codifica in 0 e 1:\n\n";
            SetConsoleTextAttribute(hConsole, 15);
            if (invsum.at(0) == '0')
                for (int i = 0; i < invsum.size(); i++) {
                    if (invsum.at(i) == '0') invsum.at(i) = '1';
                    else invsum.at(i) = '0';
                }
            cout << invsum << "\n\n";

            instr binary;
            int rows = invsum.size() / 5;
            for (int i = 0; i < 5; i++) 
                for (int j = 0; j < rows; j++) 
                    binary.push(i, 
                        invsum.at(i * rows + j) == '1'
                    );

            SetConsoleTextAttribute(hConsole, 4);
            cout << "messaggio:\n\n";
            SetConsoleTextAttribute(hConsole, 15);
            binary.AutoPrint();
            continue;
        }

        vector<vector<bool>>binaryChar{};
        instr binaryWord;
        for (char c : word) {

            auto it = charToPixelMap.find(toupper(c));
            if (it != charToPixelMap.end())
                binaryChar = it->second;
            for (int i = 0; i < 5; i++) {

                for (bool X : binaryChar[i])
                    binaryWord.push(i, X);
                binaryWord.push(i, 0);
            }
        }
        binaryWord.invertf();

        SetConsoleTextAttribute(hConsole, 4);
        cout << "codifica in 0 e 1 grafica:\n\n";
        SetConsoleTextAttribute(hConsole, 15);
        binaryWord.AutoPrint();
        string sum{ binaryWord.sum() }, hexa;
        
        SetConsoleTextAttribute(hConsole, 4);
        cout << "codifica in 0 e 1:\n\n";
        SetConsoleTextAttribute(hConsole, 15);
        cout << sum << "\n\n";

        for (int i = sum.size() - 1; i >= 0; i -= 4) 
        {
            string temp{ sum };
            stringstream stream;

            if (i + 1 < temp.size()) temp.erase(i + 1);
            if (temp.size() > 4) temp.erase(0, i - 3);
            while (temp.size() < 4) temp = '0' + temp;

            int decimal{};
            for (int i = 0; i < 4; i++)
                decimal += (temp.at(i) - '0') * pow(2, 3 - i);
           
            stream << hex << decimal;
            temp = stream.str();
            hexa = temp + hexa;
        }

        SetConsoleTextAttribute(hConsole, 4);
        cout << "esadecimale:\n\n";
        SetConsoleTextAttribute(hConsole, 15);
        cout << '/' << hexa << "/\n\n";
    }
}
