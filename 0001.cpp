// BACA PSEUDOCODE AKU SUSAH JELASINNYA
// I'LL HELP WHAT I CAN USING COMMENTS

#include "tui.hpp"
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

#define MAX_N 10

int mat[MAX_N][MAX_N];       // original grid
int current_determinant = 0; // global determinant

// blueprint for building the text to show on the screen
string getDisplayString(int n, int mat[MAX_N][MAX_N], int current_row,
                        int current_col, const string &current_input_str);

// blueprint for reacting to what the user types
void handleKeyPress(tui::Event event, bool &running, int &n,
                    int mat[MAX_N][MAX_N], int &current_row, int &current_col,
                    string &current_input_str);

// blueprint for cofactor (smaller grid)
void getCofactor(int mat[MAX_N][MAX_N], int temp[MAX_N][MAX_N], int p, int q,
                 int n) {
  int temp_i = 0;
  for (int i = 0; i < n; i++) { // if row is the skip row, skip
    if (i == p)
      continue;
    int temp_j = 0;
    for (int j = 0; j < n; j++) {
      if (j == q)
        continue;
      temp[temp_i][temp_j] = mat[i][j]; // copy value, then next
      temp_j++;
    }
    temp_i++;
  }
}

// blueprint for determinant
int determinantOfMatrix(int matrix[MAX_N][MAX_N], int n) {
  if (n == 1)
    return matrix[0][0]; // 1x1 matrix
  if (n == 2)
    return (matrix[0][0] * matrix[1][1]) -
           (matrix[0][1] * matrix[1][0]); // 2x2 matrix

  int D = 0;
  int temp[MAX_N][MAX_N];
  int sign = 1;

  for (int f = 0; f < n; f++) {
    memset( // integer needs memset for array calc otherwise it broke idk
        temp, 0,
        sizeof(temp));                  // clear cofactor with 0
    getCofactor(matrix, temp, 0, f, n); // use cofactor blueprint
    D += sign * matrix[0][f] *
         determinantOfMatrix(temp, n - 1); // rumus kofaktor
    sign = -sign;                          // after loop done, flip sign
  }

  return D;
}

int main() { // main interface default 3x3
  tui::Window window;
  int n = 3;
  memset(mat, 0, sizeof(mat));

  int current_row = 0;
  int current_col = 0;
  string current_input_str = "";
  bool running = true;

  while (running) {
    window.clear();

    string display_str =
        getDisplayString(n, mat, current_row, current_col, current_input_str);

    tui::Paragraph p; // use widget from hpp
    p.set_dimensions(0, 0, 60, 25);
    p.title = "Matrix Determinant Calculator";
    p.text = display_str;
    window.add(p);
    window.render();

    tui::Event event; // respond to user input from hpp
    if (window.poll_event(event)) {
      handleKeyPress(event, running, n, mat, current_row, current_col,
                     current_input_str);
    }
  }

  window.close();
  return 0;
}

// description
string getDisplayString(
    int n, int mat[MAX_N][MAX_N], int current_row, int current_col,
    const string &current_input_str) { // THIS IS A DUPLICATE, DO NOT DELETE
                                       // OTHERWISE IT BROKE
  string display_str =
      "Matrix (Size: " + to_string(n) + "x" + to_string(n) + ")\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      string value_to_display;
      if (i == current_row && j == current_col) {
        value_to_display = current_input_str.empty() ? to_string(mat[i][j])
                                                     : current_input_str;
        display_str += "[" + value_to_display + "] ";
      } else {
        value_to_display = to_string(mat[i][j]);
        display_str += value_to_display + " ";
      }
    }
    display_str += "\n";
  }

  display_str += "\nDeterminant: " + to_string(current_determinant);
  display_str += "\n\nUse arrow keys, hjkl, or wasd to navigate.";
  display_str += "\nUse Enter to confirm input.";
  display_str += "\nPress '.' to increase matrix size, ',' to decrease.";
  display_str += "\nPress 'q' to quit.";

  return display_str;
}

// keys
void handleKeyPress(tui::Event event, bool &running, int &n,
                    int mat[MAX_N][MAX_N], int &current_row, int &current_col,
                    string &current_input_str) { // THIS IS A DUPLICATE, DO NOT
                                                 // DELETE OTHERWISE IT BROKE
  if (event.type != tui::KEYDOWN)
    return;

  if (event.key == 'q') {
    running = false;
    return;
  }

  if (event.key == '.' || event.key == ',') { // increase matrix size
    if (event.key == '.')
      n = std::min(n + 1, MAX_N);
    if (event.key == ',')
      n = std::max(n - 1, 1);
    memset(mat, 0, MAX_N * MAX_N * sizeof(int));
    current_row = 0;
    current_col = 0;
    current_input_str = "";
    current_determinant = determinantOfMatrix(mat, n);
    return;
  }

  if (event.key == KEY_UP || event.key == 'k' || event.key == 'w') {
    current_row = max(0, current_row - 1);
  }
  if (event.key == KEY_DOWN || event.key == 'j' || event.key == 's') {
    current_row = min(n - 1, current_row + 1);
  }
  if (event.key == KEY_LEFT || event.key == 'h' || event.key == 'a') {
    current_col = max(0, current_col - 1);
  }
  if (event.key == KEY_RIGHT || event.key == 'l' || event.key == 'd') {
    current_col = min(n - 1, current_col + 1);
  }
  if (event.key == KEY_UP || event.key == KEY_DOWN || event.key == KEY_LEFT ||
      event.key == KEY_RIGHT || event.key == 'h' || event.key == 'j' ||
      event.key == 'k' || event.key == 'l' || event.key == 'w' ||
      event.key == 'a' || event.key == 's' || event.key == 'd') {
    current_input_str = "";
  }

  if ((event.key >= '0' && event.key <= '9') || event.key == '-') {
    current_input_str += (char)event.key;
  }

  if (event.key == KEY_BACKSPACE || event.key == 127) {
    if (!current_input_str.empty()) {
      current_input_str.pop_back();
    }
    return;
  }

  if (event.key == KEY_ENTER || event.key == '\n') {
    if (!current_input_str.empty()) {
      mat[current_row][current_col] = stoi(current_input_str);
      current_determinant = determinantOfMatrix(mat, n);
      current_input_str = "";
    }
    return;
  }
}
