//
//  WordList.h
//  hw6
//
//  Created by Jackson Clawson on 11/28/14.
//  Copyright (c) 2014 Jackson Clawson. All rights reserved.
//

#ifndef __hw6__WordList__
#define __hw6__WordList__

#include <stdio.h>
#include "HashTable.h"
#include "Song.h"

// the location where new songs are inserted and evaluated
#define INSERT_INDEX 11

using namespace std;

class WordList {
public:
	WordList();
	~WordList();
	
	void search();

	// read the lyrics from a file
	void read_lyrics(const char * filename, bool show_progress );
	
	void deal_with_word(HashedItems *item, Song* new_song);
	
	void sort_songs(HashedItems *item, int index);
	
	void print_song(SongInfo *info, string word);

private:
	HashTable hashtable;
	std::vector<Song*> songlist;
};





#endif /* defined(__hw6__WordList__) */
