//
//  HashTable.cpp
//  hw6
//
//  Created by Jackson Clawson on 11/24/14.
//  Copyright (c) 2014 Jackson Clawson. All rights reserved.
//

#include <iostream>
#include "HashTable.h"
#include "hashfunc.h"

using namespace std;

// constructor
HashTable::HashTable() {
	HashedItems **new_table = new HashedItems*[HASH_INIT_CAPACITY];

	table_count = 0;
	table_capacity = HASH_INIT_CAPACITY;
	
	// set all elements of the table to NULL -- only create HashedItems
	// when inserting a new word
	for (int i = 0; i < HASH_INIT_CAPACITY; i++) {
		new_table[i] = NULL;
	}
	table = new_table;

}

// destructor
HashTable::~HashTable() {
	for (int i = 0; i < table_capacity; i++) {
		delete table[i];
	}
	delete [] table;
	
}

/*
 function: insert
 does: inserts a HashedItem into the hashtable by assigning the correct
 insertion index to a pointer to the HashedItem
 arguments: a pointer to a HashedItem
 returns: none
 */
void HashTable::insert(HashedItems *item) {
	// check load factor because we might need to expand
	if (load_factor() >= MAX_LOAD_FACTOR) {
		expand();
	}
	
	unsigned int hash_value = hash_string(item->alpha_only_word);
	int table_position;
	bool done_inserting = false;
	
	// linear probing
	int attempt = 0;
	while (!done_inserting) {
		table_position = (hash_value + attempt) % table_capacity;
		if (table[table_position] == NULL) {
			// insert into table
			table[table_position] = item;
			
			done_inserting = true;
			table_count++;
		}
		else {
			// collision
			attempt++;
		}
	}
}

/* 
 function: find
 does: returns a pointer to the HashedItem where the inputted word is,
 if the word is in the hashtable
 arguments: a string
 returns: a pointer to a HashedItem
 */
HashedItems* HashTable::find(string word) {
	unsigned int hash_value = hash_string(word);
	int table_position = 0;
	bool found = false;
	bool done_searching = false;
	int attempt = 0;
	
	while (!done_searching) {
		table_position = (hash_value + attempt) % table_capacity;
		
		if (table[table_position] == NULL) {
			done_searching = true;
		}
		else if (table[table_position]->alpha_only_word != word) {
			attempt++;
		}
		else {
			done_searching = true;
			found = true;
		}
	}
	if (found) {
		return table[table_position];
	}
	else {
		return NULL;
	}
}


/*
 function: expand
 does: expands the hashtable by creating a new hashtable and taking all of the
 HashedItems in the old hashtable and pointing the correct hashed values of
 the new hashtable to those HashedItems
 arguments: none
 returns: none
 */
void HashTable::expand() {
	HashedItems **new_table = new HashedItems*[table_capacity * 2];
	HashedItems **old_table = table;
	
	// initialize indeces new table to NULL
	for (int i = 0; i < table_capacity * 2; i++) {
		new_table[i] = NULL;
	}
	
	table = new_table;
	table_count = 0;
	table_capacity = table_capacity * 2;
	// rehash all old keys by walking the old table
	// only need to rehash if old_table[i] != NULL
	for (int i = 0; i < table_capacity / 2; i++) {
		if (old_table[i] != NULL) {
			// rehash
			insert(old_table[i]);
			old_table[i] = NULL;
		}
	}
	delete [] old_table;
}