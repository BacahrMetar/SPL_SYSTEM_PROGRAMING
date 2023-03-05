#pragma once
//includes
#include <string>
#include "JoinPolicy.h"

using std::string;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 
    //getters
    State getState() const;
    int getMandates() const;
    int getTimer();
    int getPartyId() const;
    int getMaxMandates() const;
    int getCoalitionMaxMandates() const;
    int getCoalitionLastOffer() const;
    int getAgentIdLastOffer() const;
    int getAgentIdMaxMandates() const;
    const string &getName() const;
    State getMstate()  ;
    
    //setters
    void setState(State state);
    void setMaxMandates(int maxMandates);
    void setCoalitionMaxMandates(int party);
    void setCoalitionLastOffer(int party);
    void setAgentIdLastOffer(int agentId);
    void setAgentIdMaxMandates(int agentId);
    void setTimer(int timer);

    

    void step(Simulation &s);


    //rule-of-5
    //-------------------------------------------------------------  
    ~Party();  //destructor   
    Party(const Party &other);//copy constructor   
    Party &operator=(const Party &other); //copy assignment operator  
    Party(Party &&other); //move constructor 
    Party &operator=(Party &&other);//move assignment operator





private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int timer;
    int maxMandates; //  keep the max mandates from all offers
    int coalitionMaxMandates;// keep the coalition with the max mandates that offerd the party to join her
    int coalitionLastOffer;// keep the last offer party;
    int agentIdLastOffer; // keep the agent id that made the last offer
    int agentIdMaxMandates; // keep the agent id that made an offer with max mandates

};
