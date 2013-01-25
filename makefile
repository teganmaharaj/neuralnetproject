all:
	make self

signals:
	g++ -c -o signal.o Neurons/Signal.cpp

connections: signals
	g++ -c -o connection.o Neurons/Connection.cpp

neurons: connections signals
	g++ -c -o neuron.o Neurons/Neuron.cpp

brain: neurons
	g++ -c -o brain.o Neurons/Brain.cpp

self: neurons brain
	g++ -o main Neurons/Main.cpp neuron.o brain.o

clean:
	rm -f *.o ~*
