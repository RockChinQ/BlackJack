#ifndef __TEST_GENERIC_PLAYER__
#define __TEST_GENERIC_PLAYER__
#include <iostream>

#include "hand.h"

class GenericPlayer : public Hand
{
    friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer);

public:
    GenericPlayer(const std::string& name = "");
    
    virtual ~GenericPlayer();

    //indicates whether or not generic player wants to keep hitting
    virtual bool IsHitting() const = 0;

    //returns whether generic player has busted - has a total greater than 21
    bool IsBusted() const;

    //announces that the generic player busts
    void Bust() const;

    std::string GetName() const;

protected:
    std::string m_Name;
};
#endif
