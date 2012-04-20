all: tester JavaTester.class Java7Tester.class

%.class: %.java
	javac $<

clean:
	rm -rf tester *.class *.jar *.txt

tester: main.c Makefile
	gcc -o $@ $< -Wall -Wextra -O2

myjar.jar: stamp-generate
	jar -cf $@ *.txt

stamp-generate:
	test -f helloe.txt || ./tester

test: all stamp-generate
	java JavaTester
	java Java7Tester
