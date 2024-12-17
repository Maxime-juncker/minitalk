MAKEFLAGS += --no-print-directory

SSRCS = server.c
CSRCS = client.c

COBJ = $(CSRCS:.c=.o)
SOBJ = $(SSRCS:.c=.o)

OBJ_D = obj/
SRCS_D = src/
BIN_D = bin/
LOG_D = log/
INCLUDES_D = -Ilibft/includes/ -Iincludes/
CFLAGS = -Wall -Wextra -Werror -g3 $(INCLUDES_D)


COBJ := $(addprefix $(OBJ_D), $(COBJ))
SOBJ := $(addprefix $(OBJ_D), $(SOBJ))
CSRCS := $(addprefix $(SRCS_D), $(SRCS))
SSRCS := $(addprefix $(SRCS_D), $(SRCS))

# colors
RED 	= \033[31m
GREEN 	= \033[32m
YELLOW 	= \033[33m
RESET 	= \033[0m
BLUE 	= \033[34m

RM = rm -fr

all: $(BIN_D) libft/bin/libft.a $(BIN_D)server $(BIN_D)client

.PHONY: libft
libft/bin/libft.a:
	echo "$(YELLOW)[MAKE]: libft$(RESET)"
	$(MAKE)  -C libft

$(BIN_D)server: src/server.c
	echo "$(BLUE)[COMPILING]: server$(RESET)"
	$(CC) $(CFLAGS) src/server.c libft/bin/libft.a -o $(BIN_D)server

$(BIN_D)client: src/client.c
	echo "$(BLUE)[COMPILING]: client$(RESET)"
	$(CC) $(CFLAGS) src/client.c libft/bin/libft.a -o $(BIN_D)client

$(OBJ_D)%.o : $(SRCS_D)%.c | $(OBJ_D)
	echo "$(BLUE)[COMPILING]: $@$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clog
	$(RM) $(OBJ_D)
	echo "$(RED)[CLEAN]: obj files$(RESET)"

.PHONY: fclean
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
	$(RM) $(BIN_D)
	echo "$(RED)[CLEAN]: binaries$(RESET)"

.PHONY: clog
clog:
	$(RM) $(LOG_D)
	echo "$(RED)[CLEAN]: log$(RESET)"

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

# Create directories
$(OBJ_D):
	echo "$(YELLOW)[CREATING]: $(OBJ_D)$(RESET)"
	mkdir -p $(OBJ_D)

$(LOG_D):
	echo "$(YELLOW)[CREATING]: $(LOG_D)$(RESET)"
	mkdir -p $(LOG_D)

$(BIN_D):
	echo "$(YELLOW)[CREATING]: $(BIN_D)$(RESET)"
	mkdir -p $(BIN_D)


PID = 0
.PHONY: debug
debug: all $(LOG_D)
	./bin/server & echo $$! > $(LOG_D)server.pid && gnome-terminal -- bash -c "./bin/client $(shell cat $(LOG_D)server.pid); exec bash"

.SILENT: