#include <iostream>
#include <chrono>
#include <thread>
#include <string.h>
#include "MySQLConnectionPool.h"
#include "Connection.h"


//删除表中数据
void deleteSQL() {
	Connection conn;
	conn.connect("127.0.0.1", 3306, "root", "1234", "MySQLConnectionPool");
	char sql[1024] = { 0 };
	sprintf(sql, "delete from user");
	conn.update(sql);
}

/*
 * @param cycle_index 循环次数
*/
//不用数据库连接池的方法
void runSQL(int cycle_index) {
	for (int i = 0; i < cycle_index; ++i)
	{	
	Connection conn;
	char sql[1024] = { 0 };
	sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
		"zhang san", 20, "male");
	
	conn.connect("127.0.0.1", 3306, "root", "1234", "MySQLConnectionPool");
	conn.update(sql);		
	}
}

//用数据库连接池的方法
void runSQLUsingPool(int cycle_index){
	//获取连接池实例
	MySQLConnectionPool *cp = MySQLConnectionPool::getConnectionPool();
	for (int i = 0; i < cycle_index; ++i)
	{
		char sql[1024] = { 0 };
		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
			"zhang san", 20, "male");
		//获取连接
		std::shared_ptr<Connection> sp = cp->getConnection();
		sp->update(sql);
	}
}

int main()
{
	{	
	Connection conn;
	//conn.connect("127.0.0.1", 3306, "root", "1234", "MySQLConnectionPool");
	auto start = std::chrono::high_resolution_clock::now();
	//runSQL(10000);
	runSQLUsingPool(100);
	//	std::thread t1(runSQLUsingPool,25);
	//	std::thread t3(runSQLUsingPool,25);
	//  std::thread t2(runSQLUsingPool,25);
	//  std::thread t4(runSQLUsingPool,25);
	//  t1.join();
	//  t2.join();
	//  t3.join();
	//  t4.join();
	// 获取结束时间点
	auto stop = std::chrono::high_resolution_clock::now();

	//计算耗时
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "耗时：" << duration.count() << " milliseconds" << std::endl;
	}
	//deleteSQL();	
	return 0;
}
//单线程测试		
	//不通过连接池
	//1000: 2119 2126 2133
	//5000: 10581 10478 10378
	//10000: 20989 20855 22342
	//通过连接池
	//1000: 2002 2018 2017
	//5000: 10082 10096 10055
	//10000: 20099 20143 20151
//多线程测试		
	//不通过连接池
	//1000: 1032 1045 1053
	//5000: 5116 5134 5180
	//10000: 10175 10166 10198
	//通过连接池
	//1000: 1011 1017 1013
	//5000: 5048 5045 5029
	//10000: 10089  10071 10094





