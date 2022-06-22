CREATE TABLE IF NOT EXISTS LogGiveMoneyRecord (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 type INT UNSIGNED COMMENT "赠送类型:0=Web直接赠送" ,
 amount BIGINT UNSIGNED COMMENT "赠送金额" ,
 status BIGINT UNSIGNED COMMENT "状态:0=成功 1=失败" ,
 INDEX(user_id),
 INDEX(user_name),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogGiveMoneyRecord add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogGiveMoneyRecord add column sequence INT UNSIGNED;
alter table LogGiveMoneyRecord add column bus_name VARCHAR(128);
alter table LogGiveMoneyRecord add column event_time VARCHAR(128) COMMENT "时间";
alter table LogGiveMoneyRecord add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogGiveMoneyRecord add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogGiveMoneyRecord add column type INT UNSIGNED COMMENT "赠送类型:0=Web直接赠送";
alter table LogGiveMoneyRecord add column amount BIGINT UNSIGNED COMMENT "赠送金额";
alter table LogGiveMoneyRecord add column status BIGINT UNSIGNED COMMENT "状态:0=成功 1=失败";
*/
