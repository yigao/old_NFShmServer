CREATE TABLE IF NOT EXISTS LogGameRecordDetail_0 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 result_info VARCHAR(1024) COMMENT "开奖结果" ,
 pour_jetton BIGINT UNSIGNED COMMENT "下注总额" ,
 win_jetton BIGINT COMMENT "盈利总和" ,
 tax_jetton BIGINT UNSIGNED COMMENT "税收总额" ,
 win_list VARCHAR(1024) COMMENT "压住在赢的区域列表" ,
 lost_list VARCHAR(1024) COMMENT "压住在输区域列表" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogGameRecordDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogGameRecordDetail add column sequence INT UNSIGNED;
alter table LogGameRecordDetail add column bus_name VARCHAR(128);
alter table LogGameRecordDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogGameRecordDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogGameRecordDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogGameRecordDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
alter table LogGameRecordDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogGameRecordDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogGameRecordDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogGameRecordDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogGameRecordDetail add column result_info VARCHAR(1024) COMMENT "开奖结果";
alter table LogGameRecordDetail add column pour_jetton BIGINT UNSIGNED COMMENT "下注总额";
alter table LogGameRecordDetail add column win_jetton BIGINT COMMENT "盈利总和";
alter table LogGameRecordDetail add column tax_jetton BIGINT UNSIGNED COMMENT "税收总额";
alter table LogGameRecordDetail add column win_list VARCHAR(1024) COMMENT "压住在赢的区域列表";
alter table LogGameRecordDetail add column lost_list VARCHAR(1024) COMMENT "压住在输区域列表";
*/
CREATE TABLE IF NOT EXISTS LogGameRecordDetail_1 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 result_info VARCHAR(1024) COMMENT "开奖结果" ,
 pour_jetton BIGINT UNSIGNED COMMENT "下注总额" ,
 win_jetton BIGINT COMMENT "盈利总和" ,
 tax_jetton BIGINT UNSIGNED COMMENT "税收总额" ,
 win_list VARCHAR(1024) COMMENT "压住在赢的区域列表" ,
 lost_list VARCHAR(1024) COMMENT "压住在输区域列表" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogGameRecordDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogGameRecordDetail add column sequence INT UNSIGNED;
alter table LogGameRecordDetail add column bus_name VARCHAR(128);
alter table LogGameRecordDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogGameRecordDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogGameRecordDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogGameRecordDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
alter table LogGameRecordDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogGameRecordDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogGameRecordDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogGameRecordDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogGameRecordDetail add column result_info VARCHAR(1024) COMMENT "开奖结果";
alter table LogGameRecordDetail add column pour_jetton BIGINT UNSIGNED COMMENT "下注总额";
alter table LogGameRecordDetail add column win_jetton BIGINT COMMENT "盈利总和";
alter table LogGameRecordDetail add column tax_jetton BIGINT UNSIGNED COMMENT "税收总额";
alter table LogGameRecordDetail add column win_list VARCHAR(1024) COMMENT "压住在赢的区域列表";
alter table LogGameRecordDetail add column lost_list VARCHAR(1024) COMMENT "压住在输区域列表";
*/
CREATE TABLE IF NOT EXISTS LogGameRecordDetail_2 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 result_info VARCHAR(1024) COMMENT "开奖结果" ,
 pour_jetton BIGINT UNSIGNED COMMENT "下注总额" ,
 win_jetton BIGINT COMMENT "盈利总和" ,
 tax_jetton BIGINT UNSIGNED COMMENT "税收总额" ,
 win_list VARCHAR(1024) COMMENT "压住在赢的区域列表" ,
 lost_list VARCHAR(1024) COMMENT "压住在输区域列表" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogGameRecordDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogGameRecordDetail add column sequence INT UNSIGNED;
alter table LogGameRecordDetail add column bus_name VARCHAR(128);
alter table LogGameRecordDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogGameRecordDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogGameRecordDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogGameRecordDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
alter table LogGameRecordDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogGameRecordDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogGameRecordDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogGameRecordDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogGameRecordDetail add column result_info VARCHAR(1024) COMMENT "开奖结果";
alter table LogGameRecordDetail add column pour_jetton BIGINT UNSIGNED COMMENT "下注总额";
alter table LogGameRecordDetail add column win_jetton BIGINT COMMENT "盈利总和";
alter table LogGameRecordDetail add column tax_jetton BIGINT UNSIGNED COMMENT "税收总额";
alter table LogGameRecordDetail add column win_list VARCHAR(1024) COMMENT "压住在赢的区域列表";
alter table LogGameRecordDetail add column lost_list VARCHAR(1024) COMMENT "压住在输区域列表";
*/
CREATE TABLE IF NOT EXISTS LogGameRecordDetail_3 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 result_info VARCHAR(1024) COMMENT "开奖结果" ,
 pour_jetton BIGINT UNSIGNED COMMENT "下注总额" ,
 win_jetton BIGINT COMMENT "盈利总和" ,
 tax_jetton BIGINT UNSIGNED COMMENT "税收总额" ,
 win_list VARCHAR(1024) COMMENT "压住在赢的区域列表" ,
 lost_list VARCHAR(1024) COMMENT "压住在输区域列表" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogGameRecordDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogGameRecordDetail add column sequence INT UNSIGNED;
