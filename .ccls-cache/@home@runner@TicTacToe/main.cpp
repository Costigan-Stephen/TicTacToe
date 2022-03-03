/***********************************************************************
 * Program:
 *    Lesson 08, Tic-Tac-Toe
 * Summary:
 *    This program reads, displays, and writes a Tic-Tac-Toe board
 ************************************************************************/

#include <cassert>
#include <fstream>
#include <iostream>
using namespace std;

// Defined variables
#define PLYR1 'X'
#define PLYR2 'O'
#define BLANK '.'
#define BSIZE 3

bool read(char board[BSIZE][BSIZE][BSIZE], const char *fileName);
bool write(const char board[BSIZE][BSIZE][BSIZE], const char *fileName);
void display(const char board[BSIZE][BSIZE][BSIZE]);
bool didWin(const char board[BSIZE][BSIZE][BSIZE], char turn);

/**********************************************************************
 * Keeps the data and calles the read/display/write functions
 ***********************************************************************/

int main() {
  // read the board
  char board[BSIZE][BSIZE][BSIZE];
  char fileName[256];
  cout << "Enter source filename: ";
  cin >> fileName;

  if (!read(board, fileName)) {
    cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
    return 1;
  }

  // display the board
  display(board);
  
  // write the board to a file
  cout << "Enter destination filename: ";
  cin >> fileName;
  if (!write(board, fileName)) {
    cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
    return 1;
  }

  return 0;
}

/**************************************************************
 * READ
 * Read the board from the specified filename
 *************************************************************/
bool read(char board[BSIZE][BSIZE][BSIZE], const char *fileName) {
  assert(*fileName);

  // open the file
  ifstream fin(fileName);
  if (fin.fail())
    return false;

  // read 9 symbols, hopefully they are . X O
  for (int h = 0; h < BSIZE; h++)
    for (int r = 0; r < BSIZE; r++)
      for (int c = 0; c < BSIZE; c++) {
        fin >> board[h][r][c];
        assert(!fin.fail());
        assert(board[h][r][c] == PLYR1 || 
               board[h][r][c] == PLYR2 ||
               board[h][r][c] == BLANK);
      }
  

  // close the file
  fin.close();
  return true;
}

/**********************************************************
 * WRITE
 * Write to fileName the board data
 *********************************************************/
bool write(const char board[BSIZE][BSIZE][BSIZE], const char *fileName) {
  assert(fileName[0] != '\0');

  // open the file
  ofstream fout(fileName);
  if (fout.fail())
    return false;

  // write my 9 symbols
  for (int h = 0; h < BSIZE; h++)
    for (int r = 0; r < BSIZE; r++)
      for (int c = 0; c < BSIZE; c++)
        fout << board[h][r][c] << (c == BSIZE ? '\n' : ' ');

  // close it!
  fout.close();
  cout << "File written\n";
  return true;
}

/*******************************************************
 * DISPLAY
 * Display the contents the the screen
 *****************************************************/
void display(const char board[BSIZE][BSIZE][BSIZE]) {
  for (int h = 0; h < BSIZE; h++){
    // loop through each row
    cout << "\nLevel " << h+1 << endl;
    for (int r = 0; r < BSIZE; r++) {
      // only the first row is not preceeded with the --+-- magic
      if (r != 0)
        cout << "---+---+---\n";
  
      // now, on each row, do the column stuff
      for (int c = 0; c < BSIZE; c++) {
        // display a space for the dot
        if (board[h][r][c] == BLANK)
          cout << "   ";
        else
          cout << " " << board[h][r][c] << " ";
  
        // end with a | or a newline
        cout << (c == 2 ? '\n' : '|');
      }
    }
  }

  // display who won
  if (didWin(board, PLYR1))
    cout << PLYR1 << " won!\n";
  if (didWin(board, PLYR2))
    cout << PLYR2 << " won!\n";

  return;
}

/********************************************
 * DID WIN
 * Did a given player (determined by the "turn"
 * variable) win the game?
 *******************************************/
bool didWin(const char board[BSIZE][BSIZE][BSIZE], char turn) {
  int tally = 0;

  // Determine if vertical lines have 3 across
  for (int h = 0; h < BSIZE; h++){
    for (int r = 0; r < BSIZE; r++) {
      tally = 0;
      for (int c = 0; c < BSIZE; c++)
        if (board[h][r][c] == turn)
          tally++;
      if (tally == BSIZE)
        return true;
    }
  }

  // Determine if horizontal lines have 3 across
  for (int h = 0; h < BSIZE; h++){
    for (int c = 0; c < BSIZE; c++) {
      tally = 0;
      for (int r = 0; r < BSIZE; r++)
        if (board[h][r][c] == turn)
          tally++;
      if (tally == BSIZE)
        return true;
    }
  }

  // Check one diagonal
  for (int h = 0; h < BSIZE; h++){
    tally = 0;
    for (int r = 0; r < BSIZE; r++){
      for (int c = 0; c < BSIZE; c++){
         if (r == c){
            if (board[h][r][c] == turn)
               tally++;
            if (tally == BSIZE)
                return true;
         }
      }
    }
  }

  // Check other diagonal
  for (int h = 0; h < BSIZE; h++){
    tally = 0;
    for (int i = 0; i < BSIZE; i++) {
      int d = BSIZE - 1 - i;
      if (board[h][i][d] == turn)
          tally++;
      if (tally == BSIZE)
        return true;
    }
  }

  // ----------------------------------- //
  //           3D checks
  // ----------------------------------- //
  
  // 3D Determine if vertical lines have 3 across
  for (int r = 0; r < BSIZE; r++) {
    tally = 0;
    for (int c = 0; c < BSIZE; c++)
      if (board[r][r][c] == turn)
        tally++;
    if (tally == BSIZE)
      return true;
  }

  // 3D Determine if horizontal lines have 3 across
  for (int c = 0; c < BSIZE; c++) {
    tally = 0;
    for (int r = 0; r < BSIZE; r++)
      if (board[r][r][c] == turn)
        tally++;
    if (tally == BSIZE)
      return true;
  }

  // 3D Check one diagonal
  tally = 0;
  for (int r = 0; r < BSIZE; r++){
    for (int c = 0; c < BSIZE; c++){
       if (r == c){
          if (board[r][r][c] == turn)
             tally++;
          if (tally == BSIZE)
              return true;
       }
    }
  }
  
  // 3D Check other diagonal
  tally = 0;
  for (int i = 0; i < BSIZE; i++) {
    int d = BSIZE - 1 - i;
    if (board[i][i][d] == turn)
        tally++;
    if (tally == BSIZE)
      return true;
  }

  return false;
}
