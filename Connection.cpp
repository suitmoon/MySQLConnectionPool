#include "public.h"
#include "Connection.h"
#include <iostream>



Connection::Connection()
{
	// 初始化数据库连接
	_conn = mysql_init(nullptr);
}

Connection::~Connection()
{
	// 释放数据库连接资源
	if (_conn != nullptr)
		mysql_close(_conn);
}

bool Connection::connect(std::string ip, unsigned short port,
	std::string username, std::string password, std::string dbname)
{
	if (_conn == nullptr) {
		printf("Error %u: %s\n", mysql_errno(_conn), mysql_error(_conn));
		return false;
	}
	
	// 连接数据库
	MYSQL *p = mysql_real_connect(_conn, ip.c_str(), username.c_str(),
		password.c_str(), dbname.c_str(), port, nullptr, 0);

	return p != nullptr;
}

bool Connection::update(std::string sql)
{	
	// 更新操作 insert、delete、update
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("更新失败:" + sql);
		return false;
	}
	return true;
}

MYSQL_RES* Connection::query(std::string sql)
{
	// 查询操作 select
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("查询失败:" + sql);
		return nullptr;
	}
	return mysql_use_result(_conn);
}
