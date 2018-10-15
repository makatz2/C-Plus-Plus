////////////////////////////////////////////////////////////////////////////////
// File Name:      a3.cpp
//
// Author:         Michael Katz
// CS email:       mkatz@cs.wisc.edu
//               
// Description:    The source file for a3.
//
// IMPORTANT NOTE: THIS IS THE ONLY FILE THAT YOU SHOULD MODIFY FOR A3.
//                 You SHOULD NOT MODIFY any of the following:
//                   1. Name of the functions.
//                   2. The number and type of parameters of the functions.
//                   3. Return type of the functions.
//                   4. Import statements.
//
// Sources:        <Sources, if any>
//
// URL(s) of sources:
//                 <URLs of your sources, if any>
////////////////////////////////////////////////////////////////////////////////

#include "a3.hpp"

#include "trim.hpp"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

void cleanData(std::istream &inFile, std::ostream &outFile,
    		std::unordered_set<std::string> &commonWords) {
	std::string currLine;
	std::vector<std::string> rawRating;
	std::vector<std::string> noPunctuation;
	//loop through the each line of the file seperately to clean the data
	bool first = true;
	while(std::getline(inFile, currLine)){
		//Call the helper functions provided below to clean each line.
		splitLine(currLine, rawRating);
		removePunctuation(rawRating, noPunctuation);
		removeWhiteSpaces(noPunctuation);
		removeEmptyWords(noPunctuation);
		removeSingleLetterWords(noPunctuation);
		removeCommonWords(noPunctuation, commonWords);
		if(first == true){
			first = false;
		}else{
			outFile << std::endl;
		}
		bool firstLoop = true;
		// Write each cleaned word to the outFile
		for(auto i : noPunctuation){
			if(firstLoop == true){
				firstLoop = false;
}
			else{
				outFile << " ";	
			}outFile << i;
		
		}
	
		// Clear data before restarting the loop.
		currLine = "";
		rawRating.clear();
		noPunctuation.clear();
	}
	
}


void fillDictionary(std::istream &newInFile,
                    std::unordered_map<std::string, std::pair<long, long>> &dict) {
    	std::string line;
	std::string rating;
	// read in each line of inFile seperately.
	while(std::getline(newInFile, line)){
		// Seperate each word into vector
		std::istringstream split(line);
		std::istream_iterator<std::string> beg(split), end;
		std::vector<std::string> seperated(beg, end);
		// Remove first word which is the integer value rating
		std::istringstream parse(seperated.front());
		long rating;
	        parse >> rating;
		seperated.erase(seperated.begin());
		//For the remaining words loop over each one by one and add values to dict.
		for(auto& word : seperated){
			if(dict.find(word) == dict.end()){
				dict[word] = std::make_pair(rating, 1);
			}else{
				long totalRating = std::get<0>(dict.at(word)) + rating;
				long count = std::get<1>(dict.at(word)) + 1;
			 	dict[word] = std::make_pair(totalRating, count); 
			}
		}
	}
}

void fillCommonWords(std::istream &inFile,
                   std::unordered_set<std::string> &commonWords) {
	std::string input;
	while(std::getline(inFile, input)){
		commonWords.insert(trim(input));
	}
}

void rateReviews(std::istream &testFile,
                 std::unordered_map<std::string, std::pair<long, long>> &dict,
                 std::ostream &ratingsFile) {
	std::string currReview;
	std::vector<std::string> splitReview;
	bool first = true;
	// Read each line of test file seperately
	while(std::getline(testFile, currReview)){
		splitLine(currReview, splitReview);
		double fullRating = 0;
		double rating =0;
		double count = 0;
		if(first == true){
			first = false;
		}else{
			ratingsFile << std::endl;
		}
		// If review is empty (cleaned data has no remaining words) give review a 2
		if(splitReview.empty()){
			ratingsFile << std::setprecision(2) << std::fixed << 2;
		}else{
			count = splitReview.size();
			// Loop through each word and evaulate based on dict value of word
			for(std::string word :splitReview){
				// If not in dict value is 2
				if(dict.find(word) == dict.end()){
					rating = rating + 2;
				}else{
					
					rating = rating + ((double)std::get<0>(dict.at(word)) / (double)std::get<1>(dict.at(word)));
				}
			}
			ratingsFile << std::setprecision(2) << std::fixed << rating/count;
			splitReview.clear();
		}
	}
}

void removeEmptyWords(std::vector<std::string> &tokens) {
   	 tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [](std::string i){return i.length() == 0;} ),
tokens.end());
}

void removePunctuation(std::vector<std::string> &inTokens,
                       std::vector<std::string> &outTokens) {
	std::string currLine;
	std::string removedPunct;
    	for (std::vector<std::string>::iterator it = inTokens.begin() ; it != inTokens.end(); ++it){
		currLine = *it;
		currLine.erase(std::remove_if(currLine.begin(), currLine.end(), ispunct), currLine.end());
		outTokens.push_back(currLine);	
	}
}

void removeSingleLetterWords(std::vector<std::string> &tokens) {
    tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [](std::string i){return i.length() == 1 && !isdigit(i[0]); }), tokens.end());
}

void removeCommonWords(std::vector<std::string> &tokens, std::unordered_set<std::string> &commonWords) {
	for (std::string currWord : commonWords){
		tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [currWord](std::string i){return i == currWord;}), tokens.end());	
	}
}

void removeWhiteSpaces(std::vector<std::string> &tokens) {
	std::vector<std::string> temp(tokens.size());
	std::transform(tokens.begin(), tokens.end(), temp.begin(), trim); 
	tokens = temp;	    
}

void splitLine(std::string &line, std::vector<std::string> &words) {
	std::istringstream fullLine(line);
	std::string singleWord;
	char space = ' ';
   	while(std::getline(fullLine, singleWord, space)){
		words.push_back(singleWord);
	}
}
