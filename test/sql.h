#ifndef _SQL_H
#define _SQL_H

#define DB_VERSION				3
#define DB_VERSION_KEY			"DB_VERSION"

#define TABLE_NAME_CACHE		"pcs_cache"
#define TABLE_NAME_ACTION		"pcs_action"
#define TABLE_CACHE_CREATOR		"CREATE TABLE [pcs_cache] (" \
								"  [server_fs_id]			INTEGER," \
								"  [server_path]			NTEXT," \
								"  [server_filename]		NTEXT," \
								"  [server_ctime]			INTEGER," \
								"  [server_mtime]			INTEGER," \
								"  [server_size]			INTEGER," \
								"  [server_category]		INTEGER," \
								"  [server_isdir]			INTEGER," \
								"  [server_dir_empty]		INTEGER," \
								"  [server_empty]			INTEGER," \
								"  [server_md5]				NTEXT," \
								"  [server_dlink]			NTEXT," \
								"  [server_if_has_sub_dir]	INTEGER," \
								"  [ctime]					INTEGER," \
								"  [mtime]					INTEGER," \
								"  [capp]					NVARCHAR," \
								"  [mapp]					NVARCHAR,"\
								"  [flag]					INTEGER)"
#define TABLE_CACHE_INDEX_CREATOR "CREATE INDEX [ix_pcs_cache_path] ON [pcs_cache] ([server_path])"

#define TABLE_NAME_OP			"pcs_op"
#define TABLE_ACTION_CREATOR	"CREATE TABLE [pcs_action] (" \
								"  [action]					NVARCHAR, " \
								"  [status]					INTEGER, " \
								"  [start_time]				INTEGER, " \
								"  [end_time]				INTEGER, " \
								"  [capp]					NVARCHAR, " \
								"  [mapp]					NVARCHAR)"
#define TABLE_ACTION_INDEX_CREATOR "CREATE INDEX [ix_pcs_action_action] ON [pcs_action] ([action])"
#define SQL_ADD_DB_VERSION			"INSERT INTO pcs_action (action,status,start_time,end_time,capp,mapp) VALUES ('DB_VERSION',1,0,0,'SYSTEM','SYSTEM')"

#define TABLE_NAME_TASK			"pcs_task"
#define TABLE_TASK_CREATOR		"CREATE TABLE [pcs_task] (" \
	"  [id]						INTEGER, " \
	"  [method]					INTEGER, " \
	"  [enabled]				INTEGER, " \
	"  [last_run_time]			INTEGER, " \
	"  [next_run_time]			INTEGER, " \
	"  [schedule]				INTEGER, " \
	"  [interval]				INTEGER, " \
	"  [local_path]				NVARCHAR, " \
	"  [remote_path]			NVARCHAR," \
	"  [status]				    INTEGER, " \
	"  [result]				    INTEGER, " \
	"  [start_time]				INTEGER, " \
	"  [end_time]				INTEGER, " \
	"  [elapsed]				INTEGER, " \
	"  [md5]					INTEGER) "

#define SQL_UPDATE_DB_FROM_VER0	"alter table pcs_task add md5 INTEGER"

#define SQL_TABLE_EXISTS		"SELECT name FROM sqlite_master WHERE type = 'table' AND name=?"

#define SQL_TASK_SELECT_ALL		"SELECT id,method,enabled,last_run_time,next_run_time,schedule,interval,local_path,remote_path,status,result,start_time,end_time,elapsed,md5 FROM pcs_task"
#define SQL_TASK_SELECT_ONE		"SELECT id,method,enabled,last_run_time,next_run_time,schedule,interval,local_path,remote_path,status,result,start_time,end_time,elapsed,md5 FROM pcs_task WHERE method=?1 AND local_path=?2 AND remote_path=?3"
#define SQL_TASK_DELETE_ALL		"DELETE FROM pcs_task"
#define SQL_TASK_INSERT			"INSERT INTO pcs_task (id,method,enabled,last_run_time,next_run_time,schedule,interval,local_path,remote_path," \
								"status,result,start_time,end_time,elapsed,md5) " \
								"VALUES (?1,?2,?3,?4,?5,?6,?7,?8,?9,  ?11, ?12, ?13, ?14, ?15, ?10)"
