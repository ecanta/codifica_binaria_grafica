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

	// costruttori e distruttore
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
	instr(const instr& other) : dimension(other.dimension)
	{
		instructions = new vector<bool>[this->dimension];
		for (int i = 0; i < this->dimension; ++i)
			instructions[i] = other.instructions[i];
	}
	instr(instr&& other) noexcept
		: dimension(other.dimension), instructions(other.instructions)
	{
		other.dimension = 0;
		other.instructions = nullptr;
	}
	~instr()
	{
		delete[] instructions;
	}

	// assegnazione
	instr& operator=(const instr& other)
	{
		if (this != &other)
		{
			delete[] instructions;
			this->dimension = other.dimension;
			instructions = new vector<bool>[dimension];
			for (int i = 0; i < dimension; ++i)
				instructions[i] = other.instructions[i];
		}
		return *this;
	}
	instr& operator=(instr&& other) noexcept
	{
		if (this != &other)
		{
			delete[] instructions;
			dimension = other.dimension;
			instructions = other.instructions;

			other.dimension = 0;
			other.instructions = nullptr;
		}
		return *this;
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
	void invertf()
	{
		if (!this->at(0, 0)) for (int i = 0; i < this->dimension; ++i)
			for (int j = 0; j < this->size(); ++j)
				this->at(i, j) = !this->at(i, j);
	}
	
	// visualizzazione grafica
	void AutoPrint(int low = 0, const int& background = 170) const
	{
		// inizio
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		int sizemax = csbi.dwSize.X, high, size = this->size();
		SetConsoleTextAttribute(hConsole, 255);

		bool on{ true };
		while (true) {
			high = low + min(sizemax, size);

			for (int i = 0; i < this->dimension; ++i) {
				for (int j = low; j < high; ++j) {
					if (this->at(i, j)) {
						if (!on) SetConsoleTextAttribute(hConsole, 255);
						cout << 'O';
					}
					else {
						if (on) SetConsoleTextAttribute(hConsole, background);
						cout << '_';
					}
					on = this->at(i, j);
				}

				// a capo
				SetConsoleTextAttribute(hConsole, 15);
				cout << '\n';
				SetConsoleTextAttribute(hConsole, 255);
				on = true;
			}
			SetConsoleTextAttribute(hConsole, 15);
			cout << '\n';
			SetConsoleTextAttribute(hConsole, 255);
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
static ptrdiff_t find_shortcut(string name, vector<string>& vect = ShortcutNames)
{
	ptrdiff_t index{ -1 };
	for (ptrdiff_t i = 0; i < vect.size(); ++i) if (name == vect[i]) {
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
	SetConsoleTextAttribute(hConsole, 15);
	auto begin{ csbi.dwCursorPosition };
	cout << string(rows, '\n');
	
	int shiftup{ rows - csbi.dwSize.Y + begin.Y + 1 };
	if (shiftup < 0) shiftup = 0;
	begin.X = 0;
	begin.Y -= shiftup;
	SetConsoleCursorPosition(hConsole, begin);

	SetConsoleTextAttribute(hConsole, csbi.wAttributes);
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
static void new_grid(int dim, int col, COORD& end, int gap = 1)
{
	SetConsoleCursorPosition(hConsole, end);
	SetConsoleTextAttribute(hConsole, 170);
	for (int i = 0; i < dim; ++i) {
		cout << string(csbi.dwSize.X, '_');
		if (i != dim - 1) cout << '\n';
	}

	auto pos{ end };
	pos.Y += col;
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, 68);
	cout << '_';
	SetConsoleCursorPosition(hConsole, pos);
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
	SetConsoleCursorPosition(hConsole, end);
	if (linechange) {
		end.Y -= allocate_rows(dim + 3);
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
static void back_to_original_grid(
	instr grid,
	COORD& CursorPosition,
	COORD& line,
	int dim,
	bool suppress = false
)
{
	// reset dati
	SetConsoleTextAttribute(hConsole, 15);
	if (!suppress) line.Y -= 2;
	SetConsoleCursorPosition(hConsole, line);

	// output titolo
	line.Y -= allocate_rows(dim + 7);
	if (!suppress) {
		cout << "\n\n";
		title_output(line, "Riprendi il disegno");
	}
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

// separa gli elenchi formati da parentesi graffe
static bool extract_parameters(string str, vector<string>& list)
{
	int balance{};
	size_t startIndex;
	list.clear();
	for (size_t i = 0; i < str.size(); ++i)
	{
		switch (str.at(i))
		{
		case '{':
			startIndex = i;
			balance++;
			break;
		case '}':
			list.push_back(
				str.substr(startIndex + 1, i - startIndex - 1)
			);
			balance--;
			break;
		}
		if (balance != 0 and balance != 1) return false;
	}
	return true;
}

// calcola i numeri primi
vector<bool> is_prime;
vector<int> primes;
static void calculate_prime_numbers(int max)
{
	// inizio
	is_prime.resize(max + 1, true);
	const int SQUARE{ (int)sqrt(max) + 2 };

	// impostazione tabella
	for (int p = 2; p < SQUARE; ++p) {
		if (!is_prime[p]) continue;
		for (int i = p * p; i <= max; i += p) is_prime[i] = false;
	}

	// estrazione numeri primi
	for (int p = 2; p < max + 1; ++p)
		if (is_prime[p]) primes.push_back(p);
}

// approssima un numero per eccesso ad un valore primo
static int prime_approx(int val)
{
	int approx;
	size_t guess{};
	for (size_t i = 0; i < primes.size(); i += 15) if (primes[i] >= val)
	{
		guess = i > 15 ? i - 15 : 0;
		break;
	}
	for (size_t i = guess; i < primes.size(); ++i) if (primes[i] >= val)
	{
		approx = primes[i];
		break;
	}
	return approx;
}

// decodifica un esadecimale
static vector<instr> decode_hex(string word, string& invsum, int dim = -1)
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
	if (do_continue) return {};

	vector<int> likely;
	if (dim == -1)
	{
		// calcolo della prima cifra significativa
		int maxrest{ 4 };
		for (int i = 1; i <= 4; ++i) if (invsum.at(i - 1) == '1') {
			maxrest = i;
			break;
		}

		// ricerca della dimensione giusta
		const vector<int> valid_dims{ 3, 5, 7, 11, 13, 17 };
		for (const auto& attempt : valid_dims) {
			int mod = invsum.size() % attempt;
			if (mod > maxrest) continue;

			// esclusioni
			int lenght = invsum.size() / attempt;
			if (prime_approx(lenght) != lenght or lenght <= 2) continue;
			if (lenght < attempt) continue;

			likely.push_back(attempt);
		}
	}
	else likely = { dim };

	// calcolo di ogni possibile decodifica
	vector<instr> bruteforced;
	for (const auto& _dim : likely) {

		// accorciamento
		int fix = invsum.size() % _dim;
		invsum.erase(invsum.begin(), invsum.begin() + fix);

		// compilazione della tabella
		instr binary(_dim);
		int cols = invsum.size() / _dim;
		for (int i = 0; i < _dim; ++i) for (int j = 0; j < cols; ++j) binary.push(
			i, invsum.at(i * cols + j) == '1'
		);

		bruteforced.push_back(binary);
	}

	return bruteforced;
}

// funzione di disegno
static instr draw(
	int dim,
	int& global_dim,
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
	ReturnedValue = ExitWith = false;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto begin{ csbi.dwCursorPosition };
	if (csbi.dwSize.Y <= 2 * dim + 4) return instr(0);
	
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
	else new_grid(dim, 0, begin);

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
			if (max((int)ResistShorting - 1, grid.truelen()) != sc.endx) break;
			if (grid.size() - sc.startx > csbi.dwSize.X) break;

			// rimozione
			Data.pop_back();
			for (int i = 0; i < dim; ++i) for (int j = sc.startx; j <= sc.endx; ++j)
				grid.at(i, j) = false;
			if (!Data.empty()) ResistShorting = Data.at(Data.size() - 1).endx + 1;
			else ResistShorting = 0;

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
				shiftup = allocate_rows(2 * dim + 3);

				// aggiornamento posizione
				end.Y -= shiftup;
				CursorPosition.X = 0;
				CursorPosition.Y -= shiftup;
				CursorPosition.Y += dim + 1;

				// creazione griglia
				new_grid(dim, row, end);
				grid.resize(grid.size() + csbi.dwSize.X);
				SetConsoleCursorPosition(hConsole, CursorPosition);
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
			if (command == "resume" and base.extent() == 0
				and !grid.empty() and saving)
			{
				ExitWith = true;
				erase_cursor(CursorPosition, CurrentValue);
				SetConsoleCursorPosition(hConsole, end);
				grid.shorten();
				return grid;
			}

			// cancellazione griglia
			if (command == "clear")
			{
				grid.resize(csbi.dwSize.X);
				for (int i = 0; i < dim; ++i)
					for (size_t j = 0; j < grid.size(); ++j)
						grid.at(i, j) = false;
				back_to_original_grid(grid, CursorPosition, end, dim, true);
				column = row = 0;
				erase_command(end, CursorPosition, CurrentValue);
				break;
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
				int no_use0;
				bool no_use1, no_use2;
				auto NewValue{
					draw(
						dim,
						no_use0,
						no_use1,
						no_use2,
						true,
						shortcuts[dim][scIndex]
					)
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
					int zero_use;
					auto shortcut{ draw(dim, zero_use, No_use, ExitVal, true) };
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
					if (shortcut.size() < csbi.dwSize.X) {
						shortcuts[dim].push_back(shortcut);
						ShortcutNames.push_back(name);
					}
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
				// dati che devono essere estratti
				instr newbase;
				vector<instr> list;
				vector<string> scNames;
				vector<ShortcutInfo> infos;

				// input del codice
				bool start{ true };
				string codes{ CommandArgs }, out{ "Inserisci i dati esportati" };
				while (true)
				{
				redo:
					// primo input
					if (!start) {
						GetConsoleScreenBufferInfo(hConsole, &csbi);
						codes = command_input(csbi.dwCursorPosition, out);
						if (out != "Inserisci i dati esportati") cout << '\a';
						cout << '\n';
					}
					start = false;
					if (codes.empty()) goto redo;

					// estrazione della dimensione
					auto sep{ codes.find('&') };
					if (sep == string::npos) {
						out = "Il codice non contiene la dimensione, riprova";
						goto redo;
					}
					auto Dim{ codes };
					Dim.erase(sep);
					codes.erase(0, sep + 1);

					// controllo della dimensione
					if (Dim.substr(0, 4) != "dim=") {
						out = "La dimensione non ha il suo contrassegno, riprova";
						goto redo;
					}
					Dim.erase(0, 4);
					if (!is_integer(Dim) or Dim.size() > 2) {
						out = "La dimensione non e' valida, riprova";
						goto redo;
					}
					global_dim = stoi(Dim);
					if (global_dim != 3 and global_dim != 5 and global_dim != 7
						and global_dim != 11 and global_dim != 13
						and global_dim != 17)
					{
						out = "La dimensione non e' supportata, riprova";
						goto redo;
					}

					// estrazione dell'esadecimale
					sep = codes.find('&');
					if (sep == string::npos) {
						out = "Il codice non contiene l'esadecimale, riprova";
						goto redo;
					}
					auto hexadec{ codes };
					hexadec.erase(sep);
					codes.erase(0, sep + 1);

					// controllo contrassegno
					string __not;
					if (hexadec.substr(0, 4) != "hex=") {
						out = "L'esadec non ha il suo contrassegno, riprova";
						goto redo;
					}

					hexadec.erase(0, 4);
					if (hexadec != "{}") {
					
						// controllo dell'esadecimale
						for (const auto& ch : hexadec)
							if (!isdigit(ch) and (ch < 'a' or ch > 'f'))
							{
								out = "l'esadec non è valido, riprova";
								goto redo;
							}
						newbase = decode_hex(hexadec, __not, global_dim)[0];

						// griglia vuota ma sbagliata
						if (newbase.empty()) {
							out = "La griglia e' vuota, riprova";
							goto redo;
						}
					}

					// griglia vuota e giusta
					else newbase = instr(global_dim);

					// estrazione delle scorciatoie
					sep = codes.find('&');
					if (sep == string::npos) {
						out = "Il codice non contiene le scorciatoie, riprova";
						goto redo;
					}
					auto sclist{ codes };
					sclist.erase(sep);
					codes.erase(0, sep + 1);

					// controllo delle scorciatoie
					if (sclist.substr(0, 10) != "shortcuts=") {
						out = "Le scorciatoie non hanno il contrassegno, riprova";
						goto redo;
					}
					sclist.erase(0, 10);

					// ottenimento scorciatoie
					scNames.clear();
					vector<string> names;
					extract_parameters(sclist, names);
					for (const auto& sc : names)
					{
						// separazione di nome e contenuto
						size_t half{ sc.find('/') };
						if (half == string::npos) {
							out = "Una scorciatoia non e' valida, riprova";
							goto redo;
						}
						auto id{ sc };
						auto Hex{ sc };
						id.erase(half);
						Hex.erase(0, half + 1);

						// controllo nome
						for (const auto& ch : id) if (!isalnum(ch) and ch != '_') {
							out =
								"Il nome di una scorciatoia non e' valido, riprova";
							goto redo;
						}
						
						// controllo unicità
						if (find_shortcut(id, scNames) != -1) {
							out = "Una scorciatoia ha nome doppio, riprova";
							goto redo;
						}
						scNames.push_back(id);

						// controllo contenuto
						string _not;
						for (const auto& ch : Hex)
							if (!isdigit(ch) and (ch < 'a' or ch > 'f'))
							{
								out = "Il contenuto di una scorciatoia non e' ";
								out += "valido, riprova";
								goto redo;
							}
						auto last{ decode_hex(Hex, _not, global_dim)[0] };
						list.push_back(last);
					}
					
					// controllo delle posizioni delle scorciatoie
					if (codes.find('&') != string::npos) {
						out = "Il codice contiene troppe informazioni, riprova";
						goto redo;
					}
					if (codes.substr(0, 5) != "disp=") {
						out = "Le posizioni non hanno il contrassegno, riprova";
						goto redo;
					}
					codes.erase(0, 5);
					
					// ottenimento posizioni
					infos.clear();
					vector<string> positions;
					bool empty{ codes == "{}" };
					if (!empty) extract_parameters(codes, positions);
					if (!empty) for (const auto& pos : positions)
					{
						// separazione di nome e dati
						size_t half{ pos.find(',') };
						if (half == string::npos) {
							out = "Una posizione non e' valida, riprova";
							goto redo;
						}
						auto id{ pos };
						auto data_{ pos };
						id.erase(half);
						data_.erase(0, half + 1);

						// controllo esistenza
						for (const auto& ch : id)
							if (find_shortcut(id, scNames) == -1)
							{
								out = "Una posizione e' ";
								out += "di una scorciatoia sconosciuta, riprova";
								goto redo;
							}

						// splicing
						if (data_.size() < 5) {
							out = "Una posizione è incorretta, riprova";
							goto redo;
						}
						vector<string> parts;
						for (ptrdiff_t i = data_.size() - 2; i >= 0; --i)
							if (data_.at(i) == L'/')
							{
								parts.push_back(
									data_.substr(i + 1, data_.size() - i)
								);
								data_.erase(i);
							}
						parts.push_back(data_);
						if (parts.size() != 3) {
							out = "Una posizione ha troppi dati, riprova";
							goto redo;
						}

						// controllo numericità
						for (const auto& part : parts)
							if (part.size() > 4 or !is_integer(part)) {
								out = "I dati di una posizione sono incorretti";
								out += ", riprova";
								goto redo;
							}

						// push
						ShortcutInfo info(
							id, 
							stoi(parts[2]), stoi(parts[1]), stoi(parts[0])
						);
						infos.push_back(info);

						// controllo ordine
						if (info.endx <= info.startx + info.has_space) {
							out = "Una posizione e' intrecciata, riprova";
							goto redo;
						}
					}

					// controllo ordine crescente tra varie posizioni
					for (size_t i = 1; i < infos.size(); ++i)
						if (infos[i - 1].endx >= infos[i].startx)
						{
							out = "Ci sono due posizioni sovrapposte, riprova";
							goto redo;
						}

					// controllo sufficienza spazio
					if (!infos.empty())
						if (infos.at(infos.size() - 1).endx >= newbase.size())
						{
							out = "La griglia e' troppo corta, riprova";
							goto redo;
						}
					break;
				}

				// impostazione
				ShortcutNames = scNames;
				shortcuts.clear();
				shortcuts[global_dim] = list;
				Data = infos;
				cout << '\n';
				allocate_rows(global_dim + 7);
				return newbase;
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
			auto portions{ grid.size() / Size };
			int starting = grid.size() - Size;
			int ending = starting;
			
			// calcolo nuova griglia
			grid.shorten(max((short)ResistShorting, CursorPosition.X));
			CursorPosition.X = grid.size() % Size;
			if (CursorPosition.X == 0 and portions > 1)
				CursorPosition.X = Size;
			bool withspace{ CommandArgs != "nospace" and grid.size() > 0 };
			if (withspace) {
				grid.resize(grid.size() + 1);
				CursorPosition.X++;
			}
			grid.attach(shortcuts[dim][ShortcutIndex]);

			// correzione coordinate
			starting += CursorPosition.X;
			CursorPosition.X += shortcuts[dim][ShortcutIndex].size();
			ending += CursorPosition.X - 1;
			CursorPosition.X %= Size;

			// disegno
			update_grid(grid, end, dim, ceil(double(ending + 1) / Size) > portions);
			column = grid.size() - csbi.dwSize.X + CursorPosition.X;
			CursorPosition.Y = end.Y - dim - 1;
			row = 0;
			draw_cursor(CursorPosition, grid.at(row, column));
			
			// aggiunta al vettore informazioni
			Data.push_back(
				ShortcutInfo(command, starting - withspace, ending, withspace)
			);
			ResistShorting = ending + 1;
		}

		// ridisegno del cursore
		if (c == 'W' or c == 'S' or c == 'A' or c == 'D')
			draw_cursor(CursorPosition, grid.at(row, column));
	}

	grid.shorten(ResistShorting);
	return grid;
}

// conversione in esadecimale
static string hex(instr binary, string& sum, bool truthy)
{
	// calcolo lunghezza prima
	int oldsize = binary.size(), newsize{ oldsize };
	if (!truthy) newsize = prime_approx(oldsize);

	// allungamento della matrice
	binary.resize(newsize);
	oldsize += 2;
	if (newsize > oldsize) {

		// riempimento con un pattern a diagonali
		for (int i = 0; i < binary.extent(); ++i)
			for (size_t j = oldsize; j < newsize; ++j)
				if ((i + j - oldsize) % 4 == 0)
					binary.at(i, j) = true;
	}

	// conversione
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
		output += '{' + ShortcutNames[i] + '/'
			+ hex(shortcuts[dim][i], no_use, true) + '}';
	return output;
}

// lista dei posti in cui si trovano le scorciatoie
static string view_disposition()
{
	string output;
	for (const auto& sc : Data)
		output += "{" + sc.name + ","
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
	{ ' ' , "sp"                  },
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
	// calcolo dei numeri primi
	calculate_prime_numbers(500'000);

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

	// output di inizio programma
	SetConsoleTextAttribute(hConsole, 3);
	cout << "CODIFICA BINARIA GRAFICA\n";
	cout << "Questo programma permette di codificare e decodificare messaggi\n";
	cout << "inserendoli in una griglia e poi calcolando l'esadecimale dei\n";
	cout << "pixel messi di fila\n\n";
	SetConsoleTextAttribute(hConsole, 6);
	cout << "Per codificare un messaggio di testo lo si scriva\n";
	cout << "Per decodificare un esadecimale lo si inserisca tra due caratteri /\n";
	cout << "Per accedere all'interfaccia di disegno prima della codifica\n";
	cout << "si scriva l'altezza della griglia (numero primo <= 17)";
	cout << " preceduto da /\n";
	cout << "Per elencare i comandi dell'interfaccia digitare /help li'\n\n";

	while (true) 
	{
		string word;
		instr binaryWord;

		// output inizale
		SetConsoleTextAttribute(hConsole, 4);
		cout << "Inserisci una stringa da codificare (\\ = fine input)\n\n";
		SetConsoleTextAttribute(hConsole, 15);
		while (word.empty()) getline(cin, word);
		cout << '\n';
		if (word == "\\") return 0;

		// comandi
		if (word.at(0) == '/' and word.at(word.size() - 1) != '/')
		{
			// chiarimento
			if (word == "/help") {
				SetConsoleTextAttribute(hConsole, 9);
				cout << "Il comando help deve essere digitato dall'interfaccia";
				cout << " di disegno\n\n";
				SetConsoleTextAttribute(hConsole, 15);
				continue;
			}

			// variabili iniziali
			string Input{ word };
			Input.erase(0, 1);
			int dim, new_dim = -1;
			bool ret, enable, pasting{ false };

			// controllo dimensione inserita
			if (Input.empty()) dim = 1;
			else if (Input.size() <= 2)
				dim = is_integer(Input) ? stoi(Input) : 1;
			else dim = 1;

			// caso di errore
			if (dim != 3 and dim != 5 and dim != 7
				and dim != 11 and dim != 13 and dim != 17)
			{
				SetConsoleTextAttribute(hConsole, 64);
				cout << "La dimensione inserita e' sbagliata\a";
				SetConsoleTextAttribute(hConsole, 15);
				cout << "\n\n";
				continue;
			}
			
			// notifica di input corretto
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Dimensione valida, accesso all'interfaccia di disegno...\n\n";
			SetConsoleTextAttribute(hConsole, 15);

			// inizio del disegno
		retry:
			binaryWord = pasting ?
				draw(dim, new_dim, ret, enable, false, binaryWord)
				: draw(dim, new_dim, ret, enable);
			if (binaryWord.extent() == 0) {
				SetConsoleTextAttribute(hConsole, 64);
				cout << "La console e' troppo piccola, errore!\a";
				SetConsoleTextAttribute(hConsole, 15);
				cout << "\n\n";
				continue;
			}
				
			// è stato incollato qualcosa
			if (new_dim != -1) {
				dim = new_dim;
				new_dim = -1;
				pasting = true;
				goto retry;
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
				cout << "&hex=";

				auto hexa{ hex(binaryWord, _not, true) };
				cout << (hexa.empty() ? "{}" : hexa);
				cout << "&shortcuts=" << view_shortcuts(dim);
				cout << "&disp=";

				auto disp{ view_disposition() };
				cout << (disp.empty() ? "{}" : disp);
				cout << "\n\n";

				SetConsoleTextAttribute(hConsole, 15);
				continue;
			}

			if (binaryWord.empty()) continue;
			goto encode;
		}

		// decodifica dell'esadecimale
		if (word.at(0) == '/' and word.at(word.size() - 1) == '/')
		{
			// calcoli
			string invsum;
			word.pop_back();
			word.erase(0, 1);
			auto binary{ decode_hex(word, invsum) };

			// errore
			if (binary.empty()) {
				SetConsoleTextAttribute(hConsole, 64);
				cout << "NON CORRETTO!!\a";
				SetConsoleTextAttribute(hConsole, 64);
				cout << "\n\n";
				continue;
			}

			// output codice binario
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Codifica in 0 e 1:\n\n";
			SetConsoleTextAttribute(hConsole, 15);
			cout << invsum << "\n\n";

			// visualizzazione finale grafica
			SetConsoleTextAttribute(hConsole, 4);
			if (binary.size() == 1) cout << "Messaggio:\n\n";
			for (size_t i = 0; i < binary.size(); ++i) {

				SetConsoleTextAttribute(hConsole, 12);
				if (binary.size() != 1) cout << "Possibilita' " << i + 1 << ":\n\n";
				SetConsoleTextAttribute(hConsole, 15);

				binary[i].AutoPrint();
			}
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
		cout << "Codifica in 0 e 1 grafica:\n\n";
		SetConsoleTextAttribute(hConsole, 15);
		binaryWord.AutoPrint();
		
	encode:

		// output binario
		string sum;
		auto hexa{ hex(binaryWord, sum, false) };
		SetConsoleTextAttribute(hConsole, 4);
		cout << "Codifica in 0 e 1:\n\n";
		SetConsoleTextAttribute(hConsole, 15);
		cout << sum << "\n\n";

		// output esadecimale
		SetConsoleTextAttribute(hConsole, 4);
		cout << "Esadecimale:\n\n";
		SetConsoleTextAttribute(hConsole, 15);
		cout << '/' << hexa << "/\n\n";
	}
}
