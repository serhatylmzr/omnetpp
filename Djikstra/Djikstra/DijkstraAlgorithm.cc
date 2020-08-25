#include <string.h>
#include <omnetpp.h>
#include <limits>

#define ROOT_NODE 2

using namespace omnetpp;
std::vector<std::string>  sortedNodes;
std::vector< double > distances;

int INF = std::numeric_limits<int>::max();

class Node : public cSimpleModule
{
    double totalCost;
    cMessage *msg1 = new cMessage("message", 1);
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

Define_Module(Node);

void Node::initialize()
{
    if (this->getId() == ROOT_NODE) {
        sortedNodes.push_back(getName());
        totalCost = 0;
        distances.push_back(totalCost);
        for(int i =0 ; i<this->gateCount()/2; i++)
        {
            send(this->msg1->dup(), "gate$o", i);
        }
    }
    else{
        totalCost = INF;
    }

}
void Node::handleMessage(cMessage *msg)
{
    cGate *arrival_gate = msg->getArrivalGate();
    if(strcmp(msg->getName(), "message") == 0){
        if(totalCost == INF){

            sortedNodes.push_back(this->getName());

            gate("gate$o", arrival_gate->getIndex())->setDisplayString("ls=green,3");
                            arrival_gate->getPathStartGate()->setDisplayString("ls=purple,3");

            totalCost = msg->getArrivalTime().dbl();
            distances.push_back(totalCost);
            for(int i =0 ; i<this->gateCount()/2; i++)
            {
                send(this->msg1->dup(), "gate$o", i);
            }
        }

    }


}

void Node::finish()
{
    if(this->getName() == sortedNodes[sortedNodes.size()-1]){
        for(int i=0;i<sortedNodes.size();i++){
        EV << "Düğüm Sonlandı: " << sortedNodes[i] << " düğümüne varış maliyeti " << distances[i] << " ms'dir. \n";
        }
    }
}
