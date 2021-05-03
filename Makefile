.PHONY: all clean test

include config.mk

# --- Static library ---

$(BUILD)libibst.a: $(BUILD)ibst.o
	$(AR) rc $@ $?
	$(RANLIB) $@

$(BUILD)ibst.o: src/ibst.c src/ibst.h
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -o $@ -c src/ibst.c

# --- Tests ---

test: $(BUILD)tests/test
	$(BUILD)tests/test

$(BUILD)tests/test: tests/test.c $(BUILD)libibst.a
	@mkdir -p $(BUILD)tests
	$(CC) $(CFLAGS) -L$(BUILD) -o $@ tests/test.c -libst

# --- Cleanups ---

clean:
	rm -rf $(BUILD)
