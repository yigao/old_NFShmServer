CREATE TABLE IF NOT EXISTS tbGiveBankJetton (
 id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 user_id BIGINT UNSIGNED COMMENT "赠送者ID" ,
 user_name VARCHAR(64) COMMENT "赠送者昵称" ,
 user_vip_level BIGINT UNSIGNED COMMENT "赠送者VIP" ,
 give_user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 give_user_name VARCHAR(64) COMMENT "昵称" ,
 give_jetton BIGINT UNSIGNED COMMENT "数量" ,
 give_user_vip_level INT UNSIGNED COMMENT "玩家VIP" ,
 status INT UNSIGNED COMMENT "状态:0=进行中,1=失败,2=成功,3=取消中,4=取消成功" ,
 create_time BIGINT UNSIGNED COMMENT "日期" ,
 PRIMARY KEY(id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table tbGiveBankJetton add column id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table tbGiveBankJetton add column user_id BIGINT UNSIGNED COMMENT "赠送者ID";
alter table tbGiveBankJetton add column user_name VARCHAR(64) COMMENT "赠送者昵称";
alter table tbGiveBankJetton add column user_vip_level BIGINT UNSIGNED COMMENT "赠送者VIP";
alter table tbGiveBankJetton add column give_user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table tbGiveBankJetton add column give_user_name VARCHAR(64) COMMENT "昵称";
alter table tbGiveBankJetton add column give_jetton BIGINT UNSIGNED COMMENT "数量";
alter table tbGiveBankJetton add column give_user_vip_level INT UNSIGNED COMMENT "玩家VIP";
alter table tbGiveBankJetton add column status INT UNSIGNED COMMENT "状态:0=进行中,1=失败,2=成功,3=取消中,4=取消成功";
alter table tbGiveBankJetton add column create_time BIGINT UNSIGNED COMMENT "日期";
*/
