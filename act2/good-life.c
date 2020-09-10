/// http://www.dreamincode.net/forums/topic/55572-conways-game-of-life/
/// downloaded by copy-paste on 8/19/2015 and modified to use an infinite loop
/// and have different Rule functions.
///
/// This code needs serious work in these areas:
/// <ol>
/// <li>  syntax: there are a number of warnings that cause errors.
/// </li>
/// <li>  semantics: the game algorithm implementation is incorrect.
/// </li>
/// <li>  design: the implementation needs function and value refactoring.
/// </li>
/// <li>  style: formatting is poor; the mix of TAB and spaces indentation
/// needs correction, and spacing between tokens is inconsistent.
/// The course style puts the '{' at the end of the function header, not
/// on a line of its own. You should make the formatting consistent.
/// </li>
/// <li>  documentation: documentation is non-existent except for this block.
/// </li>
/// </ol>
/// file: good_life.c
/// description: a program that plays Conway's Game of Life
///
/// @author Jesse Burdick-Pless jb4411 

#include <stdio.h>
#include <stdlib.h>

#define GRID_SIZE 20

/// Prints a header meassage when the program is started

void header() {
	printf("\n\t..Welcome to the Game of life..\n");
}

/// Copies all elements from the arc array into the dest array.
///
/// @param src   the array of char to be copied into dest
/// @param dest  the array src is copied into

void copy_array(char src[][GRID_SIZE], char dest[][GRID_SIZE]) {
	int row, col;
	for(row = 0; row < GRID_SIZE; row++) {
		for(col = 0; col < GRID_SIZE; col++) {
			dest[row][col] = src[row][col];
		}
	}
}

/// Counts and returns the number of neighbors the selected cell has. a cell
/// is selected by passed in its row and column.
///
/// @param life      the array of char that holds the board of cells
/// @param life_row  the row of the selected cell
/// @param life_col  the column of the selected cell
/// @return the number of neighbors the selected cell has 

int count_neighbors(char life[][GRID_SIZE], int life_row, int life_col) {
	char newlife[GRID_SIZE][GRID_SIZE] = {{' '}};
	copy_array(life, newlife);
	int neighbors = 0;
	int row = life_row % GRID_SIZE;
	int col = life_col % GRID_SIZE;
	if(life[row - 1][col - 1] == '*')
		neighbors++;
	if(life[row - 1][col] == '*')
		neighbors++;
	if(life[row - 1][col + 1] == '*')
		neighbors++;
	if(life[row][col - 1] == '*')
		neighbors++;
	if(life[row][col + 1] == '*')
		neighbors++;
	if(life[row + 1][col - 1] == '*')
		neighbors++;
	if(life[row + 1][col] == '*')
		neighbors++;
	if(life[row + 1][col + 1] == '*')
		neighbors++;

	return neighbors;
} 

/// Generates the next generation from the board of cells passed in.
/// 
/// @param life  the array of char that holds the board of cells
void game_of_life(char life[][GRID_SIZE]) {
	char newlife[GRID_SIZE][GRID_SIZE] = {{' '}};
	copy_array(life, newlife);
	int neighbors, row, col;
	for(row = 0; row < GRID_SIZE; row++) {
		for(col = 0; col < GRID_SIZE; col++) {
			neighbors = count_neighbors(life, row, col);
			if(neighbors == 3) {
				newlife[row][col] = '*';
			} else if(neighbors == 2 && life[row][col] == '*') {
				newlife[row][col] = '*';
			} else {
				newlife[row][col] = ' ';
			}
		}
	}
	copy_array(newlife, life);
	return;
}

/// The main program asks the user to enter a starting number of organisms.
/// The first generation board is the randomly generated. From here the main
/// program simulates 100 generations from the starting board and prints each
/// one out to the user.

int main(void) {
	char life[GRID_SIZE][GRID_SIZE] = {{' '}}; /// fix 2: initlized array
	int orgs; /// fix 11: removed unused varible 'gens'
	int i = 0, row = 0, col = 0; /// fix 2: initlized varibles
	/// ^ fix 6: removed unused varibles 'a' and 'b'
	int count = 0;
	/// fix 17: removed unused varible 'int x'
	/// fix 16: removed unused varible 'int y'
	/// fix 5: removed unused varible 'char ans'

	header();

	printf("\nPlease enter the initial number of organisms: ");
	scanf("%i", &orgs);
	puts(" ");
	srand( 31 );

	while( i<orgs ) {
		row = rand();
		row %= 20;
		col = rand();
		col %= 20;
		if( life[row][col] != '*' ) {
			life[row][col] = '*'; /// fix 4: removed an '='
			i++;
		} 
	}

	for(row = 0; row<20; row++) {
		for(col = 0; col<20; col++) {
			if(life[row][col] != '*')
				life[row][col] = ' '; /// fix 3: removed an '='
			printf("%c", life[row][col]); 
			/// fix 1: changed %s to %c
		}
		puts(" "); 
		/// added functions to print generation 0 to this loop
	}

	printf("\ngeneration: 0\n");

	while ( count < 100 ) {
		game_of_life(life);
		for(row = 0; row<20; row++) {
			for(col = 0; col<20; col++) {
				printf("%c", life[row][col]); 
				/// fix 1: changed %s to %c
			}
			puts(" ");
		}
		printf("\ngeneration: %d\n", count+1);
		count++;
	}

	return 0;
}