#define SQL_TASK_UPDATE_STATUS	"UPDATE pcs_task SET status=?2, result=?3, start_time=?4, end_time=0, elapsed=0 WHERE id=?1"
#define SQL_TASK_UPDATE_STATUS2	"UPDATE pcs_task SET enabled=?2, last_run_time=?3, next_run_time=?4, status=?5, " \
								"result=?6, start_time=?7, end_time=?8, elapsed=?9 " \
								"WHERE id=?1"

#define SQL_ACTION_EXISTS		"SELECT status FROM pcs_action WHERE action=?1"
#define SQL_ACTION_SELECT		"SELECT ROWID, action,status,start_time,end_time,capp,mapp FROM pcs_action WHERE action=?1"
#define SQL_ACTION_INSERT		"INSERT INTO pcs_action (action,status,start_time,end_time,capp,mapp) VALUES (?1,?2,?3,?4,?5,?5)"
#define SQL_ACTION_UPDATE_START	"UPDATE pcs_action SET status=?2,start_time=?3,end_time=?3,capp=?4,mapp=?4 WHERE action=?1"
#define SQL_ACTION_UPDATE_END	"UPDATE pcs_action SET status=?2,end_time=?3,mapp=?4 WHERE action=?1"
#define SQL_ACTION_DELETE		"DELETE FROM pcs_action WHERE action=?1"
#define SQL_ACTION_SELECT_ALL	"SELECT ROWID, action,status,start_time,end_time,capp,mapp FROM pcs_action"

#define SQL_CACHE_SELECT		"SELECT server_fs_id, server_path, server_filename, server_ctime, server_mtime, "\
								"server_size, server_category, server_isdir, server_dir_empty, server_empty, "\
								"server_md5, server_dlink, server_if_has_sub_dir, ctime, mtime, capp, mapp, flag "\
								"FROM pcs_cache "\
								"WHERE server_path=?1"
#define SQL_CACHE_SELECT_UNTRACK "SELECT server_fs_id, server_path, server_filename, server_ctime, server_mtime, "\
								"server_size, server_category, server_isdir, server_dir_empty, server_empty, "\
								"server_md5, server_dlink, server_if_has_sub_dir, ctime, mtime, capp, mapp, flag "\
								"FROM pcs_cache "\
								"WHERE server_path LIKE ?1 AND flag = 0"
#define SQL_CACHE_SELECT_SUB	"SELECT server_fs_id, server_path, server_filename, server_ctime, server_mtime, "\
								"server_size, server_category, server_isdir, server_dir_empty, server_empty, "\
								"server_md5, server_dlink, server_if_has_sub_dir, ctime, mtime, capp, mapp, flag "\
								"FROM pcs_cache "\
								"WHERE server_path LIKE ?1"
#define SQL_CACHE_SELECT_SUB_DIR_FIRST SQL_CACHE_SELECT_SUB " ORDER BY server_isdir DESC"
#define SQL_CACHE_INSERT		"INSERT INTO pcs_cache (server_fs_id, server_path, server_filename, server_ctime, server_mtime, " \
								"server_size, server_category, server_isdir, server_dir_empty, server_empty, "\
								"server_md5, server_dlink, server_if_has_sub_dir, ctime, mtime, capp, mapp, flag) " \
								"VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8, ?9, ?10, ?11, ?12, ?13, ?14, ?14, ?15, ?15, ?16)"
#define SQL_CACHE_UPDATE		"UPDATE pcs_cache SET server_fs_id=?1, server_path=?2, server_filename=?3, server_ctime=?4, server_mtime=?5, " \
								"server_size=?6, server_category=?7, server_isdir=?8, server_dir_empty=?9, server_empty=?10, "\
								"server_md5=?11, server_dlink=?12, server_if_has_sub_dir=?13, mtime=?14, mapp=?15, flag=?16 " \
								"WHERE server_path=?2"
#define SQL_CACHE_DELETE		"DELETE FROM pcs_cache WHERE server_path=?1"
#define SQL_CACHE_CLEAR			"DELETE FROM pcs_cache WHERE server_path LIKE ?1"
#define SQL_CACHE_SET_FLAG_SUB	"UPDATE pcs_cache SET flag = ?2, mtime=?3, mapp=?4 WHERE server_path LIKE ?1"
#define SQL_CACHE_SET_FLAG		"UPDATE pcs_cache SET flag = ?2, mtime=?3, mapp=?4 WHERE server_path = ?1"
//#define SQL_CACHE_CLEAR_ALL		"DELETE FROM pcs_cache"


#endif
