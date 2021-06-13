BUILD_DIR	= build
PUSH_SWAP = src/push_swap
CHECKER = src/checker

all: push_swap checker

push_swap: $(BUILD_DIR)
	$(MAKE) -C $(PUSH_SWAP)
	cp $(PUSH_SWAP)/push_swap build

checker: $(BUILD_DIR)
	$(MAKE) -C $(CHECKER)
	cp $(CHECKER)/checker build

$(BUILD_DIR): ; @mkdir -p $@

clean:
	$(MAKE) -C $(PUSH_SWAP) clean
	$(MAKE) -C $(CHECKER) clean

fclean:
	$(MAKE) -C $(PUSH_SWAP) fclean
	$(MAKE) -C $(CHECKER) fclean
	@rm -rf build

re: fclean all
