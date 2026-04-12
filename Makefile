CC = gcc
CFLAGS = -Wall -g -Iinclude
TARGET_DIR = bin
BACKEND_TARGET = $(TARGET_DIR)/backend
FRONTEND_TARGET = $(TARGET_DIR)/frontend

# 创建目标目录
$(shell mkdir -p $(TARGET_DIR))

# 后端源文件
BACKEND_SOURCES = backend/backend_main.c \
                  backend/sre/api/backend_api.c

# 前端源文件
FRONTEND_SOURCES = frontend/frontend_main.c \
                   include/common.c

# 后端目标
$(BACKEND_TARGET): $(BACKEND_SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

# 前端目标
$(FRONTEND_TARGET): $(FRONTEND_SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

# 创建数据目录
prepare:
	mkdir -p data

# 编译所有
all: prepare $(BACKEND_TARGET) $(FRONTEND_TARGET)

# 运行前端
run-frontend: $(FRONTEND_TARGET)
	./$(FRONTEND_TARGET)

# 运行后端
run-backend: $(BACKEND_TARGET)
	./$(BACKEND_TARGET)

# 清理
clean:
	rm -rf $(TARGET_DIR) data/*.dat

.PHONY: all prepare run-frontend run-backend clean
