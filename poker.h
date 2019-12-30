//
// Created by cloud on 10/6/2018.
//
#include <stdio.h>
#include <stdlib.h>
#ifndef F18P1_THOMAS_HOROWITZ_AND_MIGUEL_GOMEZ_POKER_H
#define F18P1_THOMAS_HOROWITZ_AND_MIGUEL_GOMEZ_POKER_H


struct _card{	//creates a card class that has a char suit and an unsigned int value 2-14
    unsigned int value;
    enum {
        H,C,S,D
    } suit;
};
typedef struct _card Card;


struct _player{ // creates a player with a hand object in it
    Card hand[2];
    int tier;
    int points;
    Card highCards[5];
    char* win;

};

typedef struct _player Player;

struct _table{	//creates a table object with a three card array
    Card cards[5];
};
typedef struct _table Table;

Card set_up_card(char *s);

void sortArray(Card A[], int num_elements);

#endif //F18P1_THOMAS_HOROWITZ_AND_MIGUEL_GOMEZ_POKER_H
