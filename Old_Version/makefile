# ���������
CC = g++

# �������ѡ��
CFLAGS = -g -I/usr/include/mysql

# ��������ѡ��
LDFLAGS = -lmysqlclient -lpthread

# ����Ŀ���ļ�
TARGET = main

# ����Դ�ļ�
SOURCES = Connection.cpp main.cpp MySQLConnectionPool.cpp

# Ĭ��Ŀ��
all: $(TARGET)

# ����Ŀ���ļ�
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

# ����Ŀ���ļ����м��ļ�
clean:
	rm -f $(TARGET) *.o
