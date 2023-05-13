#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using std::vector;
using std::cout;
using std::count;
using std::ifstream;
using std::string;
using std::istringstream;


enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};

string CellString(State cell) {
  switch (cell) {
    case State::kObstacle: return "⛰️ ";
    case State::kPath: return "🚗   ";
    case State::kStart: return "🚦   ";
    case State::kFinish: return "🏁   ";
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

int Heuristic(int x1, int y1, int x2, int y2) {
	return abs(x2-x1) + abs(y2-y1);
}

void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &path, vector<vector<State>> &grid) {
  vector<int> v {x, y, g, h};
  path.push_back(v);
  grid[x][y] = State::kClosed;
}

bool CheckValidCell(int x, int y, vector<vector<State>> grid) {
  bool on_grid_x = (x >= 0 && x < grid.size());
  bool on_grid_y = (y >= 0 && y < grid[0].size());
  if (on_grid_x && on_grid_y) {
    return grid[x][y] == State::kEmpty;
  }
  return false;
}


void ExpandNeighbors(vector<int> current, int* goal, vector<vector<int>> &open, vector<vector<State>> &grid) {
  int current_x = current[0];
  int current_y = current[1];
  int current_g = current[2];
  
  const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  for (int i = 0; i < 4; i++) {
    int possible_x = current_x + delta[i][0];
    int possible_y = current_y + delta[i][1];
    if (CheckValidCell(possible_x, possible_y, grid)) {
      int updated_g = current_g + 1;
      int h = Heuristic(possible_x, possible_y, goal[0],goal[1]);
      AddToOpen(possible_x, possible_y, updated_g, h, open, grid);
    }
  }
}

bool Compare(vector<int> v1, vector<int> v2) {
	int f1 = v1[2]+v1[3];
  int f2 = v2[2]+v2[3];
	return f1 > f2;
}

void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}

vector<vector<State>> search(vector<vector<State>> board, int start[2], int goal[2]) {
  vector<vector<int>> open;
  int x = start[0];
  int y = start[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0], goal[1]);
  AddToOpen(x, y, g, h, open, board);
  
  while (open.size() > 0) {
    CellSort(&open); 
    vector<int> current = open.back();
    int x = current[0];
    int y = current[1];

    board[x][y] = State::kPath;

    if (x == goal[0] && y == goal[1]) {
      board[start[0]][start[1]] = State::kStart;
      board[goal[0]][goal[1]] = State::kFinish;
      return board;
    }
  }

  return std::vector<vector<State>>{};
}

int main() {
  int start[2]{0, 0};
  int goal[2]{4, 5};
  vector<vector<State>> board = ReadBoardFile("1.board");
  auto solution = search(board, start, goal);
  PrintBoard(solution);
}