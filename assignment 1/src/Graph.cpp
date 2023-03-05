#include "Graph.h"


Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) 
{
    // You can change the implementation of the constructor, but not the signature!
}

//getters
//----------------------------------------------------------

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}

vector<Party> Graph::getMVertices() const
{
    return mVertices;
}

vector<Party> &Graph::getMVerticesRef() 
{
    return mVertices;
}


vector<vector<int>> Graph::getEdges() const
{
    return mEdges;
}


//setters
//-------------------------------------------------------------------------
void Graph::setVertexState(int partyId,State state)
{
    mVertices[partyId].setState(state);
}

//methods
//-------------------------------------------------------------------------

//this method will update the filed of the party after reciving an offer from agent
void Graph::setVertexStatus(int partyId,int offerPartyMandates,int coalition,int agentId)
{
    //set the verex mState status
    if( mVertices[partyId].getState() == Waiting)
    {
     mVertices[partyId].setState(CollectingOffers);
     
    }

    mVertices[partyId].setCoalitionLastOffer(coalition);
    mVertices[partyId].setAgentIdLastOffer(agentId);
    

    int currentMaxMandates = mVertices[partyId].getMaxMandates();
    if(offerPartyMandates > currentMaxMandates)
    {
        mVertices[partyId].setMaxMandates(offerPartyMandates);
        mVertices[partyId].setCoalitionMaxMandates(coalition);
        mVertices[partyId].setAgentIdMaxMandates(agentId);
        
    }



}
void Graph::setVertexMaxMandates(int partyId,int coalitionId, int mandatesAmount,int agentId)
{
    mVertices[partyId].setMaxMandates(mandatesAmount);
    mVertices[partyId].setCoalitionMaxMandates(coalitionId);
    mVertices[partyId].setAgentIdMaxMandates(agentId);
    
}

