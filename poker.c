#include "poker.h"
/**
 * Who worked on what:
 * ALL functions were planned out together
 * 100% of the evaluating hands, comparing player hands and deciding an algorithm for picking a winner
 * Thomas worked on the set-up game
 * Miguel worked on the sort, contains, output functions
 */
void sortArray(Card A[], int num_elements) {

	int n, newn, i;
	Card temp;
	n = num_elements;
	do {
		newn = 0;
		for(i = 1; i <= n-1; i++) {
			if(A[i-1].value < A[i].value) {
				temp = A[i-1]; A[i-1] = A[i];
				A[i] = temp;
				newn = i;
			}
		}
		n = newn;
	} while (n != 0);
}
int contains(Card *arr, int value, int size){
    for (int i = 0; i < size; ++i) {
        if(arr[i].value == value){
            return  1;
        }
    }
    return 0;
}
int containsCard(Card *arr, int value, int Suit, int size){
    for (int i = 0; i < size; ++i) {
        if(arr[i].value == value && arr[i].suit == Suit){
            return  1;
        }
    }
    return 0;
}

Card findCard(Card *arr, int value, int Suit, int size){
    for (int i = 0; i < size; ++i) {
        if(arr[i].value == value && arr[i].suit == Suit){
            return  arr[i];
        }
    }
    Card error;
    return error;
}
int findDomSuit(Card *allCards, int size){
    int numHearts = 0;
    int numClubs = 0;
    int numSpades = 0;
    int numDiamonds = 0;
    for(int i = 0; i < size; i++){
        if(allCards[i].suit  == H){
            numHearts++;
        }
        if(allCards[i].suit == C){
            numClubs++;
        }
        if(allCards[i].suit  == D){
            numDiamonds++;
        }
        if(allCards[i].suit == S){
            numSpades++;
        }

    }
    int A[4] = {numClubs, numDiamonds, numSpades, numHearts};
    //sort array
    int n, newn, i;
    int temp;
    n = 4;
    do {
        newn = 0;
        for(i = 1; i <= n-1; i++) {
            if(A[i-1] < A[i]) {
                temp = A[i-1]; A[i-1] = A[i];
                A[i] = temp;
                newn = i;
            }
        }
        n = newn;
    } while (n != 0);
    if(A[0] == numClubs){
        return C;
    }
    if(A[0] == numDiamonds){
        return D;
    }
    if(A[0] == numHearts){
        return H;
    }
    if(A[0] == numSpades){
        return S;
    }
    return -1;
}

void set_up(char *game, Player *players, Table *table){

	char str_arr[11][3];

	//stores all the cards as strings in str_arr
	sscanf(game, "%s %s %s %s %s %s %s %s %s %s %s", str_arr[0], str_arr[1], str_arr[2], str_arr[3], str_arr[4], str_arr[5], str_arr[6], str_arr[7], str_arr[8], str_arr[9], str_arr[10]);

	//sets up player's hands
	players[0].hand[0] = set_up_card(str_arr[0]);
	players[0].hand[1] = set_up_card(str_arr[1]);
	players[1].hand[0] = set_up_card(str_arr[2]);
	players[1].hand[1] = set_up_card(str_arr[3]);
	players[2].hand[0] = set_up_card(str_arr[4]);
	players[2].hand[1] = set_up_card(str_arr[5]);

	//sets up the table
	table->cards[0] = set_up_card(str_arr[6]);
	table->cards[1] = set_up_card(str_arr[7]);
	table->cards[2] = set_up_card(str_arr[8]);
	table->cards[3] = set_up_card(str_arr[9]);
	table->cards[4] = set_up_card(str_arr[10]);

}

