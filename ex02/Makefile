# Program name
NAME		= identify

# Compiler and flags
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++20

# Source files and Object files
SRCS		= main.cpp Base.cpp
OBJS		= $(SRCS:.cpp=.o)
HEADERS		= Base.hpp A.hpp B.hpp C.hpp 

# Rules
all: $(NAME)

# Explicit rule so CXXFLAGS are guaranteed to apply
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re