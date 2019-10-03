main.out: Tetris.o main.o
	#g++ Tetris.o jogoTetris.o -lncurses -lglut -lGL -lGLU -lm
	g++ Tetris.o main.o -o main.out -lglut -lGL -lGLU -lm
Tetris.o:
	g++ -c Tetris.cpp

main.o:
	g++ -c main.cpp

jogoTetris.o:
	g++ -c jogoTetris.cpp

clean:
	rm -r -f *.o *.out
