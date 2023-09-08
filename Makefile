compile:
	@if [ ! -d out ]; then \
		mkdir out; \
	fi

	g++ -o ./out/Tetris.out main.cpp -lX11 -pthread

run: compile
	./out/Tetris.out

clean:
	rm -r ./out
