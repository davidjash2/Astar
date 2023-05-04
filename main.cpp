#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::cout;
using std::ifstream;
using std::string;

void ReadBoardFile(string fileName) {
  ifstream inputFile;
  inputFile.open(fileName);
  if (inputFile) {
    string line;
    while(getline(inputFile, line)){
      cout << line << "\n";
    }
  }
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
  ReadBoardFile("1.board");
  // vector<vector<int>> board = {{0, 1, 0, 0, 0, 0},
  //                              {0, 1, 0, 0, 0, 0},
  //                              {0, 1, 0, 0, 0, 0},
  //                              {0, 1, 0, 0, 0, 0},
  //                              {0, 0, 0, 0, 1, 0}};
  // PrintBoard(board);
}