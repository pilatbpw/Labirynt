all:
	gcc -Wall --pedantic src/*c -o bin/labirynt
	@if [ "$$(ls -A tmp)" ]; then \
        rm -rf tmp/*; \
    fi
