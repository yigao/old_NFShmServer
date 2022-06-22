CREATE TABLE IF NOT EXISTS LogRedeemCodeRechargeRecord (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "充值者ID" ,
 user_name VARCHAR(128) COMMENT "充值者昵称" ,
 amount BIGINT UNSIGNED COMMENT "充值金额" ,
 status BIGINT UNSIGNED COMMENT "状态:0=成功 1=失败" ,
 INDEX(user_id),
 INDEX(user_name),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogRedeemCodeRechargeRecord add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogRedeemCodeRechargeRecord add column sequence INT UNSIGNED;
alter table LogRedeemCodeRechargeRecord add column bus_name VARCHAR(128);
alter table LogRedeemCodeRechargeRecord add column event_time VARCHAR(128) COMMENT "时间";
alter table LogRedeemCodeRechargeRecord add column user_id BIGINT UNSIGNED COMMENT "充值者ID";
alter table LogRedeemCodeRechargeRecord add column user_name VARCHAR(128) COMMENT "充值者昵称";
alter table LogRedeemCodeRechargeRecord add column amount BIGINT UNSIGNED COMMENT "充值金额";
alter table LogRedeemCodeRechargeRecord add column status BIGINT UNSIGNED COMMENT "状态:0=成功 1=失败";
*/
