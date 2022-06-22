CREATE TABLE IF NOT EXISTS LogZhuangRecord (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 amount BIGINT COMMENT "充值金额" ,
 status BIGINT UNSIGNED COMMENT "状态:0=成功 1=失败" ,
 INDEX(user_id),
 INDEX(user_name),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogZhuangRecord add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogZhuangRecord add column sequence INT UNSIGNED;
alter table LogZhuangRecord add column bus_name VARCHAR(128);
alter table LogZhuangRecord add column event_time VARCHAR(128) COMMENT "时间";
alter table LogZhuangRecord add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogZhuangRecord add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogZhuangRecord add column amount BIGINT COMMENT "充值金额";
alter table LogZhuangRecord add column status BIGINT UNSIGNED COMMENT "状态:0=成功 1=失败";
*/
