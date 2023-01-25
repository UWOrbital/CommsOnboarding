# Makefile

TARGET = commsOnboarding
SRC_DIR = ./src
INC_DIRS = $(SRC_DIR) ./include
BUILD_DIR = ./build

SRCS = $(notdir $(wildcard $(SRC_DIR)/*.c))
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS = $(INC_FLAGS)

.PHONY: all
all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
