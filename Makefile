#-----------------------------------------------------------------------------------#
#																					#
#			███╗   ███╗██╗███╗   ██╗██╗████████╗ █████╗ ██╗     ██╗  ██╗			#
#			████╗ ████║██║████╗  ██║██║╚══██╔══╝██╔══██╗██║     ██║ ██╔╝			#
#			██╔████╔██║██║██╔██╗ ██║██║   ██║   ███████║██║     █████╔╝ 			#
#			██║╚██╔╝██║██║██║╚██╗██║██║   ██║   ██╔══██║██║     ██╔═██╗ 			#
#			██║ ╚═╝ ██║██║██║ ╚████║██║   ██║   ██║  ██║███████╗██║  ██╗			#
#			╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝			#
#																					#
#-----------------------------------------------------------------------------------#

CLIENT_NAME = client
SERVER_NAME = server

SRCDIR = src
OBJDIR = obj
INCDIR = include

# Source Files
SRC_CLIENT = utils.c client/client.c
SRC_SERVER = utils.c server/server.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

OBJ_SERVER = $(SRC_SERVER:.c=.o)

SRC_CLIENT := $(addprefix $(SRCDIR)/, $(SRC_CLIENT))
OBJ_CLIENT := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJ_CLIENT))

SRC_SERVER := $(addprefix $(SRCDIR)/, $(SRC_SERVER))
OBJ_SERVER := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJ_SERVER))

# Libraries and Linker Flags
libft = libft
LDFLAGS = -L$(libft)
LIBFT = $(libft)/libft.a

# Archiver
AR = ar
ARFLAGS = rcs

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3

# Compilation mode (silent by default, set VERBOSE=1 to show commands)
VERBOSE ?= 0
ifeq ($(VERBOSE),1)
  V := 
else
  V := @
endif

# Colors
RED     := "\033[1;31m"
GREEN   := "\033[1;32m"
RESET   := "\033[0m"



# Default Rule
all: $(OBJDIR) $(CLIENT_NAME) $(SERVER_NAME)

# Object Directory Rule
$(OBJDIR):
	$(V)mkdir -p $(OBJDIR) || true

# Dependency Files
DEP_CLIENT = $(OBJ_CLIENT:.o=.d)
DEP_SERVER = $(OBJ_SERVER:.o=.d)

# LIBFT
$(LIBFT):
	$(V)$(MAKE) --silent -C $(libft)
	$(V)echo '[$(CLIENT_NAME)] LIBFT build successfully'

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(V)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP_CLIENT)
-include $(DEP_SERVER)

# Linking Rule
$(CLIENT_NAME): $(LIBFT) $(OBJ_CLIENT)
	$(V)$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_CLIENT) $(BONUS_OBJ) $(LIBFT) $(MLXFLAGS) -o $(CLIENT_NAME) -g3
	$(V)echo $(GREEN)"[$(CLIENT_NAME)] Executable created ✅"$(RESET)

$(SERVER_NAME): $(LIBFT) $(OBJ_SERVER)
	$(V)$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_SERVER) $(BONUS_OBJ) $(LIBFT) $(MLXFLAGS) -o $(SERVER_NAME) -g3
	$(V)echo $(GREEN)"[$(SERVER_NAME)] Executable created ✅"$(RESET)

# Clean Rules
clean:
	$(V)echo $(RED)'[$(CLIENT_NAME)] and [$(SERVER_NAME)] Cleaning objects'd$(RESET)
	$(V)rm -rf $(OBJDIR)

fclean: clean
	$(V)echo $(RED)'[$(CLIENT_NAME)] Cleaning all files'$(RESET)
	$(V)$(MAKE) --silent -C $(libft) fclean
	$(V)rm -f $(CLIENT_NAME)
	$(V)echo $(RED)'[$(SERVER_NAME)] Cleaning all files'$(RESET)
	$(V)rm -f $(SERVER_NAME)

re: fclean all

# Makefile Reconfiguration 
regen:
	makemyfile

.PHONY: all clean fclean re bonus regen
.DEFAULT_GOAL := all
