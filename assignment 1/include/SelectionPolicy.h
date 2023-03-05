#pragma once

//Forward Declaration
class Simulation;
class Agent;


class SelectionPolicy 
{ 
    public:
    //virtual method will be override 
    virtual void select(Simulation &sim, Agent &agent) = 0;
    virtual SelectionPolicy* clone() const = 0 ;
    virtual  ~SelectionPolicy() = default;

};

class MandatesSelectionPolicy: public SelectionPolicy
{ 
    public:
    void select(Simulation &sim, Agent &agent);
    SelectionPolicy* clone() const override;
    ~MandatesSelectionPolicy()  override = default;

};


class EdgeWeightSelectionPolicy: public SelectionPolicy{ 
    public:
   
    void select(Simulation &sim, Agent &agent);
    SelectionPolicy* clone() const override;
    ~EdgeWeightSelectionPolicy() override = default; 

};