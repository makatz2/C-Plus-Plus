////////////////////////////////////////////////////////////////////////////////
// File Name:      a1.cpp
//
// Author:         Michael Katz
// CS email:       mkatz@cs.wisc.edu
//
// Description:    A program that reads in a string and
//                 repeats it in a grid-like format
//
// Sources:        <Sources, if any>
//
// URL(s) of sources:
//                 <URLs of your sources, if any>
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
/*
 * Prints the string fancy into the pattern specified by the rows and
 * cols theuser entered.
 * Accepts string fancy which is the string to be repeated. Accepts
 * int rows and
 * int cols which is the number of rows and columns that the pattern
 * should have
 */
void printText(std::string fancy, int rows, int cols) {
	for (int x = 0; x < rows; ++x) {
	   // Do not move to next line if it is the first interation of the loop
	   if(x != 0){
		   std::cout << std::endl;
	   }
		for (int y = 0; y < cols; ++y) {
			std::cout << fancy;
		}
	}
std::cout << std::endl;
}
/*
 * Main function which gets user input in the form of the string fancy, int rows,
 * and int cols. This information is then passed to function printText. Return 0. 
 */
int main() {
	std::cout << "Enter a fancy string: ";
	// fancy stores the string to be repeated in set pattern
	std::string fancy;
	getline(std::cin, fancy);
	std::cout << "Enter the number of rows: ";
	// rows stores the amount of rows the pattern will have
	int rows;
	std::cin >> rows; 
	std::cout << "Enter the number of cols: ";
	int cols;
	std::cin >> cols;
	// Calls printText to print the pattern
    printText(fancy, rows, cols);
return 0;
}


