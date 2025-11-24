# Standard
NAME			= libft.a

# Directories
INC			= inc/
SRC_DIR			= src/
OBJ_DIR			= obj/

# Compielr and Flags
CC			= gcc
CFLAGS			= -Wall -Wextra -Werror -I
RM			= rm -f
AR			= ar rcs

# Source Files
LIBFT_DIR	=	$(SRC_DIR)libft/ft_atoi.c		\
			$(SRC_DIR)libft/ft_bzero.c		\
			$(SRC_DIR)libft/ft_calloc.c		\
			$(SRC_DIR)libft/ft_isalnum.c		\
			$(SRC_DIR)libft/ft_isalpha.c		\
			$(SRC_DIR)libft/ft_isascii.c		\
			$(SRC_DIR)libft/ft_isdigit.c		\
			$(SRC_DIR)libft/ft_isprint.c		\
			$(SRC_DIR)libft/ft_itoa.c		\
			$(SRC_DIR)libft/ft_memchr.c		\
			$(SRC_DIR)libft/ft_memcmp.c		\
			$(SRC_DIR)libft/ft_memcpy.c		\
			$(SRC_DIR)libft/ft_memmove.c		\
			$(SRC_DIR)libft/ft_memset.c		\
			$(SRC_DIR)libft/ft_putchar_fd.c		\
			$(SRC_DIR)libft/ft_putendl_fd.c		\
			$(SRC_DIR)libft/ft_putnbr_fd.c		\
			$(SRC_DIR)libft/ft_putstr_fd.c		\
			$(SRC_DIR)libft/ft_split.c		\
			$(SRC_DIR)libft/ft_strchr.c		\
			$(SRC_DIR)libft/ft_strdup.c		\
			$(SRC_DIR)libft/ft_striteri.c		\
			$(SRC_DIR)libft/ft_strjoin.c		\
			$(SRC_DIR)libft/ft_strlcat.c 		\
			$(SRC_DIR)libft/ft_strlcpy.c		\
			$(SRC_DIR)libft/ft_strlen.c 		\
			$(SRC_DIR)libft/ft_strmapi.c		\
			$(SRC_DIR)libft/ft_strncmp.c		\
			$(SRC_DIR)libft/ft_strnstr.c		\
			$(SRC_DIR)libft/ft_strrchr.c		\
			$(SRC_DIR)libft/ft_strtrim.c		\
			$(SRC_DIR)libft/ft_substr.c		\
			$(SRC_DIR)libft/ft_tolower.c		\
			$(SRC_DIR)libft/ft_toupper.c		\
			$(SRC_DIR)libft/ft_lstadd_back.c	\
	        	$(SRC_DIR)libft/ft_lstadd_front.c	\
			$(SRC_DIR)libft/ft_lstclear.c		\
			$(SRC_DIR)libft/ft_lstdelone.c		\
        		$(SRC_DIR)libft/ft_lstiter.c		\
        		$(SRC_DIR)libft/ft_lstlast.c		\
       			$(SRC_DIR)libft/ft_lstmap.c		\
       			$(SRC_DIR)libft/ft_lstnew.c		\
        		$(SRC_DIR)libft/ft_lstsize.c		\
        		$(SRC_DIR)libft/get_next_line.c
			
FT_PRINTF_DIR	=	$(SRC_DIR)ft_printf/ft_printf.c		\
			$(SRC_DIR)ft_printf/utils/ft_putchar.c	\
			$(SRC_DIR)ft_printf/utils/ft_puthex.c	\
			$(SRC_DIR)ft_printf/utils/ft_putnbr.c	\
			$(SRC_DIR)ft_printf/utils/ft_putptr.c	\
			$(SRC_DIR)ft_printf/utils/ft_putstr.c	\
			$(SRC_DIR)ft_printf/utils/ft_putuns.c

# Concatenate all source files
SRC 			= $(LIBFT_DIR) $(FT_PRINTF_DIR)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# Build rules
all: 			$(NAME)

$(NAME): 		$(OBJ)
			@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
			@$(RM) -r $(OBJ_DIR)
			@$(RM) .cache_exists

fclean: 		clean
			@$(RM) $(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re
