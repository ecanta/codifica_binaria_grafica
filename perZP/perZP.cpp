#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <algorithm>
#include <cctype>
#include <conio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <Windows.h>
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

// informazioni sulla posizione delle scorciatoie
struct ShortcutInfo {
	string name;
	int startx;
	int endx;
	bool has_space; // spazio prima del resto
};
vector<ShortcutInfo> Data;

// mappa che contiene le informazioni sui caratteri
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
string Aliases[26];

// classe che contiene le istruzioni di disegno
class instr
{
	// dati
private:
	int dimension;
	vector<bool>* instructions;

	// costruttori
public:
	instr() : dimension(5)
	{
		instructions = new vector<bool>[5];
	}
	instr(int dim) : dimension(dim)
	{
		instructions = new vector<bool>[dim];
	}
	instr(int dim, int size) : dimension(dim)
	{
		instructions = new vector<bool>[dim];
		this->resize(size);
	}

	// dimensioni
	bool empty() const
	{
		for (size_t i = 0; i < this->dimension; ++i)
			for (size_t j = 0; j < this->size(); ++j)
				if (instructions[i][j]) return false;
		return true;
	}
	int extent() const
	{
		return dimension;
	}
	size_t size() const
	{
		return instructions[0].size();
	}
	void resize(int newsize)
	{
		for (int i = 0; i < dimension; ++i) instructions[i].resize(newsize, false);
	}
	
	// accesso
	auto at(int i, int j) const
	{
		return instructions[i][j];
	}
	auto at(int param) const
	{
		return instructions[param];
	}

	// contrazione
	int truelen() const
	{
		int MaxIndex{ -1 };
		for (int i = 0; i < dimension; ++i)
			for (int j = 0; j < (int)this->size(); ++j)
				if (this->at(i, j) and MaxIndex < j)
					MaxIndex = j;
		return MaxIndex;
	}
	void shorten(int limit = 0)
	{
		this->resize(max(limit, this->truelen() + 1));
	}
	
	// concatenazione
	void attach(const instr& other)
	{
		for (int i = 0; i < dimension; ++i) instructions[i].insert(
			instructions[i].end(),
			other.instructions[i].begin(),
			other.instructions[i].end()
		);
	}

	// rimozione di una colonna
	void erase(size_t ind)
	{
		for (int i = 0; i < this->dimension; ++i) {
			instructions[i].erase(instructions[i].begin() + ind);
			instructions[i].push_back(false);
		}
	}

	// inserimento di alcune colonne
	void insert(size_t where, size_t amount)
	{
		vector<bool> print(amount, false);
		if (where == this->size()) for (int i = 0; i < this->dimension; ++i)
			instructions[i].push_back(false);

		for (int i = 0; i < this->dimension; ++i) instructions[i].insert(
			instructions[i].begin() + where,
			print.begin(),
			print.end()
		);
	}

	// aggiunta di un bit
	void push(int pos, bool _X)
	{
		instructions[pos].push_back(_X);
	}
	
	// flip
	void invertf() const
	{
		if (!this->at(0, 0)) for (int i = 0; i < this->dimension; ++i)
			for (int j = 0; j < this->size(); ++j)
				this->at(i, j) = !this->at(i, j);
	}
	
	// visualizzazione grafica
	void AutoPrint(int low = 0, const int& background = 170) const
	{
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		int sizemax = csbi.dwSize.X, high, size = this->size();
		while (true) {
			high = low + min(sizemax, size);

			for (int i = 0; i < this->dimension; ++i) {
				for (int j = low; j < high; ++j) {
					if (this->at(i, j)) {
						SetConsoleTextAttribute(hConsole, 255);
						cout << 'O';
					}
					else {
						SetConsoleTextAttribute(hConsole, background);
						cout << '_';
					}
					SetConsoleTextAttribute(hConsole, background);
				}
				SetConsoleTextAttribute(hConsole, 15);
				cout << '\n';
			}
			cout << '\n';
			size -= sizemax;
			low += sizemax;
			if (size <= 0 or low == this->size()) break;
		}
	}

	// binario
	string sum() const
	{
		string _sum;
		for (int i = 0; i < this->dimension; ++i)
			for (int j = 0; j < this->size(); ++j)
			{
				if (this->at(i, j)) _sum += '1';
				else _sum += '0';
			}
		return _sum;
	}
};
vector<string> ShortcutNames;
unordered_map<int, vector<instr>> shortcuts;

// rimuove le maiuscole dalla stringa
static string tolower(string str)
{
	for (auto& ch : str) ch = tolower(ch);
	return str;
}

// controlla se una stringa è un numero intero
static bool is_integer(string str)
{
	if (str.empty()) return false;
	for (const auto& ch : str) if (!isdigit(ch)) return false;
	return true;
}

// cerca una scorciatoia
static ptrdiff_t find_shortcut(string name)
{
	ptrdiff_t index{ -1 };
	for (ptrdiff_t i = 0; i < ShortcutNames.size(); ++i)
		if (name == ShortcutNames[i]) {
			index = i;
			break;
		}
	return index;
}

