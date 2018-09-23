# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2518/01/04 15:18:12 by lfabbro           #+#    #+#              #
#    Updated: 2018/09/23 12:20:01 by lfabbro          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binaries
PROJECT		?= ft_ssl

# Sources
SRC_NAME		= \
	main.c ft_ssl.c ft_ssl_md5.c ft_md5.c ft_ssl_sha256.c ft_sha256.c

# Directories
SRC_PATH	= src
OBJ_PATH	= obj
TESTD		= test

# Libft
LFT_DIR		= libft
LFT_INC_DIR	= $(LFT_DIR)/include
LFT_LD		= -lft
LFT			= libft.a

# Includes and libraries directories
INC_DIR		= $(LFT_INC_DIR) include
LIB_DIR		= $(LFT_DIR)

# Includes
INC			= $(addprefix -I./,$(INC_DIR))

# Extra Libraries
LDLIBS		= $(LFT_LD) #-lncurses #-lm

# Linking flags
LDFLAGS		= $(addprefix -L./,$(LIB_DIR))

# Compilation flags
CFLAGS		+= -g    #-O3

OBJ_DIR		?= obj
OBJ_PATH	?= $(OBJ_DIR)/rel
OBJ		= $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
DEP			= $(OBJ:%.o=%.d)

# Compilation/Linking Flags for the differents public rules
WFLAGS = -Wextra -Wall #-Werror
RCFLAGS = $(WFLAGS) -Werror -O2 -march=native  # release
DCFLAGS = $(WFLAGS) -g3 -DDEBUG  # debug
SCFLAGS = $(DCFLAGS) -fsanitize=address,undefined -ferror-limit=5  # sanitize
WWFLAGS = $(WFLAGS) -Wpedantic -Wshadow -Wconversion -Wcast-align \
  -Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
  -Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
  -Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
  -Wredundant-decls  # moar warnings

# Compilation
UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
		CC			= gcc
        CCFLAGS		+= -D LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
		CC			= clang
        CCFLAGS += -D OSX
    endif

# default to "pretty" Makefile, but you can run ´VERBOSE=t make´
ifndef VERBOSE
 ifndef TRAVIS
.SILENT:
 endif
endif

# Commands
PRINTF		= test $(VERBOSE)$(TRAVIS) || printf
MAKE		?= make -j$(shell nproc 2>/dev/null || echo 4)
SUB_MAKE	= make -C
MKDIR		= mkdir -p
RMDIR		= rm -rf
RM			= rm -f

# Colors
RED			= \033[31m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
WHITE		= \033[37m
TODO1		= \033[0K  #TODO
TODO2		= \033[17C #TODO
ENDC		= \033[0m
CR			= \r


######################################
## PUBLIC RULES
######################################

# Builds
all:
	+$(SUB_MAKE) $(LFT_DIR)
	@$(PRINTF) "%-25s"    "$(PROJECT): bin"
	+$(MAKE) $(PROJECT)    "CFLAGS = $(RCFLAGS)"  "OBJ_PATH = $(OBJ_DIR)/rel"
	@$(PRINTF) "$(CR)$(GREEN)✔$(ENDC)\n"

dev:
	+$(SUB_MAKE) $(LFT_DIR) #dev
	@$(PRINTF) "%-25s"    "$(PROJECT): bin"
	+$(MAKE) $(PROJECT).dev  "PROJECT = $(PROJECT).dev"  "CFLAGS = $(DCFLAGS)" \
		"OBJ_PATH = $(OBJ_DIR)/dev"  "LFT = libft.a"  "LFTLD = -lft.dev"
		#"OBJ_PATH = $(OBJ_DIR)/dev"  "LFT = libft.dev.a"  "LFTLD = -lft.dev"
	@$(PRINTF) "$(CR)$(GREEN)✔$(ENDC)\n"

san:
	+$(SUB_MAKE) $(LFT_DIR) #san
	@$(PRINTF) "%-25s"    "$(PROJECT): bin"
	+$(MAKE) $(PROJECT).san  "PROJECT = $(PROJECT).san"  "CFLAGS = $(SCFLAGS)" \
		"OBJ_PATH = $(OBJ_DIR)/san"  "LFT = libft.san.a"  "LFTLD = -lft.san"
	@$(PRINTF) "$(CR)$(GREEN)✔$(ENDC)\n"

mecry:
	+$(MAKE) -C $(LFT_DIR) #mecry
	@$(PRINTF) "%-25s"    "$(PROJECT): omg"
	+$(MAKE) $(PROJECT)    "CFLAGS = $(WWFLAGS)"  "OBJ_PATH = $(OBJ_DIR)/rel"
	@$(PRINTF) "$(CR)$(GREEN)✔$(ENDC)\n"

######################################
# Other rules
######################################
test: all
	$(CC) $(RCFLAGS) -m64  test/main.c -o test/test64
	$(CC) $(RCFLAGS) -m32  test/main.c -o test/test32
	@$(PRINTF) "$(GREEN)✔$(ENDC)%25s\n"    "$@"

clean:
	@$(RMDIR) $(OBJ_PATH) $(PROJECT).dSYM test/test32 test/test64
	@$(PRINTF) "%-25s$(GREEN)✔$(ENDC)\n"    "$(PROJECT): $@"

fclean: clean
	@$(RM) $(PROJECT)

re: fclean all

lib:
	@$(MAKE) -C $(LFT_DIR)

libclean:
	@$(MAKE) -C $(LFT_DIR) fclean

norme:
	@$(PRINTF) "$(WHITE) Norminette $(ENDC)\n"
	norminette $(SRC_PATH) $(INC_DIR) $(LFT_DIR)

.PHONY: all dev san mecry clean fclean re lib libclean norme $(PROJECT)

######################################
## PRIVATE RULES
######################################

# (link) project
$(PROJECT): $(LFT_DIR)/$(LFT)   $(OBJ)
	@$(PRINTF) "$(CR)$(TODO1)$(TODO2)$(WHITE)  $@  $(ENDC)"
	$(CC) $(CFLAGS) $(INC) $(LDFLAGS)  $^  $(LDLIBS) -o $@

# (compile) objects
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@$(PRINTF) "$(CR)$(TODO1)$(TODO2)$(WHITE)  $<  $(ENDC)"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INC)  -c $< -o $@

# create directory for compilation sub-products
$(OBJ_PATH):
	$(MKDIR) $(dir $(OBJ))

# read dependencies list generated by -MMD flag
-include $(DEP)
