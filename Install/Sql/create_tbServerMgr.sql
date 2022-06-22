CREATE TABLE IF NOT EXISTS tbServerMgr (
 id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 contract VARCHAR(128) COMMENT "合同号" ,
 machine_addr VARCHAR(128) COMMENT "机器码" ,
 ip VARCHAR(128) COMMENT "IP地址" ,
 bus_name VARCHAR(128) COMMENT "服务器ID" ,
 server_desc VARCHAR(128) COMMENT "描述信息" ,
 cur_count INT UNSIGNED COMMENT "当前服务器数" ,
 last_login_time BIGINT UNSIGNED COMMENT "上一次登录时间" ,
 last_logout_time BIGINT UNSIGNED COMMENT "上一次下线时间" ,
 create_time BIGINT UNSIGNED COMMENT "创建时间" ,
 INDEX(contract),
 INDEX(machine_addr),
 INDEX(ip),
 INDEX(bus_name),
 PRIMARY KEY(id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table tbServerMgr add column id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table tbServerMgr add column contract VARCHAR(128) COMMENT "合同号";
alter table tbServerMgr add column machine_addr VARCHAR(128) COMMENT "机器码";
alter table tbServerMgr add column ip VARCHAR(128) COMMENT "IP地址";
alter table tbServerMgr add column bus_name VARCHAR(128) COMMENT "服务器ID";
alter table tbServerMgr add column server_desc VARCHAR(128) COMMENT "描述信息";
alter table tbServerMgr add column cur_count INT UNSIGNED COMMENT "当前服务器数";
alter table tbServerMgr add column last_login_time BIGINT UNSIGNED COMMENT "上一次登录时间";
alter table tbServerMgr add column last_logout_time BIGINT UNSIGNED COMMENT "上一次下线时间";
alter table tbServerMgr add column create_time BIGINT UNSIGNED COMMENT "创建时间";
*/
