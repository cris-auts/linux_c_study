#include"std_globals.h"
#include "db.h"
 
#define PRINTERROR(str)	


 
const char *createSQL = "create table if not exists T_Students\
(S_id integer PRIMARY KEY NOT NULL,\
S_name varchar(128),S_age integer,\
Time TimeStamp NOT NULL DEFAULT (datetime('now','localtime')));";
 
const char *deleteSQL = "delete from T_Students where S_name='sagarfan';";
const char *updateSQL = "update T_Students set S_age=25 where S_name='sagarfan';";
const char *insertSQL = "insert into T_Students (S_name,S_age) values('sagarfan',23);";
const char *selectSQL = "select S_name,S_age from T_Students;";
 
int executeNoQuery(sqlite3 *db,const char *sql);
int executeWithQuery(sqlite3 *db,char ***result,int *col,const char *sql);
 
int main()
{
	sqlite3 *conn = NULL;
	int i,ret,ncol;char sql[1024]={0}; 
	char **array;
 
	ret = DB_OpenDataBase("stu.sqlite",&conn);
	if(ret != SQLITE_OK)
		PRINTERROR(sqlite3_errmsg(conn));
	//create table
	#if 0
	ret = executeNoQuery(conn,createSQL);
	if(ret == -1)
		PRINTERROR(sqlite3_errmsg(conn));
 
	ret = executeNoQuery(conn,insertSQL);
	if(ret == -1)
		PRINTERROR(sqlite3_errmsg(conn));
 
	ret = executeWithQuery(conn,&array,&ncol,selectSQL);
	if(ret == -1)
		PRINTERROR(sqlite3_errmsg(conn));
	i=0;
	while(array[i+ncol] != NULL)
	{
		printf("Name=%s\n",array[i+ncol]);
		printf("Age=%s\n",array[i+1+ncol]);
		i+=ncol;
	}
	sqlite3_free_table(array);
 
	ret = executeNoQuery(conn,updateSQL);
	if(ret == -1)
		PRINTERROR(sqlite3_errmsg(conn));
	
	if(conn != NULL)
		sqlite3_close(conn);
 	#endif
	return 0;
}
 
int executeNoQuery(sqlite3 *db,const char *sql)
{
	sqlite3_stmt *pstmt = NULL;
 
	if(sqlite3_prepare_v2(db,sql,strlen(sql),&pstmt,NULL) != SQLITE_OK)
	{
		if(pstmt != NULL)
			sqlite3_finalize(pstmt);
		return -1;
	}
	if(sqlite3_step(pstmt) != SQLITE_DONE)
	{
		sqlite3_finalize(pstmt);
		return -1;
	}
	sqlite3_finalize(pstmt);
	return 0;
}
 
int executeWithQuery(sqlite3 *db,char ***result,int *col,const char *sql)
{
	int ret,row;
 
	ret = sqlite3_get_table(db,sql,result,&row,col,NULL);
	if(ret != SQLITE_OK)
	{
		return -1;
	}
	(*result)[(row+1)*(*col)] = NULL;
 
	return 0;
}