Card set_up_card(char *s){
	Card card;

	switch(s[0]){
		case 'A':
			card.value = 14;
			break;
		case 'K':
			card.value = 13;
			break;
		case 'Q':
			card.value = 12;
			break;
		case 'J':
			card.value = 11;
			break;
		case 'T':
			card.value = 10;
			break;
		case '9':
			card.value = 9;
			break;
		case '8':
			card.value = 8;
			break;
		case '7':
			card.value = 7;
			break;
		case '6':
			card.value = 6;
			break;
		case '5':
			card.value = 5;
			break;
		case '4':
			card.value = 4;
			break;
		case '3':
			card.value = 3;
			break;
		case '2':
			card.value = 2;
			break;
	}

	switch(s[1]){
		case 'H':
			card.suit = H;
			break;
		case 'D':
			card.suit = D;
			break;
		case 'C':
			card.suit = C;
			break;
		case 'S':
			card.suit = S;
			break;
	}
	return card;
}

void game_printer(Player *players, Table table){
	for(int i = 0; i < 3; i++){
		printf("Player %d hand: %u, ", i+1, players[i].hand[0].value);
		printf("%u\n", players[i].hand[1].value);
	}
	printf("Table cards: %u, %u, %u, %u, %u\n", table.cards[0].value, table.cards[1].value, table.cards[2].value, table.cards[3].value, table.cards[4].value);
}

int checkStraight(Player *player, Card allCards[7]){
	/**
   * Straight Ties get settled by the numerical value of the highest card in the Straight
   */

	int index = 0;
	//Ints below are for checking straight A2345
	int hasAce = 0;
	int hasTwo = 0;
	int hasThree = 0;
	int hasFour = 0;
	int hasFive = 0;

	Card aceLow[5]; // ALL cards in A2345 Straight
	while(index < 7){
		//If it has an ace, treat it as 1, and put it at the end (lowest card)
		if(allCards[index].value == 14){
			hasAce = 1;
			aceLow[4] = allCards[index];
		}
		if(allCards[index].value == 2){
			hasTwo = 1;
			aceLow[3] = allCards[index];
		}
		if(allCards[index].value == 3){
			hasThree = 1;
			aceLow[2] = allCards[index];
		}
		if(allCards[index].value == 4){
			hasFour = 1;
			aceLow[1] = allCards[index];
		}
		if(allCards[index].value == 5){
			hasFive = 1;
			aceLow[0] = allCards[index];
		}
		index++;

	}

	/**
    * This Checks the Special Case of A2345
    */

	if(hasAce == 1 && hasTwo == 1 && hasThree == 1 && hasFour == 1 && hasFive == 1){
		//player has a straight
		if(aceLow[0].suit == aceLow[4].suit && aceLow[1].suit == aceLow[4].suit && aceLow[2].suit == aceLow[4].suit && aceLow[3].suit == aceLow[4].suit){
			//player has a straight flush
			//STRAIGHT FLUSH = TIER 1
			player->tier = 1;
			player->points = 5;
			return 2;
		}
		//STRAIGHT = TIER 5
		player->tier = 5;
		player->points = 5;
		return 1;
	}
	index = 0;

	/***************************************************************
	* This Checks any normal Straight AND Straight Flush
	*/
	Card flush[5];
	flush[4].value = 0;
	int domSuit = findDomSuit(allCards, 7);
	while(index < 3){
	    if(allCards[index].suit == domSuit){
	        flush[0] = allCards[index];
	    }
	    if(contains(allCards, allCards[index].value-1, 7) ){
            if(containsCard(allCards, allCards[index].value-1, domSuit, 7)) { /****/
                flush[1] = findCard(allCards, allCards[index].value - 1, domSuit, 7);
            }
            if(contains(allCards, allCards[index].value-2, 7)){
                if(containsCard(allCards, allCards[index].value -2, domSuit, 7)) { /****/
                    flush[2] = findCard(allCards, allCards[index].value - 2, domSuit, 7);
                }
                if(contains(allCards, allCards[index].value-3, 7)){
                    if(containsCard(allCards, allCards[index].value-3, domSuit, 7)) { /****/
                        flush[3] = findCard(allCards, allCards[index].value - 3, domSuit, 7);
                    }
                    if(contains(allCards, allCards[index].value-4, 7)){
                        if(containsCard(allCards, allCards[index].value-4, domSuit, 7)) { /****/
                            flush[4] = findCard(allCards, allCards[index].value - 4, domSuit, 7);
                            player->tier = 1;
                            player->points = flush[0].value; //Highest card in straight flush
                            return 2;
                        }
                        /**
                         * straight
                         */
                        player->tier = 5;
                        player->points = allCards[index].value;
                        return 1;


                    }
                }
            }
	    }
	    index++;
	}
	return 0;
}

