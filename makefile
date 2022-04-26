all:
	if [ ! -d "./out/" ]; then mkdir out; fi;
	g++ -std=c++14 -g -Wall main.cpp -o ./out/run
	chmod u+x ./out/run
	./out/run

# Compiles and runs unittest
unittest:
	if [ ! -d "./out/" ]; then mkdir out; fi;
	g++ -std=c++14 -g -Wall unittest.cpp -o ./out/test
	chmod u+x ./out/test
	./out/test

# Cleans up all compiled files
clean: 
	rm -r out/*

again: clean
	make