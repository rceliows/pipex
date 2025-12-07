# Standard
NAME			= pipex

# Directories
LIBFT_DIR		= ./libft
LIBFT			= $(LIBFT_DIR)/libft.a
INC			= inc/
SRC_DIR			= src/
OBJ_DIR			= obj/

# Compiler and Flags
CC			= cc
CFLAGS			= -Wall -Wextra -Werror -I$(INC) -I$(LIBFT_DIR)/inc
RM			= rm -f

# Source Files
SRCS			= $(SRC_DIR)main.c \
			$(SRC_DIR)error_handling.c \
			$(SRC_DIR)execute_multiple_pipelines.c \
			$(SRC_DIR)execute_multiple_pipelines_utils.c \
			$(SRC_DIR)execute_multiple_pipelines_utils_2.c \
			$(SRC_DIR)here_doc.c \
			$(SRC_DIR)init_data.c \
			$(SRC_DIR)init_data_utils.c \
			$(SRC_DIR)path.c \
			$(SRC_DIR)shell_parser.c \
			$(SRC_DIR)shell_parser_utils.c \
			$(SRC_DIR)shell_parser_utils_2.c \
			$(SRC_DIR)utils.c

# Apply the pattern substitution
OBJ			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules
all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJ)
			@echo "Linking $(NAME)..."
			@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
			@echo "Build complete!"

# Check if libft directory exists, if not clone it
$(LIBFT_DIR):
			@echo "libft not found. Cloning from repository..."
			@git clone git@github.com:rceliows/libft.git $(LIBFT_DIR)
			@echo "libft cloned successfully!"

$(LIBFT):		$(LIBFT_DIR)
			@echo "Building libft..."
			@make -C $(LIBFT_DIR)
			@echo "libft built successfully!"

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@echo "Cleaning object files..."
			@$(RM) -r $(OBJ_DIR)
			@if [ -d "$(LIBFT_DIR)" ]; then make clean -C $(LIBFT_DIR); fi
			@echo "Clean complete!"

fclean:			clean
			@echo "Removing executables..."
			@$(RM) $(NAME)
			@if [ -d "$(LIBFT_DIR)" ]; then $(RM) $(LIBFT); fi
			@echo "Full clean complete!"

fcleanall:		fclean
			@echo "Removing library directories..."
			@if [ -d "$(LIBFT_DIR)" ]; then rm -rf $(LIBFT_DIR); echo "Removed $(LIBFT_DIR)"; fi
			@echo "Full clean with libraries complete!"

re:			fclean all

reall:			fcleanall all

# Phony targets represent actions not files
.PHONY:			all clean fclean fcleanall re reall
