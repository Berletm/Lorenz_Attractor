CC = gcc
CFLAGS = -Iinclude -g -O3
LDLIBS = -lSDL2 -lGL -lGLEW -lm -lGLU

SRCDIR = src
INCDIR = include
OBJDIR = build
SOURCES = main.c common.c input.c solver.c window.c
OBJECTS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))
EXECUTABLE = Lorenz_Attractor

$(shell mkdir -p $(OBJDIR))

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)