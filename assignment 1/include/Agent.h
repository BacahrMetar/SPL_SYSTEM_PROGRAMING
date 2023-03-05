#pragma once
//includes
#include <vector>
#include "Graph.h"

//Forward declaration 
class SelectionPolicy;
class Simulation;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent(int agentId, int partyId,int coalitionId,const Agent& other);
    

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    void setCoalition(int _coaltionId);
    int getCoalitionId() const;
    void setId(int id);
    
    //rule-of-5.
    //-------------------------------------------------------------   
    ~Agent();//destructor
    Agent(const Agent &other);//copy constructor
    Agent &operator=(const Agent &other); //copy assignment operator
    Agent(Agent &&other);//move constructor
    Agent &operator=(Agent &&other);  //move assignment operator
    
private:
    int mAgentId;
    int mPartyId;
    int coalition;//keep the coalition id that the agent belongs to
    SelectionPolicy *mSelectionPolicy;

};
