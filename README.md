File-Encoding Tests
===================

Example:
--------

Running on GNU/Linux:

    > make test
    gcc -o c-tester c-tester.c -Wall -Wextra -O2
    javac JavaTester.java
    javac Java7Tester.java
    gcc -o generator main.c -Wall -Wextra -O2
    test -f helloe.txt || ./generator
    ./c-tester
    (c)found: Escaped
    (c)found: ISO-8859-1
    (c)found: ASCII
    (c)found: UTF-8
    java JavaTester
    (java2)found: Escaped
    (java2)couldn't read file: 'hall�.txt
    (java2)found: ASCII
    (java2)found: UTF-8
    java Java7Tester
    (java7)found: Escaped
    (java7)found: ISO-8859-1
    (java7)found: ASCII
    (java7)found: UTF-8

References:
-----------

 * http://developer.gnome.org/glib/stable/glib-Character-Set-Conversion.html#file-name-encodings
 * http://mail.gnome.org/archives/desktop-devel-list/2010-July/msg00047.html
 * http://mail.gnome.org/archives/desktop-devel-list/2010-July/msg00080.html
 * http://mail.gnome.org/archives/desktop-devel-list/2010-July/msg00074.html
