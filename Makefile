# Standard
NAME		= pipex

# Directories
LIBFT		= ./libft/libft.a
INC		= inc/
SRC_DIR		= src/
OBJ_DIR		= obj/

# Compiler and Flags
CC		= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INC)
RM		= rm -f

# Source Files
SRCS		= $(SRC_DIR)main.c \
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
OBJ		= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules
start:				
		@make all

$(LIBFT):
		@make -C ./libft

all:		$(NAME)

$(NAME):	$(OBJ) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
		@echo "$(NAME) compiled successfully!"

# Compile object files from source files
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c 
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(RM) -r $(OBJ_DIR)
		@make clean -C ./libft

fclean:		clean
		@$(RM) $(NAME)
		@$(RM) $(LIBFT)

re:		fclean all

# Phony targets represent actions not files
.PHONY:		start all clean fclean re
