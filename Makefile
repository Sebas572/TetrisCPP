compile:
	@if [ ! -d out ]; then \
		mkdir out; \
	fi

	g++ -o ./out/Tetris.out main.cpp -lX11 -pthread -lXft -I /usr/include/freetype2

run: compile
	./out/Tetris.out

clean:
	rm -r ./out
