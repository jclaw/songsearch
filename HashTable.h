//
//  HashTable.h
//  hw6
//
//  Created by Jackson Clawson on 11/24/14.
//  Copyright (c) 2014 Jackson Clawson. All rights reserved.
//

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "Song.h"
#include<vector>
#include<string>

#define MAX_LOAD_FACTOR 0.7
#define HASH_INIT_CAPACITY 5
#define ARRAY_CAPACITY 11

struct SongInfo  {
	Song* song; // should be a pointer to a song
	int wordCount;
	// constructor
	SongInfo() {
		song = NULL;
		wordCount = 0;
	}
};

struct HashedItems {
	string alpha_only_word;
	int songCount;
	// every HashedItem has a full list of SongInfos
	SongInfo songs[ARRAY_CAPACITY];
	// constructor
	HashedItems() {
		alpha_only_word = "";
		songCount = 0;
	}
};

class HashTable {
public:
	HashTable();
	~HashTable();
	
	void insert(HashedItems *item);
	
	HashedItems* find(std::string word);
	
	float load_factor() { return (float)table_count / table_capacity; }
	
private:
	HashedItems **table;
	void expand();
	int table_capacity;
	int table_count;
};



#endif /* HASHTABLE_H_ */
