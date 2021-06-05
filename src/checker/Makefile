NAME = checker

OBJ_DIR = obj
SRC_DIR = src
DEP_DIR = .deps
CORE_DIR = ../../core
COMMON_DIR = ../common

CORE = $(CORE_DIR)/libcore.a
COMMON = $(COMMON_DIR)/libcom.a

SRC = $(addprefix src/, \
	checker.c \
)

OBJ = $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
CPPFLAGS = -I . -I inc -I ../../core -I ../common
LDFLAGS = -L $(CORE_DIR) -L $(COMMON_DIR)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(CORE) $(COMMON) $(OBJ)
	@echo "Link $@"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(COMMON) $(CORE) $(CPPFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEP_DIR)/%.d | $(DEP_DIR) $(OBJ_DIR)
	@echo "Compile $<"
	@$(COMPILE.c) -o $@ $<

$(DEP_DIR): ; @mkdir -p $@

$(OBJ_DIR): ; @mkdir -p $@

$(CORE): $(CORE_DIR)
	@$(MAKE) -C $(CORE_DIR)

$(COMMON): $(COMMON_DIR)
	@$(MAKE) -C $(COMMON_DIR)

DEPFILES = $(subst $(SRC_DIR), $(DEP_DIR), $(SRC:.c=.d))
$(DEPFILES):

clean:
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@$(MAKE) -C $(CORE_DIR) clean
	@$(MAKE) -C $(COMMON_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(CORE_DIR) fclean
	@$(MAKE) -C $(COMMON_DIR) fclean

re: fclean all

include $(wildcard $(DEPFILES))