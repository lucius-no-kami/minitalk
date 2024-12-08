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

CLIENT_NAME = minitalk_client
SERVER_NAME = minitalk_server

SRCDIR = src
OBJDIR = obj
INCDIR = include

# Source Files
SRC = main.c minitalk.c 
OBJ = $(SRC:.c=.o)
SRC := $(addprefix $(SRCDIR)/, $(SRC))
OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJ))

# Libraries and Linker Flags
FT_PRINTF_DIR = ft_printf
LDFLAGS = -L$(FT_PRINTF_DIR)
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

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
all: $(OBJDIR) $(CLIENT_NAME)

# Object Directory Rule
$(OBJDIR):
	$(V)mkdir -p $(OBJDIR) || true

# Dependency Files
DEP = $(OBJ:.o=.d)

# FT_PRINTF
$(FT_PRINTF):
	$(V)$(MAKE) --silent -C $(FT_PRINTF_DIR)
	$(V)echo '[$(CLIENT_NAME)] ft_printf build successfully'

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(V)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

# Linking Rule
$(CLIENT_NAME): $(FT_PRINTF) $(OBJ)
	$(V)$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(BONUS_OBJ) $(FT_PRINTF) $(MLXFLAGS) -o $(CLIENT_NAME)
	$(V)echo $(GREEN)"[$(CLIENT_NAME)] Executable created ✅"$(RESET)

# Clean Rules
clean:
	$(V)echo $(RED)'[$(CLIENT_NAME)] Cleaning objects'd$(RESET)
	$(V)rm -rf $(OBJDIR)

fclean: clean
	$(V)echo $(RED)'[$(CLIENT_NAME)] Cleaning all files'$(RESET)
	$(V)rm -f $(CLIENT_NAME)

re: fclean all

# Makefile Reconfiguration 
regen:
	makemyfile

.PHONY: all clean fclean re bonus regen
.DEFAULT_GOAL := all
