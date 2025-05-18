SRCS := $(wildcard *.c)
Outs := $(patsubst %.c, %, $(SRCS))

CC := gcc
CFLAGS = -Wall -g

all: $(Outs)

%: %.c
	 $(CC) $< -o $@ $(CFLAGS)

.PHONY: clean rebuild ALL

clean:
	$(RM) $(Outs)
rebuild: clean all
