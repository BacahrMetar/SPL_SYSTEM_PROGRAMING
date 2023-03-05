#include "Agent.h"
#include "SelectionPolicy.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId),coalition(agentId),mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!
    
}
Agent::Agent(int _agentId, int _partyId,int _coalitionId, const Agent& other):mAgentId(_agentId),mPartyId(_partyId),coalition(_coalitionId), mSelectionPolicy(other.mSelectionPolicy->clone()){}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

int Agent::getCoalitionId() const
{
    return coalition;
}
void Agent::setCoalition(int _coaltionId)
{
coalition = _coaltionId;
}
void Agent::setId(int _id)
{
    mAgentId = _id;
}

void Agent::step(Simulation &sim)
{
    mSelectionPolicy -> select(sim, *this);
}

//rule-of-5
//---------------------------------
//destructor
Agent::~Agent()
{
    if(mSelectionPolicy)
    {
        delete mSelectionPolicy;
        mSelectionPolicy = nullptr; 
    }
}

//copy constructor
Agent::Agent(const Agent &other) :mAgentId(other.mAgentId),mPartyId(other.mPartyId),coalition(other.coalition),mSelectionPolicy(other.mSelectionPolicy->clone()){}

//copy assignment operator
Agent &Agent::operator=(const Agent &other)
{
    if(this != &other)
    {
         mAgentId = other.mAgentId;
         mPartyId = other.mPartyId;
         coalition = other.coalition;

         delete mSelectionPolicy;
         mSelectionPolicy = nullptr;
         mSelectionPolicy = other.mSelectionPolicy->clone(); 

    }
    return *this;
}

//move constructor
Agent::Agent(Agent &&other) :mAgentId(other.mAgentId),mPartyId(other.mPartyId),coalition(other.coalition),mSelectionPolicy(other.mSelectionPolicy->clone()){}

//move assignment operator
Agent &Agent::operator=(Agent &&other)
{
    if(this != &other)
    {
         mAgentId = other.mAgentId;
         mPartyId = other.mPartyId;
         coalition = other.coalition;

         delete mSelectionPolicy;
         mSelectionPolicy = nullptr;
         mSelectionPolicy = other.mSelectionPolicy->clone(); 

    }
    return *this;
}