// converte un quadrato di pixel in instr
static instr convert_map_to_instr(vector<vector<bool>> square)
{
	instr map(square.size());
	map.resize(square[0].size());
	for (size_t i = 0; i < square.size(); ++i)
		for (size_t j = 0; j < square[0].size(); ++j)
			map.at(i, j) = square[i][j];
	return map;
}

// aggiunge lo spazio necessario per disegnare
static int allocate_rows(int rows)
{
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto begin{ csbi.dwCursorPosition };
	cout << string(rows, '\n');
	
	int shiftup{ rows - csbi.dwSize.Y + begin.Y + 1 };
	if (shiftup < 0) shiftup = 0;
	begin.X = 0;
	begin.Y -= shiftup;
	SetConsoleCursorPosition(hConsole, begin);

	return shiftup;
}

// disegna un cursore sulla griglia
static void draw_cursor(COORD CursorPos, bool Val)
{
	SetConsoleCursorPosition(hConsole, CursorPos);
	SetConsoleTextAttribute(hConsole, Val ? 204 : 68);
	cout << (Val ? 'O' : '_');
	SetConsoleCursorPosition(hConsole, CursorPos);
}

// rimuove il cursore dalla griglia
static void erase_cursor(COORD CursorPos, bool Val)
{
	SetConsoleCursorPosition(hConsole, CursorPos);
	SetConsoleTextAttribute(hConsole, (Val ? 255 : 170));
	cout << (Val ? 'O' : '_');
}

// cancella il comando
static void erase_command(COORD line, COORD CursorPos, bool Val, bool repo = true)
{
	SetConsoleTextAttribute(hConsole, 15);
	SetConsoleCursorPosition(hConsole, line);
	cout << string(csbi.dwSize.X, L' ');
	
	if (repo) {
		SetConsoleTextAttribute(hConsole, (Val ? 255 : 170));
		SetConsoleCursorPosition(hConsole, CursorPos);
		return;
	}
	SetConsoleCursorPosition(hConsole, line);
}

// crea una nuova griglia vuota
static void new_grid(int dim, COORD& end, int gap = 1)
{
	SetConsoleCursorPosition(hConsole, end);
	SetConsoleTextAttribute(hConsole, 170);
	for (int i = 0; i < dim; ++i) {
		cout << string(csbi.dwSize.X, '_');
		if (i != dim - 1) cout << '\n';
	}

	SetConsoleCursorPosition(hConsole, end);
	SetConsoleTextAttribute(hConsole, 68);
	cout << '_';
	SetConsoleCursorPosition(hConsole, end);
	end.Y += dim + gap;
}

// riscrive il titolo della griglia
static void title_output(COORD line, string output)
{
	SetConsoleCursorPosition(hConsole, line);
	SetConsoleTextAttribute(hConsole, 4);
	cout << output;
}

// ridisegna l'ultima parte della griglia
static void update_grid
(instr& grid, COORD& end, int dim, bool linechange, bool redraw = false)
{
	// scorrimento
	if (linechange) {
		end.Y -= allocate_rows(dim + 1);
		end.Y += dim + 1;
	}

	// arrotondamento
	int Size = csbi.dwSize.X;
	auto gridsize{ grid.size() };
	grid.resize(Size * max(ceil((double)gridsize / Size), 1.0));
	gridsize = grid.size();

	// riposizionamento
	auto Begin{ end };
	Begin.Y -= redraw ?
		(dim + 1) * (gridsize / Size)
		: ((gridsize > Size) + 1) * (dim + 1);
	if (Begin.Y < 0) Begin.Y += dim + 1;
	SetConsoleCursorPosition(hConsole, Begin);

	// ricaricamento della griglia
	int value;
	if (gridsize > Size) value = gridsize - 2 * Size;
	else value = gridsize - Size;
	if (redraw) value = 0;
	grid.AutoPrint(value);
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	end.Y = csbi.dwCursorPosition.Y;
}

// ridisegna la griglia originale
static void back_to_original_grid
(instr grid, COORD& CursorPosition, COORD& line, int dim)
{
	// reset dati
	SetConsoleTextAttribute(hConsole, 15);
	line.Y -= 2;
	SetConsoleCursorPosition(hConsole, line);

	// output titolo
	line.Y -= allocate_rows(dim + 7);
	cout << "\n\n";
	title_output(line, "Riprendi il disegno");
	cout << "\n\n";

	// ripresa della griglia di prima
	grid.AutoPrint();
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	CursorPosition = line = csbi.dwCursorPosition;
	CursorPosition.Y -= dim + 1;
	SetConsoleCursorPosition(hConsole, CursorPosition);
}

// richiede un comando all'utente
static string command_input(COORD line, string output)
{
	string input;
	SetConsoleCursorPosition(hConsole, line);
	SetConsoleTextAttribute(hConsole, 4);
	cout << output << ": ";
	SetConsoleTextAttribute(hConsole, 12);
	while (input.empty()) getline(cin, input);
	return tolower(input);
}

