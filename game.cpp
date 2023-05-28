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

void Game::Bet()
{
	//ask player for bet
	for(int i = 0; i < m_Players.size(); ++i){
        std::cout<<i<<": "<<m_Players[i].GetName()<<std::endl;
    }
    int choice = -1;
    do{
        std::cout<<"Enter the number of the player you want to bet on (0-"<<m_Players.size()-1<<"): ";
        std::cin>>choice;
    }while(choice < 0 || choice > m_Players.size()-1);
    m_playerBet = m_Players[choice].GetName();
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
        //everyone still playing wins
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) 
		{
            if ( !(pPlayer->IsBusted()) )
			{
                pPlayer->Win();
                CheckBet(pPlayer->GetName(), true);
			}
		}
    }
    else
    {
         //compare each player still playing to house
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end();
             ++pPlayer)      
        {
            if ( !(pPlayer->IsBusted()) )
            {
                if (pPlayer->GetTotal() > m_House.GetTotal())
                {
                    pPlayer->Win();
                    CheckBet(pPlayer->GetName(), true);
                }
                else if (pPlayer->GetTotal() < m_House.GetTotal())
                {
                    pPlayer->Lose();
                    CheckBet(pPlayer->GetName(), false);
                }
                else
                {
                    pPlayer->Push();
                }
            }
        }
    }

    //remove everyone's cards
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) 
	{
        pPlayer->Clear();
	}
    m_House.Clear();
}

void Game::CheckBet(std::string winner, bool won)
{
    if(winner == m_playerBet){
        if(won){
            std::cout<<"You won on the bet!"<<std::endl;
        }else{
            std::cout<<"You lost on the bet!"<<std::endl;
        }
    }
}
