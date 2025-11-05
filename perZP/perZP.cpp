#include <cctype>
#include <conio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <Windows.h>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

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

// classe che contiene le istruzioni di disegno
class instr
{
private:
	int dimension;
	vector<bool>* instructions;
public:
	instr(int dim) : dimension(dim)
	{
		instructions = new vector<bool>[dim];
	}
	instr() : dimension(5)
	{
		instructions = new vector<bool>[5];
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
		for (int i = 0; i < dimension; i++) instructions[i].resize(newsize, false);
	}
	auto at(int i, int j) const
	{
		return instructions[i][j];
	}
	auto at(int param) const
	{
		return instructions[param];
	}

	void shorten()
	{
		int MaxIndex{ -1 };
		for (int i = 0; i < dimension; ++i)
			for (size_t j = 0; j < this->size(); ++j)
				if (this->at(i, j)) MaxIndex = j;
		this->resize(MaxIndex + 1);
	}
	void attach(const instr& other)
	{
		for (int i = 0; i < dimension; i++) instructions[i].insert(
			instructions[i].end(),
			other.instructions[i].begin(),
			other.instructions[i].end()
		);
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
	void AutoPrint(const int& background = 170) const
	{
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		int sizemax = csbi.dwSize.X;
		int low{}, high;
		int size = this->size();
		while (true) {
			high = low + min(sizemax, size);

			for (int i = 0; i < this->dimension; i++) {
				for (int j = low; j < high; j++) {
					if (this->at(i, j)) {
						SetConsoleTextAttribute(hConsole, 119);
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
			if (size <= 0) break;
		}
	}

	string sum() const
	{
		string _sum;
		for (int i = 0; i < 5; i++) for (int j = 0; j < this->size(); j++) {
			if (this->at(i, j)) _sum += '1';
			else _sum += '0';
		}
		return _sum;
	}
};
vector<string> ShortcutNames;
unordered_map<int, vector<instr>> shortcuts;

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

// rimuove il cursore dalla griglia
static void erase_cursor(COORD CursorPos, bool Val)
{
	SetConsoleCursorPosition(hConsole, CursorPos);
	SetConsoleTextAttribute(hConsole, (Val ? 255 : 170));
	cout << (Val ? 'O' : '_');
}

// crea una nuova griglia vuota
static void new_grid(int dim, COORD& end, int gap = 1)
{
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

// richiede un comando all'utente
static string command_input(COORD line, string output)
{
	string input;
	SetConsoleCursorPosition(hConsole, line);
	SetConsoleTextAttribute(hConsole, 4);
	cout << output << ": ";
	SetConsoleTextAttribute(hConsole, 12);
	while (input.empty()) getline(cin, input);
	return input;
}

// adatta una scorciatoia ad una dimensione diversa
static instr adapte(instr shortcut, int NewDimension)
{
	// ...
}

// funzione di disegno
static instr draw(int dim, bool& ExitWith, bool saving = false)
{
	// ridimensionamento delle scorciatoie per la dimensione data
	if (!saving) {

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
	instr grid(dim);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	auto begin{ csbi.dwCursorPosition };
	if (csbi.dwSize.Y <= dim + 7) return instr(0);
	
	// creazione della griglia di disegno
	grid.resize(csbi.dwSize.X);
	begin.X = 0;
	begin.Y -= allocate_rows(dim + 3);
	auto end{ begin };
	end.Y += dim + 1;
	auto CursorPosition{ begin };
	new_grid(dim, begin);

	// loop dell'input
	int row{}, column{};
	bool CurrentValue{ false };
	while (true) if (_kbhit())
	{
		char c = tolower(_getch());
		CurrentValue = grid.at(row, column);

		// uscita
		if (c == '\r') {
			erase_cursor(CursorPosition, CurrentValue);
			SetConsoleTextAttribute(hConsole, 15);
			SetConsoleCursorPosition(hConsole, end);
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

			// inversione di un pixel
		case 'c': {
			grid.at(row, column) = !CurrentValue;
			SetConsoleTextAttribute(hConsole, (CurrentValue ? 68 : 204));
			cout << (CurrentValue ? '_' : 'O');
			SetConsoleCursorPosition(hConsole, CursorPosition);
			break;
		}

			// movimenti
		case 'w': {
			if (row == 0) break;
			row--;
			erase_cursor(CursorPosition, CurrentValue);
			CursorPosition.Y--;
			break;
		}
		case 's': {
			if (row == dim - 1) break;
			row++;
			erase_cursor(CursorPosition, CurrentValue);
			CursorPosition.Y++;
			break;
		}
		case 'a': {
			if (column == 0) break;
			column--;
			erase_cursor(CursorPosition, CurrentValue);
			CursorPosition.X--;
			break;
		}
		case 'd': {

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
			auto command{ command_input(end, "Inserisci comando") };

			// fine del salvataggio
			if (command == "resume" and saving) {
				ExitWith = true;
				erase_cursor(CursorPosition, CurrentValue);
				SetConsoleCursorPosition(hConsole, end);
				grid.shorten();
				return grid;
			}

			// undo messaggio comando o filtro comandi in modalità salvataggio
			if (command == "void" or saving) {

				// cancellazione del comando
				SetConsoleTextAttribute(hConsole, 15);
				SetConsoleCursorPosition(hConsole, end);
				cout << string(csbi.dwSize.X, L' ');

				// reset attributi
				SetConsoleTextAttribute(hConsole, (CurrentValue ? 255 : 170));
				SetConsoleCursorPosition(hConsole, CursorPosition);
				break;
			}

			// salvataggio di una scorciatoia
			if (command == "saveone" or command == "save")
			{
				// creazione di una griglia di disegno separata
				erase_cursor(CursorPosition, CurrentValue);
				SetConsoleCursorPosition(hConsole, end);
				SetConsoleTextAttribute(hConsole, 15);
				cout << "\n\n";
				bool ExitVal;

				// ciclo
				do {
					auto shortcut{ draw(dim, ExitVal, true) };
					end.Y += dim + 3;
					if (ExitVal) break;

					// input comando
					auto name{
						command_input(end, "Inserisci il nome della scorciatoia")
					};
					cout << '\n';

					// push
					shortcuts[dim].push_back(shortcut);
					ShortcutNames.push_back(name);
				} while (command == "save");
				// ridisegno

				if (command == "saveone") end.Y += 4;

				// reset dati
				SetConsoleTextAttribute(hConsole, 15);
				end.Y -= 2;
				SetConsoleCursorPosition(hConsole, end);

				// output titolo
				end.Y -= allocate_rows(dim + 7);
				cout << "\n\n";
				title_output(end, "Riprendi il disegno");
				cout << "\n\n";

				// ripresa della griglia di prima
				grid.AutoPrint();
				CursorPosition.Y = end.Y + 2;
				end.Y += dim + 3;
				SetConsoleCursorPosition(hConsole, CursorPosition);

				break;
			}

			// caricamento della scorciatoia
			cout << '\n';
			ptrdiff_t index{ -1 };
			for (size_t i = 0; i < ShortcutNames.size(); ++i)
				if (command == ShortcutNames[i])
					index = i;
			if (index == -1) {
				SetConsoleTextAttribute(hConsole, 15);
				SetConsoleCursorPosition(hConsole, end);
				cout << string(csbi.dwSize.X, L' ');

				SetConsoleTextAttribute(hConsole, (CurrentValue ? 255 : 170));
				SetConsoleCursorPosition(hConsole, CursorPosition);
				break;
			}
			grid.shorten();
			grid.attach(shortcuts[dim][index]);

			// ricaricamento della griglia
			int Size = csbi.dwSize.X;
			grid.resize((grid.size() / Size + 1) * Size);
			grid.AutoPrint();
			GetConsoleScreenBufferInfo(hConsole, &csbi);
			end.Y = csbi.dwCursorPosition.Y;
			CursorPosition.X += shortcuts[index].size();
			CursorPosition.Y = end.Y - dim;
		}

		// ridisegno del cursore
		if (c == 'w' or c == 's' or c == 'a' or c == 'd') {
			SetConsoleCursorPosition(hConsole, CursorPosition);
			SetConsoleTextAttribute(hConsole, (grid.at(row, column) ? 204 : 68));
			cout << (grid.at(row, column) ? 'O' : '_');
			SetConsoleCursorPosition(hConsole, CursorPosition);
		}
	}

	grid.shorten();
	return grid;
}

unordered_map<char, string> symbolToNameMap{
	{ '.' , "dot"                 },
	{ ',' , "comma"               },
	{ ';' , "semicolon"           }, 
	{ ':' , "colon"               },
	{ '-' , "dash"                },
	{ '+' , "plus"                },
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
	// calcolo preventivo di alcune scorciatoie di default
	shortcuts.insert({ 5, {} });
	for (const auto& sq : charToPixelMap) {
		shortcuts[5].push_back(convert_map_to_instr(sq.second));

		// nome corto
		auto ch{ sq.first };
		if (('0' <= ch and ch <= 9) or ('A' <= ch and ch <= 'Z')) {
			ShortcutNames.push_back(string(1, ch));
			continue;
		}

		// nome esteso (simboli)
		ShortcutNames.push_back(symbolToNameMap[ch]);
	}

	while (true) 
	{
		string word;
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
				bool no_use;
				int dim;
				do {
					cout << "Quale dimensione vuoi usare per la scrittura?\n";
					cin >> dim;
					cout << '\n';
				} while (dim != 3 and dim != 5 and dim != 7
					and dim != 11 and dim != 13 and dim != 17);

				auto extract{ draw(dim, no_use) };
				if (extract.extent() == 0) {
					SetConsoleTextAttribute(hConsole, 64);
					cout << "La console e' troppo piccola, errore!";
					SetConsoleTextAttribute(hConsole, 15);
					cout << "\n\n";
					continue;
				}
			}
			continue;
		}

		// decodifica
		else if (word.at(0) == '/') 
		{
			word.pop_back();
			word.erase(0, 1);

			string invsum;
			bool do_continue{ false };
			
			for (auto c : word) {
				int decimal;
				c = toupper(c);
				if (isdigit(c)) decimal = c - '0';
				else decimal = c - 'A' + 10;
				if (decimal > 15) {
					do_continue = 1;
					break;
				}

				string bin(4, '0');
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
		// codifica

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
			auto temp{ sum };
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
