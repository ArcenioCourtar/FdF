CC			= cc
NAME		= libft.a

OBJDIR		= obj/
SRCDIR		= src/

SRCFILES	= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
	ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
	ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
	ft_substr.c ft_tolower.c ft_toupper.c ft_lstsize.c ft_lstnew.c \
	ft_lstlast.c ft_lstclear.c ft_lstiter.c ft_lstadd_front.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstmap.c ft_isspace.c ft_atol.c \
	ft_printf.c
GNLFILES	= get_next_line.c get_next_line_utils.c
HEADERFILE	= libft.h get_next_line.h

CFLAGS		= -Wall -Werror -Wextra

# The files in OBJAFTER were added after libft's completion.

OBJ_ALL := $(addprefix $(OBJDIR), $(SRCFILES:.c=.o)) \
$(addprefix $(OBJDIR), $(GNLFILES:.c=.o))
SRC_ALL	:= $(addprefix $(SRCDIR), $(SRCFILES))
# SRC_ALL := $(addprefix $(SRCDIR), $(SRC_ALL))
# Commented out the flag since I want to add the bonus by default from now on
# ifdef COMP_BONUS
# OBJ_ALL := $(OBJFILES) $(OBJBONUS) $(OBJAFTER)
# else
# OBJ_ALL := $(OBJFILES)
# endif

all: $(NAME)	

$(NAME): $(OBJ_ALL)
	ar -rcs $@ $^

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERFILE)
	@mkdir -p $(@D)
	$(CC) -I. -c $(CFLAGS) -o $@ $<

re: fclean all

clean:
	rm -f $(OBJ_ALL)
	rmdir $(OBJDIR)

fclean:
	rm -f $(OBJ_ALL) $(NAME)
	rmdir $(OBJDIR)

bonus:
	@$(MAKE)

# Ensures that these commands run even if there's a file
# with the same name is in the folder.
# Not needed for all, and re? ?_?
.PHONY: clean fclean bonus re all