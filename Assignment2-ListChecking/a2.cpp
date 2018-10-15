///////////////////////////////////////////////////////////////////////
// File Name:      a2.cpp
//
// Author:         Michael Katz
// CS email:       mkatz@cs.wisc.edu
// 
// Description: Accepts user input of two file names full of recipes. 
// 	The program will check for any intersecting values in the files.
// 	The intersecting recipes are printed and the program creates a
// 	file of the intersecting recipes and of the different recipes.  
//
// Sources:       
//
// URL(s) of sources:           
///////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main() {
	string file1;
        string file2;
        set<string> recipes1;
       	set<string> recipes2;
	
	// While loop that continues to prompt user for name of the first file and checks that
	// it is a real file. If it is a real file it puts the contents in a set before breaking.
        while(true){
        	cout << "Enter the name of the first file: ";
                getline(cin, file1);
		ifstream stream1 (file1);
                
		if(!stream1.is_open()){
                        cout << "Input file " + file1 + " is NOT found. Please try again." << endl;
                }else{
			for(string nextLine; getline(stream1, nextLine);){
                	recipes1.insert(nextLine);
			}
			break;
                }
        }
	// While loop that continues to prompt user for name of the second file and checks that
        // it is a real file. If it is a real file it puts the contents in a set before breaking.
        while(true){
               cout << "Enter the name of the second file: ";
               getline(cin, file2);
               ifstream stream2 (file2);
               
	       if(!stream2.is_open()){
               cout << "Input file " + file2 + " is NOT found. Please try again." << endl;
               }else{
                        for(string nextLine; getline(stream2, nextLine);){
                		recipes2.insert(nextLine);
			}
			break;
               }
        }
        // Creates an ofstream to print the intersection values to and verifies that it was opened
        // correctly. Returns if it is unable to open the file.
	ofstream inter("intersection.txt", ofstream::out);
        if(!inter.is_open()){
                cout << "Unable to open the output file(s)." << endl;
		return 0;
        }
	// Creates an ofstream to print the difference values to and verifies that it was opened
	// correctly. Returns if it is unable to open the file.
        ofstream diff("difference.txt", ofstream::out);
        if(!diff.is_open()){
                cout << "Unable to open the output file(s)." << endl;
		return 0;
        }

        set<string> intersection;
        set<string> difference;
	// Finds the intersecting values in the two files and inserts them into the set.
        set_intersection(recipes1.begin(), recipes1.end(), recipes2.begin(), recipes2.end(),
		       	inserter(intersection, intersection.begin()));
	// Finds the different values in the first file and inserts them into the set.
        set_difference(recipes1.begin(), recipes1.end(), recipes2.begin(), recipes2.end(),
		       	inserter(difference, difference.begin()));
	// Prints intersection set to the intersection.txt file.
	for(set<string>::iterator i = intersection.begin(); i != intersection.end(); i++){
		if(i != intersection.begin()){
			inter << endl;
		}
		inter << *i;
	}
	// Prints the difference set to the difference.txt file.
	for(set<string>::iterator i = difference.begin(); i != difference.end(); i++){
		if(i != difference.begin()){
			diff << endl;
		}	
		diff << *i;
        }	
	cout << endl;
	cout << "Number of recipes in " + file1 + " = " << recipes1.size() << endl;
	cout << "Number of recipes in " + file2 + " = " << recipes2.size() << endl;
	cout << "Number of recipes that are present in BOTH " + file1 + " AND " + file2
	       	+ " = " << intersection.size() << endl;
	cout << "Number of recipes that are in " + file1 + " BUT NOT IN " + file2
	       	+ " = " << (recipes1.size() - intersection.size()) << endl;
	// Only prints if intersection is not empty.
	if(intersection.size() != 0){
		cout << endl;
		cout << "List of recipes that are present in BOTH " + file1 + " AND " + file2 +  ":" << endl;
		for(set<string>::iterator i = intersection.begin(); i != intersection.end(); i++){
                	cout << *i << endl;
		}
	}

	cout << endl;
	cout << "The set intersection of the two files was written to a file named intersection.txt" << endl;
	cout << "The set difference of the two files was written to a file named difference.txt";
return 0;
}
