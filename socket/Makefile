CC = gcc
CFLAGS = -O0 -g

OBJECTS = backlog accept send recv getservbyname dup writev sendfile splice uid client

all: $(OBJECTS)

$(OBJECTS): % : %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)
