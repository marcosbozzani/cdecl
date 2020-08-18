SHELL = C:/Windows/System32/cmd.exe
NAME = cdecl.exe
SRC_DIR = src
TST_DIR = tst
OUT_DIR = out
CFLAGS = -std=c11
CFLAGS += -D_GNU_SOURCE
CFLAGS += -fvisibility=hidden
CFLAGS += -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers

DEBUG = $(filter debug,$(MAKECMDGOALS))
TARGET = $(if $(DEBUG),debug,release)

CFLAGS += $(if $(DEBUG),-g,)
CFLAGS += $(if $(DEBUG),,-O2)

OBJ_DIR = $(OUT_DIR)/obj/$(TARGET)
BIN_DIR = $(OUT_DIR)/bin/$(TARGET)

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BIN = $(BIN_DIR)/$(NAME)

.PHONY: clean

release: all
debug: all

all: $(BIN)
	$(info $(BIN))

$(BIN_DIR):
	$(call mkdirp, $@)

$(OBJ_DIR):
	$(call mkdirp, $@)

$(BIN): $(OBJS) | $(BIN_DIR)
	@echo gcc $^ -o $@ $(CFLAGS)
	@gcc $^ -o $@ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo gcc -c $< -o $@ $(CFLAGS) -MMD
	@gcc -c $< -o $@ $(CFLAGS) -MMD
	
test: $(BIN_DIR)/test.exe
	$(call test,all)
	$(call test,unions)
	$(call test,structs)
	$(call test,functions)
	$(call test,variables)
	$(call test,static_functions)
	$(call test,static_variables)

$(BIN_DIR)/test.exe: $(TST_DIR)/test.c
	@gcc $< -o $@

clean:
	$(call rimraf,$(OUT_DIR))

-include $(OBJS:%.o=%.d)

define test
$(BIN_DIR)/test.exe \
$(subst /,\\,"$(BIN_DIR)/cdecl.exe $(TST_DIR)/input.c $(filter-out all,$(1))") \
$(subst /,\\,"$(TST_DIR)/output.$(1).c")
endef

define mkdirp
@if not exist $(subst /,\\,$(1)) ( md $(subst /,\\,$(1)) )
endef

define rimraf
@if exist $(subst /,\\,$(1)) ( rd /q /s $(subst /,\\,$(1)) )
endef

define cp
@copy /b /y $(subst /,\\,$(1)) $(subst /,\\,$(2)) > nul
endef

define dump
$(info $$@: $@)
$(info $$^: $^)
$(info $$<: $<)
$(info $$|: $|)
$(info ----------)
endef