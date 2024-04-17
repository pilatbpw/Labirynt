all:
		gcc -Wall --pedantic src/*c -o bin/labirynt
			@mkdir -p tmp;
				@if [ "$$(ls -A tmp)" ]; then \
					        rm -rf tmp/*; \
							fi 
							@if [ ! -d "wyniki" ]; then \
							mkdir wyniki; \
							fi
					@if [ "$$(ls -A wyniki)" ]; then \
							rm -rf wyniki/*; \
							    	fi
