/*
 * main.cpp
 *
 */
#include <iostream>
#include <sstream>
#include <fstream>

#include "WordList.h"
#include "Song.h"

using namespace std;

int main(int argc, char *argv[])
{
	string filename;
	WordList wordlist;
	string word;
	
	if (argc == 2) { // if there is a filename on the command line
		wordlist.read_lyrics(argv[1],true);
	}
	else { // use a pre-defined filename
		filename = "2316Songs.txt";
		//filename = "lyrics_fulldb.txt";
	        wordlist.read_lyrics(filename.c_str(),true);
	}

        wordlist.search();

        return 0;
}
