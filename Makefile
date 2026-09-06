BINARY=conway
INCDIRS=include
CODEDIRS=. lib

CC=gcc
DEPFLAGS=-MP -MD
CFLAGS=-Wall -Wextra $(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)

CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install:
	make all
	sudo cp $(BINARY) /usr/local/bin/

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

-include $(DEPFILES)
