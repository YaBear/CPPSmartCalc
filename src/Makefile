CC = gcc
CFLAGS = -lstdc++ -std=c++17 -Wall -Werror -Wextra
PRJNAME = s21_Smart_Calc

all: clean install

test: clean
	@$(CC) $(CFLAGS) tests/main.cc -lgtest -o tests/test
	./tests/test

install: uninstall
	@mkdir Build
	@cd Project && qmake && make && make clean && rm -rf Makefile && cd ../ && mv Project/$(PRJNAME).app Build
	@rm -rf Project/.qmake.stash

uninstall:
	@rm -rf Build*

dist:
	@tar -czf $(PRJNAME).tar.gz --directory=Build/ .

dvi:
	@open README.md

clean:
	@rm -rf Build/ *.tgz $(PRJNAME)/ tests/test