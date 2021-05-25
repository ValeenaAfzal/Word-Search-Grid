#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<fstream>
using namespace std;

class Grid
{
private:
	char** array;
	int rowsInFile;// rows/words in a file
	int UserWords;
	int UserCols;
	int UserRows;
public:
	Grid();
	Grid(ifstream&);
	~Grid();
	void Input(ifstream&);
	void Output();
	int Lines(ifstream&);// counts number of words in file
	void Place(ofstream&);
	void InputfromUser();// takes input from user
	int GetDimension()// getters
	{
		return rowsInFile;
	}
	int GetUserRows()
	{
		return UserRows;
	}

};

Grid::Grid()
{
	array = NULL;
	rowsInFile = 0;
	UserWords = 0;
	UserCols = 0;
	UserRows = 0;
}

Grid::Grid(ifstream& File)
{
	rowsInFile = Lines(File);
	array = new char* [rowsInFile];
	for (int i = 0; i < rowsInFile; i++)
		array[i] = new char[rowsInFile];

	for (int i = 0; i < rowsInFile; i++)// initialize to 0
		for (int j = 0; j < rowsInFile; j++)
			array[i][j] = 0;
}

Grid::~Grid()
{
	for (int i = 0; i < rowsInFile; i++)
		delete[] array[i];
	delete[] array;
	array = NULL;
}

void Grid::InputfromUser()
{
	cout << "Enter the Number of words in a File: ";
	cin >> UserWords;
	cout << "Enter The Number of Columns: ";
	cin >> UserCols;
	cout << "Enter The Number of Rows: ";
	cin >> UserRows;
}

void Grid::Input(ifstream& File)
{
	File.seekg(0, ios::beg);
	char chars[80];
	int j = rowsInFile - 1, k = 0, f = 0;

	while (!File.eof())
	{
		f = j;
		File.getline(chars, 80);
		int length = 0;
		int i = 0;
		while (chars[i] != '\0')// read one word and count length
		{
			length++;
			i++;
		}
		i = 0;

		while (i < length)
		{
			if (f > 0)
			{
				array[j][k] = chars[i];// place the word in GRID array
				i++; j--;
			}
			else
			{
				array[j][k] = chars[i];
				i++; j++;
			}

		}

		if (f == 0)// change value
			j = rowsInFile - 1;
		else
			j = 0;
		k++;
	}

	for (int i = 0; i < rowsInFile; i++)
	{
		for (int j = 0; j < rowsInFile; j++)
			if (array[i][j] == 0)
			{
				char a = rand() % 25 + 65; // place the random Letters in remaining spaces
				array[i][j] = a;
			}
	}
}

int Grid::Lines(ifstream& fin)
{
	fin.seekg(0, ios::beg);// moving to beginning to count number of lines
	int rows = 0;
	int large = 0;
	while (!fin.eof())
	{
		string line;
		getline(fin, line);
		if (line.length() > large)
			large = line.length();
		rows++;// counting no of words in file
	}
	if (large > rows)
		return large;
	else
		return rows;
}

void Grid::Output()// output grid
{
	cout << "GRID" << endl;
	cout << "_____________________________________" << endl << endl;
	for (int i = 0; i < rowsInFile; i++)
	{
		cout << "|   ";
		for (int j = 0; j < rowsInFile; j++)
		{
			cout << array[i][j] << "  ";
		}
		cout << "  |" << endl;
	}
	cout << "_____________________________________" << endl << endl;
}

void Grid::Place(ofstream& Out)// output grid
{
	for (int i = 0; i < rowsInFile; i++)
	{
		for (int j = 0; j < rowsInFile; j++)
			Out << array[i][j] << "  ";
		Out << endl;
	}
}

class WordPuzzle
{
private:
	char** Grid;
	int rows;// number of rows and cols in Grid
	int cols;
	int inputs;
	int endrow;// ending row and col
	int endcol;
	int count;// no of words to be found
public:
	WordPuzzle();
	WordPuzzle(ifstream&);
	~WordPuzzle();
	int GETINPUTS();// return total words to be found
	int GETCOUNT();
	void ReadFile(ifstream&);
	void Output(ofstream&, string);// output in file
	bool Find(int, int, string);// find word
};

WordPuzzle::WordPuzzle()
{
	Grid = NULL;
	rows = 0;// number of rows and cols in Grid
	cols = 0;
	inputs = 0;
	endrow = 0;// ending row and col
	endcol = 0;
	count = 0;
}

WordPuzzle::WordPuzzle(ifstream& File)
{
	File >> rows;
	File >> cols;
	File >> inputs;

	Grid = new char* [rows];
	for (int i = 0; i < rows; i++)
		Grid[i] = new char[cols];
}

