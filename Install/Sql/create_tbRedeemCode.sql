CREATE TABLE IF NOT EXISTS tbRedeemCode (
 id VARCHAR(128) NOT NULL COMMENT "ID" ,
 gold BIGINT UNSIGNED COMMENT "点卡额度" ,
 create_time BIGINT UNSIGNED COMMENT "创建时间" ,
 code_name VARCHAR(128) COMMENT "代号名" ,
 state INT UNSIGNED COMMENT "状态:0=未使用,1=已使用" ,
 user_id BIGINT UNSIGNED COMMENT "使用玩家ID" ,
 use_time BIGINT UNSIGNED COMMENT "使用时间" ,
 INDEX(code_name),
 INDEX(user_id),
 PRIMARY KEY(id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table tbRedeemCode add column id VARCHAR(128) NOT NULL COMMENT "ID";
alter table tbRedeemCode add column gold BIGINT UNSIGNED COMMENT "点卡额度";
alter table tbRedeemCode add column create_time BIGINT UNSIGNED COMMENT "创建时间";
alter table tbRedeemCode add column code_name VARCHAR(128) COMMENT "代号名";
alter table tbRedeemCode add column state INT UNSIGNED COMMENT "状态:0=未使用,1=已使用";
alter table tbRedeemCode add column user_id BIGINT UNSIGNED COMMENT "使用玩家ID";
alter table tbRedeemCode add column use_time BIGINT UNSIGNED COMMENT "使用时间";
*/
