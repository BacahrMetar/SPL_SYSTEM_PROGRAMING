#pragma once
//includes
#include <vector>
#include "Party.h"
using std::vector;

class Graph
{
public:
    Graph(vector<Party> vertices, vector<vector<int>> edges);
    int getMandates(int partyId) const;
    int getEdgeWeight(int v1, int v2) const;
    int getNumVertices() const;
    const Party &getParty(int partyId) const;
    vector<Party> getMVertices() const;
    vector<vector<int>> getEdges() const ;
    void setVertexState(int partyId,State state);
    void setVertexStatus(int partyId,int offerPartyMandates,int coalition,int agentId);
    vector<Party> &getMVerticesRef() ;
    void setVertexMaxMandates(int partyId,int coalitionId, int mandatesAmount,int agentId);

    



private:
    vector<Party> mVertices;
    vector<vector<int>> mEdges;
};
