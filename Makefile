all: c-tester JavaTester.class Java7Tester.class

%.class: %.java Makefile
	javac $<

clean:
	rm -rf generator c-tester *.class *.jar *.txt

c-tester: c-tester.c Makefile
	gcc -o $@ $< -Wall -Wextra -O2

generator: main.c Makefile
	gcc -o $@ $< -Wall -Wextra -O2

myjar.jar: stamp-generate
	jar -cf $@ *.txt

stamp-generate: generator
	test -f helloe.txt || ./$<

test: all stamp-generate
	./c-tester
	java JavaTester
	java Java7Tester
