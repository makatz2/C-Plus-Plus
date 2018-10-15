## About
This program takes in to sets of data. The first set movie information as well as the rating that movie received. The second set of data is just the movie data. This program cleans the movie data so that it only represents key words (Uses a list of common words to remove those) and no longer has puncuation. It then uses this data to predict ratings for the unrated movie in the second list. 

## How to Run
This program should be compiled with the following command:  
g++ -std=c++11 *.cpp  
The program accepts two arguments and should be run as follows:  
./a.out <fileWithRatings> <FileWithoutRatings>  
I have provided an example below
./a.out rawReviewRatings.txt rawReviews.txt  
  This will produce files with the clean movie data as well as a final file with ratings for the previously unrated file. 
