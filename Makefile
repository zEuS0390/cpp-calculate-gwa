output: CalculateGWA.o
	g++ obj/CalculateGWA.o -o build/CalculateGWA

CalculateGWA.o: src/CalculateGWA.cpp
	g++ -c src/CalculateGWA.cpp -o obj/CalculateGWA.o

clean:
	rm -rf obj/*

