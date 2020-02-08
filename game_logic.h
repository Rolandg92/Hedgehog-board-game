/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]);


/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);



/* 
 *  * Manages the logic of the game
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players 
 */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);

/**
 * Function to check if a row is empty.
 * 
 * Input:
 * Dice roll and board array
 * 
 * Output:
 * Return 0 if the row is empty.
 * Return a 1 if the row is not empty.
**/
int checkRow(int x, square board[NUM_ROWS][NUM_COLUMNS]);

/**
 * Function to check the empty squares on the left hand side of an obstacle square
 * 
 * Input:
 * Variable representing the column up to which the function will
 * check the squares
 * 
 * The board array
 * 
 * Output:
 * Return 1 if not all of the squares are empty
 * 
 * Return 0 if all of the squares were found empty
 */
int checkSquares(int x, square board[NUM_ROWS][NUM_COLUMNS]);

/**
 * Function to print the color tag of a player so that players can keep track
 * of their color easier
 * 
 * Inputs:
 * The array of players
 * 
 * An int representing the place of a specific player in the array
 * 
 * Output:
 * 
 * Returns the character associated with the player color
 */
char printPlayerCol(player *players, int x);

/**
 * This function is used when players place their tokens in the first column.
 * 
 * It checks if there are no squares with a minimum amount of tokens and a color different than
 * that of the player, a valid move and returns a 1.
 * 
 * If a square with the minimum amount of tokens is found but it is the same color as the player
 * it will return a 0.
 */
int noLegalMove(int minTokens, square board[NUM_ROWS][NUM_COLUMNS], player players[], int x);