#include "tui.hpp"
#include <algorithm> // For std::min and std::max
#include <cstring>   // For memset
#include <stdexcept> // For std::out_of_range
#include <string>

using namespace std;

// Define a constant for the maximum size of the matrix.
#define MAX_N 10

// Forward declarations for functions used in main loop
string getDisplayString(int n, int mat[MAX_N][MAX_N], int current_row,
                        int current_col, const string &current_input_str);
void handleKeyPress(tui::Event event, bool &running, int &n,
                    int mat[MAX_N][MAX_N], int &current_row, int &current_col,
                    string &current_input_str);

// This function calculates the submatrix (cofactor) needed for the determinant
// calculation.
void getCofactor(int mat[MAX_N][MAX_N], int temp[MAX_N][MAX_N], int p, int q,
                 int n) {
  int temp_i = 0;
  for (int i = 0; i < n; i++) {
    if (i == p)
      continue;
    int temp_j = 0;
    for (int j = 0; j < n; j++) {
      if (j == q)
        continue;
      temp[temp_i][temp_j] = mat[i][j];
      temp_j++;
    }
    temp_i++;
  }
}

// This function calculates the determinant of a square matrix using Laplace's
// expansion.
int determinantOfMatrix(int matrix[MAX_N][MAX_N], int n) {
  // Base case 1: If matrix is 1x1, determinant is the single element.
  if (n == 1)
    return matrix[0][0];
  // Base case 2: For a 2x2 matrix, the formula is simple and ends the
  // recursion.
  if (n == 2)
    return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);

  int D = 0;
  int temp[MAX_N][MAX_N];
  int sign = 1;

  for (int f = 0; f < n; f++) {
    memset(temp, 0, sizeof(temp));
    getCofactor(matrix, temp, 0, f, n);
    D += sign * matrix[0][f] * determinantOfMatrix(temp, n - 1);
    sign = -sign;
  }

  return D;
}

// The main function where the program starts.
int main() {
  tui::Window window;
  int n = 3;
  int mat[MAX_N][MAX_N];
  memset(mat, 0, sizeof(mat));

  int current_row = 0;
  int current_col = 0;
  string current_input_str = "";
  bool running = true;

  while (running) {
    window.clear();

    // 1. Build the display string
    string display_str =
        getDisplayString(n, mat, current_row, current_col, current_input_str);

    // 2. Setup and render the TUI widget
    tui::Paragraph p;
    p.set_dimensions(0, 0, 60, 25);
    p.title = "Matrix Determinant Calculator";
    p.text = display_str;
    window.add(p);
    window.render();

    // 3. Handle user input
    tui::Event event;
    if (window.poll_event(event)) {
      handleKeyPress(event, running, n, mat, current_row, current_col,
                     current_input_str);
    }
  }

  window.close();
  return 0;
}

// This function builds the string that gets displayed in the TUI.
// It's separated from the main loop to make the main loop easier to read.
string getDisplayString(int n, int mat[MAX_N][MAX_N], int current_row,
                        int current_col, const string &current_input_str) {
  string display_str =
      "Matrix (Size: " + to_string(n) + "x" + to_string(n) + ")\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == current_row && j == current_col) {
        display_str += "[" +
                       (current_input_str.empty() ? to_string(mat[i][j])
                                                  : current_input_str) +
                       "] ";
      } else {
        display_str += " " + to_string(mat[i][j]) + "  ";
      }
    }
    display_str += "\n";
  }

  int det = determinantOfMatrix(mat, n);
  display_str += "\nDeterminant: " + to_string(det);
  display_str += "\n\nUse arrow keys to navigate.";
  display_str += "\nPress '.' to increase matrix size, ',' to decrease.";
  display_str += "\nPress 'q' to quit.";

  return display_str;
}

// This function handles all the key presses from the user.
// It's separated from the main loop to make the main loop easier to read.
void handleKeyPress(tui::Event event, bool &running, int &n,
                    int mat[MAX_N][MAX_N], int &current_row, int &current_col,
                    string &current_input_str) {
  if (event.type != tui::KEYDOWN)
    return;

  // Handle quitting
  if (event.key == 'q') {
    running = false;
    return;
  }

  // Handle matrix resizing
  if (event.key == '.' || event.key == ',') {
    if (event.key == '.')
      n = std::min(n + 1, MAX_N);
    if (event.key == ',')
      n = std::max(n - 1, 1);
    // When passing a C-style array to a function, it decays to a pointer.
    // This means sizeof(mat) would give the size of a pointer, not the full
    // array. We must use the full, explicit size to clear the whole array.
    memset(mat, 0, MAX_N * MAX_N * sizeof(int));
    current_row = 0;
    current_col = 0;
    current_input_str = "";
    return;
  }

  // Handle navigation
  if (event.key == KEY_UP)
    current_row = std::max(0, current_row - 1);
  if (event.key == KEY_DOWN)
    current_row = std::min(n - 1, current_row + 1);
  if (event.key == KEY_LEFT)
    current_col = std::max(0, current_col - 1);
  if (event.key == KEY_RIGHT)
    current_col = std::min(n - 1, current_col + 1);
  // After any navigation, clear the input string
  if (event.key == KEY_UP || event.key == KEY_DOWN || event.key == KEY_LEFT ||
      event.key == KEY_RIGHT) {
    current_input_str = "";
    return;
  }

  // Handle number input
  if (event.key >= '0' && event.key <= '9') {
    current_input_str += (char)event.key;
    return;
  }

  // Handle backspace
  if (event.key == KEY_BACKSPACE || event.key == 127) {
    if (!current_input_str.empty()) {
      current_input_str.pop_back();
    }
    return;
  }

  // Handle enter
  if (event.key == KEY_ENTER || event.key == '\n') {
    if (!current_input_str.empty()) {
      try {
        mat[current_row][current_col] = stoi(current_input_str);
      } catch (const std::out_of_range &oor) {
        mat[current_row][current_col] = 0; // Default to 0 if input is too large
      }
      current_input_str = "";
    }
    return;
  }
}
