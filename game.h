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
    
    void Bet();

    //plays the game of blackjack    
    void Play();

    void CheckBet(std::string winner, bool won);

private:
    Deck m_Deck;
    House m_House;
    std::vector<Player> m_Players;  
    std::string m_playerBet;
};

#endif
