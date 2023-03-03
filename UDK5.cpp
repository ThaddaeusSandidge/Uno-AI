#include "UDK5.h"

#include <iostream>
using namespace std;

UDK5::UDK5(int playerNumber) : AI(playerNumber)
{

	/* allCardCount.resize(60);
	for (int i = 0;i < allCardCount.size();i++)
	{
		allCardCount[i] = 7;
	} */
}

void UDK5::onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor)
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

void UDK5::onOtherPlayerDraw(int playerNumber)
{

}
bool UDK5::playFirstC(vector<Card> playableCards)
{
	bool canPlay = false;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getColor() == firstC)
			canPlay = true;
			
	}
	return canPlay;
}

bool UDK5::playSecondC(vector<Card> playableCards)
{
	bool canPlay = false;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getColor() == secondC)
			canPlay = true;

	}
	return canPlay;
}

bool UDK5::playThirdC(vector<Card> playableCards)
{
	bool canPlay = false;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getColor() == thirdC)
			canPlay = true;

	}
	return canPlay;
}

bool UDK5::playFourthC(vector<Card> playableCards)
{
	bool canPlay = false;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getColor() == fourthC)
			canPlay = true;

	}
	return canPlay;
}
void UDK5::colorPrioritySort(vector<Card> cardsInHand)
{
	vector<int> colorSum;
	colorSum.resize(4);
	firstC = -1;
	secondC = -1;
	thirdC = -1;
	fourthC = -1;
	numOfColorsInHand = 0;
	for (int i = 0; i < cardsInHand.size(); i++)
	{
		if (cardsInHand[i].getColor() == RED)
		{
			colorSum[0]++;

		}
		if (cardsInHand[i].getColor() == BLUE)
		{
			colorSum[1]++;

		}
		if (cardsInHand[i].getColor() == GREEN)
		{
			colorSum[2]++;

		}
		if (cardsInHand[i].getColor() == YELLOW)
		{
			colorSum[3]++;

		}
	}

	for (int i = 0;i < colorSum.size();i++)
	{
		if (colorSum[i] != NULL)
			numOfColorsInHand++;
	}
	int maxColorPoints = -1;
	int maxColorIndex = -1;
	if (numOfColorsInHand == 4)
	{
		for (int i = 0;i < colorSum.size();i++) //Rank first color
		{
			if (colorSum[i] > maxColorPoints)
			{
				maxColorPoints = colorSum[i];
				firstC = i;
			}
		}
		int minColorPoints = 99;
		for (int i = 0;i < colorSum.size();i++) //Rank second color
		{
			if (colorSum[i] < minColorPoints)
			{
				minColorPoints = colorSum[i];
				fourthC = i;
			}
		}
		int secondMax = -1;
		for (int i = 0;i < colorSum.size();i++) //Rank third color
		{
			if (i != firstC && i != fourthC)
			{
				if (colorSum[i] > secondMax)
				{
					secondMax = colorSum[i];
					secondC = i;
				}
			}
		}
		for (int i = 0;i < colorSum.size();i++) //Rank fourth color
		{
			if (i != firstC && i != fourthC && i != secondC)
			{
				thirdC = i;
			}
		}
	}
	else if (numOfColorsInHand == 3)
	{
		for (int i = 0;i < colorSum.size();i++) //Rank first color
		{
			if (colorSum[i] > maxColorPoints)
			{
				maxColorPoints = colorSum[i];
				firstC = i;
			}
		}
		int minColorPoints = 99;
		for (int i = 0;i < colorSum.size();i++) //Rank second color
		{
			if (colorSum[i] < minColorPoints && colorSum[i] != NULL)
			{
				minColorPoints = colorSum[i];
				thirdC = i;
			}
		}
		int secondMax = -1;
		for (int i = 0;i < colorSum.size();i++) //Rank third color
		{
			if (i != firstC && i != thirdC)
			{
				if (i != firstC && i != thirdC && colorSum[i] != NULL)
				{

					secondC = i;
				}
			}
		}
	}
	else if (numOfColorsInHand == 2)
	{
		for (int i = 0;i < colorSum.size();i++) //Rank first color
		{
			if (colorSum[i] > maxColorPoints)
			{
				maxColorPoints = colorSum[i];
				firstC = i;
			}
		}
		int minColorPoints = 99;
		for (int i = 0;i < colorSum.size();i++) //Rank second color
		{
			if (i != maxColorIndex && colorSum[i] != NULL)
			{
				minColorPoints = colorSum[i];
				secondC = i;
			}
		}
	}
	else
	{
		for (int i = 0;i < colorSum.size();i++) //Rank first color
		{
			if (colorSum[i] > maxColorPoints)
			{
				maxColorPoints = colorSum[i];
				firstC = i;
			}
		}
	}

	cout << firstC << "\n" << secondC << "\n" << thirdC << "\n" << fourthC << "\n";
}
int UDK5::playableCardsInColor(vector<Card> playableCards, Color c)
{
	int cards = 0;
	for (int j = 0; j < playableCards.size(); j++)
	{
		if (playableCards[j].getColor() == c)
		{
			cards += 1;

		}

	}
	return cards;
}
void UDK5::colorSelect(vector<Card> cardsInHand) //Color Select Variation, picks based on max point values not card num
{
	//Change saved color based on how many points of each color in hand
	
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
int UDK5::specialCardCount(vector<Card> playableCards)
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
int UDK5::highestPlayableSpecial(vector<Card> playableCards) //Returns index of card in playable hand
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
int UDK5::normalCardCount(vector<Card> playableCards)
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
int UDK5::highestPlayableNormal(vector<Card> playableCards) //Returns index of card in playable hand
{
	int toReturn = -1;
	int max = -1;

	
	if (playFirstC(playableCards))
	{
		for (int i = 0; i < playableCards.size(); i++)
		{
				if (playableCards[i].getPoints() > max && playableCards[i].getColor() == firstC)
				{
					max = playableCards[i].getPoints();
					toReturn = i;
				}
			

		}
	}
	else if (playSecondC(playableCards))
	{
		for (int i = 0; i < playableCards.size(); i++)
		{

				if (playableCards[i].getPoints() > max && playableCards[i].getColor() == secondC)
				{
					max = playableCards[i].getPoints();
					toReturn = i;
				}
			

		}
	}
	else if (playThirdC(playableCards))
	{
		for (int i = 0; i < playableCards.size(); i++)
		{

				if (playableCards[i].getPoints() > max && playableCards[i].getColor() == thirdC)
				{
					max = playableCards[i].getPoints();
					toReturn = i;
				}
			

		}
	}
	else if (playFourthC(playableCards))
	{
		for (int i = 0; i < playableCards.size(); i++)
		{

				if (playableCards[i].getPoints() > max && playableCards[i].getColor() == fourthC)
				{
					max = playableCards[i].getPoints();
					toReturn = i;
				}
			

		}
	}
	else
	{
		for (int i = 0; i < playableCards.size(); i++)
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

int UDK5::minCardAmountsByPlayer(vector<int> cardAmountsByPlayer) //Lowest count of cards off players in game, determine whether to cash out on specials
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

int UDK5::nextPlayerCardAmount(vector<int> cardAmountsByPlayer, int direction)
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
int UDK5::getPlayableSkip(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getNumber() == 10)
			index = i;
	}
	return index;
}
int UDK5::getPlayableDra2(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getNumber() == 11)
			index = i;
	}
	return index;
}
int UDK5::getPlayableReverse(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if (playableCards[i].getNumber() == 12)
			index = i;
	}
	return index;
}
int UDK5::getPlayableWild(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if ((playableCards[i].getColor() == BLACK) && (playableCards[i].getNumber() == 0))
			index = i;
	}
	return index;
}

