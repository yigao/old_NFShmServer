CREATE TABLE IF NOT EXISTS LogGameDetail (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "庄家ID" ,
 user_name VARCHAR(128) COMMENT "庄家昵称" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 bet_info VARCHAR(1024) COMMENT "游戏下注信息" ,
 result_info VARCHAR(1024) COMMENT "游戏结果信息" ,
 game_time BIGINT UNSIGNED COMMENT "游戏时间" ,
 INDEX(record_id),
 INDEX(game_id),
 INDEX(room_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogGameDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogGameDetail add column sequence INT UNSIGNED;
alter table LogGameDetail add column bus_name VARCHAR(128);
alter table LogGameDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogGameDetail add column user_id BIGINT UNSIGNED COMMENT "庄家ID";
alter table LogGameDetail add column user_name VARCHAR(128) COMMENT "庄家昵称";
alter table LogGameDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
alter table LogGameDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogGameDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogGameDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogGameDetail add column bet_info VARCHAR(1024) COMMENT "游戏下注信息";
alter table LogGameDetail add column result_info VARCHAR(1024) COMMENT "游戏结果信息";
alter table LogGameDetail add column game_time BIGINT UNSIGNED COMMENT "游戏时间";
*/
