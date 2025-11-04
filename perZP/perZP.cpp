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
		int MaxIndex{};
		for (int i = 0; i < dimension; ++i)
			for (size_t j = 0; j < this->size(); ++j)
				if (this->at(i, j)) MaxIndex = j;
		this->resize(MaxIndex);
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

			for (int i = 0; i < 5; i++) {
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
vector<instr> shortcuts;
vector<string> ShortcutNames;

static instr draw(int dim, bool& ExitWith, bool blockCommands = false)
{
	ExitWith = false;
	instr grid(dim);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	if (csbi.dwSize.Y <= dim) return instr(0);
	grid.resize(csbi.dwSize.X);

	// aggiunta di spazio
	cout << string(dim + 1, '\n');
	auto begin{ csbi.dwCursorPosition };
	int shiftup{ dim - csbi.dwSize.Y + begin.Y + 2 };
	if (shiftup < 0) shiftup = 0;
	begin.X = 0;
	begin.Y -= shiftup;
	SetConsoleCursorPosition(hConsole, begin);

	// disegno preventivo
	SetConsoleTextAttribute(hConsole, 170);
	for (int i = 0; i < dim; ++i) {
		cout << string(csbi.dwSize.X, '_');
		if (i != dim - 1) cout << '\n';
	}
	SetConsoleCursorPosition(hConsole, begin);
	SetConsoleTextAttribute(hConsole, 68);
	wcout << L'_';
	SetConsoleCursorPosition(hConsole, begin);

	// loop dell'input
	int row{}, column{};
	bool CurrentValue{ false };
	COORD CursorPosition{ begin }, end{ begin };
	end.Y += dim + 1;
	while (true) if (_kbhit())
	{
		char c = _getch();
		c = tolower(c);
		CurrentValue = grid.at(row, column);

		// uscita
		if (c == '\r') {
			SetConsoleTextAttribute(hConsole, (CurrentValue ? 255 : 170));
			wcout << (CurrentValue ? L'O' : L'_');
			SetConsoleCursorPosition(hConsole, end);
			break;
		}

		// switch dell'input
		switch (c)
		{
			// inserimento di un pixel
		case ' ':
			grid.at(row, column) = true;
			SetConsoleTextAttribute(hConsole, 204);
			cout << 'O';
			SetConsoleCursorPosition(hConsole, CursorPosition);
			break;

			// cancellazione di un pixel
		case '\b':
			grid.at(row, column) = false;
			SetConsoleTextAttribute(hConsole, 68);
			cout << '_';
			SetConsoleCursorPosition(hConsole, CursorPosition);
			break;

			// inversione di un pixel
		case 'c':
			grid.at(row, column) = !CurrentValue;
			SetConsoleTextAttribute(hConsole, (CurrentValue ? 68 : 204));
			cout << (CurrentValue ? '_' : 'O');
			SetConsoleCursorPosition(hConsole, CursorPosition);
			break;

			// movimenti

		case 'w':
			if (row == 0) break;
			row--;
			SetConsoleTextAttribute(hConsole, (CurrentValue ? 255 : 170));
			cout << (CurrentValue ? 'O' : '_');
			CursorPosition.Y--;
			break;

		case 's':
			if (row == dim - 1) break;
			row++;
			SetConsoleTextAttribute(hConsole, (CurrentValue ? 255 : 170));
			cout << (CurrentValue ? 'O' : '_');
			CursorPosition.Y++;
			break;

		case 'a':
			if (column == 0) break;
			column--;
			SetConsoleTextAttribute(hConsole, (CurrentValue ? 255 : 170));
			cout << (CurrentValue ? 'O' : '_');
			CursorPosition.X--;
			break;

		case 'd': {

			// movimento
			column++;
			SetConsoleTextAttribute(hConsole, (CurrentValue ? 255 : 170));
			cout << (CurrentValue ? 'O' : '_');

			// aggiunta di una seconda fascia
			int shiftup{};
			if (column % csbi.dwSize.X == 0 and column > 0) {

				// aggiunta dello spazio necessario
				SetConsoleTextAttribute(hConsole, 15);
				SetConsoleCursorPosition(hConsole, end);
				cout << string(dim + 1, '\n');
				shiftup = dim - csbi.dwSize.Y + end.Y + 2;
				if (shiftup < 0) shiftup = 0;
				end.X = 0;
				end.Y -= shiftup;

				// preparazione del terreno
				SetConsoleCursorPosition(hConsole, end);
				SetConsoleTextAttribute(hConsole, 170);
				for (int i = 0; i < dim; ++i) {
					cout << string(csbi.dwSize.X, '_');
					if (i != dim - 1) cout << '\n';
				}
				SetConsoleCursorPosition(hConsole, end);

				// aggiornamenti
				end.Y += dim + 1;
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
			
			// input comando
			string command;
			SetConsoleCursorPosition(hConsole, end);
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Inserisci comando: ";
			SetConsoleTextAttribute(hConsole, 12);
			while (command.empty()) getline(cin, command);

			// undo messaggio comando
			if (command == "void") break;

			// salvataggio di una scorciatoia
			if (command == "save_once" or command == "save")
			{
				// creazione di una nuova griglia
				SetConsoleCursorPosition(hConsole, CursorPosition);
				SetConsoleTextAttribute(hConsole, (CurrentValue ? 255 : 170));
				wcout << (CurrentValue ? L'O' : L'_');
				SetConsoleCursorPosition(hConsole, end);
				SetConsoleTextAttribute(hConsole, 15);
				cout << "\n\n";
				bool ExitVal;

				// ciclo
				do {
					auto shortcut{ draw(dim, ExitVal, true) };
					end.Y += dim + 2;
					string name;

					SetConsoleCursorPosition(hConsole, end);
					SetConsoleTextAttribute(hConsole, 4);
					cout << "Inserisci nome della scorciatoia: ";
					SetConsoleTextAttribute(hConsole, 12);
					while (name.empty()) getline(cin, name);
					cout << '\n';

					shortcuts.push_back(shortcut);
					ShortcutNames.push_back(name);
				} while (!ExitVal and command == "save");

				break;
			}

			// caricamento della scorciatoia
			cout << "\n\n";
			ptrdiff_t index{ -1 };
			for (size_t i = 0; i < ShortcutNames.size(); ++i)
				if (command == ShortcutNames[i])
					index = i;
			if (index == -1) break;
			grid.shorten();
			grid.attach(shortcuts[index]);

			// ricaricamento della griglia
			int Size = csbi.dwSize.X;
			grid.resize((grid.size() / Size + 1) * Size);
			grid.AutoPrint();
			GetConsoleScreenBufferInfo(hConsole, &csbi);
			end.Y = csbi.dwCursorPosition.Y;
			CursorPosition.X += shortcuts[index].size();
			CursorPosition.Y = end.Y - dim;
		}

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

int main()
{
	while (true) 
	{
		string word;
		SetConsoleTextAttribute(hConsole, 4);
		cout << "Inserisci una stringa da codificare (/ = fine input)\n\n";
		SetConsoleTextAttribute(hConsole, 15);
		while (word.empty()) getline(cin, word);
		cout << '\n';
		if (word == "/") return 0;

		// comandi
		if (word.at(0) == '/' and word.at(word.size() - 1) != '/')
		{
			if (word == "/write")
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
