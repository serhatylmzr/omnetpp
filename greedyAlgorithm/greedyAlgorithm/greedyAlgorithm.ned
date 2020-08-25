simple Node
{
    parameters:
        @display("i=abstract/router");
    gates:
        inout gate[];
}

network greedyAlgorithm
{
    parameters:

        @display("bgb=2205.5337,743.2512");


    submodules:

        node: Node {
            @display("p=629.565,74.55375;i=abstract/router");
        }
        node1: Node {
            @display("p=897.40625,71.7925;i=abstract/router");
        }
        node2: Node {
            @display("p=383.81375,356.20126;i=abstract/router");
        }
        node3: Node {
            @display("p=127.0175,74.55375;i=abstract/router");
        }
        node4: Node {
            @display("p=629.565,356.20126;i=abstract/router");
        }
        node5: Node {
            @display("p=127.0175,356.20126;i=abstract/router");
        }

        node6: Node {
            @display("p=897.40625,356.20126");
        }
        node7: Node {
            @display("p=383.81375,74.55375");
        }
    connections:
        node.gate++ <--> {  delay = 120ms; } <-->  node1.gate++;
        node1.gate++ <--> {  delay = 120ms; } <-->  node.gate++;
        node1.gate++ <--> {  delay = 120ms; } <-->  node6.gate++;
        node6.gate++ <--> {  delay = 120ms; } <-->  node1.gate++;
        node6.gate++ <--> {  delay = 120ms; } <-->  node4.gate++;
        node4.gate++ <--> {  delay = 120ms; } <-->  node6.gate++;
        node4.gate++ <--> {  delay = 120ms; } <-->  node2.gate++;
        node2.gate++ <--> {  delay = 120ms; } <-->  node4.gate++;
        node2.gate++ <--> {  delay = 120ms; } <-->  node5.gate++;
        node5.gate++ <--> {  delay = 120ms; } <-->  node2.gate++;
        node5.gate++ <--> {  delay = 120ms; } <-->  node3.gate++;
        node3.gate++ <--> {  delay = 120ms; } <-->  node5.gate++;
        node3.gate++ <--> {  delay = 120ms; } <-->  node7.gate++;
        node7.gate++ <--> {  delay = 120ms; } <-->  node3.gate++;
        node7.gate++ <--> {  delay = 120ms; } <-->  node.gate++;
        node.gate++ <--> {  delay = 120ms; } <-->  node7.gate++;
        node5.gate++ <--> {  delay = 120ms; } <-->  node7.gate++;
        node7.gate++ <--> {  delay = 120ms; } <-->  node5.gate++;
        node7.gate++ <--> {  delay = 120ms; } <-->  node2.gate++;
        node2.gate++ <--> {  delay = 120ms; } <-->  node7.gate++;
        node2.gate++ <--> {  delay = 120ms; } <-->  node.gate++;
        node.gate++ <--> {  delay = 120ms; } <-->  node2.gate++;
        node.gate++ <--> {  delay = 120ms; } <-->  node4.gate++;
        node4.gate++ <--> {  delay = 120ms; } <-->  node.gate++;
        node4.gate++ <--> {  delay = 120ms; } <-->  node1.gate++;
        node1.gate++ <--> {  delay = 120ms; } <-->  node4.gate++;
}
