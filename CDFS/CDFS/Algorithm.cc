#include <string.h>
#include <omnetpp.h>

#define ROOT_NODE 2

using namespace omnetpp;

class Node : public cSimpleModule
{
    std::string parent_name;
    //node 'a ait komşuların çocuk ve diğerleri olarak tutulduğu dizi
    std::vector< int > othersAndChilds;
    int parent;
    // mesaj tipleri
    cMessage *msg1 = new cMessage("probe", 1);
    cMessage *msg2 = new cMessage("accept", 1);
    cMessage *msg3 = new cMessage("reject", 1);

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

Define_Module(Node);

void Node::initialize()
{
    //başlangıçta herkesin ebeveynini -1 olarak ata
    parent_name = "";
    parent = -1;
    //Başlangıçta Kapı sayısının yarısı kadar yani komşu sayısı kadar others ve childs dizisine 0 ata
    for(int i = 0; i < this->gateCount() / 2; i++){
        this->othersAndChilds.push_back(0);
    }
    //Başlangıç node u root ise parent ını kendi yap ve tüm komşularına probe mesajı yolla
    if (this->getId() == ROOT_NODE) {
        this->parent = ROOT_NODE;
        for(int i =0 ; i<this->gateCount()/2; i++){
              send(this->msg1->dup(), "gate$o", i);
        }
    }
}
//Gecikme süresi en kısa olan node buraya girecek
void Node::handleMessage(cMessage *msg)
{
    //Probe mesajından kapısına eriş
    cGate *arrival_gate = msg->getArrivalGate();
    //Bu node un komşularının kaçı çocuğu kaçı değil sayısını al
    int childCount = 1, otherCount = 0;
            for(int i = 0; i < this->gateCount() / 2; i++){
                if(this->othersAndChilds.at(i) == 1)

                    childCount++;
                else{
                    otherCount++;
                }
            }
    //Eğer Çocuk sayısı ve diğerleri toplamı  komşu sayısına eşit değilse
    if((childCount + otherCount) != this->gateCount() / 2){
        //Gelen mesaj probe türünde ise
        if(strcmp(msg->getName(), "probe") == 0){
            //bu node un babası yoksa babasını mesajı yollayan node yap ,parent ismini al , ack mesajını döndür,tüm komşularına probe yolla
            if(this->parent == -1){
                this->parent = msg->getArrivalGate()->getIndex();
                this->parent_name = msg->getArrivalGate()->getPreviousGate()->getOwner()->getFullName();
                send(this->msg2->dup(), "gate$o", this->parent);
                for(int i =0 ; i<this->gateCount()/2; i++){
                    send(this->msg1->dup(), "gate$o", i);
                }
            }
            else{
                //Babası olduğu için geriye reject mesajı yolluyor
                send(this->msg3->dup(), "gate$o", msg->getArrivalGate()->getIndex());
            }
        }
        if(strcmp(msg->getName(), "accept") == 0){
            //Gelen mesaj ack tipinde ise mesajı yollayan node u çocuğu olarak diziye atıyor
            this->othersAndChilds.at(msg->getArrivalGate()->getIndex()) = 1;
        }
    }
    else{
        this->finish();
    }
}

void Node::finish()
{
    EV << "FINISH: " << this->getFullName() <<  ",    Parent :" << parent_name << "\n";
}

