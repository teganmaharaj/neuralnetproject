all: clean self test2

test1:
	./main begin.net 111 y
	nano begin.net

test2:
	./main middle.net 111 1
	nano middle.net

run:
	./main middle.net 1110010101 1

nur:
	./main middle.net 0000010001 0

test3:
	./fresh middle.net 111100111 2
	nano middle.net

freshthree:
	./fresh three.net 0 0

both:
	./main middle.net 0000000000 0
	./main middle.net 0000110000 1
	./main middle.net 0001001000 2
	./main middle.net 0001111000 3
	./main middle.net 0010000100 4
	./main middle.net 0010110100 5
	./main middle.net 0011001100 6
	./main middle.net 0011111100 7
	./main middle.net 0100000010 8
	./main middle.net 0100110010 9

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
	g++ -c -o brain.o -DTRAIN Neurons/Brain.cpp

brainverb: connections neurons
	g++ -c -o layer.o Neurons/Layer.cpp
	g++ -c -o playground.o -Dverbose_output_file Neurons/Playground.cpp
	g++ -c -o brain.o -Dverbose_output_file Neurons/Brain.cpp

brainfreeze: connections neurons
	g++ -c -o layer.o Neurons/Layer.cpp
	g++ -c -o playground.o Neurons/Playground.cpp
	g++ -c -o brain.o Neurons/Brain.cpp

self: neurons brain
	g++ -o train Neurons/Main.cpp brain.o playground.o layer.o signal.o connection.o neuron.o inputneuron.o outputneuron.o node.o

frozen: neurons brainfreeze
	g++ -o frozen Neurons/Main.cpp brain.o playground.o layer.o signal.o connection.o neuron.o inputneuron.o outputneuron.o node.o

verb: neurons brainverb
	g++ -o verb -DFRESH_BRAIN Neurons/Main.cpp brain.o playground.o layer.o signal.o connection.o neuron.o inputneuron.o outputneuron.o node.o
	./verb test.net 111 1
	nano test.net

fresh: neurons brain
	g++ -o fresh -DFRESH_BRAIN Neurons/Main.cpp brain.o playground.o signal.o connection.o neuron.o inputneuron.o outputneuron.o node.o layer.o
	make test3

clean:
	rm -f ~* *.o
