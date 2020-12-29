.PHONY : all run clean objdir

SRC_DIR := ./src
INC_DIR := ./inc
OUT_DIR := ./out

CC := gcc
CFLAGS := -std=gnu99 -I$(INC_DIR) -Wall -Werror -pedantic

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

EXEC := app.exe

TEMPFILE := table_temp.txt

all: $(EXEC)

$(EXEC): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

objdir:
	@mkdir -p $(OUT_DIR)

${OUT_DIR}/%.o : ${SRC_DIR}/%.c objdir
	@$(CC) $(CFLAGS) -c $< -o $@

$(INC_DIR)/%.h:

clean:
	@$(RM) $(EXEC) $(TEMPFILE) ${OUT_DIR}/*
	@rm -rf $(OUT_DIR)