int checkFlush(Player *player, Card allCards[7]){
	/**
	 * Flush Ties get settled by comparing each card in the flush, ordered descendingly (To find the highest flush)
	 */

	Card hearts[5];
	hearts[4].value = 0;
	int hi = 0;
	Card clubs[5];
	clubs[4].value = 0;
	int ci = 0;
	Card diamonds[5];
	diamonds[4].value = 0;
	int di = 0;
	Card spades[5];
	spades[4].value = 0;
	int si = 0;
	// FLUSH = TIER 4
	for(int i = 0; i < 7; i++){

		if (allCards[i].suit == H && hi < 5){
			hearts[hi] = allCards[i];
			hi++;
		}
		if (allCards[i].suit == C && ci < 5){
			clubs[ci] = allCards[i];
			ci++;
		}
		if (allCards[i].suit == D && di < 5){
			diamonds[di] = allCards[i];
			di++;
		}
		if (allCards[i].suit == S && si < 5){
			spades[si] = allCards[i];
			si++;
		}
	}
	if(hearts[4].value != 0){
		//Flush of Hearts
		player->tier = 4;
		for(int i = 0; i < 5; i++){
			player->highCards[i] = hearts[i];
		}
		return 1;
	}
	if(clubs[4].value != 0){
		//Flush of Clubs
		player->tier = 4;
		for(int i = 0; i < 5; i++){
			player->highCards[i] = clubs[i];
		}
		return 1;
	}
	//Flush of Clubs
	if(diamonds[4].value != 0){
		player->tier = 4;
		for(int i = 0; i < 5; i++){
			player->highCards[i] = diamonds[i];
		}
		return 1;
	}
	//Flush of spades
	if(spades[4].value != 0){
		player->tier = 4;
		for(int i = 0; i < 5; i++){
			player->highCards[i] = spades[i];
		}
		return 1;
	}

	return 0;
}

int checkFourOfAKind(Player *player, Card allCards[7]){
	/**
     * Four of a kind ties are settled by the value of the card in the four of a kind.
     * The next highest card is stored in the hand as well, but is not used
    */

	int index = 0;
	while(index < 4){
		if(allCards[index].value == allCards[index+1].value){
			if(allCards[index].value == allCards[index+2].value){
				if(allCards[index].value == allCards[index+3].value){
					player->tier = 2; // FOUR OF A KIND = TIER 2
					player->points = allCards[index].value; // HIGHEST 4 OF A KIND WINS
					return 1;
				}
			}
		}

		index++;
	}
	return 0;
}

int checkFullHouse(Player *player, Card allCards[7]){
	/**
     * Full house ties are settled by comparing the value of the three of a kind.
     * The pair is stored in the hand as well, but not used.
     */
	int index = 0;
	int oi = 0;//index of other
	int index2 = 0;//index for searching other 4 cards
	int value = 0;
	Card other[4];
	while(index < 5){
		if(allCards[index].value == allCards[index+1].value){
			if(allCards[index].value == allCards[index+2].value){
				value = allCards[index].value; //Value is the value of the 3 of a kind
				//player has three of a kind
				for(int i = 0; i < 7; i++){
					if(allCards[i].value != allCards[index].value){
						other[oi] = allCards[i];
						oi++;
					}
				}
				while(index2 < 3){
					if(other[index2].value == other[index2 +1].value){
						//player has full house
						player->tier = 3; //FULL HOUSE = TIER 3
						player->points = value;
						return 1;
					}
					index2++;
				}
			}
		}
		index++;
	}
	return 0;

}

