#pragma once
#include "AI.h"

class UDK3 : public AI
{

private:
	Color savedColor = RED;
	//vector<int> allCardCount;

public:
	UDK3(int playerNumber);

	void onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor);

	void onOtherPlayerDraw(int playerNumber);
	//My methods
	void colorSelect(vector<Card> cardsInHand);
	int specialCardCount(vector<Card> cardsInHand);
	int highestPlayableSpecial(vector<Card> playableCards); //Returns index of card in playable hand
	int normalCardCount(vector<Card> cardsInHand);
	int highestPlayableNormal(vector<Card> playableCards); //Returns index of card in playable hand
	int minCardAmountsByPlayer(vector<int> cardAmountsByPlayer);

	//Specific special card playables
	int getPlayableReverse(vector<Card> playableCards);
	int getPlayableSkip(vector<Card> playableCards);
	int getPlayableWild(vector<Card> playableCards);
	int getPlayableDra4(vector<Card> playableCards);
	int getPlayableDra2(vector<Card> playableCards);
	
	//returns the index of the card to play
	int makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand, int direction);
	
	string getName();



	Color getNewColor();

};
