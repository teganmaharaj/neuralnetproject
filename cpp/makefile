all: train

signals:
	g++ -c -o signal.o Neurons/Signal.cpp

connections: signals
	g++ -c -o node.o Neurons/Node.cpp
	g++ -c -o connection.o Neurons/Connection.cpp

neurons: connections signals
	g++ -c -o system.o Neurons/System.h
	g++ -c -o neuron.o Neurons/Neuron.cpp
	g++ -c -o inputneuron.o Neurons/InputNeuron.cpp
	g++ -c -o outputneuron.o Neurons/OutputNeuron.cpp

brain: connections neurons
	g++ -c -o layer.o Neurons/Layer.cpp
	g++ -c -o playground.o Neurons/Playground.cpp
	g++ -c -o brain.o -DTRAIN Neurons/Brain.cpp

brainverb: connections neurons
	g++ -c -o layer.o Neurons/Layer.cpp
	g++ -c -o playground.o -Dverbose_output_file Neurons/Playground.cpp
	g++ -c -o brain.o -Dverbose_output_file Neurons/Brain.cpp

brainfreeze: connections neurons
	g++ -c -o layer.o Neurons/Layer.cpp
	g++ -c -o playground.o Neurons/Playground.cpp
	g++ -c -o brain.o Neurons/Brain.cpp

train: neurons brain
	g++ -o train -DTRAIN Neurons/Main.cpp brain.o playground.o layer.o signal.o connection.o neuron.o inputneuron.o outputneuron.o node.o

frozen: neurons brainfreeze
	g++ -o frozen Neurons/Main.cpp brain.o playground.o layer.o signal.o connection.o neuron.o inputneuron.o outputneuron.o node.o

verb: neurons brainverb
	g++ -o verb -DFRESH_BRAIN Neurons/Main.cpp brain.o playground.o layer.o signal.o connection.o neuron.o inputneuron.o outputneuron.o node.o system.o
	./verb test.net 111 1
	nano test.net

fresh: neurons brain
	g++ -o fresh -DFRESH_BRAIN Neurons/Main.cpp brain.o playground.o signal.o connection.o neuron.o inputneuron.o outputneuron.o node.o layer.o
	./fresh final.net 0 0

clean:
	rm -f ~* *.o
