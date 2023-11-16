# 定义编译器
CC = g++

# 定义编译选项
CFLAGS = -g -I/usr/include/mysql

# 定义链接选项
LDFLAGS = -lmysqlclient -lpthread

# 定义目标文件
TARGET = main

# 定义源文件
SOURCES = Connection.cpp main.cpp MySQLConnectionPool.cpp

# 默认目标
all: $(TARGET)

# 链接目标文件
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

# 清理目标文件和中间文件
clean:
	rm -f $(TARGET) *.o
