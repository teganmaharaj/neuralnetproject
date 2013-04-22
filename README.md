neuralnetproject
================

- CSC310 Software Engineering
- Demo: http://neuralnet.jordanslaman.com/


##Overview
Meet our friend S.E.A.N.N (software engineering artificial neural network)! 
We've written a neural network in C++ and trained it to identify numbers drawn on a html canvas.

Artificial neural networks use a weighted graph to imitate the way our brain learns things.
As you show SEANN things and tell him what they are, the paths inside his weighted graph will change so that over time (with training), the lowest-cost paths will lead to correct answers.

SEANN is currently able to learn and recognize the numbers 0-9 from drawings.

An artificial neural network is a set of nodes with connections between them that each have a "weight", or cost to traverse the connection.
To train the neural net, you give it some kind of input (like a drawing of a number), and if it gives the correct output (if it correctly identifies the number), you reward all the connection-paths that brought it to that output (you reduce the cost of traversing those connections later).
If the neural network gives an incorrect output, you punish all the connection-paths leading to that output (increase the cost of going along that path).

After doing this many times, the neural network will have sets of low-cost paths that make it more likely to reach correct outputs.


##Setup
The neural net can be executed as a standalone C++ application, or driven through the web frontend.

###Frontend + Backend
The front-end requires a server running PHP, and enough permission to execute commands within it's own directories.
Git clone or manually place the repository into your webserver's document root.

This code will re-compile the neural net for your system and give you a blank brainfile:

	#!! Do this in the /cpp/ directory!
	make fresh && make train && make frozen

Users will not be able to execute malicious code on the server in it's default state.

It would be a good idea to remove the files train.php and make_fresh.php, or to require authentication on those pages to avoid curious/malicious users from modifying or clearing your brainfile. You can also delete or comment out the link to train.php on result.php to remove this element completely.

###Backend
The backend requires  a c compiler and ?
If you would like to run the neural network without the web interface, you can do so by compiling a new copy with the makefile included in /cpp

Create a new brain in final.net (weights random -1 to 1, biases 0)

	make fresh

Create the train executable (all weights/biases are modifiable)

	make train

Create the frozen executable (weights/biases are not modifiable)

	make frozen

Make a new brain file in the file passed

	./fresh {brain file} {garbage string} {garbage string}
	
Modify the weights of the brain(still outputs the answer)

	./train {brain file} {string of inputs} {expected answer}

Will only output the answer of the brain, but this does not do anything to the brain, the same answer will be produced if you give the same input string.

	./frozen {brain file} {string of inputs} {garbage string}


##Libraries and frameworks

Drawing from canvas was adapted from the Thomas Bradley's signature-pad jQuery plugin - http://thomasjbradley.ca/lab/signature-pad/ 
Converting it to an image in PHP was adapted from his signature-to-image script - http://thomasjbradley.ca/lab/signature-to-image/

Bootstrap.js was used as a framework for the front-end, to allow for quick and responsive html/css templating and user interface elements. - http://twitter.github.io/bootstrap/

Background image courtesy of http://subtlepatterns.com/
	
###Credits
This neural net and implementation were created by Geoffrey Guest, JC
Charbonneau, Jordan Slaman, and Tegan Maharaj for CSC310 - Software
Engineering, taught by Lin Jensen at Bishop's University, Winter 2013.
