#include <string.h>
#include <omnetpp.h>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace omnetpp;

class Node : public cSimpleModule
{
    std::vector< int > colorPalette = {1,2,3,4};
    std::vector< int > myNeighbours;
    std::vector< int > received;
    bool round_recvd;
    bool round_over;
    bool colored;
    int nodeColor;
    cMessage *msg1 = new cMessage("neighbourFind",0);
    cMessage *msg2 = new cMessage("round", 0);
    cMessage *msg3 = new cMessage("color", 0);
    cMessage *msg4 = new cMessage("discard", 0);
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

Define_Module(Node);

void Node::initialize()
{
    this->colored = false;
    this->nodeColor = 0;
    this->round_recvd = false;
    this->round_over = false;
    //Komşu listesini doldurmak için mesaj yolluyoruz
        for(int i = 0; i < this->gateCount() / 2; i++){
            send(this->msg1-> dup(), "gate$o", i);
        }
}

void Node::handleMessage(cMessage *msg)
{
    cGate *arrival_gate = msg->getArrivalGate();
    int prevNodeID = arrival_gate->getPreviousGate()->getOwnerModule()->getId();
    int nodeID = this->getId();

    if(strcmp(msg->getName(), "neighbourFind") == 0){
        auto control = std::find(std::begin(myNeighbours),std::end(myNeighbours), prevNodeID);
        if(control == std::end(myNeighbours)){
            this->myNeighbours.push_back(prevNodeID);
        }
        if(this->myNeighbours.size() == this->gateCount() / 4){
            for(int i = 0; i < this->gateCount() / 4; i++){
                send(this->msg2->dup(), "gate$o", i);
            }
        }
    }
    if(this->round_over == false){

        if(strcmp(msg->getName(), "round") == 0){

            if(this->colored == false){
                // Komşu listesindeki en büyük node u ilk sıraya koy
                for(int i = 0; i< myNeighbours.size() ; i++){
                    if(myNeighbours[0]< myNeighbours[i]){
                        std::iter_swap(myNeighbours.begin() + 0 ,myNeighbours.begin() + i);
                    }
                }
                // nodeId komşularının node undan fazla ise veya komşu listesi boş ise
                if(nodeID > myNeighbours[0] || this->myNeighbours.size() == 0){
                    this->nodeColor = this->colorPalette[0];
                    this->colored = true;
                    this->round_recvd = true;
                    // Renk mesajını herkese yolluyor
                    for(int i = 0; i<this->gateCount() / 2; i++){
                        this->msg3->setKind(this->nodeColor);
                        send(this->msg3->dup(),"gate$o", i);
                        // Renk sırasına göre  node un rengini değiştiriyor...
                        if(colorPalette[0] == 1){
                            arrival_gate->getPreviousGate()->getOwnerModule()->getDisplayString().setTagArg("i",1,"red");
                        }else if(colorPalette[0] == 2){
                            arrival_gate->getPreviousGate()->getOwnerModule()->getDisplayString().setTagArg("i",1,"blue");
                        }else if(colorPalette[0] == 3){
                            arrival_gate->getPreviousGate()->getOwnerModule()->getDisplayString().setTagArg("i",1,"green");
                        }else if(colorPalette[0] == 4){
                            arrival_gate->getPreviousGate()->getOwnerModule()->getDisplayString().setTagArg("i",1,"yellow");
                        }
                    }
                }else{
                    //Discard Mesajı Yolluyor
                    for(int i = 0; i < this->gateCount() / 2; i++){
                        send(this->msg4-> dup(), "gate$o", i);
                    }
                }
            }
        }
        if(strcmp(msg->getName(), "discard") == 0){
            EV << " discard durumundayım\n";
        }

        if(strcmp(msg->getName(), "color") == 0){
            //Mesajı yollayan nodeu komşular listesinden sil renk dizisinden kullandığı rengi sil süreklilik için round mesajı yolla komşularına
            myNeighbours.erase(std::remove(myNeighbours.begin(),myNeighbours.end(),prevNodeID), myNeighbours.end());
            colorPalette.erase(std::remove(colorPalette.begin(),colorPalette.end(),msg->getKind()), colorPalette.end());
            for(int i =0 ; i<this->gateCount() / 2; i++){
                send(this->msg2->dup(), "gate$o", i);
            }
        }
        //Rengini tamamlayan node bir daha giremesin diye
        if(this->round_recvd == true ){
            this->round_over == true;
        }
    }
}

void Node::finish()
{

    EV<< this->getFullName() << "  renk numarası: "<<this->nodeColor<<"\n";
}
