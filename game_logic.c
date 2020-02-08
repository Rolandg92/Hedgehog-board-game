#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function to check token placement
//If no legal spot is available returns 0
int noLegalMove(int minTokens, square board[NUM_ROWS][NUM_COLUMNS], player players[], int x)
{
    int condition = 0;
    for(int i = 0; i < 6; i++)                             //  This function loops through each row of the initial column first finding
    {                                                       //the minimum squares then checking to see if they are the same color as the
        if(board[i][0].numTokens == minTokens)              //current player. If the player has no move that wouldn't cover his own color
        {                                                   //then that rule is over written for that players turn allowing them to stack
            if(players[x].col != board[i][0].stack->col)    //on their own color to keep the stacks even.
            {
                condition = 1;
            }
        }
    }
    return condition;
}

// Checks if there are squares on the left hand side of the chosen square
int checkSquares(int x, square board[NUM_ROWS][NUM_COLUMNS])
{
    int i, t, a = 0;
    
    for(i = 0; i < 6; i++)// loop through the rows
    {
        for(t = 0; t < x; t++)// loop through the columns
        {
            //check the square
            if(board[i][t].stack != NULL){
                a = 1;// assign 1 to a if a non null square has been found
            }            
        }        
    }
    // return a, if a = 0 no tokens found on any of the checked squares, else tokens were found a = 1
    return a;
}

// Check if the row is empty, return 0 if it's empty
int checkRow(int x, square board[NUM_ROWS][NUM_COLUMNS])
{
    int a = 0;
    
    for(int i = 0; i < 8; i++)// loop through the columns
    {
        if(board[x][i].stack != NULL)
            a = 1;// assign 1 to a if a non null square has been found       
    }
    // if a = 0 the row is empty, else a = 1 row is not empty, return a
    return a;
}
/**
 * Function to push a token onto the stack
**/
token *push(int val, token *top)
{
    token *temp = top;// temporary pointer to store the value of the top pointer
    
    if(temp != NULL)// if the temp pointer is not null
    {
        top = (token *)malloc(sizeof(token));//allocate memory to the top
        top->col = val;// insert the data in the stack, assign the color value 
        top ->next = temp;// assign the value of temp to next
    }
    else// if the temp/top pointer is null
    {
        top = (token *)malloc(sizeof(token));// allocate required memory
        top->col = val;// // insert the data in the stack, assign the color value 
        top->next = NULL;// assign the value null to 'next' element of top
    }
    return top;// return the new top address/value
}

/**
 * Function to take the top token from the stack
**/
token *pop(token *top)
{
    token *temp = top;// temporary pointer to store the value of the top pointer
    
    if(top != NULL)// if the value of top isn't null
    {        
        top = temp->next;// assign the value of next element of temp to top
    }
    free(temp);// clear the temp pointer
    return top;// return the new address of top
}
//-------------------------------------------------------------------
void printLine();

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLU) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

//Returns the first letter associated with the color of the token
// 
//Input: players - pointer to players color
//         x - current player
//Output: initial of the color of the token
 
char printPlayerCol(player *players, int x){
    if(players[x].col== PINK) return 'P';
    if(players[x].col== RED) return 'R';
    if(players[x].col== BLU) return 'B';
    if(players[x].col== GREEN) return 'G';
    if(players[x].col== ORANGE) return 'O';
    if(players[x].col== YELLOW) return 'Y';
    return '\0';
}

