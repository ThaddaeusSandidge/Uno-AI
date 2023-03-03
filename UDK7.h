#pragma once
#include "AI.h"

class UDK7 : public AI
{

private:
	Color savedColor = RED;
	vector<vector<Card>> colorVec;
	vector<vector<Card>> playableColor;
	Color current;
	vector<vector<int>> playerFlags;
	int minPlayer;
	int count;
	int myNum;

public:
	UDK7(int playerNumber);

	void onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor);

	void onOtherPlayerDraw(int playerNumber);
	void colorSelect(vector<Card> cardsInHand, vector<int> cardAmountsByPlayer);

	//returns the index of the card to play
	int makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand, int direction);

	string getName();

	int getDra4(vector<Card> cardsInHand);
	int getWild(vector<Card> playableCards);
	int getWildCount(vector<Card> playableCards);
	int highestPlayable(vector<Card> playableCards);
	int highestPlayableColor(vector<Card> playableCards);
	int highestPlayableColor2(vector<Card> playableCards);
	int playBlack(vector<Card> playableCards);
	int playHighestNormal(vector<Card> playableCards);
	int playableCardsInColor(vector<Card> playableCards, Color c);
	int max(int x, int y);
	int minCardAmountsByPlayer(vector<int> cardAmountsByPlayer);
	int minCardAmountsByPlayerNumber(vector<int> cardAmountsByPlayer);
	bool handHasColor(vector<Card> cardsInHand);
	bool equalNumOfColors(int maxNum);
	Color getNewColor();

};

