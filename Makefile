all: tester JavaTester.class Java7Tester.class

clean:
	rm -rf tester *.class *.jar *.txt

tester: main.c Makefile
	gcc -o $@ $< -Wall -Wextra -O2

jar: all
	test -f helloe.txt || ./tester
	jar -cf myjar.jar *.txt
	java JavaTester

%.class: %.java
	javac $<
