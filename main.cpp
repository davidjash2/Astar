#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using std::vector;
using std::cout;
using std::ifstream;
using std::string;
using std::istringstream;

vector<int> ParseLine(string line) {
  vector<int> parsedLine = {};
  istringstream my_stream(line);

  char c;
  int n;

  while (my_stream >> n >> c) {
    parsedLine.push_back(n);
  }
  return parsedLine;
}

vector<vector<int>> ReadBoardFile(string fileName) {
  ifstream inputFile;
  inputFile.open(fileName);
  vector<vector<int>> board = {};
  if (inputFile) {
    string line;
    while(getline(inputFile, line)){
      vector<int> pl = ParseLine(line);
      board.push_back(pl);
    }
  }
  return board;
}

void PrintBoard(vector<vector<int>> board) {
  for (vector<int> r: board) {
    for (int c: r) {
      cout << c;
    }
    cout << "\n";
  }
}

int main() {
   
  vector<vector<int>> board = ReadBoardFile("1.board");
  PrintBoard(board);
}