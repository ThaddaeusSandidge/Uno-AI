#include "UDK6.h"

#include <iostream>
using namespace std;

UDK6::UDK6(int playerNumber) : AI(playerNumber)
{
	playerFlags.resize(5);
	for (int i = 0;i < playerFlags.size();i++)
	{
		playerFlags[i].resize(4);
	}
}

void UDK6::onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor)
{
	current = choosenCardColor;
	if (justPlayed.getColor() == RED)
	{
		playerFlags[playerNumber][0] = 0;
	}
	if (justPlayed.getColor() == BLUE)
	{
		playerFlags[playerNumber][1] = 0;
	}
	if (justPlayed.getColor() == GREEN)
	{
		playerFlags[playerNumber][2] = 0;
	}
	if (justPlayed.getColor() == YELLOW)
	{
		playerFlags[playerNumber][3] = 0;
	}
}

void UDK6::onOtherPlayerDraw(int playerNumber)
{
	if (current == RED)
	{
		playerFlags[playerNumber][0] = 1;
	}
	if (current == BLUE)
	{
		playerFlags[playerNumber][1] = 1;
	}
	if (current == GREEN)
	{
		playerFlags[playerNumber][2] = 1;
	}
	if (current == YELLOW)
	{
		playerFlags[playerNumber][3] = 1;
	}
}
int UDK6::getDra4(vector<Card> cardsInHand)
{
	int index = -1;
	for (int i = 0; i < cardsInHand.size(); i++)
	{
		if ((cardsInHand[i].getColor() == BLACK) && (cardsInHand[i].getNumber() == 1))
			index = i;
	}
	return index;
}
int UDK6::getWild(vector<Card> playableCards)
{
	int index = -1;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if ((playableCards[i].getColor() == BLACK) && (playableCards[i].getNumber() == 0))
			index = i;
	}
	return index;
}
int UDK6::getWildCount(vector<Card> playableCards)
{
	int count = 0;
	for (int i = 0; i < playableCards.size(); i++)
	{
		if ((playableCards[i].getColor() == BLACK) && (playableCards[i].getNumber() == 0))
			count++;
	}
	return count;
}
int UDK6::highestPlayable(vector<Card> playableCards)
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
	/*
	if ((getWildCount(playableCards) == playableCards.size()) || minPlayer < 4)
	{

	}
	else
	{
		for (int j = 0; j < playableCards.size(); j++)
		{
			if (cardTOString(playableCards[j]) != "Wild")
			{
				if (playableCards[j].getPoints() > max)
				{
					max = playableCards[j].getPoints();
					indexTemp = j;
				}
			}

		}
	}
	*/


	return indexTemp;
}
int UDK6::highestPlayableColor(vector<Card> playableCards)
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
int UDK6::highestPlayableColor2(vector<Card> playableCards)
{
	return 0;
}
int UDK6::playableCardsInColor(vector<Card> playableCards, Color c)
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
int UDK6::max(int x, int y)
{
	if (x > y)
		return x;
	else if (y > x)
		return y;
	else
		return x;
}

int UDK6::minCardAmountsByPlayer(vector<int> cardAmountsByPlayer) //Lowest count of cards off players in game, determine whether to cash out on specials
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
int UDK6::minCardAmountsByPlayerNumber(vector<int> cardAmountsByPlayer)
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
bool UDK6::handHasColor(vector<Card> cardsInHand)
{
	return false;
}
bool UDK6::equalNumOfColors(int maxNum)
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

void UDK6::colorSelect(vector<Card> cardsInHand, vector<int> cardAmountsByPlayer)
{
	//Change saved color based on how many cards of each color in hand
	/*
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
	} */
	
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
	/*
	for (int i = 0; i < colorVec.size(); i++)
	{
		cout << colorVec[i].size() << "\n";

	} */
	/*
	if (equalNumOfColors(maxColorSize))
	{
		//cout << "equal number of colors, selecting on point basis\n";
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
		maxColorIndex = -1;
		for (int i = 0;i < colorSum.size();i++)
		{
			if (colorSum[i] > maxColorPoints)
			{
				maxColorPoints = colorSum[i];
				maxColorIndex = i;
			}
		}
	} */
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
	/*
	if (minCardAmountsByPlayer(cardAmountsByPlayer) < 3)
	{
		if (playerFlags[minCardAmountsByPlayerNumber(cardAmountsByPlayer)][0] == 1 && playableCardsInColor(cardsInHand, RED) != 0)
		{
			savedColor == RED;
		}
		if (playerFlags[minCardAmountsByPlayerNumber(cardAmountsByPlayer)][1] == 1 && playableCardsInColor(cardsInHand, BLUE) != 0)
		{
			savedColor == BLUE;
		}
		if (playerFlags[minCardAmountsByPlayerNumber(cardAmountsByPlayer)][2] == 1 && playableCardsInColor(cardsInHand, GREEN) != 0)
		{
			savedColor == GREEN;
		}
		if (playerFlags[minCardAmountsByPlayerNumber(cardAmountsByPlayer)][3] == 1 && playableCardsInColor(cardsInHand, YELLOW) != 0)
		{
			savedColor == YELLOW;
		}
		//cout << savedColor;
	} */
	/*
	if (getDra4(cardsInHand) == -1)
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
	} */
	


	//if (maxColorIndex == 4)
	//{
		//savedColor = BLACK;
	//}
	//if (maxColorIndex == 5)
		//savedColor = NONE;

}

//returns the index of the card to play
int UDK6::makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand, int direction)
{
	/*
	for (int i = 0; i < cardAmountsByPlayer.size(); i++)
	{
		cout << cardAmountsByPlayer[i] << "\n";
	} */



	vector<Card> cards = getPlayableCardsInHand(justPlayed, choosenCardColor, cardsInHand);

	if (cards.size() == 0)
	{
		return -1; //draw
	}

	//special card key
	//reverse = 12, skip = 10, and draw2 = 11 of any of red/blue/green/yellow.
	//wild is black 0, draw4 is black 1


	savedColor = YELLOW;
	colorSelect(cardsInHand, cardAmountsByPlayer);
	minPlayer = minCardAmountsByPlayer(cardAmountsByPlayer);
	//Play card
	int index; /*
	if (minCardAmountsByPlayer(cardAmountsByPlayer) > 7)
		index = highestPlayableColor(cards);
	else  */
	/*
	if (getWildCount(cards) > 1)
	{
		index = getWild(cards);
	}
	else *//*
	if (count % 4 == 0)
	{
		index = highestPlayableColor(cards);
	}
	else */
		index = highestPlayable(cards);
	
	count++;
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

string UDK6::getName()
{
	return "UDK6";
}



Color UDK6::getNewColor()
{
	return savedColor;
}