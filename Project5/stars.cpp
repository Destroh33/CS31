#include "utilities.h"
#include <iostream>
#include <cstring>
using namespace std;
const int MAXWORDS = 8000;
const char WORDFILENAME[] = "C:/CS31/Project5/smallwords.txt"; //file path for words file
int runOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum);
int main()
{
	char wordList[MAXWORDS][MAXWORDLEN + 1]; //word array
	int nWords = getWords(wordList, MAXWORDS, WORDFILENAME); //loads word array with words
	if (nWords < 1) {
		cout << "No words were loaded, so I can't play the game." << endl;
		return 1;
	}
	if (nWords > MAXWORDS) {
		return 1;
	}
	cout << "How many rounds do you want to play? ";
	int numRounds;
	cin >> numRounds;//taking in number of rounds wanted to play
	cin.ignore(10000, '\n');
	cout << endl;
	if (numRounds < 1) {
		cout << "The number of rounds must be positive." << endl;
		return 1;
	}
	double totalscore = 0.00;
	cout.setf(ios::fixed);
	cout.precision(2);
	int minimum = 100000000;
	int maximum = 0;
	for (int y = 1; y <= numRounds; y++) {//runs the game for the number of rounds chosen
		cout << "Round "<<y<<endl;
		int a = randInt(0, nWords - 1);
		cout << "The secret word is " << strlen(wordList[a]) << " letters long." << endl;//gets the secret word length and prints it
		int x = runOneRound(wordList, nWords, a);//runs a round
		if (x < 0) {
			return 1;
		}else if (x > 1) {
			cout << "You got it in " << x << " tries." << endl;//score>1
		}
		else if (x == 1) {//score =1
			cout << "You got it in 1 try." << endl;
		}
		if (x < minimum) {//determines if score for that round is the min or max
			minimum = x;
		}
		if (x > maximum) {
			maximum = x;
		}
		totalscore += x;//adds score to total score so that avg can be computed
		cout << "Average: "<<totalscore/y<<", minimum: "<<minimum<<", maximum: "<<maximum<<endl<<endl;
	}
}
int runOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum) {
	if (nWords < 1 || wordnum < 0 || wordnum >= nWords) {//failsafe for bad parameters
		return -1;
	}
	int guesses = 0;
	for (;;) {//runs until word is found
		cout << "Trial word: ";
		char trial[100];
		cin.getline(trial, 100);
		if (strlen(trial) > 6 || strlen(trial) < 4) {// if the word is too small or large
			cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
			continue;
		}
		bool lower = true;
		for (int y = 0; y < strlen(trial); y++) {
			if (!(islower(trial[y]) && isalpha(trial[y]))) {//if the word is not lowercase and alphabet chars only
				cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
				lower = false;
				break;
			}
		}
		if (!lower) {
			continue;

		}
		bool exists = false;
		for (int x = 0; x < MAXWORDS; x++) {//if the word exists in the list given
			if (strcmp(words[x], trial) == 0) {
				exists = true;
				break;
			}
		}
		if (!exists) {
			cout << "I don't know that word." << endl;
			continue;
		}
		int starCount = 0;
		int planetCount = 0;
		for (int x = 0; words[wordnum][x]!='\0'; x++) {//if both words have same char at same index, subtracting from planetCount and adding to starCount
			if (trial[x] == words[wordnum][x]) {//runs through trial word and adds to starcount each time the two words have the same char at the same index
				starCount++;
				trial[x] = '0';
				continue;
			}
			for (int y = 0; trial[y]!='\0'; y++) {
				if (trial[y] == words[wordnum][x] && y!=x && trial[y]!=words[wordnum][y]) {//runs through trial word and adds 1 planet each time there is a match between trial and secret word
					planetCount++;
					trial[y] = '0';
					break;

				}
			}
		}
		guesses++;//number of guesses goes up
		if (starCount == strlen(words[wordnum])) {//ends round, returns score if it is the same number of stars as letters of secret word
			return guesses;
		}
		else {
			cout << "Stars: " << starCount << ", Planets: " << planetCount << endl;
		}
	}
}