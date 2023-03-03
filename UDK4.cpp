#include "UDK4.h"

#include <iostream>
using namespace std;

UDK4::UDK4(int playerNumber) : AI(playerNumber)
{
	
	/* allCardCount.resize(60);
	for (int i = 0;i < allCardCount.size();i++)
	{
		allCardCount[i] = 7;
	} */
}

void UDK4::onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor)
{
	/* if (playerNumber > allCardCount.size())
	{
		vector<int> temp = allCardCount;
		allCardCount.resize(allCardCount.size() * 2);
		for (int i = 0;i < allCardCount.size();i++)
		{
			allCardCount[i] = 7;
		}
		for (int i = 0;i < temp.size();i++)
		{
			allCardCount[i] == temp[i];
		}
	} */
	//allCardCount[playerNumber] = allCardCount[playerNumber]

}

void UDK4::onOtherPlayerDraw(int playerNumber)
{

}

void UDK4::colorSelect(vector<Card> cardsInHand) //Color Select Variation, picks based on max point values not card num
{
	//Change saved color based on how many cards of each color in hand
	vector<int> colorSum;
	colorSum.resize(4);
	for (int i = 0; i < cardsInHand.size(); i++)
	{
		if (cardsInHand[i].getColor() == RED)
		{
			colorSum[0] += cardsInHand[i].getPoints();
		}
		if (cardsInHand[i].getColor() == BLUE)
		{
			colorSum[1] += cardsInHand[i].getPoints();
		}
		if (cardsInHand[i].getColor() == GREEN)
		{
			colorSum[2] += cardsInHand[i].getPoints();
		}
		if (cardsInHand[i].getColor() == YELLOW)
		{
			colorSum[3] += cardsInHand[i].getPoints();
		}
	}
	int maxColorPoints = 0;
	int maxColorIndex = -1;
	for (int i = 0;i < colorSum.size();i++)
	{
		if (colorSum[i] > maxColorPoints)
		{
			maxColorPoints = colorSum[i];
			maxColorIndex = i;
		}
	}

	if (maxColorIndex == 0) //Change saved color based on index of most cards in vector (index num corresponds to color num)
	{
		savedColor = RED;
	}
	if (maxColorIndex == 1)
	{
		savedColor = BLUE;
	}
	if (maxColorIndex == 2)
	{
		savedColor = GREEN;
	}
	if (maxColorIndex == 3)
	{
		savedColor = YELLOW;
	}

}
//Returns the amount of playable special cards, takes in playable card vector
int UDK4::specialCardCount(vector<Card> playableCards)
{
	int specialCardCount = 0;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getPoints() >= 10)
			specialCardCount++;
	}
	return specialCardCount;
}

//Returns the highest playable special card, takes in playable card vector (MUST CALL specialCardCount BEFORE!!!)
int UDK4::highestPlayableSpecial(vector<Card> playableCards) //Returns index of card in playable hand
{
	int toReturn = -1;
	int max = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getPoints() > max)
		{
			max = playableCards[i].getPoints();
			toReturn = i;
		}
	}
	return toReturn;
}

//Returns the amount of playable normal cards, takes in playable card vector
int UDK4::normalCardCount(vector<Card> playableCards)
{
	int normalCardCount = 0;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getPoints() <= 10)
			normalCardCount++;
	}
	return normalCardCount;
}

//Returns the highest playable normal card, takes in playable card vector (MUST CALL normalCardCount BEFORE!!!)
int UDK4::highestPlayableNormal(vector<Card> playableCards) //Returns index of card in playable hand
{
	int toReturn = -1;
	int max = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getPoints() < 10)
		{
			if (playableCards[i].getPoints() > max)
			{
				max = playableCards[i].getPoints();
				toReturn = i;
			}
		}

	}
	return toReturn;
}

int UDK4::minCardAmountsByPlayer(vector<int> cardAmountsByPlayer) //Lowest count of cards off players in game, determine whether to cash out on specials
{
	int min = 99;
	for (int i = 0; i < cardAmountsByPlayer.size(); i++)
	{
		if (cardAmountsByPlayer[i] < min)
		{
			if (i != myPlayerNumber)
			{
				min = cardAmountsByPlayer[i];
			}
		}
	}
	return min;
}

int UDK4::nextPlayerCardAmount(vector<int> cardAmountsByPlayer, int direction)
{
	int nextPlayerNum = -1;
	int myNum = myPlayerNumber;
	if (direction == 1)
	{
		if (myNum != cardAmountsByPlayer.size() - 1)
		{
			nextPlayerNum = myNum + 1;
		}
		else
			nextPlayerNum = 0;
	}
	if (direction == -1)
	{
		if (myNum != 0)
		{
			nextPlayerNum = myNum - 1;
		}
		else
			nextPlayerNum = cardAmountsByPlayer.size() - 1;
	}
	return cardAmountsByPlayer[nextPlayerNum];
}


