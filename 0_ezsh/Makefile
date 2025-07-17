CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Og \
         -std=c89 -pedantic \
         -fsanitize=address,undefined \
         -fstack-protector-strong \
         -fno-strict-aliasing \
		 -fwrapv

ezsh: ezsh.c
	$(CC) $(CFLAGS) -o ezsh ezsh.c

clean:
	rm -f ezsh

run: ezsh
	./ezsh
	$(MAKE) clean
