//
//  WordList.cpp
//  hw6
//
//  Created by Jackson Clawson on 11/28/14.
//  Copyright (c) 2014 Jackson Clawson. All rights reserved.
//

#include "WordList.h"
#include "alpha_only.h"
#include <iostream>
#include <sstream>
#include <fstream>

WordList::WordList() {
	
}

WordList::~WordList() {
	
	// delete songs from songlist
	for (int i = 0; i < songlist.size(); i++) {
		
		delete songlist[i];
	}
}

void WordList::search() {
	
	string user_word;

	while (cin >> user_word && user_word != "<BREAK>") {
		
		user_word = alpha_only(user_word);
		HashedItems *item = hashtable.find(user_word);
		
		
		if (item != NULL) {
			for (int i = 0; i < item->songCount; i++) {
				if (i < 10) {
					print_song(&item->songs[i], user_word);
				}
			}
		}
		cout << "<END OF REPORT>" << endl;
	}
}


//
// read_lyrics
//   purpose: read in song data from a disk file
//   arguments: the name of the file, bool to ask for progress status
//   returns: nothing
//   does: calls a function each time a word is found
//
void WordList::read_lyrics(const char * filename, bool show_progress)
{
	ifstream in(filename);			// creates an input stream
	int song_count = 0;			// for progress indicator
	string artist, title, word, alpha_word;
	HashedItems *item;
	
	
	// -- While more data to read...
	while ( ! in.eof() )
	{
		// create new song
		Song *new_song = new Song();
		// cout << "created: " << new_song << endl;
		
		// -- First line is the artist
		getline(in, artist);
		if (in.fail()) {
			delete new_song;
			break;
		}
		new_song->set_artist(artist);
		
		// -- Second line is the title
		getline(in, title);
		if (in.fail()) break;
		new_song->set_title(title);
		
		if ( show_progress )
		{
			song_count++;
			if (song_count % 10000 == 0) {
				cout << "At "       << song_count <<
				" Artist: " << artist     <<
				" Title:"   << title << endl;
			}
		}
		// -- Then read all words until we hit the
		// -- special <BREAK> token
		while ( in >> word && word != "<BREAK>" ){
			//
			// -- Found a word
			
			// put word in lyrics vector of current song
			new_song->insert_word(word);
			
			alpha_word = alpha_only(word);
			
			// find the location in the hashtable where the word
			// should go
			item = hashtable.find(alpha_word);
			
			// update hashtable
			if (item == NULL) {
				// create a new array and set it equal
				// to temp
				item = new HashedItems();
				// add song to the first position
				item->songs[0].song = new_song;
				item->songs[0].wordCount = 1;
				
				//update other data of item
				item->alpha_only_word = alpha_word;
				item->songCount = 1;
				// insert
				hashtable.insert(item);
			}
			else {
				deal_with_word(item, new_song);
			}
		}
		// Song is done -- put it into vector of songs
		songlist.push_back(new_song);
		
		
		// -- Important: skip the newline left behind
		in.ignore();
	}
}

/*
 function: deal_with_word
 purpose: deals with the case that the word is found in the hashtable
 arguments: a pointer to a HashedItem and a pointer to a Song
 returns: none
 */
void WordList::deal_with_word(HashedItems *item, Song* new_song) {
	bool songFound = false;
	int i, song_index;
	// see if the song is already in the list,
	// from end to beginning
	songFound = false;
	song_index = -1; // if song_index is -1, it
	// shouldn't be used
	i = item->songCount - 1;
	
	// determine if the song is in the top 10 list
	while (!songFound && i >= 0) {
		if (item->songs[i].song == new_song) {
			item->songs[i].wordCount++;
			songFound = true;
			song_index = i;
		}
		i--;
	}
	
	// if the song is in the list and the list is
	// longer than 1, sort
	if (songFound) {
		if (item->songCount > 1) {
			sort_songs(item, song_index);
		}
	}
	// if the song is not in the list, add it to
	// the end -- no need to sort
	else {
		// add song after the last song
		if (item->songCount < 11) {
			item->songs[item->songCount]
			.song = new_song;
			item->songs[item->songCount]
			.wordCount = 1;
			item->songCount++;
		}
		// otherwise, array is full so insert
		// song at end of list
		else {
			item->songs[ARRAY_CAPACITY - 1]
			.song = new_song;
			item->songs[ARRAY_CAPACITY - 1]
			.wordCount = 1;
		}
	}
}

/*
 function: sort_songs
 purpose: sorts the top 10 list of the passed HashedItem
 arguments: a pointer to HashedItems, an index
 returns: none
 */
void WordList::sort_songs(HashedItems *item, int index) {
	
	if (item->songs == NULL) return;
	
	// store the song that was modified
	SongInfo curr = item->songs[index];
	int placeholder = index;
	
	// sort, starting at one above the modified song
	for (int i = index - 1; i >= 0; i--) {
		if (curr.wordCount > item->songs[i].wordCount) {
			item->songs[i+1] = item->songs[i];
			placeholder = i;
		}
	}
	// if any readjusting happened, reinsert the stored item
	if (placeholder != index)
		item->songs[placeholder] = curr;
}

/*
 function: print_song
 purpose: prints out the occurences of the word in the given song
 arguments: a pointer to a SongInfo, a string
 returns: none
 */
void WordList::print_song(SongInfo *info, string word) {
	int index = 0;
	for (int i = 0; i < info->wordCount; i++) {
		cout << "Title: " << info->song->get_title() << endl
		<< "Artist: " << info->song->get_artist() << endl
		<< "Context: ";
		index = info->song->find_and_print(word, index) + 1;
		cout << endl << endl;
	}
	
}
