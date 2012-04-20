all: tester JavaTester.class

clean:
	rm -rf tester *.txt *.jar

tester: main.c Makefile
	gcc -o $@ $< -Wall -Wextra -O2

jar: all
	test -f helloe.txt || ./tester
	jar -cf myjar.jar *.txt
	java JavaTester

JavaTester.class: JavaTester.java
	javac JavaTester.java
