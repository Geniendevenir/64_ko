#Directories
INC = inc/
SRC_DIR = srcs/
OBJ_DIR = obj/

# Compiler and Flag
CXX = g++
CXXFLAGS = -Os -Wall -Werror -Wextra -I/usr/local/include -I$(INC) 
LIBS = -L/usr/local/lib -lGLEW -lglfw -lGL
NAME = tiny_game 


#Sources and objects
SRCS = $(SRC_DIR)main.cpp \
		$(SRC_DIR)Player.cpp \
		$(SRC_DIR)windows_managment.cpp \
		$(SRC_DIR)texture.cpp \
		$(SRC_DIR)game_loop.cpp \
		$(SRC_DIR)error_managment.cpp \
		$(SRC_DIR)input.cpp \
		$(SRC_DIR)global.cpp

OBJS = $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRCS))

# Default rule
all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Linking
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LIBS)

# Compilation
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

strip:
	strip $(NAME)

# Clean rule
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re strip