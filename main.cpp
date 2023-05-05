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


enum class State {kEmpty, kObstacle};

string CellString(State cell) {
  switch (cell) {
    case State::kObstacle: return "⛰️ ";
    default: return "0 ";
  }
}

vector<State> ParseLine(string line) {
  vector<State> parsedLine = {};
  istringstream my_stream(line);

  char c;
  int n;

  while (my_stream >> n >> c) {
    if (n==1) {
      parsedLine.push_back(State::kObstacle);
    } else {
      parsedLine.push_back(State::kEmpty);
    }
  }
  return parsedLine;
}

vector<vector<State>> ReadBoardFile(string fileName) {
  ifstream inputFile;
  inputFile.open(fileName);
  vector<vector<State>> board = {};
  if (inputFile) {
    string line;
    while(getline(inputFile, line)){
      vector<State> pl = ParseLine(line);
      board.push_back(pl);
    }
  }
  return board;
}

void PrintBoard(vector<vector<State>> board) {
  for (vector<State> r: board) {
    for (State c: r) {
      cout << CellString(c);
    }
    cout << "\n";
  }
}

int main() {
   
  vector<vector<State>> board = ReadBoardFile("1.board");
  PrintBoard(board);
}