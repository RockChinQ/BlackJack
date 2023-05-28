#include "genericPlayer.h"

GenericPlayer::GenericPlayer(const std::string& name): 
    m_Name(name)
{}

GenericPlayer::~GenericPlayer()  
{}

bool GenericPlayer::IsBusted() const
{ 
    return (GetTotal() > 21);
}

void GenericPlayer::Bust() const
{
    std::cout << m_Name << " busts.\n";
}

std::string GenericPlayer::GetName() const
{
    return m_Name;
}