alter table LogGameRecordDetail add column bus_name VARCHAR(128);
alter table LogGameRecordDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogGameRecordDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogGameRecordDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogGameRecordDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
alter table LogGameRecordDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogGameRecordDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogGameRecordDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogGameRecordDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogGameRecordDetail add column result_info VARCHAR(1024) COMMENT "开奖结果";
alter table LogGameRecordDetail add column pour_jetton BIGINT UNSIGNED COMMENT "下注总额";
alter table LogGameRecordDetail add column win_jetton BIGINT COMMENT "盈利总和";
alter table LogGameRecordDetail add column tax_jetton BIGINT UNSIGNED COMMENT "税收总额";
alter table LogGameRecordDetail add column win_list VARCHAR(1024) COMMENT "压住在赢的区域列表";
alter table LogGameRecordDetail add column lost_list VARCHAR(1024) COMMENT "压住在输区域列表";
*/
CREATE TABLE IF NOT EXISTS LogGameRecordDetail_4 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 result_info VARCHAR(1024) COMMENT "开奖结果" ,
 pour_jetton BIGINT UNSIGNED COMMENT "下注总额" ,
 win_jetton BIGINT COMMENT "盈利总和" ,
 tax_jetton BIGINT UNSIGNED COMMENT "税收总额" ,
 win_list VARCHAR(1024) COMMENT "压住在赢的区域列表" ,
 lost_list VARCHAR(1024) COMMENT "压住在输区域列表" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogGameRecordDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogGameRecordDetail add column sequence INT UNSIGNED;
alter table LogGameRecordDetail add column bus_name VARCHAR(128);
alter table LogGameRecordDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogGameRecordDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogGameRecordDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogGameRecordDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
alter table LogGameRecordDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogGameRecordDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogGameRecordDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogGameRecordDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogGameRecordDetail add column result_info VARCHAR(1024) COMMENT "开奖结果";
alter table LogGameRecordDetail add column pour_jetton BIGINT UNSIGNED COMMENT "下注总额";
alter table LogGameRecordDetail add column win_jetton BIGINT COMMENT "盈利总和";
alter table LogGameRecordDetail add column tax_jetton BIGINT UNSIGNED COMMENT "税收总额";
alter table LogGameRecordDetail add column win_list VARCHAR(1024) COMMENT "压住在赢的区域列表";
alter table LogGameRecordDetail add column lost_list VARCHAR(1024) COMMENT "压住在输区域列表";
*/
CREATE TABLE IF NOT EXISTS LogGameRecordDetail_5 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 result_info VARCHAR(1024) COMMENT "开奖结果" ,
 pour_jetton BIGINT UNSIGNED COMMENT "下注总额" ,
 win_jetton BIGINT COMMENT "盈利总和" ,
 tax_jetton BIGINT UNSIGNED COMMENT "税收总额" ,
 win_list VARCHAR(1024) COMMENT "压住在赢的区域列表" ,
 lost_list VARCHAR(1024) COMMENT "压住在输区域列表" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogGameRecordDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogGameRecordDetail add column sequence INT UNSIGNED;
alter table LogGameRecordDetail add column bus_name VARCHAR(128);
alter table LogGameRecordDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogGameRecordDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogGameRecordDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogGameRecordDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
alter table LogGameRecordDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogGameRecordDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogGameRecordDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogGameRecordDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogGameRecordDetail add column result_info VARCHAR(1024) COMMENT "开奖结果";
alter table LogGameRecordDetail add column pour_jetton BIGINT UNSIGNED COMMENT "下注总额";
alter table LogGameRecordDetail add column win_jetton BIGINT COMMENT "盈利总和";
alter table LogGameRecordDetail add column tax_jetton BIGINT UNSIGNED COMMENT "税收总额";
alter table LogGameRecordDetail add column win_list VARCHAR(1024) COMMENT "压住在赢的区域列表";
alter table LogGameRecordDetail add column lost_list VARCHAR(1024) COMMENT "压住在输区域列表";
*/
CREATE TABLE IF NOT EXISTS LogGameRecordDetail_6 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 result_info VARCHAR(1024) COMMENT "开奖结果" ,
 pour_jetton BIGINT UNSIGNED COMMENT "下注总额" ,
 win_jetton BIGINT COMMENT "盈利总和" ,
 tax_jetton BIGINT UNSIGNED COMMENT "税收总额" ,
 win_list VARCHAR(1024) COMMENT "压住在赢的区域列表" ,
 lost_list VARCHAR(1024) COMMENT "压住在输区域列表" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogGameRecordDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogGameRecordDetail add column sequence INT UNSIGNED;
