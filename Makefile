main.out: Tetris.o main.o INF390.o
	#g++ Tetris.o jogoTetris.o -lncurses -lglut -lGL -lGLU -lm
	g++ Tetris.o main.o INF390.o -o main.out -lglut -lGL -lGLU -lm
Tetris.o:
	g++ -c Tetris.cpp

INF390.o : INF390.cpp INF390.h
	g++ -c INF390.cpp

main.o: main.cpp
	g++ -c main.cpp

jogoTetris.o:
	g++ -c jogoTetris.cpp

clean:
	rm -r -f *.o *.out