int UDK5::getPlayableDra4(vector<Card> playableCards)
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
int UDK5::makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand, int direction)
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
	colorPrioritySort(cardsInHand);
	
	int playableIndex = -1;
	if (getPlayableDra4(cards) != -1)
		playableIndex = getPlayableDra4(cards);
	else if (getPlayableWild(cards) != -1)
		playableIndex = getPlayableWild(cards);
	else
		playableIndex = highestPlayableNormal(cards);
	/*
	if (minCardAmountsByPlayer(cardAmountsByPlayer) > 3)
	{
		if (highestPlayableNormal(cards) != -1)
		{
			playableIndex = highestPlayableNormal(cards);
		}
		else
			playableIndex = highestPlayableSpecial(cards);
	}
	else
	{
		if (highestPlayableSpecial(cards) != -1)
		{
			playableIndex = highestPlayableSpecial(cards);
		}
		else
			playableIndex = highestPlayableNormal(cards);
	} */
		
	/*if (cardsInHand.size() - minCardAmountsByPlayer(cardAmountsByPlayer) > 0)
	{
		if (getPlayableReverse(cards) != -1)
			playableIndex = getPlayableReverse(cards);
		else if (getPlayableSkip(cards) != -1)
			playableIndex = getPlayableSkip(cards);
		else if (getPlayableDra2(cards) != -1)
			playableIndex = getPlayableDra2(cards);
		else if (highestPlayableNormal(cards) != -1)
		{
			playableIndex = highestPlayableNormal(cards);
		}
			
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

	} */
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

string UDK5::getName()
{
	return "UDK5";
}



Color UDK5::getNewColor()
{
	return savedColor;
}