int checkThreeOfAKind(Player *player, Card allCards[7]){
	/**
    * Three of a Kind ties are settled by the value of the card.
    * The other two cards are stored in the hand, but not used.
    */
	int index = 0;
	while(index < 5){
		if(allCards[index].value == allCards[index+1].value){
			if(allCards[index].value == allCards[index+2].value){
				player->tier = 6; //THREE OF A KIND = TIER 6
				player->points = allCards[index].value;
				return 1;
			}
		}
		index++;
	}
	return 0;
}

int checkTwoPair(Player *player, Card allCards[7]){
	/**
     * Two pair ties are stored by comparing the highest pair first, then the second pair, then the next high card.
     */
	int index = 0;
	int oi = 0;
	int index2 = 0;
	Card other[5];
	Card p1;
	while(index < 6){
		//check for one pair
		if(allCards[index].value == allCards[index+1].value){
			//player has two of a kind
			p1 = allCards[index];
			for(int i = 0; i < 7; i++){
				if(allCards[i].value != allCards[index].value){
					other[oi] = allCards[i]; //other[] is automatically sorted
					oi++;
				}

			}
			//check, second pair
			player->highCards[4].value = 0;
			while(index2 < 4){
				if(other[index2].value == other[index2 +1].value){
					//player has two pair
					player->tier = 7; //TWO PAIR = TIER 7
					//set the highCards array to be [high pair 1, high pair 2, high card]
					if(p1.value > other[index2].value){
						player->highCards[0] = p1;
						player->highCards[1] = p1;
						player->highCards[2] = other[index2];
						player->highCards[3] = other[index2];

					}
					else{
						player->highCards[0] = other[index2];
						player->highCards[1] = other[index2];
						player->highCards[2] = p1;
						player->highCards[3] = p1;

					}
					if(index2+1 < 5 && player->highCards[4].value == 0){
					    player->highCards[4] = other[index2+1];
					}
					return 1; //player has 2 pair
				}
				if(player->highCards[4].value == 0){
				    player->highCards[4] = other[index2]; //Current card isnt a pair, but is high. Add it to last
				}
				index2++;
			}
		}
		index++;
	}
    player->highCards[4].value = 0;
	return 0;
}

int checkPair(Player *player, Card allCards[7]){
	/**
	 * same as pair, but with more high cards
	 */
	int index = 0;
	Card other[5]; // array that will have all cards EXCEPT the pair
	int oi = 0; // index of other for adding cards
	while(index < 6){
		if(allCards[index].value == allCards[index+1].value){
			//player has two of a kind
			player->tier = 8; //ONE PAIR = TIER 8
			//generate array of all cards without pair
			for(int i = 0; i < 7; i++){
				if(allCards[i].value != allCards[index].value){
					other[oi] = allCards[i]; //other[] is automatically sorted
					oi++;
				}
			}
			player->highCards[0] = allCards[index];
			player->highCards[1] = allCards[index+1];
			player->highCards[2] = other[0];
			player->highCards[3] = other[1];
			player->highCards[4] = other[2];

			return 1;//player has one pair
		}
		index++;
	}

	return 0;
}

