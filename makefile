output: main.o point.o boardTile.o clueBoard.o emptyBoardLoad.o loadClueBoard.o token.o
	g++ -std=c++11 main.o point.o boardTile.o clueBoard.o emptyBoard.o loadClueBoard.o token.o -o clue -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp clueBoard.h token.hpp
	g++ -std=c++11 -c main.cpp

point.o: point.cpp point.h
	g++ -std=c++11 -c point.cpp

boardTile.o: boardTile.cpp boardTile.h point.h
	g++ -std=c++11 -c boardTile.cpp

clueBoard.o: clueBoard.cpp clueBoard.h boardTile.h
	g++ -std=c++11 -c clueBoard.cpp

emptyBoardLoad.o: emptyBoardLoad.cpp clueBoard.h
	g++ -std=c++11 -c emptyBoardLoad.cpp

loadClueBoard.o: loadClueBoard.o clueBoard.h
	g++ -std=c++11 -c loadClueBoard.cpp

token.o: token.o token.hpp
	g++ -std=c++11 -c token.cpp

clean:
	rm *.o output
