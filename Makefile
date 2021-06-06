BUILD_DIR	= build
PUSH_SWAP = src/push_swap
CHECKER = src/checker

all: $(BUILD_DIR)
	$(MAKE) -C $(PUSH_SWAP)
	$(MAKE) -C $(CHECKER)
	cp $(PUSH_SWAP)/push_swap build
	cp $(CHECKER)/checker build
	gcc tests/random_numbers.c core/libcore.a -o build/random

$(BUILD_DIR): ; @mkdir -p $@

clean:
	$(MAKE) -C $(PUSH_SWAP) clean
	$(MAKE) -C $(CHECKER) clean

fclean:
	$(MAKE) -C $(PUSH_SWAP) fclean
	$(MAKE) -C $(CHECKER) fclean
	@rm -rf build

re: fclean all