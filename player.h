#ifndef __TEST_PLAYER__
#define __TEST_PLAYER__
#include "genericPlayer.h"

class Player : public GenericPlayer
{
public:
    static int initialFund;
    
    int fund;

    Player(const std::string& name = "");

    virtual ~Player();

    //returns whether or not the player wants another hit       
    virtual bool IsHitting() const;

    //announces that the player wins
    void Win() const;

    //announces that the player loses
    void Lose() const;

    //announces that the player pushes
    void Push() const;

    std::string GetName() const;

    int GetFund() const;
};
#endif
