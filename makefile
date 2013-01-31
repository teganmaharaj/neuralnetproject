all: self

signals:
	g++ -c -o signal.o Neurons/Signal.cpp

connections: signals
	g++ -c -o connection.o Neurons/Connection.cpp

neurons: connections signals
	g++ -c -o neuron.o Neurons/Neuron.cpp
	g++ -c -o neuron.o Neurons/InputNeuron.cpp
	g++ -c -o neuron.o Neurons/OutputNeuron.cpp

brain: connections neurons
	g++ -c -o brain.o Neurons/Brain.cpp

self: neurons brain
	g++ -o main Neurons/Main.cpp neuron.o brain.o

clean:
	rm -f *.o ~*
