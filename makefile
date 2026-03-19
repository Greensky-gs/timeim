CC ?= gcc
DESTDIR ?= 
PREFIX ?= /usr
DATADIR = /usr/share/timeim
OUTPUT = timeim

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
ASSETS_DIR = assets

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) $(DATADIR) $(BIN_DIR) $(BIN_DIR)/$(OUTPUT)

$(DATADIR):
	cp -r ./assets $(DATADIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) -DDATADIR=\"$(DESTDIR)$(DATADIR)\" $^ -o $@ -c

$(BIN_DIR)/$(OUTPUT): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -DDATADIR=\"$(DATADIR)\" -o $(BIN_DIR)/$(OUTPUT)

install: $(BIN_DIR)/$(OUTPUT)
	install -Dm755 $(BIN_DIR)/$(OUTPUT) "$(DESTDIR)$(PREFIX)/bin/$(OUTPUT)"
	install -d "$(DESTDIR)$(DATADIR)"
	install -m644 $(ASSETS_DIR)/*.txt "$(DESTDIR)$(DATADIR)/"

shared: $(BUILD_DIR) $(SOURCES)
	$(CC) -fPIC -shared -DDATADIR=\"$(DATADIR)\" -o $(BUILD_DIR)/shared.so $(SOURCES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

launch:
	./$(BIN_DIR)/$(OUTPUT)

full:
	make clean
	make
	clear
	make launch

.PHONY: all install clean launch full shared

