//bots/botstrategy.h
#include <game/client/gameclient.h>
#include <game/client/components/controls.h>

class IBotStrategy
{
protected:
    friend class CGameClient;

	CGameClient *m_pClient;

	class IClient *Client() const { return m_pClient->Client(); }
	class IConsole *Console() const { return m_pClient->Console(); }

    CControls *m_pControls;

public:
        virtual void Execute() = 0;
        virtual bool UsesDirection() = 0;
};
#endif

//bots/bumbletee.h
#include "botstrategy.h"

class CBumbleteeBot : public IBotStrategy
{

public:
    CBumbleteeBot(CControls *pControls);

    void Execute();
    bool UsesDirection(){ return false; };

};


//bot.h
#include "controls.h"
#include "bots/botstrategy.h"

class CBot
{
protected:
    class CNoBot *m_pStrategyNoBot;
    class CLeechLikeBot *m_pStrategyLeechLikeBot;
    class CBumbleteeBot *m_pStrategyBumbleteeBot;
    class CInfectionBot *m_pStrategyInfectionBot;

    CControls *m_pControls;

public:
    enum {
        BOT_NOBOT,
        BOT_LEECHLIKE,
        BOT_BUMBLETEE,
        BOT_INFECTION
    };

    CBot(CControls *pControls);
    void Execute();
    IBotStrategy* Strategy();
    bool UsesDirection();
};

//bot.cpp
CBot::CBot(CControls *pControls)
{
    m_pStrategyNoBot = new CNoBot(pControls);
    m_pStrategyLeechLikeBot = new CLeechLikeBot(pControls);
    m_pStrategyBumbleteeBot = new CBumbleteeBot(pControls);
    m_pStrategyInfectionBot = new CInfectionBot(pControls);
}

void CBot::Execute()
{
    Strategy()->Execute();
}

IBotStrategy* CBot::Strategy()
{
    switch(g_Config.m_LolBotType)
    {
        case BOT_LEECHLIKE:
            return (IBotStrategy*) m_pStrategyLeechLikeBot;
        case BOT_BUMBLETEE:
            return (IBotStrategy*) m_pStrategyBumbleteeBot;
        case BOT_INFECTION:
            return (IBotStrategy*) m_pStrategyInfectionBot;
        case BOT_NOBOT:
        default:
            return (IBotStrategy*) m_pStrategyNoBot;
    }
}

bool CBot::UsesDirection()
{
    return Strategy()->UsesDirection();
}
