simple Node
{
    parameters:
        @display("i=abstract/router");
    gates:
        inout gate[];
}

network cdfsN
{
    parameters:

        @display("bgb=2205.5337,743.2512");

    types:
        channel Ch extends ned.DelayChannel
        {
            delay = 100ms;
        }
    submodules:

        node: Node {
            @display("p=81,59;i=abstract/router");
        }
        node1: Node {
            @display("p=385,65;i=abstract/router");
        }
        node2: Node {
            @display("p=684,71;i=abstract/router");
        }
        node3: Node {
            @display("p=86,239;i=abstract/router");
        }
        node4: Node {
            @display("p=385,245;i=abstract/router");
        }
        node5: Node {
            @display("p=691,239;i=abstract/router");
        }


    //                node[nodeCount]: Node;
    connections:
//                for i=0..(nodeCount-2) {
//                    node[i].gate++ <--> Ch <--> node[i+1].gate++;
//                    node[i].gate++ <--> Ch <--> node[nodeCount-i-1].gate++;
//                }




        node5.gate++ <--> {  delay = 90ms; } <--> node1.gate++;
        node1.gate++ <--> {  delay = 90ms; } <--> node2.gate++;
        node2.gate++ <--> {  delay = 90ms; } <--> node5.gate++;
        node5.gate++ <--> {  delay = 90ms; } <--> node4.gate++;
        node4.gate++ <--> {  delay = 90ms; } <--> node3.gate++;
        node4.gate++ <--> {  delay = 90ms; } <--> node1.gate++;
        

        node.gate++ <-->{  delay = 90ms; } <--> node1.gate++;
        node1.gate++ <-->{  delay = 90ms; } <--> node.gate++;
        node.gate++ <-->{  delay = 90ms; } <--> node3.gate++;
        node3.gate++ <-->{  delay = 90ms; } <--> node.gate++;
        node.gate++ <-->{  delay = 300ms; } <--> node4.gate++;
        node4.gate++ <-->{  delay = 300ms; } <--> node.gate++;
}

