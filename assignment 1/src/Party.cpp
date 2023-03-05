#include "Party.h"
#include "Simulation.h"
#include "JoinPolicy.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting),timer(2),maxMandates(0),coalitionMaxMandates(-1),coalitionLastOffer(-1),agentIdLastOffer(-1),agentIdMaxMandates(-1)
{
    // You can change the implementation of the constructor, but not the signature!

}
//getters
//--------------------------------------------------------------------------
State Party::getState() const
{
    return mState;
}

int Party::getMandates() const
{
    return mMandates;
}

int Party::getPartyId() const
{
    return mId;
}

int Party::getMaxMandates() const
{
    return maxMandates;
}

int Party::getCoalitionMaxMandates() const
{
    return coalitionMaxMandates;
}

int Party::getCoalitionLastOffer() const
{
    return coalitionLastOffer;
}

const string & Party::getName() const
{
    return mName;
}

int Party::getAgentIdLastOffer() const
{
    return agentIdLastOffer;
}

int Party::getAgentIdMaxMandates() const
{
    return agentIdMaxMandates;
} 

int Party::getTimer()
{
    return timer;
}


//setters
//--------------------------------------------------------------------

void Party::setState(State state)
{
    mState = state;
}

void Party::setMaxMandates(int _maxMandates)
{
    maxMandates = _maxMandates;
}

void Party::setCoalitionMaxMandates(int _party)
{
    coalitionMaxMandates = _party;
}

void Party::setCoalitionLastOffer(int _party)
{
    coalitionLastOffer = _party;
}

void Party::setAgentIdLastOffer(int _agentId)
{
    agentIdLastOffer = _agentId;
}
void Party::setAgentIdMaxMandates(int _agentId)
{
    agentIdMaxMandates = _agentId;
}
void Party::setTimer(int _timer)
{
    timer = _timer - 1;
}

//methods
//---------------------------------------------------------------------------
void Party::step(Simulation &s)
{
    if(mState == CollectingOffers)
    {
        if(timer > 0)
        {
            timer = timer - 1;
            s.setSelectesCoalition(-1);
        }
   
     
        else if(timer == 0)
        {
            //time to decide - join policy     
            mJoinPolicy -> joinParty(s,*this); 
            //change the state to joined
            mState = Joined;
            
          
        }
    }
    else if (mState == Joined || mState == Waiting)
    {
        //sign that we didnt joined to any coalition
        s.setSelectesCoalition(-1);
    }

}

  //rule-of-5
  //-----------------------------------------------------------------------------------
    //destructor
    Party::~Party()
    {
        if(mJoinPolicy)
        {
            delete mJoinPolicy;
            mJoinPolicy = nullptr;
        } 

    }
     //copy constructor
    Party::Party(const Party &other) : mId(other.mId),mName(other.mName),mMandates(other.mMandates),mJoinPolicy(other.mJoinPolicy->clone()),mState(other.mState),
    timer(other.timer),maxMandates(other.maxMandates),coalitionMaxMandates(other.coalitionMaxMandates),coalitionLastOffer(other.coalitionLastOffer),
    agentIdLastOffer(other.agentIdLastOffer),agentIdMaxMandates(other.agentIdMaxMandates){}

    //copy assignment operator
    Party &Party::operator=(const Party &other)
    {
        if(this != &other)
        {
            mId = other.mId;
            mName = other.mName;
            mMandates = other.mMandates;

            delete mJoinPolicy;
            mJoinPolicy = nullptr;
            mJoinPolicy = other.mJoinPolicy->clone();

            mState = other.mState;
            timer = other.timer;

            maxMandates = other.maxMandates;
            coalitionMaxMandates = other.coalitionMaxMandates;
            coalitionLastOffer = other.coalitionLastOffer;
            agentIdLastOffer = other.agentIdLastOffer;
            agentIdMaxMandates = other.agentIdMaxMandates;

        }
        return *this;
    }

    //move constructor
    Party::Party(Party &&other) : mId(other.mId),mName(other.mName),mMandates(other.mMandates),mJoinPolicy(other.mJoinPolicy->clone()),mState(other.mState),
    timer(other.timer),maxMandates(other.maxMandates),coalitionMaxMandates(other.coalitionMaxMandates),coalitionLastOffer(other.coalitionLastOffer),
    agentIdLastOffer(other.agentIdLastOffer),agentIdMaxMandates(other.agentIdMaxMandates){}

    //move assignment operator
    Party &Party::operator=(Party &&other)
    {
        if(this != &other)
       {
            mId = other.mId;
            mName = other.mName;
            mMandates = other.mMandates;

            delete mJoinPolicy;
            mJoinPolicy = nullptr;
            mJoinPolicy = other.mJoinPolicy->clone();

            mState = other.mState;
            timer = other.timer;

            maxMandates = other.maxMandates;
            coalitionMaxMandates = other.coalitionMaxMandates;
            coalitionLastOffer = other.coalitionLastOffer;
            agentIdLastOffer = other.agentIdLastOffer;
            agentIdMaxMandates = other.agentIdMaxMandates;

        }
        return *this;
    }

     

       
