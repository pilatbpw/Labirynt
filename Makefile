all:
		
			@mkdir -p tmp;
			@mkdir -p bin;
			@mkdir -p wyniki;
				@if [ "$$(ls -A tmp)" ]; then \
					        rm -rf tmp/*; \
							fi 
							
					@if [ "$$(ls -A wyniki)" ]; then \
							rm -rf wyniki/*; \
							    	fi
				
				@if [ "$$(ls -A bin)" ]; then \
					        rm -rf bin/*; \
							fi 
							
			gcc -Wall --pedantic src/*c -o bin/labirynt