// adatta una scorciatoia ad una dimensione diversa
static instr adapte(const instr& matrix, int NewH)
{
	// inizio
	int h1 = matrix.extent();
	if (h1 == 0) return instr(0);
	int w1 = matrix.size();
	if (w1 == 0) return instr(0);

	// calcolo delle nuove dimensioni
	double scale = (double)NewH / h1;
	int NewW = round(w1 * scale);
	instr result(NewH);
	result.resize(NewW);

	for (int y = 0; y < NewH; ++y) for (int x = 0; x < NewW; ++x) {

		// copertura del pixel nuovo
		double y0 = (int)floor(y * (double)h1 / NewH);
		double y1 = (int)ceil((y + 1) * (double)h1 / NewH);
		double x0 = (int)floor(x * (double)w1 / NewW);
		double x1 = (int)ceil((x + 1) * (double)w1 / NewW);

		// attivazione
		int count{};
		double sum{};
		for (int iy = y0; iy < y1; ++iy) {
			if (iy < 0 or iy >= h1) continue;

			for (int ix = x0; ix < x1; ++ix) {
				if (ix < 0 or ix >= w1) continue;

				sum += matrix.at(iy, ix);
				count++;
			}
		}
		result.at(y, x) = count > 0 and sum / count >= 0.5;
	}

	return result;
}

// conta gli spazi di una stringa e trova il primo
static int count_spaces(string str, ptrdiff_t& FirstSpace)
{
	bool first{ true };
	int spaces{};
	FirstSpace = -1;
	for (size_t i = 0; i < str.size(); ++i) if (str.at(i) == L' ') {
		spaces++;
		if (first) {
			first = false;
			FirstSpace = i;
		}
	}
	return spaces;
}

