simple Node //Node class ı  tanımlandı!
{
    parameters:
        @display("i=abstract/router"); // icon felan seçimi
    gates:
        inout gate[];
}

network cdfsN
{
    parameters:
        int nodeCount = 14;
        @display("bgb=2205.5337,743.2512");
    submodules:
        ////
        node: Node {
            @display("p=433.51627,372.76877;i=abstract/router");
        }
        node1: Node {
            @display("p=737.2538,458.36752;i=abstract/router");
        }
        node2: Node {
            @display("p=1049.275,474.935;i=abstract/router");
        }
        node3: Node {
            @display("p=1049.275,245.75125;i=abstract/router");
        }
        node4: Node {
            @display("p=737.2538,245.75125;i=abstract/router");
        }
    connections:

        node.gate++ <--> {  delay = 200ms; } <-->  node1.gate++;
        node.gate++ <--> {  delay = 800ms; } <-->  node4.gate++;
        node1.gate++ <--> {  delay = 200ms; } <-->  node.gate++;
        node4.gate++ <--> {  delay = 800ms; } <-->  node.gate++;
        node1.gate++ <--> {  delay = 100ms; } <-->  node4.gate++;
        node4.gate++ <--> {  delay = 100ms; } <-->  node1.gate++;
        node4.gate++ <--> {  delay = 100ms; } <-->  node3.gate++;
        node3.gate++ <--> {  delay = 100ms; } <-->  node4.gate++;
        node4.gate++ <--> {  delay = 200ms; } <-->  node2.gate++;
        node2.gate++ <--> {  delay = 200ms; } <-->  node4.gate++;
        node2.gate++ <--> {  delay = 400ms; } <-->  node3.gate++;
        node3.gate++ <--> {  delay = 400ms; } <-->  node2.gate++;
        node2.gate++ <--> {  delay = 600ms; } <-->  node1.gate++;
        node1.gate++ <--> {  delay = 600ms; } <-->  node2.gate++;
}

