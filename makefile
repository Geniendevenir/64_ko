#Directories
INC = inc/
SRC_DIR = srcs/
OBJ_DIR = obj/

# Compiler and Flag
CXX = g++
CXXFLAGS = -Os -Wall -Werror -Wextra -I/usr/local/include -I$(INC) 
LIBS = -L/usr/local/lib -lGLEW -lglfw -lGL
NAME = ReverseKinematics


#Sources and objects
SRCS = $(SRC_DIR)main.cpp \
		$(SRC_DIR)Globals.cpp \
		$(SRC_DIR)RobotArm.cpp \
		$(SRC_DIR)Vector.cpp \

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