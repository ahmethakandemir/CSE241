all: clear compile run 

clear: 
	clear

compile:
	@g++ quiz.cpp
run:
	@./a.out
clean:
	@rm deneme