// funzione di disegno
static instr draw(
	int dim,
	bool& ReturnedValue,
	bool& ExitWith,
	bool saving = false,
	instr base = instr(0)
)
{
	// ridimensionamento delle scorciatoie per la dimensione data
	if (!saving) {
		Data.clear();

		// inserimento del vettore se non c'è di già
		if (shortcuts.find(dim) == shortcuts.end())
			shortcuts.insert({ dim, {} });

		// calcolo dimensione da cui copiare
		int sizemaxindex{}, sizemax{};
		for (const auto& it : shortcuts) if (sizemax < it.second.size()) {
			sizemax = it.second.size();
			sizemaxindex = it.first;
		}

		// copia e adattamento
		auto& vect{ shortcuts[sizemaxindex] };
		if (sizemaxindex != dim)
			for (size_t i = shortcuts[dim].size(); i < vect.size(); ++i)
				shortcuts[dim].push_back(adapte(vect[i], dim));
	}

	// inizio
	ExitWith = false;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto begin{ csbi.dwCursorPosition };
	if (csbi.dwSize.Y <= dim + 7) return instr(0);
	
	// creazione della griglia di disegno
	if (base.extent() != dim) base = instr(dim);
	instr grid = base;
	grid.resize((grid.size() / csbi.dwSize.X + 1) * csbi.dwSize.X);

	// coordinamenti
	begin.X = 0;
	begin.Y -= allocate_rows(dim + 3);
	auto end{ begin };
	end.Y += dim + 1;
	auto CursorPosition{ begin };
	
	// disegno di quella griglia
	if (base.size() > 0) {
		grid.AutoPrint();
		SetConsoleCursorPosition(hConsole, CursorPosition);
		SetConsoleTextAttribute(hConsole, (grid.at(0, 0) ? 204 : 68));
		cout << '_';
		SetConsoleCursorPosition(hConsole, CursorPosition);
	}
	else new_grid(dim, begin);

	// loop dell'input
	size_t ResistShorting{};
	bool TryExit{ false };
	int row{}, column{};
	bool CurrentValue{ false };
	while (true) if (_kbhit() or TryExit)
	{
		string command, CommandArgs;
		ptrdiff_t ShortcutIndex;

		// input carattere
		char c = TryExit ? '\r' : _getch();
		if (saving) c = toupper(c);
		CurrentValue = grid.at(row, column);

		// alias di una lettera
		if (c < 0) continue;
		if (isalpha(c) and islower(c)) {
			command = Aliases[c - 'a'];
			CommandArgs.clear();
			ShortcutIndex = find_shortcut(command);
			goto write_shortcut;
		}

		// uscita
		if (c == '\r') if (!grid.empty() or TryExit) {

			// conferma dell'invio
			if (!saving and !TryExit) {
				auto ans{ command_input(
					end,
					"Sei sicuro di volere inviare? il testo non verra' salvato. "
				) };

				// niente conferma
				if (ans != "si") {
					erase_command(end, CursorPosition, CurrentValue);
					draw_cursor(CursorPosition, grid.at(row, column));
					continue;
				}

				cout << "\n\n";
			}

			erase_cursor(CursorPosition, CurrentValue);
			SetConsoleTextAttribute(hConsole, 15);
			erase_command(end, end, 0);
			break;
		}

		// switch dell'input
		switch (c)
		{
			// inserimento di un pixel
		case ' ': {
			grid.at(row, column) = true;
			SetConsoleTextAttribute(hConsole, 204);
			cout << 'O';
			SetConsoleCursorPosition(hConsole, CursorPosition);
			break;
		}

			// cancellazione di un pixel
		case '\b': {
			grid.at(row, column) = false;
			SetConsoleTextAttribute(hConsole, 68);
			cout << '_';
			SetConsoleCursorPosition(hConsole, CursorPosition);
			break;
		}

			// rimozione dell'ultima scorciatoia
		case 127: {
			
			// controllo accessibilità
			if (Data.empty()) break;
			auto sc{ Data[Data.size() - 1] };
			if (grid.truelen() != sc.endx) break;
			if (grid.size() - sc.startx > csbi.dwSize.X) break;

			// rimozione
			Data.pop_back();
			for (int i = 0; i < dim; ++i) for (int j = sc.startx; j <= sc.endx; ++j)
				grid.at(i, j) = false;
			if (!Data.empty()) ResistShorting = Data.at(Data.size() - 1).endx;

			// disegno
			update_grid(grid, end, dim, false);
			CursorPosition.X -= (sc.endx - sc.startx + 1);
			column -= (sc.endx - sc.startx + 1);
			draw_cursor(CursorPosition, grid.at(row, column));
			break;
		}

			// inversione di un pixel
		case 'C': {
			grid.at(row, column) = !CurrentValue;
			SetConsoleTextAttribute(hConsole, (CurrentValue ? 68 : 204));
			cout << (CurrentValue ? '_' : 'O');
			SetConsoleCursorPosition(hConsole, CursorPosition);
			break;
		}

			// movimenti
		case 'W': {
			if (row == 0) break;
			row--;
			erase_cursor(CursorPosition, CurrentValue);
			CursorPosition.Y--;
			break;
		}
		case 'S': {
			if (row == dim - 1) break;
			row++;
			erase_cursor(CursorPosition, CurrentValue);
			CursorPosition.Y++;
			break;
		}
		case 'A': {
			if (column % csbi.dwSize.X == 0) break;
			column--;
			erase_cursor(CursorPosition, CurrentValue);
			CursorPosition.X--;
			break;
		}
		case 'D': {

			// movimento
			int shiftup{};
			column++;
			erase_cursor(CursorPosition, CurrentValue);

			// aggiunta di una seconda fascia
			if (column % csbi.dwSize.X == 0 and column > 0) {
				allocate_rows(dim + 3);
				new_grid(dim, end);
				grid.resize(grid.size() + csbi.dwSize.X);
				SetConsoleCursorPosition(hConsole, CursorPosition);
			}

			// aggiornamento posizione speciale
			if (column % csbi.dwSize.X == 0 and column > 0) {
				CursorPosition.X = 0;
				CursorPosition.Y += dim + 1;
				CursorPosition.Y -= shiftup;
				break;
			}

			// aggiornamento posizione normale
			CursorPosition.X++;
			break;
		}

			// comandi
		case '/':
			end.Y -= allocate_rows(4);
			command = CommandArgs = command_input(end, "Inserisci comando");
			
			// taglio degli spazi
			{
				size_t _pos{ command.find(' ') };
				if (_pos != string::npos) {
					command.erase(_pos);
					CommandArgs.erase(0, _pos + 1);
				}
				else CommandArgs.clear();
			}
			
			// rimozione spazi finali
			{
				int spaces{};
				for (; spaces < CommandArgs.size(); ++spaces)
					if (CommandArgs.at(CommandArgs.size() - spaces - 1) != L' ')
						break;
				if (!CommandArgs.empty() and spaces > 0)
					CommandArgs.erase(CommandArgs.size() - spaces);
			}

			// fine del salvataggio
			if (command == "resume" and !grid.empty() and saving)
			{
				ExitWith = true;
				erase_cursor(CursorPosition, CurrentValue);
				SetConsoleCursorPosition(hConsole, end);
				grid.shorten();
				return grid;
			}

			// undo messaggio comando o filtro comandi in modalità salvataggio
			if (command == "void" or saving)
			{
				erase_command(end, CursorPosition, CurrentValue);
				break;
			}

			// lista delle scorciatoie o dei comandi
			if (command == "list_shortcuts" or
				command == "help" or
				command == "export")
			{
				auto ans{ command_input(
					end,
					"Per eseguire il comando \
e' necessario tornare alla schermata principale, continuare?"
				) };
				if (ans == "si") {
					ExitWith = TryExit = true;
					ReturnedValue = command != "list_shortcuts";

					if (command == "export") ExitWith = false;
					cout << "\n\n";
				}
				break;
			}

			// impostazione dell'alias di una scorciatoia
			if (command == "alias")
			{
				erase_command(end, end, 0);

				// troppi spazi
				ptrdiff_t FirstSpace;
				int spaces{ count_spaces(CommandArgs, FirstSpace) };
				if (spaces > 1) {
					erase_command(end, CursorPosition, CurrentValue);
					break;
				}

				// ottenimento argomenti
				ptrdiff_t scIndex;
				string shortcut, key;
				if (spaces < 1) shortcut = CommandArgs;
				else {
					key = shortcut = CommandArgs;
					shortcut.erase(FirstSpace);
					key.erase(0, FirstSpace + 1);
				}

				// conferma scorciatoia
				do {
					erase_command(end, end, 0);
					scIndex = find_shortcut(shortcut);

					if (scIndex == -1) shortcut = command_input(
						end, "Inserisci il nome corrente della scorciatoia"
					);
				} while (scIndex == -1);

				// conferma tasto
				do {
					erase_command(end, end, 0);
					if (key.size() > 1 or !isalnum(key.at(0))) 
						key = command_input(end, "Inserisci il nome del tasto");

				} while (key.size() > 1 or !isalnum(key.at(0)));

				// impostazione
				Aliases[key.at(0) - 'A'] = shortcut;
				erase_command(end, CursorPosition, CurrentValue);
				break;
			}

			// rinominazione di una scorciatoia
			if (command == "rename")
			{
				erase_command(end, end, 0);

				// troppi spazi
				ptrdiff_t FirstSpace;
				int spaces{ count_spaces(CommandArgs, FirstSpace) };
				if (spaces > 1) {
					erase_command(end, CursorPosition, CurrentValue);
					break;
				}

				// ottenimento argomenti
				ptrdiff_t scIndex, otherIndex;
				string from, to;
				if (spaces < 1) from = CommandArgs;
				else {
					to = from = CommandArgs;
					from.erase(FirstSpace);
					to.erase(0, FirstSpace + 1);
				}
				
				// conferma scorciatoia
				do {
					erase_command(end, end, 0);
					scIndex = find_shortcut(from);

					if (scIndex == -1) from = command_input(
						end, "Inserisci il nome corrente della scorciatoia"
					);
				} while (scIndex == -1);

				// conferma nome
				do {
					erase_command(end, end, 0);
					otherIndex = find_shortcut(to);

					// controllo caratteri
					if (to.empty()) otherIndex = 0;
					for (const auto& ch : to) if (!isalnum(ch) and ch != '_') {
						otherIndex = 0;
						break;
					}

					if (otherIndex != -1)
						to = command_input(end, "Inserisci il nuovo nome");
				} while (otherIndex != -1);

				// impostazione
				ShortcutNames[scIndex] = to;
				erase_command(end, CursorPosition, CurrentValue);
				break;
			}

			// modifica di una scorciatoia
			if (command == "edit")
			{
				// controllo spazi
				auto original_size{ grid.size() };
				if (CommandArgs.find(' ') != string::npos) {
					erase_command(end, CursorPosition, CurrentValue);
					break;
				}

				// conferma scorciatoia
				ptrdiff_t scIndex;
				do {
					erase_command(end, end, 0);
					scIndex = find_shortcut(CommandArgs);

					if (scIndex == -1) CommandArgs = command_input(
						end, "Inserisci il nome della scorciatoia da modificare"
					);
				} while (scIndex == -1);
				erase_command(end, CursorPosition, CurrentValue);
				auto oldsize{ shortcuts[dim][scIndex].size() };

				// modifica della scorciatoia
				bool no_use1, no_use2;
				auto NewValue{
					draw(dim, no_use1, no_use2, true, shortcuts[dim][scIndex])
				};
				GetConsoleScreenBufferInfo(hConsole, &csbi);
				end = csbi.dwCursorPosition;
				shortcuts[dim][scIndex] = NewValue;
				auto newsize{ shortcuts[dim][scIndex].size() };

				// modifica delle occorrenze di quella scorciatoia nella griglia
				ptrdiff_t sizediff = newsize - oldsize;
				for (ptrdiff_t i = Data.size() - 1; i >= 0; --i)
					if (Data[i].name == CommandArgs)
					{
						// modifica spazio
						if (sizediff > 0) grid.insert(Data[i].endx + 1, sizediff);
						else for (int j = 0; j < -sizediff; ++j)
							grid.erase(Data[i].startx);

						// riscrizione
						bool has_space{ Data[i].has_space };
						for (int I = 0; I < dim; ++I)
							for (size_t j = 0; j < newsize; ++j)
								grid.at(I, Data[i].startx + j + has_space)
								= NewValue.at(I, j);
					}

				// arrotondamento dimensione
				int Size = csbi.dwSize.X;
				grid.resize(Size * max(ceil((double)grid.size() / Size), 1.0));
				if (grid.size() > original_size) column = grid.size() - Size;
				
				// ripresa della griglia
				end.Y += 2;
				back_to_original_grid(grid, CursorPosition, end, dim);
				draw_cursor(CursorPosition, grid.at(row, column));
				break;
			}

			// salvataggio di una scorciatoia
			if (command == "save" or command == "savemany")
			{
				// creazione di una griglia di disegno separata
				erase_cursor(CursorPosition, CurrentValue);
				SetConsoleCursorPosition(hConsole, end);
				SetConsoleTextAttribute(hConsole, 15);
				cout << "\n\n";
				bool ExitVal, No_use;

				// ciclo
				do {
					auto shortcut{ draw(dim, No_use, ExitVal, true) };
					GetConsoleScreenBufferInfo(hConsole, &csbi);
					end = csbi.dwCursorPosition;
					if (ExitVal) break;

					// input controllato comando
					string text{ "Inserisci il nome della scorciatoia" }, name;
					ptrdiff_t index;
					do {
						// input
						index = -1;
						name = command_input(end, text);

						// controllo caratteri
						bool wrong{ false };
						for (const auto& ch : name) if (!isalnum(ch) and ch != L'_')
						{
							wrong = true;
							break;
						}

						// scorciatoia già esistente
						index = find_shortcut(name);
						if (index >= 0) {
							erase_command(end, end, 0);
							text = "Esiste gia' \
una scorciatoia con tale nome, riprova\a";
						}
						
						// errore per i caratteri non ammessi
						if (wrong) {
							text = "Il nome puo' contenere solo \
numeri, lettere e underscore\a";
							index = 0;
						}
					} while (index >= 0);

					// push
					cout << '\n';
					shortcuts[dim].push_back(shortcut);
					ShortcutNames.push_back(name);
				} while (command == "savemany");

				// ridisegno
				if (command == "save") end.Y += 4;
				back_to_original_grid(grid, CursorPosition, end, dim);
				draw_cursor(CursorPosition, grid.at(row, column));
				break;
			}

			// strumenti di disegno
			if (command == "horizontal" or command == "rubber")
			{
				// controllo spazi
				if (CommandArgs.find(' ') != string::npos) {
					erase_command(end, end, 0);
					break;
				}

				// conferma lunghezza
				do {
					erase_command(end, end, 0);

					if (!is_integer(CommandArgs)) CommandArgs = command_input(
						end, "Inserisci la lunghezza del tratto"
					);
				} while (!is_integer(CommandArgs));
				
				// disegno linea
				int amount{ stoi(CommandArgs) };
				size_t endpos = CursorPosition.X + amount - 1;
				if (endpos >= grid.size()) endpos = grid.size() - 1;
				bool fill{ command == "horizontal" };
				for (size_t i = CursorPosition.X; i <= endpos; ++i)
					grid.at(row, i) = fill;

				// disegno griglia nuova
				update_grid(grid, end, dim, false);
				CursorPosition.X = endpos;
				column = grid.size() - csbi.dwSize.X + CursorPosition.X;
				draw_cursor(CursorPosition, grid.at(row, column));
				erase_command(end, CursorPosition, CurrentValue);
				break;
			}

			// rimozione della colonna
			if (command == "erase_col")
			{
				grid.erase(column);
				update_grid(grid, end, dim, false);
				draw_cursor(CursorPosition, grid.at(row, column));
				erase_command(end, CursorPosition, CurrentValue);
				break;
			}

			// fetch dati
			if (command == "paste")
			{
				int global_dim;

				// input del codice
				bool start{ true };
				string codes{ CommandArgs }, out{ "Inserisci i dati esportati"};
				while (true)
				{
					// primo input
					if (!start) {
						erase_command(end, end, 0);
						codes = command_input(end, out);
					}
					start = false;
					if (codes.empty()) continue;

					// estrazione della dimensione
					auto sep{ codes.find('&') };
					if (sep == string::npos) {
						out = "Il codice non contiene la dimensione, riprova";
						continue;
					}
					auto Dim{ codes };
					Dim.erase(sep);
					codes.erase(0, sep + 1);

					// controllo della dimensione
					if (Dim.substr(0, 4) != "dim=") {
						out = "La dimensione non ha il suo contrassegno, riprova";
						continue;
					}
					Dim.erase(0, 4);
					if (!is_integer(Dim) or Dim.size() > 2) {
						out = "La dimensione non e' valida, riprova";
						continue;
					}
					global_dim = stoi(Dim);
					if (global_dim != 3 and global_dim != 5 and global_dim != 7
						and global_dim != 11 and global_dim != 13
						and global_dim != 17)
					{
						out = "La dimensione non e' supportata, riprova";
						continue;
					}

					// estrazione dell'esadecimale
					sep = codes.find('&');
					if (sep == string::npos) {
						out = "Il codice non contiene l'esadecimale, riprova";
						continue;
					}
					auto hexadec{ codes };
					hexadec.erase(sep);
					codes.erase(0, sep + 1);

					// controllo dell'esadecimale
					if (hexadec.substr(0, 4) != "hex=") {
						out = "L'esadec non ha il suo contrassegno, riprova";
						continue;
					}
					hexadec.erase(0, 4);
					for (const auto& ch : hexadec)
						if (!isdigit(ch) and (ch < 'a' or ch > 'f'))
						{
							out = "l'esadec non è valido, riprova";
							continue;
						}

					// estrazione delle scorciatoie

				}
				erase_command(end, end, 0);
				break;
			}

			// ricerca della scorciatoia
			erase_command(end, end, 0);
			ShortcutIndex = find_shortcut(command);
			if (ShortcutIndex == -1) {
				erase_command(end, CursorPosition, CurrentValue);
				break;
			}

			// scrittura
		write_shortcut:
			int Size = csbi.dwSize.X;
			int starting = grid.size() - Size;
			int ending = starting;
			grid.shorten(ResistShorting);
			bool withspace{ CommandArgs != "nospace" and grid.size() > 0 };
			if (withspace) {
				grid.resize(grid.size() + 1);
				CursorPosition.X++;
			}
			grid.attach(shortcuts[dim][ShortcutIndex]);

			// correzione coordinate
			starting += CursorPosition.X;
			CursorPosition.X += shortcuts[dim][ShortcutIndex].size();
			auto original{ CursorPosition.X };
			CursorPosition.X %= Size;
			ending += CursorPosition.X - 1;

			// disegno
			update_grid(grid, end, dim, CursorPosition.X != original);
			column = grid.size() - csbi.dwSize.X + CursorPosition.X;
			CursorPosition.Y = end.Y - dim - 1;
			draw_cursor(CursorPosition, grid.at(row, column));
			
			// aggiunta al vettore informazioni
			Data.push_back(
				ShortcutInfo(command, starting - withspace, ending, withspace)
			);
			ResistShorting = ending;
		}

		// ridisegno del cursore
		if (c == 'W' or c == 'S' or c == 'A' or c == 'D')
			draw_cursor(CursorPosition, grid.at(row, column));
	}

	grid.shorten(ResistShorting);
	return grid;
}

