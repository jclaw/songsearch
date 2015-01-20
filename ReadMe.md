# ReadMe for COMP 15 HW6
## Song Search 
## Jackson Clawson

purpose:	To be able to store a database of songs quickly with the 
		ability for a user to search for a word and for the program to 
		return a top 10 list of the songs in which the word appears
files:
	alpha_only(.h, .cpp)	Contains the alpha only function available to 
				the Song class and the WordList class. 
	HashTable(.h, .cpp)	The HashTable class allows for the inserting 
				and finding of words
	Song(.h, .cpp)		The Song class is a model of a song containing 
				artist, title, and a vector of lyrics
	WordList(.h, .cpp)	The WordList class manages the reading in of 
				songs and the searching for words
	hashfunc(.h, .cpp)	Contains the function for finding the hash 
				value for a word
	main.cpp		The client file for SongSearch
	Makefile		The makefile

compile: use included Makefile

data structure:
All data for each song is inputted into an instance of a Song class. Every word 
is also hashed into the hashtable and the location of all the songs the word is 
in are stored in an array associated with the word.

algorithm:
insert (HashTable)	used linear probing when accounting for collisions
sort_songs (WordList)	used a modified insertion sort -- only finds the 
			correct location for the bottom element, the rest are 
			always sorted


worked with: Michael Seltzer, Dan Callahan

