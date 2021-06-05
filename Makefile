BUILD_DIR	= build

all: $(BUILD_DIR)
	$(MAKE) -C src
	$(MAKE) -C checker
	cp src/push_swap build
	cp checker/checker build

$(BUILD_DIR): ; @mkdir -p $@

clean:
	$(MAKE) -C src clean
	$(MAKE) -C checker clean

fclean:
	$(MAKE) -C src fclean
	$(MAKE) -C checker fclean
	@rm -rf build

re: fclean all