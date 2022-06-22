CREATE TABLE IF NOT EXISTS LogVipRechargeRecord (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 amount BIGINT UNSIGNED COMMENT "充值金额" ,
 recharge_id INT UNSIGNED COMMENT "充值者ID" ,
 recharge_name VARCHAR(128) COMMENT "充值者昵称" ,
 status BIGINT UNSIGNED COMMENT "状态:0=成功 1=失败" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(recharge_name),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogVipRechargeRecord add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogVipRechargeRecord add column sequence INT UNSIGNED;
alter table LogVipRechargeRecord add column bus_name VARCHAR(128);
alter table LogVipRechargeRecord add column event_time VARCHAR(128) COMMENT "时间";
alter table LogVipRechargeRecord add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogVipRechargeRecord add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogVipRechargeRecord add column amount BIGINT UNSIGNED COMMENT "充值金额";
alter table LogVipRechargeRecord add column recharge_id INT UNSIGNED COMMENT "充值者ID";
alter table LogVipRechargeRecord add column recharge_name VARCHAR(128) COMMENT "充值者昵称";
alter table LogVipRechargeRecord add column status BIGINT UNSIGNED COMMENT "状态:0=成功 1=失败";
*/
