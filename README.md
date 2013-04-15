neuralnetproject
================

CSC310 Software Engineering

An artificial neural network is a set of nodes with connections between them that each have a "weight", or cost to traverse the connection.
To train the neural net, you give it some kind of input (like a drawing of a number), and if it gives the correct output (if it correctly identifies the number), you reward all the connection-paths that brought it to that output (you reduce the cost of traversing those connections later).
If the neural network gives an incorrect output, you punish all the connection-paths leading to that output (increase the cost of going along that path).

After doing this many times, the neural network will have sets of low-cost paths that make it more likely to reach correct outputs.