static instr decode_hex(string word, string& invsum, int dim = -1)
{
	// conversione in binario
	bool do_continue{ false };
	for (auto c : word) {

		// da carattere a numero
		int decimal;
		c = toupper(c);
		if (isdigit(c)) decimal = c - '0';
		else decimal = c - 'A' + 10;
		if (decimal > 15) {
			do_continue = true;
			break;
		}

		// in binario
		string bin(4, '0');
		for (int i = 0, binpow = 8; i < 4; ++i, binpow /= 2)
			if (decimal >= binpow)
			{
				decimal -= binpow;
				bin.at(i) = '1';
			}

		invsum += bin;
	}
	if (do_continue) return instr(0);

	// flip se necessario
	if (invsum.at(0) == '0') for (int i = 0; i < invsum.size(); ++i)
		invsum.at(i) = (invsum.at(i) == '0' ? '1' : '0');

	// compilazione della tabella
	instr binary;
	int rows = invsum.size() / dim;
	for (int i = 0; i < dim; ++i) for (int j = 0; j < rows; ++j)
		binary.push(i,
			invsum.at(i * rows + j) == '1'
		);

	return binary;
}

// conversione in esadecimale
static string hex(instr binary, string& sum)
{
	string hexa;
	sum = binary.sum();

	for (int i = sum.size() - 1; i >= 0; i -= 4) {
		auto temp{ sum };
		stringstream stream;

		if (i + 1 < temp.size()) temp.erase(i + 1);
		if (temp.size() > 4) temp.erase(0, i - 3);
		while (temp.size() < 4) temp = '0' + temp;

		int decimal{};
		for (int i = 0; i < 4; ++i)
			decimal += (temp.at(i) - '0') * pow(2, 3 - i);

		stream << hex << decimal;
		temp = stream.str();
		hexa = temp + hexa;
	}

	return hexa;
}

