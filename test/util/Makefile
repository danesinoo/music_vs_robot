CC = g++
CFLAGS = -Wsuggest-override -Werror=suggest-override -std=c++2a
DEP = ../../util/independentfn.o test_deque.o 
ARG = ./main.cpp

%.o: %.cpp
	@$(CC) -c $(CFLAGS) $< -o $@

compile: $(DEP)
	@$(CC) $(CFLAGS) $(DEP) $(ARG) -o $(basename $(ARG))

run: compile
	@./$(basename $(ARG))

clean:
	@rm *.o ../../playground/*.o ../../util/*.o $(basename $(ARG))
