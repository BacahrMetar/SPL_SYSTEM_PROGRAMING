#include "JoinPolicy.h"
////// added
#include "Simulation.h"


JoinPolicy* MandatesJoinPolicy::clone() const
{
    return new MandatesJoinPolicy();
}

JoinPolicy* LastOfferJoinPolicy::clone() const
{
    return new LastOfferJoinPolicy();
}

void MandatesJoinPolicy::joinParty(Simulation &sim,Party &party)
{
    sim.setSelectesCoalition(party.getCoalitionMaxMandates());
    sim.setAgentIdFromParty(party.getAgentIdMaxMandates());

}

void LastOfferJoinPolicy::joinParty(Simulation &sim,Party &party)
{
    sim.setSelectesCoalition(party.getCoalitionLastOffer());
    sim.setAgentIdFromParty(party.getAgentIdLastOffer());


}

