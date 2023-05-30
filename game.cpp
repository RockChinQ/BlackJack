#include "game.h"
#include "player.h"

Game::Game(const std::vector<std::string>& names)
{
    //create a vector of players from a vector of names       
    std::vector<std::string>::const_iterator pName;
    for (pName = names.begin(); pName != names.end(); ++pName)
	{
        m_Players.push_back(Player(*pName));
	}

	//seed the random number generator
	srand(static_cast<unsigned int>(time(0)));    
    m_Deck.Populate();
    m_Deck.Shuffle();
}

Game::~Game()
{}

void Game::AskBet()
{
    m_Bets.clear();
    std::vector<Player>::iterator pPlayer;
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        int bet = 0;
        std::cout << pPlayer->GetName() << ", please bet: ";
        std::cin >> bet;
        m_Bets.push_back(bet);
    }
}

void Game::Play()
{         
    //deal initial 2 cards to everyone
    std::vector<Player>::iterator pPlayer;
    for (int i = 0; i < 2; ++i)
    {
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) 
		{
            m_Deck.Deal(*pPlayer);
		}
        m_Deck.Deal(m_House);
    }
    
    //hide house's first card
    m_House.FlipFirstCard();    
    
    //display everyone's hand
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) 
	{
        std::cout << *pPlayer << std::endl;
	}
    std::cout << m_House << std::endl;

    //deal additional cards to players
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
	{
        m_Deck.AdditionalCards(*pPlayer);    
	}

    //reveal house's first card
    m_House.FlipFirstCard();    
    std::cout << std::endl << m_House; 
  
    //deal additional cards to house
    m_Deck.AdditionalCards(m_House);

    if (m_House.IsBusted())
    {
        int betIndex = 0;
        //everyone still playing wins
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) 
		{
            if ( !(pPlayer->IsBusted()) )
			{
                pPlayer->Win();
                pPlayer->SetFund(pPlayer->GetFund() + m_Bets[betIndex]);
			}else{
                pPlayer->SetFund(pPlayer->GetFund() - m_Bets[betIndex]);
            }
            betIndex++;
		}
    }
    else
    {
        int betIndex = 0;
         //compare each player still playing to house
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end();
             ++pPlayer)      
        {
            if ( !(pPlayer->IsBusted()) )
            {
                if (pPlayer->GetTotal() > m_House.GetTotal())
                {
                    pPlayer->Win();
                    pPlayer->SetFund(pPlayer->GetFund() + m_Bets[betIndex]);
                }
                else if (pPlayer->GetTotal() < m_House.GetTotal())
                {
                    pPlayer->Lose();
                    pPlayer->SetFund(pPlayer->GetFund() - m_Bets[betIndex]);
                }
                else
                {
                    pPlayer->Push();
                }
            }else{
                pPlayer->SetFund(pPlayer->GetFund() - m_Bets[betIndex]);
            }
            betIndex++;
        }
    }

    // 输出所有人的资金量
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        std::cout << pPlayer->GetName() << "'s fund: " << pPlayer->GetFund() << std::endl;
    }

    //remove everyone's cards
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) 
	{
        pPlayer->Clear();
	}
    m_House.Clear();
}
