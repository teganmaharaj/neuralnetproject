all: clean self test2

test1:
	./main begin.net 111 y
	nano begin.net

test2:
	./main middle.net 101 0
	nano middle.net

run:
	./main middle.net 101 0

test3:
	./fresh middle.net 111100111 2
	nano middle.net

signals:
	g++ -c -o signal.o Neurons/Signal.cpp

connections: signals
	g++ -c -o node.o Neurons/Node.cpp
	g++ -c -o connection.o Neurons/Connection.cpp

neurons: connections signals
	g++ -c -o neuron.o Neurons/Neuron.cpp
	g++ -c -o inputneuron.o Neurons/InputNeuron.cpp
	g++ -c -o outputneuron.o Neurons/OutputNeuron.cpp

brain: connections neurons
	g++ -c -o layer.o Neurons/Layer.cpp
	g++ -c -o playground.o Neurons/Playground.cpp
	g++ -c -o brain.o Neurons/Brain.cpp

brainverb: connections neurons
	g++ -c -o layer.o Neurons/Layer.cpp
	g++ -c -o playground.o -Dverbose_output_file Neurons/Playground.cpp
	g++ -c -o brain.o -Dverbose_output_file Neurons/Brain.cpp


self: neurons brain
	g++ -o main Neurons/Main.cpp brain.o playground.o layer.o signal.o connection.o neuron.o inputneuron.o outputneuron.o node.o

verb: neurons brainverb
	g++ -o verb -DFRESH_BRAIN Neurons/Main.cpp brain.o playground.o layer.o signal.o connection.o neuron.o inputneuron.o outputneuron.o node.o
	./verb test.net 111 1
	nano test.net

fresh: neurons brain
	g++ -o fresh -DFRESH_BRAIN Neurons/Main.cpp brain.o playground.o signal.o connection.o neuron.o inputneuron.o outputneuron.o node.o layer.o
	make test3

clean:
	rm -f *.o ~*
