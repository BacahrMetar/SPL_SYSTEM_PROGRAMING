#pragma once
//Forward declaration 
class Simulation;
class Party;

class JoinPolicy {
     public:
    //virtual method will be override
    virtual void joinParty(Simulation &sim, Party &party) = 0;
    virtual JoinPolicy* clone() const = 0 ;
    virtual ~JoinPolicy() = default;
};




class MandatesJoinPolicy : public JoinPolicy
{
     public:
     void joinParty(Simulation &sim,Party &party) override;
     virtual ~MandatesJoinPolicy() override = default;
     virtual JoinPolicy* clone() const override;

};

class LastOfferJoinPolicy : public JoinPolicy 
{
     public:
     void joinParty(Simulation &sim,Party &party) override;
     virtual ~LastOfferJoinPolicy() override = default;
     virtual JoinPolicy* clone() const override;


};