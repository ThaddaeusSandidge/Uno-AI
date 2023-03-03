#include "UDK7.h"

#include <iostream>
using namespace std;

UDK7::UDK7(int playerNumber) : AI(playerNumber)
{

}

void UDK7::onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor) //No card counting in my implementation
{

}

void UDK7::onOtherPlayerDraw(int playerNumber) //No card counting in my implementation
{

}
int UDK7::getDra4(vector<Card> cardsInHand) //Returns index of draw 4 if it exists, otherwise return -1
{
	int index = -1;
	for (int i = 0; i < cardsInHand.size(); i++)
	{
		if ((cardsInHand[i].getColor() == BLACK) && (cardsInHand[i].getNumber() == 1))
			index = i;
	}
	return index;
}
int UDK7::getWild(vector<Card> playableCards) //Returns index of Wild if it exists, otherwise return -1
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if ((playableCards[i].getColor() == BLACK) && (playableCards[i].getNumber() == 0))
			index = i;
	}
	return index;
}
int UDK7::getWildCount(vector<Card> playableCards) //Returns number of wild cards in hand, did use in implementation
{
	int count = 0;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if ((playableCards[i].getColor() == BLACK) && (playableCards[i].getNumber() == 0))
			count++;
	}
	return count;
}
int UDK7::highestPlayable(vector<Card> playableCards) //Returns highest playable card
{
	int max = -1;
	int indexTemp = -1;
	for (int j = 0; j < playableCards.size(); j++)
	{
		if (playableCards[j].getPoints() > max)
		{
			max = playableCards[j].getPoints();
			indexTemp = j;
		}
	}
	return indexTemp;
}
int UDK7::highestPlayableColor(vector<Card> playableCards) //Returns highest playable card of the color with the most cards, did not use in implementation
{
	if (myNum < 10)
	{
		int max = -1;
		int indexTemp = -1;
		for (int j = 0; j < playableCards.size(); j++)
		{
			if (playableCards[j].getPoints() > max)
			{
				max = playableCards[j].getPoints();
				indexTemp = j;
			}
		}
		return indexTemp;
	}
	else
	{
		playableColor.resize(6);
		for (int i = 0;i < playableColor.size();i++)
		{
			playableColor[i].resize(0);
		}
		for (int i = 0; i < playableCards.size(); i++)
		{
			playableColor.at(playableCards[i].getColor()).push_back(playableCards[i]);
		}

		bool redB = false;
		bool blueB = false;
		bool greenB = false;
		bool yellowB = false;
		for (int j = 0; j < playableCards.size(); j++)
		{
			if (playableCards[j].getColor() == RED)
				redB = true;
			if (playableCards[j].getColor() == BLUE)
				blueB = true;
			if (playableCards[j].getColor() == GREEN)
				greenB = true;
			if (playableCards[j].getColor() == YELLOW)
				yellowB = true;
		}
		if (getDra4(playableCards) != -1)
		{
			return getDra4(playableCards);
		}
		if (getWild(playableCards) != -1)
		{
			return getWild(playableCards);
		}
		int red = 0;
		int blue = 0;
		int green = 0;
		int yellow = 0;
		if (!colorVec[0].empty() && !playableColor[0].empty())
		{
			red = colorVec[0].size();
		}
		if (!colorVec[1].empty() && !playableColor[1].empty())
		{
			blue = colorVec[1].size();
		}
		if (!colorVec[2].empty() && !playableColor[2].empty())
		{
			green = colorVec[2].size();
		}
		if (!colorVec[3].empty() && !playableColor[3].empty())
		{
			yellow = colorVec[3].size();
		}
		int rb = max(red, blue);
		int gy = max(yellow, green);
		int finalC = max(rb, gy);
		int max = -1;
		int indexTemp = -1;
		if (finalC == rb && finalC == gy)
		{
			for (int j = 0; j < playableCards.size(); j++)
			{
				if (playableCards[j].getPoints() > max)
				{
					max = playableCards[j].getPoints();
					indexTemp = j;

				}
			}
			return indexTemp;
		}
		else
		{
			if (finalC == red && redB)
			{
				//cout << "\nin red";
				for (int j = 0; j < playableCards.size(); j++)
				{
					if (playableCards[j].getPoints() > max && playableCards[j].getColor() == RED)
					{
						max = playableCards[j].getPoints();
						indexTemp = j;
					}
				}
				if (indexTemp != -1)
					return indexTemp;
			}
			if (finalC == blue && blueB)
			{
				//cout << "\nin blue";
				for (int j = 0; j < playableCards.size(); j++)
				{
					if (playableCards[j].getPoints() > max && playableCards[j].getColor() == BLUE)
					{
						max = playableCards[j].getPoints();
						indexTemp = j;
					}
				}
				if (indexTemp != -1)
					return indexTemp;
			}
			if (finalC == green && greenB)
			{
				//cout << "\nin green";
				for (int j = 0; j < playableCards.size(); j++)
				{
					if (playableCards[j].getPoints() > max && playableCards[j].getColor() == GREEN)
					{
						max = playableCards[j].getPoints();
						indexTemp = j;
					}
				}
				if (indexTemp != -1)
					return indexTemp;
			}
			if (finalC == yellow && yellowB)
			{
				//cout << "\nin yellow";
				for (int j = 0; j < playableCards.size(); j++)
				{
					if (playableCards[j].getPoints() > max && playableCards[j].getColor() == YELLOW)
					{
						max = playableCards[j].getPoints();
						indexTemp = j;
					}
				}
				if (indexTemp != -1)
					return indexTemp;
			}
		}
	}
}

