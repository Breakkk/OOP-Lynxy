all: main

main: test.o sherlockDetect.o HashFactory.o Manual.o
	g++ test.o sherlockDetect.o HashFactory.o Manual.o -o main -std=c++11
test.o: test.cpp
	g++ -c test.cpp -o test.o -std=c++11
sherlockDetect.o: sherlockDetect.cpp
	g++ -c sherlockDetect.cpp -o sherlockDetect.o -std=c++11
HashFactory.o: HashFactory.cpp
	g++ -c HashFactory.cpp -o HashFactory.o -std=c++11
Manual.o: Manual.cpp
	g++ -c Manual.cpp -o Manual.o -std=c++11

clean:
	del *.o