//Get index of playable specials
int UDK4::getPlayableSkip(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getNumber() == 10)
			index = i;
	}
	return index;
}
int UDK4::getPlayableDra2(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getNumber() == 11)
			index = i;
	}
	return index;
}
int UDK4::getPlayableReverse(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getNumber() == 12)
			index = i;
	}
	return index;
}
int UDK4::getPlayableWild(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if ((playableCards[i].getColor() == BLACK) && (playableCards[i].getNumber() == 0))
			index = i;
	}
	return index;
}

int UDK4::getPlayableDra4(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if ((playableCards[i].getColor() == BLACK) && (playableCards[i].getNumber() == 1))
			index = i;
	}
	return index;
}



//returns the index of the card to play
int UDK4::makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand, int direction)
{
	/*
	for (int i = 0; i < cardAmountsByPlayer.size(); i++)
	{
		cout << "Player " << i << ": " << cardAmountsByPlayer[i] << "\n";
	}  */



	vector<Card> cards = getPlayableCardsInHand(justPlayed, choosenCardColor, cardsInHand);

	if (cards.size() == 0)
	{
		return -1; //draw
	}

	//special card key
	//reverse = 12, skip = 10, and draw2 = 11 of any of red/blue/green/yellow.
	//wild is black 0, draw4 is black 1


	savedColor = YELLOW;
	colorSelect(cardsInHand);

	int playableIndex = -1;
	if (cardsInHand.size()-minCardAmountsByPlayer(cardAmountsByPlayer) > 0)
	{
		if (getPlayableReverse(cards) != -1)
			playableIndex = getPlayableReverse(cards);
		else if (getPlayableSkip(cards) != -1)
			playableIndex = getPlayableSkip(cards);
		else if (getPlayableDra2(cards) != -1)
			playableIndex = getPlayableDra2(cards);
		else if (highestPlayableNormal(cards) != -1)
			playableIndex = highestPlayableNormal(cards);
		else if (getPlayableWild(cards) != -1)
			playableIndex = getPlayableWild(cards);
		else
			playableIndex = getPlayableDra4(cards);
	}

	else if (specialCardCount(cards) >= minCardAmountsByPlayer(cardAmountsByPlayer))
	{
		if (getPlayableReverse(cards) != -1)
			playableIndex = getPlayableReverse(cards);
		else if (getPlayableWild(cards) != -1)
			playableIndex = getPlayableWild(cards);
		else if (getPlayableSkip(cards) != -1)
			playableIndex = getPlayableSkip(cards);
		else if (getPlayableDra4(cards) != -1)
			playableIndex = getPlayableDra4(cards);
		else if (getPlayableDra2(cards) != -1)
			playableIndex = getPlayableDra2(cards);
	}
	else if (nextPlayerCardAmount(cardAmountsByPlayer, direction) < 3)
	{
		if (getPlayableDra4(cards) != -1)
			playableIndex = getPlayableDra4(cards);
		else if (getPlayableDra2(cards) != -1)
			playableIndex = getPlayableDra2(cards);
		else if (getPlayableSkip(cards) != -1)
			playableIndex = getPlayableSkip(cards);
		else if (getPlayableReverse(cards) != -1)
			playableIndex = getPlayableReverse(cards);
		if (highestPlayableNormal(cards) != -1)
			playableIndex = highestPlayableNormal(cards);
		else
			playableIndex = highestPlayableSpecial(cards);
	}
	else if ((minCardAmountsByPlayer(cardAmountsByPlayer) <= 2))
	{
		if (highestPlayableSpecial(cards) != -1)
			playableIndex = highestPlayableSpecial(cards);
		else
			playableIndex = highestPlayableNormal(cards);
	}
	else
	{
		if (highestPlayableNormal(cards) != -1)
			playableIndex = highestPlayableNormal(cards);
		else
		{
			if (getPlayableDra2(cards) != -1)
				playableIndex = getPlayableDra2(cards);
			else if (getPlayableSkip(cards) != -1)
				playableIndex = getPlayableSkip(cards);
			else if (getPlayableReverse(cards) != -1)
				playableIndex = getPlayableReverse(cards);
			else if (getPlayableWild(cards) != -1)
				playableIndex = getPlayableWild(cards);
			else if (getPlayableDra4(cards) != -1)
				playableIndex = getPlayableDra4(cards);
		}

	}
	if (playableIndex == -1)
		cout << "it didnt work mf";


	Card c = cards[playableIndex];
	for (int i = 0; i < cardsInHand.size(); i++)
	{
		if (c == cardsInHand[i])
		{
			return i;
		}
	}

	//should not get here in my AI???
	cerr << "bbaaaad happeeeened\n";
	return -1;
}

string UDK4::getName()
{
	return "UDK4";
}



Color UDK4::getNewColor()
{
	return savedColor;
}