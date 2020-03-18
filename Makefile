RM = rm -f
MKDIR = mkdir -p

NAME = 2048

SRCDIR = src
INCDIR = include
OBJDIR = build

CXX = g++
CXXFLAGS = -Wall -Wextra -I$(INCDIR) $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf

SRC = $(shell find $(SRCDIR) -type f -name "*.cpp")
INC = $(shell find $(INCDIR) -type f -name "*.h" -name "*.hpp")
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: prebuild $(NAME)

prebuild:
	$(MKDIR) $(OBJDIR)

$(NAME): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
