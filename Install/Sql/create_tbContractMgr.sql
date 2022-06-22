CREATE TABLE IF NOT EXISTS tbContractMgr (
 id BIGINT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT "ID" ,
 contract VARCHAR(128) COMMENT "合同号" ,
 machine_addr VARCHAR(128) COMMENT "机器码" ,
 ip VARCHAR(128) COMMENT "IP地址" ,
 server_desc VARCHAR(128) COMMENT "描述信息" ,
 INDEX(machine_addr),
 INDEX(ip),
 UNIQUE(contract),
 PRIMARY KEY(id)) AUTO_INCREMENT = 1 ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table tbContractMgr add column id BIGINT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT "ID";
alter table tbContractMgr add column contract VARCHAR(128) COMMENT "合同号";
alter table tbContractMgr add column machine_addr VARCHAR(128) COMMENT "机器码";
alter table tbContractMgr add column ip VARCHAR(128) COMMENT "IP地址";
alter table tbContractMgr add column server_desc VARCHAR(128) COMMENT "描述信息";
*/
