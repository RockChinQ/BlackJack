#include "deck.h"

Deck::Deck()
{ 
    m_Cards.reserve(52);
    Populate(1);
}

Deck::~Deck()
{}

void Deck::Populate(int nDeck)
{
    Clear();
    //create standard deck
    for (int n=0; n<nDeck; n++){
        for (int s = Card::CLUBS; s <= Card::SPADES; ++s)
        {
            for (int r = Card::ACE; r <= Card::KING; ++r)
            {
                Add(new Card(static_cast<Card::rank>(r),
                            static_cast<Card::suit>(s)));
            }
        }
    }
}

void Deck::Shuffle()
{
    random_shuffle(m_Cards.begin(), m_Cards.end());
}

void Deck::Deal(Hand& aHand)
{
    if (!m_Cards.empty())
    {
        aHand.Add(m_Cards.back());
        m_Cards.pop_back();
    }
    else
    {
        std::cout << "Out of cards. Unable to deal.";
    }
}

void Deck::AdditionalCards(GenericPlayer& aGenericPlayer)
{
    std::cout << std::endl;
    //continue to deal a card as long as generic player isn't busted and
    //wants another hit
    while ( !(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting() )
    {
        Deal(aGenericPlayer);
        std::cout << aGenericPlayer << std::endl;
        
        if (aGenericPlayer.IsBusted())
		{
            aGenericPlayer.Bust();
		}
    }
} 
