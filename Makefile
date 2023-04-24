CFLAGS = -Wall -pedantic -Werror -Wextra -std=gnu89

betty-all:
	betty shell.h ss-* simple-shell.c

ssc:
	gcc $(CFLAGS) ss-*.c simple-shell.c -o simple_shell -g

ssw:
	gcc ss-*.c simple_shell.c -o simple_shell -g
