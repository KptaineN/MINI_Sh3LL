###############################################################################
#                                   VARIABLES                                 #
###############################################################################



# Project directories (current directory)
PROJECT_DIR  := .
SRC_DIR      := $(PROJECT_DIR)/SRC
INC_DIR      := $(PROJECT_DIR)/include
# Subdirectories under SRC (omit Enrico_Parsing entirely)
SUBDIRS      := built env exec from_pipex handle_utils handle_utils/handler_cast_t_shell handle_utils/handler_operator main old_parser parser signal built/echo built/export
# Include libft under include
LIBFT_INC    := $(INC_DIR)/LIBFT
LIBFT_DIR    := $(INC_DIR)/LIBFT
LIBFT_A      := $(LIBFT_DIR)/libft.a
# Object directory
OBJ_DIR      := obj/
# Source files discovery
SRC_C        := $(foreach s,$(SUBDIRS),$(wildcard $(SRC_DIR)/$(s)/*.c))
ALL_C        := $(SRC_C)
# Object files path (mirror structure under OBJ_DIR)
ALL_OBJ      := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)%.o,$(ALL_C))
# Directories to search for sources
ALL_DIRS     := $(SRC_DIR) $(foreach s,$(SUBDIRS),$(SRC_DIR)/$(s))
# Include flags
ALL_PATHS    := -I$(INC_DIR) -I$(LIBFT_INC)
# Compiler settings
CC           := cc
CFLAGS       := -g -fsanitize=address -fno-omit-frame-pointer -Wall -Wextra -Werror $(ALL_PATHS)
# Linker flags
LDFLAGS      := -lreadline -fsanitize=address

###############################################################################
#                                VPATH & RULES                               #
###############################################################################
# Disable implicit rules to avoid conflicts
.SUFFIXES:
%.o: %.c

# Pattern rule: compile any .c into corresponding .o in OBJ_DIR
$(OBJ_DIR)%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build libft.a only if it doesn't exist or is out of date
$(LIBFT_A):
	@echo "Checking libft directory: $(LIBFT_DIR)"
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "ERROR: Directory $(LIBFT_DIR) does not exist"; \
		echo "Current directory: $(pwd)"; \
		echo "Available directories:"; \
		ls -la 2>/dev/null || echo "Cannot list current directory"; \
		exit 1; \
	fi
	@if [ ! -f $(LIBFT_A) ]; then \
		echo "Building libft..."; \
		$(MAKE) -C "$(LIBFT_DIR)"; \
	else \
		echo "libft.a already exists, skipping build"; \
	fi

###############################################################################
#                                   TARGETS                                   #
###############################################################################
# Default target
all: minishell

# Link all objects into executable
minishell: $(ALL_OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(ALL_OBJ) $(LIBFT_A) -o $@ $(LDFLAGS)

# Remove object files
clean:
	rm -rf $(OBJ_DIR)

# Remove objects + executable (keep libft.a)
fclean: clean
	rm -f minishell

# Clean everything including libft
fclean-all: clean
	rm -f minishell
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Debug target to see what files are found
debug:
	@echo "=== PATHS ==="
	@echo "PROJECT_DIR: $(PROJECT_DIR)"
	@echo "SRC_DIR: $(SRC_DIR)"
	@echo "INC_DIR: $(INC_DIR)"
	@echo "LIBFT_DIR: $(LIBFT_DIR)"
	@echo "LIBFT_A: $(LIBFT_A)"
	@echo ""
	@echo "=== CHECKING DIRECTORIES ==="
	@echo "Project dir exists:" && ls -la "$(PROJECT_DIR)" 2>/dev/null || echo "PROJECT_DIR NOT FOUND"
	@echo "Include dir exists:" && ls -la "$(INC_DIR)" 2>/dev/null || echo "INC_DIR NOT FOUND"
	@echo "Libft dir exists:" && ls -la "$(LIBFT_DIR)" 2>/dev/null || echo "LIBFT_DIR NOT FOUND"
	@echo ""
	@echo "=== SOURCE FILES ==="
	@echo "SRC_C: $(SRC_C)"
	@echo "ALL_OBJ: $(ALL_OBJ)"
	@echo ""
	@echo "=== PROJECT STRUCTURE ==="
	@find . -name "*.c" -o -name "Makefile" -o -name "libft*" 2>/dev/null | head -20

.PHONY: all clean fclean fclean-all re debug