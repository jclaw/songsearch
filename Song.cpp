//
//  Song.cpp
//  hw6
//
//  Created by Jackson Clawson on 11/24/14.
//  Copyright (c) 2014 Jackson Clawson. All rights reserved.
//

#include "Song.h"
#include "alpha_only.h"

Song::Song() {
	artist = "";
	title = "";
}

string Song::get_artist() {
	return artist;
}

void Song::set_artist(string new_artist) {
	artist = new_artist;
}


string Song::get_title() {
	return title;
}

void Song::set_title(string new_title) {
	title = new_title;
}

void Song::insert_word(string word) {
	lyrics.push_back(word);
}

/*
 function: find_and_print
 does: finds a given word after a given starting index and then prints it out
 */
int Song::find_and_print(string word, int start_index){
	int i;

	for (i = start_index; i < lyrics.size(); i++) {
		if (alpha_only(lyrics[i]) == word) {
			// print out 5 before and 5 after
			for (int n = i - 5; n < i + 6; n++) {
				// if the index of the word minus 5 goes off
				// the beginning of the vector, start n at 0
				if (n < 0) {
					n = 0;
				}
				// otherwise, if n goes of the end of the
				// vector, get out of the loop
				else if (n >= lyrics.size()) {
					break;
				}
				cout << lyrics[n] << " ";
			}
			return i;
		}
	}
	//if the word was not found, return -1
	return -1;
}

void Song::debug_print() {
	for (int i = 0; i < lyrics.size(); i++) {
		cout << lyrics[i] << endl;
	}
}

