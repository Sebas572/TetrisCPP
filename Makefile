compile:
	@if [ ! -d out ]; then \
		mkdir out; \
	fi

	g++ -o ./out/Tetris.out main.cpp src/events/keyboard.h -lX11
clean:
	rm -r ./out
