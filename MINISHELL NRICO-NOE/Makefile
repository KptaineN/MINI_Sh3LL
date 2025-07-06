###############################################################################
#                                   VARIABLES                                 #
###############################################################################

# Project directories (escape space in name)
PROJECT_DIR  := MINISHELL\ NRICO-NOE
SRC_DIR      := $(PROJECT_DIR)/SRC
INC_DIR      := $(PROJECT_DIR)/include

# Subdirectories under SRC (omit Enrico_Parsing entirely)
SUBDIRS      := built env exec from_pipex handle_utils main old_parser parser signal

# Include libft under include
LIBFT_INC    := $(INC_DIR)/LIBFT

# Object directory
OBJ_DIR      := obj/

# Source files discovery
SRC_C        := $(foreach s,$(SUBDIRS),$(wildcard $(SRC_DIR)/$(s)/*.c))
ALL_C        := $(SRC_C)

# Object files path (mirror structure under OBJ_DIR)
ALL_OBJ      := $(ALL_C:%.c=$(OBJ_DIR)%.o)

# Directories to search for sources
ALL_DIRS     := $(SRC_DIR) $(foreach s,$(SUBDIRS),$(SRC_DIR)/$(s))

# Include flags
ALL_PATHS    := -I$(INC_DIR) -I$(LIBFT_INC)

# Compiler settings
CC           := gcc
CFLAGS       := -Wall -Wextra -Werror $(ALL_PATHS)

###############################################################################
#                                VPATH & RULES                               #
###############################################################################

# Let make search .c files in these directories
vpath %.c $(ALL_DIRS)

# Pattern rule: compile any .c into corresponding .o in OBJ_DIR
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

###############################################################################
#                                   TARGETS                                   #
###############################################################################

# Default target
all: minishell

# Link all objects into executable
minishell: $(ALL_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Remove object files
clean:
	rm -rf $(OBJ_DIR)

# Remove objects + executable
fclean: clean
	rm -f minishell

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
