
.PHONY: all

all: sat-solver tester

# even non-Haskell solutions will need to compile the tester to run the tests
tester: Tester.hs
	ghc -o tester Tester.hs

# can comment this if your solution is not in Haskell
#sat-solver: sat-solver.hs Parser.hs Utils.hs
#	ghc -o sat-solver sat-solver.hs

main.o: main.C 
	g++ -c -O2 main.C

Absyn.o: Absyn.C Absyn.H
	g++ -c -O2 Absyn.C

CNF.o: CNF.cpp CNF.h
	g++ -c -O2 CNF.cpp

DPLL.o: DPLL.cpp DPLL.h
	g++ -c -O2 DPLL.cpp

Lexer.o: Lexer.C
	g++ -c -O2 Lexer.C

Parser.o: Parser.C Parser.H
	g++ -c -O2 Parser.C

Simplifier.o: Simplifier.cpp Simplifier.h
	g++ -c -O2 Simplifier.cpp

Tseytin.o: Tseytin.cpp Tseytin.h
	g++ -c -O2 Tseytin.cpp

sat-solver: main.o Absyn.o CNF.o DPLL.o Lexer.o Parser.o Simplifier.o Tseytin.o
	g++ -o sat-solver main.o Absyn.o CNF.o DPLL.o Lexer.o Parser.o Simplifier.o Tseytin.o

clean:
	rm sat-solver tester *.hi *.o