/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){
       
        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].stack != NULL){
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");  
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
       
    int minNumofTokens = 0; //Holds minimum number of tokens allowed in each square in the initial column before a stack can increase
    int selectedSquare = 0; //User selected square to place token in
    
    for(int i=0; i<4; i++){ //Loops through each player allow them to place all their tokens on the first column
        for(int j=0; j<numPlayers; j++){
            printf("Player %s[%c] please select a square\n>", players[j].name, printPlayerCol(players, j));
            scanf(" %d", &selectedSquare);
            
            if(board[selectedSquare][0].numTokens==minNumofTokens)  //conditional to check square chosen has stack equal to minimum token value
            {
                if(board[selectedSquare][0].stack != NULL)  //conditional to check if the stack is empty 
                {
                    //conditional to make sure player doesn't lay on their own color unless there is no other move decided by noLegalMove function
                    if(board[selectedSquare][0].stack->col != players[j].col || noLegalMove(minNumofTokens, board, players, j) != 1)
                    {
                        board[selectedSquare][0].stack = push(players[j].col, board[selectedSquare][0].stack);  //place token on square
                        board[selectedSquare][0].numTokens++;   //increases stack count on square
            
                        if(((numPlayers * i) + j + 1)%NUM_ROWS == 0){   //every 6 tokens the minimum token count is increased by one
                        minNumofTokens++;
                        }
                        print_board(board); //print board after each token laid
                    }
                    else{   //When color conditional not met an error is printed letting the player no why their choice wasn't accepted and to chose again
                    printf("Invalid choice! Cannot place starting token on top of your own color.\n");
                    j--;
                    }             
                }
                else{   //if stack is empty a token is added to the square
                    board[selectedSquare][0].stack = push(players[j].col, board[selectedSquare][0].stack);
                    board[selectedSquare][0].numTokens++;
            
                    if(((numPlayers * i) + j + 1)%NUM_ROWS == 0){
                        minNumofTokens++;
                    }
                    print_board(board);//print board to show changes
                }
            }
            else
            {
                //When minimum stack conditional not met an error is printed
                //letting the player know why their choice wasn't accepted and to chose again
                printf("Invalid choice! Must place tokens evenly across column.\n");
                j--;
            } 
        }
    }
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    
    srand(time(NULL));// call srand function to randomise numbers generated
    
    // declare and initialize variable
    int squareSelected, dice, winner, choiceCol, choiceRow, input;
    char choice;
    int condition = 1;
    input = 0;
    winner = 0;
    
    while(condition)// loop while the condition is 1, if it is changed to 0, end loop
    {
        for(int j=0; j < numPlayers; j++)
        {
            printf(">> Player %s's[%c] turn <<\n", players[j].name, printPlayerCol(players, j));
            
            // Die roll            
            do{
                dice = ( 1 + (rand() % 6));// generate a number between 1 and 6 using rand function
                dice = dice - 1;//decrease dice value by one to match the rows on the board
            }while(checkRow(dice, board) != 1);// roll again if the row is empty
            printf("Die %d :: Row %d\n", (dice + 1), dice);// print the value of the die roll and the row corresponding row
            
            
            /*Code for the optional side move*/
            // Prompt user to enter if they want to make a vertical move
            printf("\nDo you want to make a vertical move? [y or n]\n>");
            scanf(" %c", &choice);
            
            //if the user entered y
            if(choice == 'y' || choice == 'Y')
            {
                //ask user to enter the number of the col and row the token is place in and read input
                printf("Please select the column: \n");
                scanf(" %d", &choiceCol);
                printf("Please select the row: \n");
                scanf(" %d", &choiceRow);
                    
                if(board[choiceRow][choiceCol].stack != NULL)// if the chosen square is not empty continue execution
                {
                    // if the chosen token is on an obstacle square and there are tokens 
                    // present on the left hand side of the chose square, display the message
                    if(board[choiceRow][choiceCol].type == OBSTACLE && checkSquares(choiceCol, board) != 0)
                    {
                        puts("<xx The square is an obstacle and there are tokens on the left side of the chosen square xx>");
                    }
                    else// otherwise continue execution
                    {
                        // check if the chosen token color is the same as the player color, if yes run continue
                        if(board[choiceRow][choiceCol].stack->col == players[j].col)
                        {
                            
                            if(choiceRow == 0){// if the chosen row is 0 then automatically move the token to row one
                                input = 1;//assign 1 to input
                            }
                            else if(choiceRow == 5){// if the chose row is 5 then automatically move the token to row 4
                                input = -1;// assign -1 to input, since choiceRow + input, if input is -1 then the row will decrease from 5 to 4
                            }                            
                            else
                            {
                                do{
                                    // prompt user to enter if the want to move up or down
                                    printf("\nPlease enter if you want to move up or down.\nEnter -1 for up and 1 for down:");
                                    scanf(" %d", &input);
                                    if(input == 0)// if input is 0
                                        input +=10;// change the value of input from 0 to a positive int greater than 1
                                }while(!(input > -2 && input < 2));// loop while the input is not 1 or -1
                            }                       
                            // using push and pop functions, move a token from one square to another
                            board[choiceRow + input][choiceCol].stack = push(board[choiceRow][choiceCol].stack->col, board[choiceRow + input][choiceCol].stack);
                            board[choiceRow][choiceCol].stack = pop(board[choiceRow][choiceCol].stack);
                            print_board(board);// print board to show changes 
                        }                           
                        else// if the color of the chosen token is different than that of the player then display the message
                        {
                            puts("<xx Invalid choice. You can only use your tokens to do a vertical move xx>");
                        }
                    }                    
                }
                else// If the square selected is empty display the message
                {
                    puts("<xx There are no tokens on the square selected xx>");
                }
            }/*End of code to do the side move*/
            
            // If the side move cleared a row and how there are no token on the row to be moved
            // automatically roll the die again
            if(checkRow(dice, board) != 1)
            {
                do{
                    dice = ( 1 + (rand() % 6));
                    dice = dice - 1;
                }while(checkRow(dice, board) != 1);
                printf("\n<Empty row new roll>\nDie %d :: Row %d\n", (dice + 1), dice);
            }
            
            // Ask for user to choose the token they want to move forward and move if the chose square has no tokens on it
            // or the chose square is not a valid square, outside of the value of the rows and columns
            do{
                printf("\nPlease select which token to move right: ");
                scanf(" %d", &squareSelected);
            }while(!(squareSelected >= 0 || squareSelected <= 7) || board[dice][squareSelected].stack == NULL);
            
            // If the chose token is on an obstacles square and there are tokens present
            // on the left hand side of the chose token, display the message
            if(board[dice][squareSelected].type == OBSTACLE && checkSquares(squareSelected, board) != 0){
                puts("<xx The selected token is on an obstacle square and cannot be moved yet xx>");
            }
            else// Otherwise
            {
                // call the push and pop functions to make the change on the board, change a token from one square to another
                board[dice][squareSelected + 1].stack = push(board[dice][squareSelected].stack->col, board[dice][squareSelected + 1].stack);
                board[dice][squareSelected].stack = pop(board[dice][squareSelected].stack);
                
                // if a token ends up in the 8th column
                if(squareSelected + 1 == 8)
                {
                    // based on the color of the token equivalent to a player's color
                    switch(board[dice][squareSelected + 1].stack->col)
                    {
                        // For each player based on their color:
                        // - add a 1 to numTokensLastCol variable
                        // - if the numTokensLastCol reaches the value of 3 tokens
                        // assign 0 to condition(it will stop the loop)
                        // and the value corresponding to each player to winner
                        case 0:
                            players[0].numTokensLastCol++;
                            if(players[0].numTokensLastCol >= 3)
                            {
                                condition = 0;
                                winner = 0;
                            }
                            break;                        
                        case 1:
                            players[1].numTokensLastCol++;
                            if(players[1].numTokensLastCol >= 3)
                            {
                                condition = 0;
                                winner = 1;
                            }
                            break;                        
                        case 2:
                            players[2].numTokensLastCol++;
                            if(players[2].numTokensLastCol >= 3)
                            {
                                condition = 0;
                                winner = 2;
                            }
                            break;                        
                        case 3:
                            players[3].numTokensLastCol++;
                            if(players[3].numTokensLastCol >= 3)
                            {
                                condition = 0;
                                winner = 3;
                            }
                            break;
                        case 4:
                            players[4].numTokensLastCol++;
                            if(players[4].numTokensLastCol >= 3)
                            {
                                condition = 0;
                                winner = 4;
                            }
                            break;
                        case 5:
                            players[5].numTokensLastCol++;
                            if(players[5].numTokensLastCol >= 3)
                            {
                                condition = 0;
                                winner = 5;
                            }
                            break;
                        default:
                            break;                        
                    }//end switch                    
                }//end if                
            }//end if
            
            puts("=====================^=====================\n");            
            print_board(board);// print the board
            
            // based on the value of winner display a message showing the winner            
            if( winner == 1 || winner == 2 || winner == 3 || winner == 4 || winner == 5 || winner == 6)
            {
                printf("\n>>>>>>>>>>* Player [%s] Won *<<<<<<<<<<\n", players[winner].name);
                j = numPlayers;//to end the for loop
            }            
        }//end for        
    }//end while    
}//end of play_game


