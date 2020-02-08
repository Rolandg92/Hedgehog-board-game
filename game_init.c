/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){
   
    for (int i =0; i< NUM_ROWS; i++){
        for(int j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4) 
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].stack = NULL;// initialize stack to null
            board[i][j].numTokens = 0;// initialize numTokens to 0
        }
    }
}
    
 /*
 * This function creates players for the first time
 * 
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(player players[]){
    
    int i;
    for(i=0;i<6;i++)
    {
        printf("Enter player %d: ", (i+1));// prompts user to enter their
        fgets(players[i].name, 30, stdin);//read user input
        players[i].col = i;//assign a color to each player
        players[i].numTokensLastCol = 0;// initialize the numTOkensLastCol to 0
        
        // if user input is a new line character then it will stop taking input from user
        if(players[i].name[0]== '\n'){
            break;
        }
        else{
            clearName(players[i].name);//call clearName function to remove the new line char from the name
        }
    }
    return i;
}
/**
 * Function to clear the last character in the name which is '\n' 
 */
void clearName(char *string)
{
    while(*string != '\n')//loop until the new line char is found
    {
        string++;
    }
    *string = '\0';// remove the new line char by replacing it with a null char
}
   
     

