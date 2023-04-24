CFLAGS = -Wall -pedantic -Werror -Wextra -std=gnu89

betty-all:
	betty shell.h ss-*.c simple_shell.c

ssc:
	gcc $(CFLAGS) ss-*.c simple_shell.c -o simple_shell -g

ssw:
	gcc ss-*.c simple_shell.c -o simple_shell -g
