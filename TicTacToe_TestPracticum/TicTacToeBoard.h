#pragma once
/*****************************************************************//**
 * \file   TicTacToeBoard.h
 * \brief  board class - TicTacToeBoard
 *     Scope - all aspects of the board, including defining the # rows & columns, win conditions, current/starting player
 *        supports retrieving data elements for displaying the board
 *
 * \author Lee
 * \date   updated: November 2025
 *
 * Implementation notes:
 *     - Player enum is used for both the name of the player & for the player's move
 *     - lots of Technical debt in this implementation, including need to consistently use BOARD_NUM_ROWS and BOARD_NUM_COLS
 *     - the range for valid rows & columns is [0,2], all other values are invalid (note: max = BOARD_NUM_... - 1)
 *     - if row or column is out of range, all methods should throw an invalid argument exception
 *
 * constructor                                 - initializes board via resetBoard() method
 * resetBoard()                                - initializes board & number of turns played in current game
 *                                               (note: no method currently implemented returns # of cells played)
 * bool isSquareEmpty(int row, int column)     - returns true = square empty, false otherwise
 * bool writeSquare(int row, int column, Player player) - if cell empty, writes enum into square & returns true, returns false if square !empty
 * char getSquareContents(int row, int column) - returns character in specified square (e.g. 'X', 'O', ' ')
 * 
 * Player getPlayer()                          - returns player (enum) whose turn it is
 * char getPlayerName()                        - returns player (character) whose turn it is
 * Player nextPlayer()                         - swaps player whose turn it is &
 *                                                 returns Player (ie enum) of the new player (e.g. if O playing, returns X)
 * bool isWinner(Player playerToCheck)         - true if the specified player has won, false otherwise
 * bool isDraw()                               - true if no-one has won & no open squares, false otherwise (e.g. consider - no spaces empty)
 **/

#include <set>          // for pattern matching design
#include <array>        //   ditto - pattern matching

class TicTacToeBoard
{

public:
	enum Player { X, O, EMPTY };    // define player enums, map to display character, ToDo: use "class" for type safety

	// define some constants for public consumption, note initial player defined here in the Board class
	static constexpr int BOARD_NUM_ROWS = 4;
	static constexpr int BOARD_NUM_COLS = 4;
	static constexpr Player INITIAL_PLAYER = Player::X;


	TicTacToeBoard();
	void resetBoard();										// resets the squares to EMPTY and the # of turns played in the current game
		                                                    //   Note: reset board DOES NOT reinitialize the player whose turn it is
	bool isSquareEmpty(int row, int col) const;				// returns true if given space is empty, false if already occupied
	bool writeSquare(int row, int col, Player currentPlayer);  // returns true if successfully written, false on failure (e.g. space not empty)
	char getSquareContents(int row, int col) const;       // used for displaying board, return player character
	char getPlayerName() const;							  // returns name of the player - hardcoded as 'X' or 'O'
	Player getPlayer() const;								// returns internal ID (ie enum) of the player
	Player nextPlayer();					              // swap player for next move, returns new player
	bool isDraw() const;								// check if a draw
	bool isWinner(Player playerToCheck) const;           // check if specified player has won



private:  // reserve memory for board & current player
	Player board[BOARD_NUM_ROWS][BOARD_NUM_COLS];      // board storage, indexed by row [0-2] and column [0-2]
	Player player = INITIAL_PLAYER;                    // tracks the current player, ie next symbol placed
	int takenSquareCount = 0;                        // # of spaces played in current game, reset for new games

	  // map player enum to player character - used as a helper function
	char playerMap(Player playerEnum) const;		// ToDo - create mapping list rather than switch statement
	  // validates arguments against BOARD_NUM_..., throws invalid arg exception
	void validateRowsAndColumns(int row, int column) const;

		//                                 Pattern matching winners
		//  following methods & data structures are used in a new approach to check for a win
		//   set based approach, where row & column are mapped into a 0-8 position (actually 0-#rows*#cols-1)
		//   writeSquare() fills in legacy board[][], as well as tracking X & Os positions played
		//   matchesWinningPattern() checks if any of the winning patterns (e.g. 0,4,8 - forward diagonal) is a subset of the player's moves
		//     isWinner() via comment removal can be set to use the new approach
		//
		// Important!  an inline declaration would require C++ v17 or newer, default in MS VS 2022 is v14
		//   To mitigate: the initialization is in the cpp file -> no inline declaration required, and can run in v14
	std::set<int> xMoves;		// track X moves by position 0-8 for set based evaluation
	std::set<int> oMoves;       // track O moves by position 0-8 for same

	bool matchesWinningPattern(Player p) const;     // refactor isWinner() to pattern matching approach
	int rowColToPosition(int row, int column);      // helper function to map row & column to a position
};