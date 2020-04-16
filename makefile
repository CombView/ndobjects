all:
	g++ --std=c++17 -fconcepts main.cpp -o appNDObjs

run:
	./appNDObjs