alter table LogGameRecordDetail add column bus_name VARCHAR(128);
alter table LogGameRecordDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogGameRecordDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogGameRecordDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogGameRecordDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
alter table LogGameRecordDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogGameRecordDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogGameRecordDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogGameRecordDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogGameRecordDetail add column result_info VARCHAR(1024) COMMENT "开奖结果";
alter table LogGameRecordDetail add column pour_jetton BIGINT UNSIGNED COMMENT "下注总额";
alter table LogGameRecordDetail add column win_jetton BIGINT COMMENT "盈利总和";
alter table LogGameRecordDetail add column tax_jetton BIGINT UNSIGNED COMMENT "税收总额";
alter table LogGameRecordDetail add column win_list VARCHAR(1024) COMMENT "压住在赢的区域列表";
alter table LogGameRecordDetail add column lost_list VARCHAR(1024) COMMENT "压住在输区域列表";
*/
CREATE TABLE IF NOT EXISTS LogGameRecordDetail_7 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 result_info VARCHAR(1024) COMMENT "开奖结果" ,
 pour_jetton BIGINT UNSIGNED COMMENT "下注总额" ,
 win_jetton BIGINT COMMENT "盈利总和" ,
 tax_jetton BIGINT UNSIGNED COMMENT "税收总额" ,
 win_list VARCHAR(1024) COMMENT "压住在赢的区域列表" ,
 lost_list VARCHAR(1024) COMMENT "压住在输区域列表" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogGameRecordDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogGameRecordDetail add column sequence INT UNSIGNED;
alter table LogGameRecordDetail add column bus_name VARCHAR(128);
alter table LogGameRecordDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogGameRecordDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogGameRecordDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogGameRecordDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
alter table LogGameRecordDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogGameRecordDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogGameRecordDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogGameRecordDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogGameRecordDetail add column result_info VARCHAR(1024) COMMENT "开奖结果";
alter table LogGameRecordDetail add column pour_jetton BIGINT UNSIGNED COMMENT "下注总额";
alter table LogGameRecordDetail add column win_jetton BIGINT COMMENT "盈利总和";
alter table LogGameRecordDetail add column tax_jetton BIGINT UNSIGNED COMMENT "税收总额";
alter table LogGameRecordDetail add column win_list VARCHAR(1024) COMMENT "压住在赢的区域列表";
alter table LogGameRecordDetail add column lost_list VARCHAR(1024) COMMENT "压住在输区域列表";
*/
CREATE TABLE IF NOT EXISTS LogGameRecordDetail_8 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 result_info VARCHAR(1024) COMMENT "开奖结果" ,
 pour_jetton BIGINT UNSIGNED COMMENT "下注总额" ,
 win_jetton BIGINT COMMENT "盈利总和" ,
 tax_jetton BIGINT UNSIGNED COMMENT "税收总额" ,
 win_list VARCHAR(1024) COMMENT "压住在赢的区域列表" ,
 lost_list VARCHAR(1024) COMMENT "压住在输区域列表" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogGameRecordDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogGameRecordDetail add column sequence INT UNSIGNED;
alter table LogGameRecordDetail add column bus_name VARCHAR(128);
alter table LogGameRecordDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogGameRecordDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogGameRecordDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogGameRecordDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
alter table LogGameRecordDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogGameRecordDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogGameRecordDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogGameRecordDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogGameRecordDetail add column result_info VARCHAR(1024) COMMENT "开奖结果";
alter table LogGameRecordDetail add column pour_jetton BIGINT UNSIGNED COMMENT "下注总额";
alter table LogGameRecordDetail add column win_jetton BIGINT COMMENT "盈利总和";
alter table LogGameRecordDetail add column tax_jetton BIGINT UNSIGNED COMMENT "税收总额";
alter table LogGameRecordDetail add column win_list VARCHAR(1024) COMMENT "压住在赢的区域列表";
alter table LogGameRecordDetail add column lost_list VARCHAR(1024) COMMENT "压住在输区域列表";
*/
CREATE TABLE IF NOT EXISTS LogGameRecordDetail_9 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 result_info VARCHAR(1024) COMMENT "开奖结果" ,
 pour_jetton BIGINT UNSIGNED COMMENT "下注总额" ,
 win_jetton BIGINT COMMENT "盈利总和" ,
 tax_jetton BIGINT UNSIGNED COMMENT "税收总额" ,
 win_list VARCHAR(1024) COMMENT "压住在赢的区域列表" ,
 lost_list VARCHAR(1024) COMMENT "压住在输区域列表" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogGameRecordDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogGameRecordDetail add column sequence INT UNSIGNED;
alter table LogGameRecordDetail add column bus_name VARCHAR(128);
alter table LogGameRecordDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogGameRecordDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogGameRecordDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogGameRecordDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
alter table LogGameRecordDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogGameRecordDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogGameRecordDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogGameRecordDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogGameRecordDetail add column result_info VARCHAR(1024) COMMENT "开奖结果";
alter table LogGameRecordDetail add column pour_jetton BIGINT UNSIGNED COMMENT "下注总额";
alter table LogGameRecordDetail add column win_jetton BIGINT COMMENT "盈利总和";
alter table LogGameRecordDetail add column tax_jetton BIGINT UNSIGNED COMMENT "税收总额";
alter table LogGameRecordDetail add column win_list VARCHAR(1024) COMMENT "压住在赢的区域列表";
alter table LogGameRecordDetail add column lost_list VARCHAR(1024) COMMENT "压住在输区域列表";
*/
