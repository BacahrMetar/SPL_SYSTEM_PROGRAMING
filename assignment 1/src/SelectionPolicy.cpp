#include "SelectionPolicy.h"
#include "Simulation.h"


SelectionPolicy* MandatesSelectionPolicy::clone() const
{
    return new MandatesSelectionPolicy();
}

SelectionPolicy* EdgeWeightSelectionPolicy::clone() const
{
    return new EdgeWeightSelectionPolicy();
}

void MandatesSelectionPolicy::select(Simulation &sim,Agent &agent){
   //find the valids neighbors and find which party to select, with biggest mandates amount
    int maxMandates = -1;
    int party = -1;
    int agentId = -1; //will keep the agentid with most mandates offer
    int neighborsSize = sim.getNeighbors().size();
   for(int i = 0; i < neighborsSize ; i++)
   {
     //if exist a neigbord to the agent party, and the state is not joined
        if(sim.getNeighbors()[i] > 0 && !(sim.getGraph().getMVertices()[i].getState() == Joined) )
        {       
                if(sim.getPropose()[i][agent.getCoalitionId()] == 0 ) //so my coalition hasnt offerd yet
                {
                    int currMandates = sim.getGraph().getMVertices()[i].getMandates();
                    if( currMandates > maxMandates)
                    {
                        //if i found a party with more mandates
                        party = i;
                        maxMandates = currMandates;
                        agentId = agent.getId();

                    }
                }

        }
   }
   //update the offer variable - will help to mark 
   sim.setOffer(party);
   sim.setAgentId(agentId);
  
}


void EdgeWeightSelectionPolicy::select(Simulation &sim,Agent &agent){
    int maxEdgeWeight = -1;
    int party = -1;
    int agentId = -1; //will keep the agent id with max edge weight
    int neighborsSize = sim.getNeighbors().size();
   for(int i = 0; i < neighborsSize ; i++)
   {
     //if exist a neigbord to the agent party, and the state is not joined
        if(sim.getNeighbors()[i] > 0)
        {
             if(!(sim.getGraph().getMVertices()[i].getState() == Joined) )
            {       
                if(sim.getPropose()[i][agent.getCoalitionId()] == 0 ) //so my coalition hasnt offerd yet
              
                {
                    int currentMaxWeight = sim.getGraph().getEdges()[i][agent.getPartyId()];
                        // int currentMaxWeight = sim.getGraph().getEdges()[0][0];                    
                    if( currentMaxWeight > maxEdgeWeight)
                    {
                        //if i found a party with bigger edge
                        party = i;
                        maxEdgeWeight = currentMaxWeight;
                         agentId = agent.getId();
                    }
                }

            }
        }
   }
   //update the offer variable - will help to mark 
    sim.setOffer(party);
    sim.setAgentId(agentId);

}







































