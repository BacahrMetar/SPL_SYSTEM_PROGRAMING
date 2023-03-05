#pragma once
#include <vector>
#include "Graph.h"
#include "Agent.h"
using std::string;
using std::vector;

class Party;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);
    void step();
    bool shouldTerminate() const;
    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;


 
   //our code
    //getters
    //---------------------------------------------------
    const vector<vector<int>> getPartiesByCoalitions() const;
    const vector<int> getNeighbors() const;
    const vector<vector<int>> &getPropose() const;
    const vector<vector<int>> &getCoalitionStatus() const;
    int getOffer() const;
    int getAgentId() const;
    int getCountMaxMandates() const;
    int getCountAlreadyJoined() const;
    int getAgentIdFromParty() const ;

    //setters
    //----------------------------------------------------
    void setOffer(int offer);
    void setPropose(int partId, int coalitionId);
    void setCoalitionStatus(int partId ,int coalitionId);
    void setSelectesCoalition(int coalition);
    void setAgentId (int agentid);
    void setCountAlreadyJoined(int joinedAmount);
    void setCountMaxMandates(int maxMandates);
    void setAgentIdFromParty(int _agentId);
    void setCoalitionStatusOrder();
    

private:
    Graph mGraph;
    vector<Agent> mAgents;
    
    //our code
    //-------------------------------------------------------------------------------------------------
    int offer;
    int selectedCoalition;//represent the selected coalition
    int agentId;//represent the agentId thah made an offer
    int agentFromParty;//represent the agentId from the selectedParty
    int countMaxMandates;//represent the current maxMandates
    int countAlreadyJoined;//represent the amount of parties that alraedy joined
    

    vector<int> neighbors; // a pointer to negibors
    vector<vector<int>> propose;//for each party whic coalition already propose it to join
    vector<vector<int>> coalitionStatus;//which partys alredy belong to the coaliton
    vector<int> currentCoalitionMandates; // vector that keeps the mandates for each coalitioin
    vector<vector<int>> coalitionStatusByOrder; //which partys alredy belong to the coaliton -by join in order
};
