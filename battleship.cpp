/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"

static CellContent field_my[FIELDSIZE][FIELDSIZE];
static CellContent field_op[FIELDSIZE][FIELDSIZE];
static CellContent guesses[FIELDSIZE][FIELDSIZE];

void load_game(){
  FILE* me_fd = fopen("battleship.my", "r");
  FILE* op_fd = fopen("battleship.op", "r");
  for(int y = 0;y < FIELDSIZE;y++){
    for (int x = 0; x < FIELDSIZE;x++)
    {
        fread(&field_my[x][y],4,1,me_fd);
        fread(&field_op[x][y],4,1,op_fd);
        guesses[x][y] = Unknown;
    }
  }
  fclose(me_fd);
  fclose(op_fd);
}

/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col){
  if(row < 0 || row >= FIELDSIZE || col < 0 || col >= FIELDSIZE)
    return OutOfRange;
  else
    return field_my[col][row];
}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col)
{
 CellContent check_surrounding = get_my_guess(row, col);

 if(check_surrounding == OutOfRange)
   return false;

 if(field_op[col][row] == Boat || field_op[col][row] == Water)
 {
   guesses[col][row] = field_op[col][row];
   if(guesses[col][row] == Boat)
   {
     for (int y= - 1; y < 2; y++) {
       for (int x = - 1; x < 2; x++) {
         check_surrounding = get_my_guess(row + x, col + y);
         switch (check_surrounding) {
           case Unknown: guesses[col + y][row + x] = Water;
            break;
           default:
            break;
         }
       }
     }
   }
 }
 return true;

}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col)
{
  if(row < 0 || row >= FIELDSIZE || col < 0 || col >= FIELDSIZE)
    return OutOfRange;
  else
    return guesses[col][row];
}
