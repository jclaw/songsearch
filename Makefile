#
# Makefile for SongSearch, Assignment 6
#
CXX = clang++
FLAGS = -Wall -g3

songsearch: hashfunc.cpp hashfunc.h Song.cpp Song.h \
			HashTable.cpp HashTable.h WordList.cpp \
			WordList.h alpha_only.cpp alpha_only.h \
			main.cpp
	${CXX} ${FLAGS} -o songsearch hashfunc.cpp Song.cpp \
			HashTable.cpp WordList.cpp alpha_only.cpp \
			main.cpp
	
clean:
	rm -f songsearch

provide_design:
	provide comp15 hw6_design songsearch_design.txt

provide:
	provide comp15 hw6 hashfunc.cpp hashfunc.h Song.cpp Song.h \
			HashTable.cpp HashTable.h WordList.cpp \
			WordList.h alpha_only.cpp alpha_only.h \
			ReadMe.md Makefile main.cpp