int UDK7::playBlack(vector<Card> playableCards) //Returns index of black card, otherwise return -1
{
	int max = -1;
	int indexTemp = -1;
	for (int j = 0; j < playableCards.size(); j++)
	{
		if (playableCards[j].getColor() == BLACK && playableCards[j].getNumber() == 0)
		{
			indexTemp = j;
		}
	}
	for (int j = 0; j < playableCards.size(); j++)
	{
		if (playableCards[j].getColor() == BLACK && playableCards[j].getNumber() == 1)
		{
			indexTemp = j;
		}
	}
	return indexTemp;
}
int UDK7::playHighestNormal(vector<Card> playableCards) //Play highest card that is not black, if none returns -1
{
	int max = -1;
	int indexTemp = -1;
	for (int j = 0; j < playableCards.size(); j++)
	{
		if (playableCards[j].getPoints() > max && playableCards[j].getColor() != BLACK)
		{
			max = playableCards[j].getPoints();
			indexTemp = j;
		}
	}
	return indexTemp;
}
int UDK7::playableCardsInColor(vector<Card> playableCards, Color c) //Returns number of playable cards in a color, did not use in final implementation
{
	int cards = 0;
	for (int j = 0; j < playableCards.size(); j++)
	{
		if (playableCards[j].getColor() == c)
		{
			cards++;

		}

	}
	return cards;
}
int UDK7::max(int x, int y) //Returns the max of two passed in ints
{
	if (x > y)
		return x;
	else if (y > x)
		return y;
	else
		return x;
}

int UDK7::minCardAmountsByPlayer(vector<int> cardAmountsByPlayer) //Lowest count of cards of players in game, determine whether to cash out on specials
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
int UDK7::minCardAmountsByPlayerNumber(vector<int> cardAmountsByPlayer) //Returns player number of player with lowest cards, did not use in final implementation
{
	int min = 99;
	int playerNum = -1;
	for (int i = 0; i < cardAmountsByPlayer.size(); i++)
	{
		if (cardAmountsByPlayer[i] < min)
		{
			if (i != myPlayerNumber)
			{
				min = cardAmountsByPlayer[i];
				playerNum = i;
			}
		}
	}
	return playerNum;
}

bool UDK7::equalNumOfColors(int maxNum) //Returns if there is an equal number of cards in color, takes in a max color num, tried to use for highestPlayableColor, did not implement in final code
{
	count = 0;
	for (int i = 0;i < 4;i++)
	{
		if (colorVec[i].size() == maxNum)
		{
			count++;
		}
	}
	if (count == 1)
		return false;
	else
		return true;
}

void UDK7::colorSelect(vector<Card> cardsInHand, vector<int> cardAmountsByPlayer)
{
	//Change saved color based on how many cards of each color in hand

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
		//cout << "red\n";
		savedColor = RED;
	}
	if (maxColorIndex == 1)
	{
		//cout << "blue\n";
		savedColor = BLUE;
	}
	if (maxColorIndex == 2)
	{
		//cout << "green\n";
		savedColor = GREEN;
	}
	if (maxColorIndex == 3)
	{
		//cout << "yellow\n";
		savedColor = YELLOW;
	}

	if (getDra4(cardsInHand) != -1) //If hand has draw 4 and a vector is empty, set color to empty vector to be able to play draw 4
	{
		if (colorVec[0].empty())
		{
			savedColor = RED;
		}
		if (colorVec[1].empty())
		{
			savedColor = BLUE;
		}
		if (colorVec[2].empty())
		{
			savedColor = GREEN;
		}
		if (colorVec[3].empty())
		{
			savedColor = YELLOW;
		}
	}

}

//returns the index of the card to play
int UDK7::makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand, int direction)
{

	vector<Card> cards = getPlayableCardsInHand(justPlayed, choosenCardColor, cardsInHand);

	if (cards.size() == 0)
	{
		return -1; //draw
	}

	//special card key
	//reverse = 12, skip = 10, and draw2 = 11 of any of red/blue/green/yellow.
	//wild is black 0, draw4 is black 1


	savedColor = YELLOW;
	colorSelect(cardsInHand, cardAmountsByPlayer); //Set saved color
	minPlayer = minCardAmountsByPlayer(cardAmountsByPlayer); //Get minimum player count
	myNum = cardsInHand.size(); //Get cards in my hand
	//Play card
	int index;
	if (minPlayer <= 7) //Case for playing black, 7 was best number found in testing
	{
		if (playBlack(cards) != -1) //Play black card if exists
			index = playBlack(cards);
		else
			index = highestPlayable(cards);
	}

	else
	{
		if (getDra4(cards) != -1) //Play draw 4 if possible
			index = getDra4(cards);
		else if (playHighestNormal(cards) != -1) //Play highest normal
			index = playHighestNormal(cards);
		else
			index = highestPlayable(cards); //Otherwise highest playable
	}
	//cout << "\nindex " << index;
	Card c = cards[index];
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

string UDK7::getName()
{
	return "UDK7";
}



Color UDK7::getNewColor()
{
	return savedColor;
}