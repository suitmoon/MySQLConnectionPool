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
	Connection conn;
	//conn.connect("127.0.0.1", 3306, "root", "1234", "MySQLConnectionPool");
	auto start = std::chrono::high_resolution_clock::now();
	//runSQL(10000);
	//runSQLUsingPool(10000);

	std::thread t1(runSQLUsingPool,250);
	std::thread t3(runSQLUsingPool,250);
	std::thread t2(runSQLUsingPool,250);
	std::thread t4(runSQLUsingPool,250);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	// 获取结束时间点
	auto stop = std::chrono::high_resolution_clock::now();

	//计算耗时
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "耗时：" << duration.count() << " milliseconds" << std::endl;

	//deleteSQL();	
	return 0;
}




//单线程测试		
	//不通过连接池
	//1000: 2880 2749 2841 
	//5000: 12512 13011 12977 
	//10000: 26089 25824 25694
	//通过连接池
	//1000: 262 260 276
	//5000: 1088 1189 1183
	//10000: 2385 2303 2371
//多线程测试		
	//不通过连接池
	//1000: 696 820 743
	//5000: 3373 3275 3322 
	//10000: 6450 6204 6365
	//通过连接池
	//1000: 116 121 129
	//5000: 473 468 435
	//10000: 848 866 947






