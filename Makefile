VPATH = ./src : ./test : ./doc

CPPFLAGS = -g -std=c++11
CC = g++
RM = rm -rf

LIBSPOI = testPoint.o
LIBSSEG = testSegment.o
LIBSJC 	= testJordanCurve.o
LIBSPAS = testPasting.o
LIBSATO = testAtomSpajor.o
LIBSSPA	= testSpajor.o


design : design.tex
	pdflatex $<
	pdflatex $<
	make clean

answer : answer.tex
	pdflatex $<
	pdflatex $<
	make clean

testSpajor :testSpajor.o
	$(CC) -o $@ $(CPPFLAGS) $(LIBSSPA)
	./testSpajor
	make clean	

testPoint :  $(LIBSPOI)
	$(CC) -o $@ $(CPPFLAGS) $(LIBSPOI)
	./testPoint
	make clean

testSegment :  $(LIBSSEG)
	$(CC) -o $@ $(CPPFLAGS) $(LIBSSEG)
	./testSegment
	make clean

testJordanCurve :  $(LIBSJC)
	$(CC) -o $@ $(CPPFLAGS) $(LIBSJC)
	./testJordanCurve
	make clean

testAtom :  $(LIBSATO)
	$(CC) -o $@ $(CPPFLAGS) $(LIBSATO)
	./testAtom
	make clean

testPasting :  $(LIBSPAS)
	$(CC) -o $@ $(CPPFLAGS) $(LIBSPAS)
	./testPasting
	make clean

.PHONY : clean

clean :
	$(RM) *.aux *.log *.o

realclean :
	$(MAKE) clean
	$(RM) *.pdf  testPoint testSegment testJordanCurve testPasting testAtom testSpajor
