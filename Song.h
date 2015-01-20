//
//  Song.h
//  hw6
//
//  Created by Jackson Clawson on 11/24/14.
//  Copyright (c) 2014 Jackson Clawson. All rights reserved.
//

#ifndef __hw6__Song__
#define __hw6__Song__

#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

class Song {
public:
	Song();
	string get_artist();
	void set_artist(string new_artist);
	string get_title();
	void set_title(string new_title);
	void insert_word(string word);
	// returns the index of the word
	int find_and_print(string word, int start_index);
	
	//debug
	void debug_print();
private:
	string artist;
	string title;
	vector<string> lyrics;
};


#endif /* defined(__hw6__Song__) */