void evaluate(Player *player, Table table){
	//Evaluates best possible hand for current player
	/** THIS REQUIRES THE PLAYERS HANDS TO BE SORTED BY VALUE IN DESCENDING ORDER
	 * Tier 1 - Straight Flush; Highest Card in Flush wins (COMPARE VALUE)
	 * Tier 2 - 4 of a Kind; Value of 4 of a Kind's Card wins (COMPARE VALUE)
	 * Tier 3 - Full House; Value of the 3 of a Kind's Card Wins (COMPARE VALUE)
	 * Tier 4 - Flush; Highest Card wins in flush (COMPARE ARRAY OF BEST HAND)
	 * Tier 5 - Straight; Highest Card in Straight wins (COMPARE VALUE)
	 * Tier 6 - 3 of a Kind; Value of 3 of a Kind's Card wins
	 * Tier 7 - Two Pair; Set winning hands array to be [p1, p1, p2, p2, HK] (COMPARE ARRAY OF BEST HAND)
	 * Tier 8 - Pair; Same as 2 Pair, [p1, p1, HK1, HK2, HK3] (COMPARE ARRAY OF BEST HAND)
	 * Tier 9 - High Card; Set Array of highest 5 (COMPARE ARRAY OF BEST HAND)
	 */
	//Array of all cards
	Card allCards[7] = {player->hand[0], player->hand[1], table.cards[0], table.cards[1],
						table.cards[2], table.cards[3], table.cards[4]};
	sortArray(allCards, 7);

	if(checkStraight(player, allCards)== 2){
		return; //Checking straight flush
	}
	if(checkFourOfAKind(player, allCards) != 0){
		return;
	}
	if(checkFullHouse(player, allCards) != 0){
		return;
	}
	if(checkFlush(player, allCards) != 0){
		return;
	}
	if(checkStraight(player, allCards) != 0){
		return;
	}
	if(checkThreeOfAKind(player, allCards) != 0){
		return;
	}
	if(checkTwoPair(player, allCards) != 0){
		return;
	}
	if(checkPair(player, allCards) != 0){
		return;
	}

	//HIGH CARD = TIER 9
	player->tier = 9;
	for(int i = 0; i < 5; i++){
		//SET ARRAY OF HIGHEST 5 CARDS
		player->highCards[i] = allCards[i];
	}

}
Player compare(Player p1, Player p2){
	/**
	* Compares any two given players based on their rank first, then value of rank OR hand itself
	* Returns the winner
	*/
	//player 1 has a better hand tier
	if(p1.tier < p2.tier){
		return  p1;
	}
	//player 2 has a better hand tier
	if(p2.tier < p1.tier){
		return  p2;
	}
	//Both Players Tier 1, 2, 3, 5, or 6
	if(p1.tier == 1 || p1.tier == 2 || p1.tier == 3 || p1.tier == 5 || p1.tier == 6){
		//Compare points
		if(p1.points > p2.points){
			return p1;
		}
		return p2;
	}
	//Both Players must be tier 4, 7, 8, or 9
	//Compare player.HighCards[]
	for (int i = 0; i < 5; i++) {
		if(p1.highCards[i].value > p2.highCards[i].value){
			return p1;
		}
		if(p2.highCards[i].value > p1.highCards[i].value){
			return p2;
		}
	}
	return p1;

}

Player *chooseWinner(Player *players, Table table, Player *winner){

	for(int i = 0; i< 3; i++){
		//Set properties of each players hand
		evaluate(&(players[i]), table);
	}
	//find winner
	*winner = compare(players[0], players[1]);

	*winner = compare(*winner, players[2]);
	printf("%s\n", winner->win);
	printf("Tiers: P1- %d, P2- %d, P3- %d\n",players[0].tier, players[1].tier, players[2].tier);
	return winner;

}

int main(int x, char **y){
	//set up a bunch of stuff needed to save the values of the input file
	Player player1;
	player1.win = "Player 1 wins.";
	Player player2;
	player2.win = "Player 2 wins.";
	Player player3;
	player3.win = "Player 3 wins.";
	Player players[3] = {player1, player2, player3};
	Table table;
	Player winner;
	FILE *fp = fopen(y[1], "r");
	FILE *output = fopen("Output.txt", "w");

	char game[256];
	int count = 1;

	while(fgets(game, 255, fp)){
		printf("*******************\nHand: %d\n", count++);
		set_up(game, players, &table);
		game_printer(players, table);
		chooseWinner(players, table, &winner);
		fprintf(output, "%s\n", winner.win);
	}

	fclose(output);
	fclose(fp);
	return 0;
}
