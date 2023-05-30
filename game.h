#ifndef __TEST_GAME__
#define __TEST_GAME__
#include <iostream>
#include <string>
#include <vector>

#include "deck.h"
#include "house.h"
#include "player.h"

class Game
{
public:
    Game(const std::vector<std::string>& names);
    
    ~Game();

    // Ask each player bet for this round
    void AskBet();
    
    //plays the game of blackjack    
    void Play();

private:
    Deck m_Deck;
    House m_House;
    std::vector<Player> m_Players;  

    std::vector<int> m_Bets;
};

#endif
