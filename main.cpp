#include <iostream>
#include <vector>
using std::vector;
using std::cout;

void PrintBoard(vector<vector<int>> board) {
  for (vector<int> r: board) {
    for (int c: r) {
      cout << c;
    }
    cout << "\n";
  }
}

int main() {
  vector<vector<int>> board = {{0, 1, 0, 0, 0, 0},
                               {0, 1, 0, 0, 0, 0},
                               {0, 1, 0, 0, 0, 0},
                               {0, 1, 0, 0, 0, 0},
                               {0, 0, 0, 0, 1, 0}};
  PrintBoard(board);
}