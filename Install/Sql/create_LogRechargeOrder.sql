CREATE TABLE IF NOT EXISTS LogRechargeOrder (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 order_id VARCHAR(128) COMMENT "订单ID" ,
 pay_id INT UNSIGNED COMMENT "支付类型" ,
 pay_channel VARCHAR(128) COMMENT "充值渠道" ,
 pay_type INT UNSIGNED COMMENT "充值:0=支付宝,1=微信,3=银联" ,
 ch_order_id VARCHAR(128) COMMENT "渠道获得的ID" ,
 state INT UNSIGNED COMMENT "支付状态:0=收到支付回调，支付成功,1=发起支付请求,2=返回失败" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(order_id),
 INDEX(ch_order_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogRechargeOrder add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogRechargeOrder add column sequence INT UNSIGNED;
alter table LogRechargeOrder add column bus_name VARCHAR(128);
alter table LogRechargeOrder add column event_time VARCHAR(128) COMMENT "时间";
alter table LogRechargeOrder add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogRechargeOrder add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogRechargeOrder add column order_id VARCHAR(128) COMMENT "订单ID";
alter table LogRechargeOrder add column pay_id INT UNSIGNED COMMENT "支付类型";
alter table LogRechargeOrder add column pay_channel VARCHAR(128) COMMENT "充值渠道";
alter table LogRechargeOrder add column pay_type INT UNSIGNED COMMENT "充值:0=支付宝,1=微信,3=银联";
alter table LogRechargeOrder add column ch_order_id VARCHAR(128) COMMENT "渠道获得的ID";
alter table LogRechargeOrder add column state INT UNSIGNED COMMENT "支付状态:0=收到支付回调，支付成功,1=发起支付请求,2=返回失败";
*/
