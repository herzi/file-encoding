all: tester

clean:
	rm -rf tester *.txt *.jar

tester: main.c Makefile
	gcc -o $@ $< -Wall -Wextra -O2

jar: tester
	test -f helloe.txt || ./$<
	jar -cf myjar.jar *.txt
