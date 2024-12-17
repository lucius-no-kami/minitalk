################### BEGGINING #######################

NAME := libftprintf.a

#---------------------------------------------------#
#					INGREDIENTS						#
#---------------------------------------------------#
# SRCS	source files
# OBJS	object files
#
# CC	 	compiler
# CFLAGS	compiler flags
# INCLUDES	include pathes

SRCS		=	ft_printf.c utils.c

OBJS		= 	ft_printf.o utils.o

cc			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I .

#---------------------------------------------------#
#					UTENSILS						#
#---------------------------------------------------#
# RM	force remove

RM = rm -rf

#---------------------------------------------------#
#					RECIPES							#
#---------------------------------------------------#
# all		default goal
# $(NAME)	linking .o -> binary
# clean		remove .o
# fclean	remove .o + binary
# re		using fclean then all

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	$(info CREATED $(NAME))

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all