// lista delle scorciatoie con il loro esadecimale
static string view_shortcuts(int dim)
{
	size_t size{ shortcuts[dim].size() };
	string output, no_use;
	for (size_t i = 0; i < size; ++i)
		output +=
			'{' + ShortcutNames[i] + '/' + hex(shortcuts[dim][i], no_use) + '}';
	return output;
}

// lista dei posti in cui si trovano le scorciatoie
static string view_disposition()
{
	string output;
	for (const auto& sc : Data)
		output += "{" + sc.name + ", "
			+ to_string(sc.startx) + "/" + to_string(sc.endx) + "/"
			+ (sc.has_space ? "1" : "0") + "}";
	return output;
}

unordered_map<char, string> symbolToNameMap{
	{ '.' , "dot"                 },
	{ ',' , "comma"               },
	{ ';' , "semicolon"           }, 
	{ ':' , "colon"               },
	{ '-' , "dash"                },
	{ '+' , "plus"                },
	{ ' ' , "space"               },
	{ '<' , "left_angle_bracket"  },
	{ '=' , "equal"               },
	{ '>' , "right_angle_bracket" },
	{ '!' , "exclamation_mark"    },
	{ '?' , "question_mark"       },
	{ '&' , "ampersand"           },
	{ '#' , "hash"                },
	{ '%' , "percentage"          },
	{ '$' , "dollar"              },
	{ '£' , "pound"               },
	{ '^' , "caret"               },
	{ '_' , "underscore"          },
	{ '\\', "backslash"           },
	{ '/' , "forwardslash"        },
	{ '|' , "vertical_bar"        }
};
int main()
{
	// calcolo dei dati predefiniti, alias e scorciatoie
	for (int i = 0; i < 26; ++i) Aliases[i] = string(1, i + 'a');
	shortcuts.insert({ 5, {} });
	for (const auto& sq : charToPixelMap) {

		// scorciatoie
		shortcuts[5].push_back(convert_map_to_instr(sq.second));

		// nome corto
		auto ch{ sq.first };
		if (('0' <= ch and ch <= '9') or ('A' <= ch and ch <= 'Z')) {
			ShortcutNames.push_back(string(1, tolower(ch)));
			continue;
		}

		// nome esteso (simboli)
		ShortcutNames.push_back(symbolToNameMap[ch]);
	}

	while (true) 
	{
		// output di inizio programma
		string word;
		instr binaryWord;
		if (false) { ///
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Inserisci una stringa da codificare (/ = fine input)\n\n";
			SetConsoleTextAttribute(hConsole, 15);
			while (word.empty()) getline(cin, word);
			cout << '\n';
			if (word == "/") return 0;
		} ///

		// comandi
		if (true or (word.at(0) == '/' and word.at(word.size() - 1) != '/')) ///
		{
			if (word == "/write" or true) ///
			{
				string Input;
				int dim;
				bool ret, enable;
				do {
					cout << "Quale dimensione vuoi usare per la scrittura?\n";
					cin >> Input;
					cout << '\n';

					if (Input.size() <= 2)
						dim = is_integer(Input) ? stoi(Input) : 1;
					else dim = 1;

				} while (dim != 3 and dim != 5 and dim != 7
					and dim != 11 and dim != 13 and dim != 17);

				binaryWord = draw(dim, ret, enable);
				if (binaryWord.extent() == 0) {
					SetConsoleTextAttribute(hConsole, 64);
					cout << "La console e' troppo piccola, errore!\a";
					SetConsoleTextAttribute(hConsole, 15);
					cout << "\n\n";
					continue;
				}
			
				// liste
				if (enable) {
					SetConsoleTextAttribute(hConsole, 9);

					// lista dei comandi
					if (ret) {
						cout << "Elenco dei comandi: \n";
						cout << "/void: non fa niente\n";
						cout << "/list_shortcuts: elenca tutte le scorciatoie\n";
						cout << "/help: elenca tutti i comandi\n";
						cout << "/save: abilita il salvataggio di";
						cout << " una scorciatoia\n";
						cout << "/savemany: permette di salvare piu' scorciatoie";
						cout << " di fila senza dover usare /save tante volte\n";
						cout << "per fermare quest'operazione si usa /resume\n";
						cout << "/alias [shortcut] [key]: associa a una";
						cout << " scorciatoia un tasto alfanumerico\n";
						cout << "/rename [from] [to]: rinomina una scorciatoia\n";
						cout << "/edit [shortcut]: modifica una scorciatoia\n";
						cout << "/horizontal [amount]:";
						cout << " disegna una linea orizzontale\n";
						cout << "/rubber [amount]:";
						cout << " cancella una linea orizzontale\n";
						cout << "/erase_col: rimuove la colonna corrente\n";
						cout << "/export: trascrive la griglia";
						cout << " in un formato copiabile\n";
						cout << "/paste [code]: carica tutti i dati esportati\n";
						cout << "/[shortcut]: utilizza la scorciatoia\n";
						cout << "/[shortcut] nospace: utilizza la scorciatoia";
						cout << " ma senza lo spazio prima di essa\n\n";
						SetConsoleTextAttribute(hConsole, 15);
						continue;
					}

					// lista delle scorciatoie
					cout << "Elenco delle scorciatoie: \n";
					for (const auto& name : ShortcutNames) cout << name << ' ';
					cout << "\n\n";
					SetConsoleTextAttribute(hConsole, 15);
					continue;
				}

				// esportazione
				if (ret) {
					string _not;
					SetConsoleTextAttribute(hConsole, 10);
					cout << "Export:=\n";
					cout << "dim=" << dim;
					cout << "&hex=" << hex(binaryWord, _not);
					cout << "&shortcuts=" << view_shortcuts(dim);
					cout << "&disp=" << view_disposition();
					cout << "\n\n";
					SetConsoleTextAttribute(hConsole, 15);
					continue;
				}
			}

			if (binaryWord.empty()) continue;
			goto encode;
		}

		// decodifica dell'esadecimale
		if (word.at(0) == '/') {
			// calcoli
			word.pop_back();
			word.erase(0, 1);
			string invsum;
			auto binary{ decode_hex(word, invsum, 5) };

			// output codice binario
			SetConsoleTextAttribute(hConsole, 4);
			cout << "codifica in 0 e 1:\n\n";
			SetConsoleTextAttribute(hConsole, 15);
			cout << invsum << "\n\n";

			// visualizzazione finale grafica
			SetConsoleTextAttribute(hConsole, 4);
			cout << "messaggio:\n\n";
			SetConsoleTextAttribute(hConsole, 15);
			binary.AutoPrint();
			continue;
		}
		// codifica

		// trascrizione 0 e 1
		for (const auto& c : word) {
			vector<vector<bool>>binaryChar{};
			auto it = charToPixelMap.find(toupper(c));
			if (it != charToPixelMap.end()) binaryChar = it->second;

			for (int i = 0; i < 5; ++i) {
				for (bool X : binaryChar[i]) binaryWord.push(i, X);
				binaryWord.push(i, 0);
			}
		}
		binaryWord.invertf();

		// visualizzazione
		SetConsoleTextAttribute(hConsole, 4);
		cout << "codifica in 0 e 1 grafica:\n\n";
		SetConsoleTextAttribute(hConsole, 15);
		binaryWord.AutoPrint();
		
	encode:

		// output binario
		string sum;
		auto hexa{ hex(binaryWord, sum) };
		SetConsoleTextAttribute(hConsole, 4);
		cout << "codifica in 0 e 1:\n\n";
		SetConsoleTextAttribute(hConsole, 15);
		cout << sum << "\n\n";

		// output esadecimale
		SetConsoleTextAttribute(hConsole, 4);
		cout << "esadecimale:\n\n";
		SetConsoleTextAttribute(hConsole, 15);
		cout << '/' << hexa << "/\n\n";
	}
}