WordPuzzle::~WordPuzzle()
{
	for (int i = 0; i < rows; i++)
		delete[] Grid[i];
	delete[] Grid;
	Grid = NULL;
}

void WordPuzzle::ReadFile(ifstream& file)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			char val;
			file >> val;
			Grid[i][j] = val;
			cout << val << "  ";
		}
		cout << endl;
	}
}

int WordPuzzle::GETINPUTS()
{
	return inputs;
}

int WordPuzzle::GETCOUNT()
{
	return count;
}

void WordPuzzle::Output(ofstream& file, string word)
{
	for (int row = 0; row < rows; row++)
		for (int col = 0; col < cols; col++)
			if (Find(row, col, word))
			{
				cout<< "{ " << (row + 1) << " , " << (col + 1) << " }" << "  " << "{ " << endrow << " , " << endcol << " }" << endl;
				file << "{ " << (row + 1) << " , " << (col + 1) << " }" << "  " << "{ " << endrow << " , " << endcol << " }" << endl;
				count++;
			}
}

bool::WordPuzzle::Find(int row, int col, string word)
{
	int x[] = { -1, -1, -1,  0, 0,  1, 1, 1 };
	int y[] = { -1,  0,  1, -1, 1, -1, 0, 1 };

	if (Grid[row][col] != word[0])
		return false;
	int len = word.length(); int temprow, tempcol;

	for (int dir = 0; dir < 8; dir++)
	{
		// Initialize starting point for current direction
		int count, rowdir = row + x[dir], coldir = col + y[dir];

		//remaining characters
		for (count = 1; count < len; count++)
		{
			if (rowdir >= rows || rowdir < 0 || coldir >= cols || coldir < 0)// if exceed rows and cols range
				break;

			if (Grid[rowdir][coldir] != word[count])// NOT matched
				break;

			rowdir += x[dir], coldir += y[dir];// moving in a direction
		}
		temprow = row; tempcol = col, endrow = rowdir; endcol = coldir;// storing strt and end positions

		if (count == len)// if count and len are eqaul word found
		{
			if (endrow == temprow)
				++endrow;
			if (endcol == tempcol)
				++endcol;
			if (endcol<tempcol && endrow>temprow)
				endcol += 2;
			if (endcol > tempcol && endrow < temprow)
				endrow += 2;
			if (endcol < tempcol && endrow < temprow)
			{
				endcol += 2;
				endrow += 2;
			}
			return true;
		}
	}
	return false;
}


int main()
{
	system("color 0D");
	char choice;

	do
	{
		cout << "Enter the function You want to perform: " << endl << "G for Grid" << endl << "S for search from Grid" << endl << "Q to Quit" << endl << endl;
		cin >> choice;

		if (choice == 'G')// creates objext of grid typ to form grid
		{
			string file;
			cout << "Enter The File Name: ";
			cin >> file;
			ifstream FILE(file);

			if (FILE)
			{

				Grid grid(FILE);
				cout << endl << "Opening File....." << endl << endl;

				grid.InputfromUser();

				if (grid.GetDimension() > grid.GetUserRows())
				{
					cout << "Grid Cannot be contructed....." << endl;
					return 0;
				}

				string File;
				cout << "Enter Output File Name: ";
				cin >> File;
				ofstream FILEO(File);// output file

				grid.Input(FILE);
				grid.Output();
				grid.Place(FILEO);
				cout << "Grid has been placed successfully....." << endl;
				FILEO.close();
			}
			else
				cout << endl << "Unable to Open File...." << endl << endl;
			FILE.close();
		}

		else if (choice == 'S')// creates object of word puzzle type to search words
		{
			string file;
			cout << "Enter Input File Name: ";
			cin >> file;

			string secFile;
			cout << "Enter Search File Name: ";
			cin >> secFile;
			ifstream search(secFile);

			ifstream File(file);
			if (File && search)
			{
				cout << "Opening File...." << endl << endl;
				WordPuzzle Game(File);
				Game.ReadFile(File);// reading grid
				int r = Game.GETINPUTS();// total inputs

				string File;
				cout << "Enter Output File Name: ";
				cin >> File;
				ofstream FILE(File);// output file
				FILE << r << endl;

				while (r > 0)// LOOP FOR INPUTS
				{
					string word;
					search >> word;
					cout << word << endl;

					Game.Output(FILE, word);
					r--;
				}
				if (Game.GETCOUNT() < Game.GETINPUTS())
					FILE << "One or More word Not found";
				FILE.close();
			}
			else
				cout << "Unable to Open File....." << endl << endl;
			File.close();
			search.close();
		}
		else if (choice == 'Q')// quits
		{
			exit;
			return 0;
		}
	} 
	while (1);

	return 0;
}