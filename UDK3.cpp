#include "UDK3.h"

#include <iostream>
using namespace std;

UDK3::UDK3(int playerNumber) : AI(playerNumber)
{
	/* allCardCount.resize(60);
	for (int i = 0;i < allCardCount.size();i++)
	{
		allCardCount[i] = 7;
	} */
}

void UDK3::onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor)
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

void UDK3::onOtherPlayerDraw(int playerNumber)
{

}

void UDK3::colorSelect(vector<Card> cardsInHand)
{
	//Change saved color based on how many cards of each color in hand
	vector<vector<Card>> colorVec;
	colorVec.resize(6);
	for (int i = 0;i < colorVec.size();i++)
	{
		colorVec[i].resize(0);
	}

	for (int i = 0; i < cardsInHand.size(); i++)
	{
		colorVec.at(cardsInHand[i].getColor()).push_back(cardsInHand[i]);
	}
	int maxColorSize = 0;
	int maxColorIndex = -1;
	for (int i = 0; i < colorVec.size(); i++)
	{
		if (colorVec[i].size() > maxColorSize)
		{
			maxColorSize = colorVec[i].size();
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
int UDK3::specialCardCount(vector<Card> playableCards)
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
int UDK3::highestPlayableSpecial(vector<Card> playableCards) //Returns index of card in playable hand
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
int UDK3::normalCardCount(vector<Card> playableCards)
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
int UDK3::highestPlayableNormal(vector<Card> playableCards) //Returns index of card in playable hand
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

int UDK3::minCardAmountsByPlayer(vector<int> cardAmountsByPlayer) //Lowest count of cards off players in game, determine whether to cash out on specials
{
	int min = 99;
	for (int i = 0; i < cardAmountsByPlayer.size(); i++)
	{
		if (cardAmountsByPlayer[i] < min)
			min = cardAmountsByPlayer[i];
	}
	return min;
}


//Get index of playable specials
int UDK3::getPlayableSkip(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getNumber() == 10)
			index = i;
	}
	return index;
}
int UDK3::getPlayableDra2(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getNumber() == 11)
			index = i;
	}
	return index;
}
int UDK3::getPlayableReverse(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getNumber() == 12)
			index = i;
	}
	return index;
}
int UDK3::getPlayableWild(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if ((playableCards[i].getColor() == BLACK) && (playableCards[i].getNumber() == 0))
			index = i;
	}
	return index;
}

int UDK3::getPlayableDra4(vector<Card> playableCards)
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
int UDK3::makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand, int direction)
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
	if (specialCardCount(cards) >= minCardAmountsByPlayer(cardAmountsByPlayer))
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
	else if (minCardAmountsByPlayer(cardAmountsByPlayer) <= 3)
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

string UDK3::getName()
{
	return "UDK3";
}



Color UDK3::getNewColor()
{
	return savedColor;
}