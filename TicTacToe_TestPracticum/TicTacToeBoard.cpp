#include "TicTacToeBoard.h"
#include <iostream>
#include <stdlib.h>
#include <string>

/*
 * ToDo - Validate row & columns everywhere  (highest priority - poor OO coding!!!
 * ToDo - Separate player name from 'X' and 'O' characters - e.g. default player name to character, but then allow it to change
*/

/*
 * Instance variables (declared in header file)
 *   board[][] - two dimensional array indexed by row (0-2) & column (0-2), cleared when starting a new game
 *   takenSquareCount - integer tracking # of moves in the game, reset at instance creation & on starting a new game
 *   player - character indicating the player making the current move
 *     notes - default player defined in board class header file,
 *     current player is tracked and can be retrived by the board class, but is updated from outside the class via nextPlayer()
 * 
 * Notes
 *   Error handling
 *      For writeSquare() - returns true if update was successful, false if not (e.g. space already occupied)
 *      For all methods w/ row & column params - invalid argument exception thrown if params are out of range
 */

// Constructor -- initialize all board spaces to empty, starting player intialized in .h file when memory allocated
TicTacToeBoard::TicTacToeBoard() {
	resetBoard();
}

// Reset board and variable tracking # of spaces played in current game
void TicTacToeBoard::resetBoard() {
	takenSquareCount = 0;
	for (int r = 0; r < BOARD_NUM_ROWS; r++) {
		for (int c = 0; c < BOARD_NUM_COLS; c++) {
			board[r][c] = EMPTY;
		}
	}
}

// If specified space is empty - return true
//    no arg checking on this one :)
bool TicTacToeBoard::isSquareEmpty(int row, int col) const {
	if (board[row][col] == EMPTY)
		return true;
	else
		return false;
}

// Updates space to the player (marker) specified, return false if space not empty
//   intentional arg check issue
bool TicTacToeBoard::writeSquare(int row, int col, Player currentPlayer) {
	// use helper function to validate parameters, if invalid exception thrown, won't get pass the call
	validateRowsAndColumns(row, col);

	// if within range & the square is empty, enter the player's move, update # of spaces played & return true
	if (this -> isSquareEmpty(row, col)) {
		board[row][col] = currentPlayer;
		takenSquareCount++;
		return true;
	}
	else { // the space was already occupied, return false
		return false;
	}
}

// Returns character (ie player marker) in the given row/col, throws exception if args invalid
char TicTacToeBoard::getSquareContents(int row, int col) const {
	if ((row >= BOARD_NUM_ROWS) || (col >= BOARD_NUM_COLS)) {
		// note: if we get here, everything after the above throw line is skipped — it never runs.
		throw std::invalid_argument("Invalid row or column passed to getSquareContents\n");
	}
	// else - good row & column passed
	return playerMap(board[row][col]);
}

// Returns the current player (enum)
TicTacToeBoard::Player TicTacToeBoard::getPlayer() const {
	return player;
}

// Returns player name (character)
char TicTacToeBoard::getPlayerName() const {
	return playerMap(player);
}

// Toggles next to play (e.g. if current player is X, next to play is O)
TicTacToeBoard::Player TicTacToeBoard::nextPlayer() {
	if (player == X)
		player = O;
	else
		player = X;
	return player;
}

// Return true if specified player has won the game
//   Legacy version - exhaustive check - cell by cell
bool TicTacToeBoard::isWinner(Player playerToCheck) const {

	// check rows
	for (int r = 0; r < BOARD_NUM_ROWS; r++) {
		if ((board[r][0] == playerToCheck) &&
			(board[r][1] == playerToCheck) &&
			(board[r][2] == playerToCheck))
			return true;
	}

	// check columns
	for (int c = 0; c < BOARD_NUM_COLS; c++) {
		if ((board[0][c] == playerToCheck) &&
			(board[1][c] == playerToCheck) &&
			(board[2][c] == playerToCheck))
			return true;
	}

	// check diagonals
	if ((board[0][0] == playerToCheck) &&
		(board[1][1] == playerToCheck) &&
		(board[2][2] == playerToCheck))
		return true;
	// reverse
	if ((board[0][2] == playerToCheck) &&
		(board[1][1] == playerToCheck) &&
		(board[2][0] == playerToCheck))
		return true;

	return false;              // no winner this time
}


// Return true if game is a Draw - all squares filled and no one has won
//   intentional defect added
bool TicTacToeBoard::isDraw() const {
	if ((takenSquareCount > BOARD_NUM_ROWS * BOARD_NUM_COLS) && 
		!this->isWinner(X) && !this->isWinner(O)) {
		return true;
	}
	else
		return false;
}

// map enum to character for displaying player name
char TicTacToeBoard::playerMap(Player playerEnum) const {
	switch (playerEnum) {
	case X:
		return 'X';
	case O:
		return 'O';
	default:
		return ' ';
	}
}

// helper function to validate row & column arguments
//   if outside range [0:BOARD_NUM_...], throws invalid_argument exception
//   ToDo - determine if called method (or even the whole stack) is shown in the exception output
void TicTacToeBoard::validateRowsAndColumns(int row, int column) const {
	if ((row >= BOARD_NUM_ROWS) || (column >= BOARD_NUM_COLS) ||
		(row < 0) || (column < 0)) {
		std::string errorMessage = "Exception thrown: invalid row or column.  row: " + std::to_string(row) + "  column: " + std::to_string(column) + "\n";
		throw std::invalid_argument(errorMessage);
	}
}
