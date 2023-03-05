#include "Simulation.h"
#include "Agent.h"
#include "Graph.h"
#include "Party.h"


#include <vector>
#include <iostream>


Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents),offer(-1),selectedCoalition(-1),agentId(-1), agentFromParty(-1),countMaxMandates(0),countAlreadyJoined(agents.size()),
neighbors(vector<int>()),propose(vector<vector<int>>()),coalitionStatus(vector<vector<int>>()),currentCoalitionMandates(vector<int>()),coalitionStatusByOrder(vector<vector<int>>())
{
    
       //init the neighbors with null
        currentCoalitionMandates = vector<int>(mAgents.size(),0);
        //init a vector of vectors rows =party.size coulumns = coalitions amount
        propose = vector<vector<int>> (mGraph.getMVertices().size(), vector<int> (agents.size(), 0));
        coalitionStatus = vector<vector<int>> (mGraph.getMVertices().size(), vector<int> (agents.size(), 0));
        //vector that represent the coalitions party sort by entering order
        coalitionStatusByOrder = vector<vector<int>> (mAgents.size());
        
    for(Agent agent : agents)
    { 
        //set for each agent his coalition
        agent.setCoalition(agent.getId());
        //set a party with agent to state Joined
        mGraph.setVertexState(agent.getPartyId(),Joined);
        //adding the party with the agent to the coalition 
        coalitionStatus[agent.getPartyId()][agent.getCoalitionId()] = 1; 
        currentCoalitionMandates[agent.getCoalitionId()] = mGraph.getParty(agent.getPartyId()).getMandates();      
        if(mGraph.getParty(agent.getPartyId()).getMandates() > countMaxMandates)
        countMaxMandates = mGraph.getParty(agent.getPartyId()).getMandates();

    }

     setCoalitionStatusOrder();

       
}
void Simulation::setCoalitionStatusOrder()
{
    //inserting the parties to their coalition before any changes made
    for(Agent agent : mAgents)
    {
        int coalition = agent.getCoalitionId() ;
        int partyId = agent.getPartyId();
        if( coalition >-1)
        {
            coalitionStatusByOrder[coalition].push_back(partyId);
        }
    }
}

void Simulation::step()
{
  
    //foreach on all the vertices (parties)
    for(Party &party : mGraph.getMVerticesRef())
    {
        
        party.step(*this);
        
        if(selectedCoalition != -1)
        {
            countAlreadyJoined += 1;
            //adding the mandates to corret coalition
            currentCoalitionMandates[selectedCoalition] += party.getMandates();
            //keep the coalition with the max mandates-helper to ShouldTerminate func
            if(currentCoalitionMandates[selectedCoalition] > countMaxMandates)
            {
                countMaxMandates = currentCoalitionMandates[selectedCoalition];
            }

            //join the party to the coalition
            coalitionStatus[party.getPartyId()][selectedCoalition] = 1;
            coalitionStatusByOrder[selectedCoalition].push_back(party.getPartyId());
            //clone an agent to the joined party
            Agent clonedAgent = Agent(mAgents.size(),party.getPartyId(),selectedCoalition ,mAgents[getAgentIdFromParty()]);      

  
            mAgents.push_back(clonedAgent);
            int check1= mGraph.getMVertices().size();
            for(int i=0;i<check1; i++)
            {
                
                if(mGraph.getMVertices()[i].getState() == CollectingOffers)
                {
                    if(propose[i][selectedCoalition] == 1)
                        {
                           if(mGraph.getMVertices()[i].getMaxMandates() < currentCoalitionMandates[selectedCoalition])
                           {
                            int aId=mGraph.getMVertices()[i].getAgentIdMaxMandates();
                            mGraph.setVertexMaxMandates(i,selectedCoalition,currentCoalitionMandates[selectedCoalition],aId);
                           } 
                        }

                }

            }

        }

    }
    
    //foreach on all agents
    for(Agent agent : mAgents)
    {
        neighbors = mGraph.getEdges()[agent.getPartyId()];
        agent.step(*this);
        //check the partyId that we get an offer from 
        if(offer != -1)
        {
            //update that party = offer recived an offer from acoalition
            propose[offer][agent.getCoalitionId()] = 1;
            //cuurent amount of mandates for this coalition            
            int offeredCoalition = currentCoalitionMandates[agent.getCoalitionId()];
            int coalition = agent.getCoalitionId();
            //update he party with the relvant information
            mGraph.setVertexStatus(offer,offeredCoalition,coalition,agentId);

        }
       
    }
}
//getters
//------------------------------------------------------------------------
const vector<int> Simulation::getNeighbors() const
{
    return neighbors;

}

const vector<vector<int>> &Simulation::getPropose() const
{
    return propose;

}
const vector<vector<int>> &Simulation::getCoalitionStatus() const
{
    return coalitionStatus;
    ;

}
int Simulation::getOffer() const
{
    return offer;
}

int Simulation::getAgentId() const
{
    return agentId;
}

int Simulation::getCountMaxMandates() const
{
    return countMaxMandates;
}

int Simulation::getCountAlreadyJoined() const
{
    return countAlreadyJoined;
}

int Simulation::getAgentIdFromParty() const
{
    return agentFromParty;
}


//setters
//-----------------------------------------------------------------------
void Simulation::setOffer(int _offer) 
{
    offer = _offer;
}

void Simulation::setPropose(int _partyId,int _coalitionId) 
{
    propose[_partyId][_coalitionId] = 1;
}

void Simulation::setCoalitionStatus(int _partyId,int _coalitionId) 
{
    coalitionStatus[_partyId][_coalitionId] = 1;
}

void Simulation::setSelectesCoalition(int _coalition)
{
    selectedCoalition = _coalition;
}

void Simulation::setAgentId(int _agentId)
{
    agentId = _agentId;
}

void Simulation::setCountAlreadyJoined(int _joinedAmount)
{
    countAlreadyJoined = _joinedAmount;
}

void Simulation::setCountMaxMandates(int _maxMandates)
{
    countMaxMandates = _maxMandates;
}
void Simulation::setAgentIdFromParty(int _agentId)
{
    agentFromParty = _agentId;
}

bool Simulation::shouldTerminate() const
{
    int numOfParties = mGraph.getMVertices().size() ;
    if(countAlreadyJoined == numOfParties  || countMaxMandates > 60)
       { 
        return true;
       }
    return false;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    
    return coalitionStatusByOrder;
}


