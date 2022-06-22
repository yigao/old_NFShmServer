CREATE TABLE IF NOT EXISTS LogMoneyDetail_0 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 account_type INT UNSIGNED COMMENT "账号类型" ,
 opt_type INT UNSIGNED COMMENT "操作类型" ,
 opt_reason INT UNSIGNED COMMENT "操作缘由" ,
 all_jetton BIGINT UNSIGNED COMMENT "全部金币" ,
 jetton BIGINT UNSIGNED COMMENT "身上金币" ,
 bank_jetton BIGINT UNSIGNED COMMENT "银行金币" ,
 change_count BIGINT UNSIGNED COMMENT "改变数量" ,
 agent_id BIGINT UNSIGNED COMMENT "上级代理ID" ,
 ip VARCHAR(128) COMMENT "IP地址" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogMoneyDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogMoneyDetail add column sequence INT UNSIGNED;
alter table LogMoneyDetail add column bus_name VARCHAR(128);
alter table LogMoneyDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogMoneyDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogMoneyDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogMoneyDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogMoneyDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogMoneyDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogMoneyDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogMoneyDetail add column account_type INT UNSIGNED COMMENT "账号类型";
alter table LogMoneyDetail add column opt_type INT UNSIGNED COMMENT "操作类型";
alter table LogMoneyDetail add column opt_reason INT UNSIGNED COMMENT "操作缘由";
alter table LogMoneyDetail add column all_jetton BIGINT UNSIGNED COMMENT "全部金币";
alter table LogMoneyDetail add column jetton BIGINT UNSIGNED COMMENT "身上金币";
alter table LogMoneyDetail add column bank_jetton BIGINT UNSIGNED COMMENT "银行金币";
alter table LogMoneyDetail add column change_count BIGINT UNSIGNED COMMENT "改变数量";
alter table LogMoneyDetail add column agent_id BIGINT UNSIGNED COMMENT "上级代理ID";
alter table LogMoneyDetail add column ip VARCHAR(128) COMMENT "IP地址";
alter table LogMoneyDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
*/
CREATE TABLE IF NOT EXISTS LogMoneyDetail_1 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 account_type INT UNSIGNED COMMENT "账号类型" ,
 opt_type INT UNSIGNED COMMENT "操作类型" ,
 opt_reason INT UNSIGNED COMMENT "操作缘由" ,
 all_jetton BIGINT UNSIGNED COMMENT "全部金币" ,
 jetton BIGINT UNSIGNED COMMENT "身上金币" ,
 bank_jetton BIGINT UNSIGNED COMMENT "银行金币" ,
 change_count BIGINT UNSIGNED COMMENT "改变数量" ,
 agent_id BIGINT UNSIGNED COMMENT "上级代理ID" ,
 ip VARCHAR(128) COMMENT "IP地址" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogMoneyDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogMoneyDetail add column sequence INT UNSIGNED;
alter table LogMoneyDetail add column bus_name VARCHAR(128);
alter table LogMoneyDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogMoneyDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogMoneyDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogMoneyDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogMoneyDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogMoneyDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogMoneyDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogMoneyDetail add column account_type INT UNSIGNED COMMENT "账号类型";
alter table LogMoneyDetail add column opt_type INT UNSIGNED COMMENT "操作类型";
alter table LogMoneyDetail add column opt_reason INT UNSIGNED COMMENT "操作缘由";
alter table LogMoneyDetail add column all_jetton BIGINT UNSIGNED COMMENT "全部金币";
alter table LogMoneyDetail add column jetton BIGINT UNSIGNED COMMENT "身上金币";
alter table LogMoneyDetail add column bank_jetton BIGINT UNSIGNED COMMENT "银行金币";
alter table LogMoneyDetail add column change_count BIGINT UNSIGNED COMMENT "改变数量";
alter table LogMoneyDetail add column agent_id BIGINT UNSIGNED COMMENT "上级代理ID";
alter table LogMoneyDetail add column ip VARCHAR(128) COMMENT "IP地址";
alter table LogMoneyDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
*/
CREATE TABLE IF NOT EXISTS LogMoneyDetail_2 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 account_type INT UNSIGNED COMMENT "账号类型" ,
 opt_type INT UNSIGNED COMMENT "操作类型" ,
 opt_reason INT UNSIGNED COMMENT "操作缘由" ,
 all_jetton BIGINT UNSIGNED COMMENT "全部金币" ,
 jetton BIGINT UNSIGNED COMMENT "身上金币" ,
 bank_jetton BIGINT UNSIGNED COMMENT "银行金币" ,
 change_count BIGINT UNSIGNED COMMENT "改变数量" ,
 agent_id BIGINT UNSIGNED COMMENT "上级代理ID" ,
 ip VARCHAR(128) COMMENT "IP地址" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogMoneyDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogMoneyDetail add column sequence INT UNSIGNED;
alter table LogMoneyDetail add column bus_name VARCHAR(128);
alter table LogMoneyDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogMoneyDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogMoneyDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogMoneyDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogMoneyDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogMoneyDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogMoneyDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogMoneyDetail add column account_type INT UNSIGNED COMMENT "账号类型";
alter table LogMoneyDetail add column opt_type INT UNSIGNED COMMENT "操作类型";
alter table LogMoneyDetail add column opt_reason INT UNSIGNED COMMENT "操作缘由";
alter table LogMoneyDetail add column all_jetton BIGINT UNSIGNED COMMENT "全部金币";
alter table LogMoneyDetail add column jetton BIGINT UNSIGNED COMMENT "身上金币";
alter table LogMoneyDetail add column bank_jetton BIGINT UNSIGNED COMMENT "银行金币";
alter table LogMoneyDetail add column change_count BIGINT UNSIGNED COMMENT "改变数量";
alter table LogMoneyDetail add column agent_id BIGINT UNSIGNED COMMENT "上级代理ID";
alter table LogMoneyDetail add column ip VARCHAR(128) COMMENT "IP地址";
alter table LogMoneyDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
*/
CREATE TABLE IF NOT EXISTS LogMoneyDetail_3 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 account_type INT UNSIGNED COMMENT "账号类型" ,
 opt_type INT UNSIGNED COMMENT "操作类型" ,
 opt_reason INT UNSIGNED COMMENT "操作缘由" ,
 all_jetton BIGINT UNSIGNED COMMENT "全部金币" ,
 jetton BIGINT UNSIGNED COMMENT "身上金币" ,
 bank_jetton BIGINT UNSIGNED COMMENT "银行金币" ,
 change_count BIGINT UNSIGNED COMMENT "改变数量" ,
 agent_id BIGINT UNSIGNED COMMENT "上级代理ID" ,
 ip VARCHAR(128) COMMENT "IP地址" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogMoneyDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogMoneyDetail add column sequence INT UNSIGNED;
alter table LogMoneyDetail add column bus_name VARCHAR(128);
alter table LogMoneyDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogMoneyDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogMoneyDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogMoneyDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogMoneyDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogMoneyDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogMoneyDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogMoneyDetail add column account_type INT UNSIGNED COMMENT "账号类型";
alter table LogMoneyDetail add column opt_type INT UNSIGNED COMMENT "操作类型";
alter table LogMoneyDetail add column opt_reason INT UNSIGNED COMMENT "操作缘由";
alter table LogMoneyDetail add column all_jetton BIGINT UNSIGNED COMMENT "全部金币";
alter table LogMoneyDetail add column jetton BIGINT UNSIGNED COMMENT "身上金币";
alter table LogMoneyDetail add column bank_jetton BIGINT UNSIGNED COMMENT "银行金币";
alter table LogMoneyDetail add column change_count BIGINT UNSIGNED COMMENT "改变数量";
alter table LogMoneyDetail add column agent_id BIGINT UNSIGNED COMMENT "上级代理ID";
alter table LogMoneyDetail add column ip VARCHAR(128) COMMENT "IP地址";
alter table LogMoneyDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
*/
CREATE TABLE IF NOT EXISTS LogMoneyDetail_4 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 account_type INT UNSIGNED COMMENT "账号类型" ,
 opt_type INT UNSIGNED COMMENT "操作类型" ,
 opt_reason INT UNSIGNED COMMENT "操作缘由" ,
 all_jetton BIGINT UNSIGNED COMMENT "全部金币" ,
 jetton BIGINT UNSIGNED COMMENT "身上金币" ,
 bank_jetton BIGINT UNSIGNED COMMENT "银行金币" ,
 change_count BIGINT UNSIGNED COMMENT "改变数量" ,
 agent_id BIGINT UNSIGNED COMMENT "上级代理ID" ,
 ip VARCHAR(128) COMMENT "IP地址" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogMoneyDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogMoneyDetail add column sequence INT UNSIGNED;
alter table LogMoneyDetail add column bus_name VARCHAR(128);
alter table LogMoneyDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogMoneyDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogMoneyDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogMoneyDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogMoneyDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogMoneyDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogMoneyDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogMoneyDetail add column account_type INT UNSIGNED COMMENT "账号类型";
alter table LogMoneyDetail add column opt_type INT UNSIGNED COMMENT "操作类型";
alter table LogMoneyDetail add column opt_reason INT UNSIGNED COMMENT "操作缘由";
alter table LogMoneyDetail add column all_jetton BIGINT UNSIGNED COMMENT "全部金币";
alter table LogMoneyDetail add column jetton BIGINT UNSIGNED COMMENT "身上金币";
alter table LogMoneyDetail add column bank_jetton BIGINT UNSIGNED COMMENT "银行金币";
alter table LogMoneyDetail add column change_count BIGINT UNSIGNED COMMENT "改变数量";
alter table LogMoneyDetail add column agent_id BIGINT UNSIGNED COMMENT "上级代理ID";
alter table LogMoneyDetail add column ip VARCHAR(128) COMMENT "IP地址";
alter table LogMoneyDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
*/
CREATE TABLE IF NOT EXISTS LogMoneyDetail_5 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 account_type INT UNSIGNED COMMENT "账号类型" ,
 opt_type INT UNSIGNED COMMENT "操作类型" ,
 opt_reason INT UNSIGNED COMMENT "操作缘由" ,
 all_jetton BIGINT UNSIGNED COMMENT "全部金币" ,
 jetton BIGINT UNSIGNED COMMENT "身上金币" ,
 bank_jetton BIGINT UNSIGNED COMMENT "银行金币" ,
 change_count BIGINT UNSIGNED COMMENT "改变数量" ,
 agent_id BIGINT UNSIGNED COMMENT "上级代理ID" ,
 ip VARCHAR(128) COMMENT "IP地址" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogMoneyDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogMoneyDetail add column sequence INT UNSIGNED;
alter table LogMoneyDetail add column bus_name VARCHAR(128);
alter table LogMoneyDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogMoneyDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogMoneyDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogMoneyDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogMoneyDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogMoneyDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogMoneyDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogMoneyDetail add column account_type INT UNSIGNED COMMENT "账号类型";
alter table LogMoneyDetail add column opt_type INT UNSIGNED COMMENT "操作类型";
alter table LogMoneyDetail add column opt_reason INT UNSIGNED COMMENT "操作缘由";
alter table LogMoneyDetail add column all_jetton BIGINT UNSIGNED COMMENT "全部金币";
alter table LogMoneyDetail add column jetton BIGINT UNSIGNED COMMENT "身上金币";
alter table LogMoneyDetail add column bank_jetton BIGINT UNSIGNED COMMENT "银行金币";
alter table LogMoneyDetail add column change_count BIGINT UNSIGNED COMMENT "改变数量";
alter table LogMoneyDetail add column agent_id BIGINT UNSIGNED COMMENT "上级代理ID";
alter table LogMoneyDetail add column ip VARCHAR(128) COMMENT "IP地址";
alter table LogMoneyDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
*/
CREATE TABLE IF NOT EXISTS LogMoneyDetail_6 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 account_type INT UNSIGNED COMMENT "账号类型" ,
 opt_type INT UNSIGNED COMMENT "操作类型" ,
 opt_reason INT UNSIGNED COMMENT "操作缘由" ,
 all_jetton BIGINT UNSIGNED COMMENT "全部金币" ,
 jetton BIGINT UNSIGNED COMMENT "身上金币" ,
 bank_jetton BIGINT UNSIGNED COMMENT "银行金币" ,
 change_count BIGINT UNSIGNED COMMENT "改变数量" ,
 agent_id BIGINT UNSIGNED COMMENT "上级代理ID" ,
 ip VARCHAR(128) COMMENT "IP地址" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogMoneyDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogMoneyDetail add column sequence INT UNSIGNED;
alter table LogMoneyDetail add column bus_name VARCHAR(128);
alter table LogMoneyDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogMoneyDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogMoneyDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogMoneyDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogMoneyDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogMoneyDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogMoneyDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogMoneyDetail add column account_type INT UNSIGNED COMMENT "账号类型";
alter table LogMoneyDetail add column opt_type INT UNSIGNED COMMENT "操作类型";
alter table LogMoneyDetail add column opt_reason INT UNSIGNED COMMENT "操作缘由";
alter table LogMoneyDetail add column all_jetton BIGINT UNSIGNED COMMENT "全部金币";
alter table LogMoneyDetail add column jetton BIGINT UNSIGNED COMMENT "身上金币";
alter table LogMoneyDetail add column bank_jetton BIGINT UNSIGNED COMMENT "银行金币";
alter table LogMoneyDetail add column change_count BIGINT UNSIGNED COMMENT "改变数量";
alter table LogMoneyDetail add column agent_id BIGINT UNSIGNED COMMENT "上级代理ID";
alter table LogMoneyDetail add column ip VARCHAR(128) COMMENT "IP地址";
alter table LogMoneyDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
*/
CREATE TABLE IF NOT EXISTS LogMoneyDetail_7 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 account_type INT UNSIGNED COMMENT "账号类型" ,
 opt_type INT UNSIGNED COMMENT "操作类型" ,
 opt_reason INT UNSIGNED COMMENT "操作缘由" ,
 all_jetton BIGINT UNSIGNED COMMENT "全部金币" ,
 jetton BIGINT UNSIGNED COMMENT "身上金币" ,
 bank_jetton BIGINT UNSIGNED COMMENT "银行金币" ,
 change_count BIGINT UNSIGNED COMMENT "改变数量" ,
 agent_id BIGINT UNSIGNED COMMENT "上级代理ID" ,
 ip VARCHAR(128) COMMENT "IP地址" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogMoneyDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogMoneyDetail add column sequence INT UNSIGNED;
alter table LogMoneyDetail add column bus_name VARCHAR(128);
alter table LogMoneyDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogMoneyDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogMoneyDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogMoneyDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogMoneyDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogMoneyDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogMoneyDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogMoneyDetail add column account_type INT UNSIGNED COMMENT "账号类型";
alter table LogMoneyDetail add column opt_type INT UNSIGNED COMMENT "操作类型";
alter table LogMoneyDetail add column opt_reason INT UNSIGNED COMMENT "操作缘由";
alter table LogMoneyDetail add column all_jetton BIGINT UNSIGNED COMMENT "全部金币";
alter table LogMoneyDetail add column jetton BIGINT UNSIGNED COMMENT "身上金币";
alter table LogMoneyDetail add column bank_jetton BIGINT UNSIGNED COMMENT "银行金币";
alter table LogMoneyDetail add column change_count BIGINT UNSIGNED COMMENT "改变数量";
alter table LogMoneyDetail add column agent_id BIGINT UNSIGNED COMMENT "上级代理ID";
alter table LogMoneyDetail add column ip VARCHAR(128) COMMENT "IP地址";
alter table LogMoneyDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
*/
CREATE TABLE IF NOT EXISTS LogMoneyDetail_8 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 account_type INT UNSIGNED COMMENT "账号类型" ,
 opt_type INT UNSIGNED COMMENT "操作类型" ,
 opt_reason INT UNSIGNED COMMENT "操作缘由" ,
 all_jetton BIGINT UNSIGNED COMMENT "全部金币" ,
 jetton BIGINT UNSIGNED COMMENT "身上金币" ,
 bank_jetton BIGINT UNSIGNED COMMENT "银行金币" ,
 change_count BIGINT UNSIGNED COMMENT "改变数量" ,
 agent_id BIGINT UNSIGNED COMMENT "上级代理ID" ,
 ip VARCHAR(128) COMMENT "IP地址" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogMoneyDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogMoneyDetail add column sequence INT UNSIGNED;
alter table LogMoneyDetail add column bus_name VARCHAR(128);
alter table LogMoneyDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogMoneyDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogMoneyDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogMoneyDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogMoneyDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogMoneyDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogMoneyDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogMoneyDetail add column account_type INT UNSIGNED COMMENT "账号类型";
alter table LogMoneyDetail add column opt_type INT UNSIGNED COMMENT "操作类型";
alter table LogMoneyDetail add column opt_reason INT UNSIGNED COMMENT "操作缘由";
alter table LogMoneyDetail add column all_jetton BIGINT UNSIGNED COMMENT "全部金币";
alter table LogMoneyDetail add column jetton BIGINT UNSIGNED COMMENT "身上金币";
alter table LogMoneyDetail add column bank_jetton BIGINT UNSIGNED COMMENT "银行金币";
alter table LogMoneyDetail add column change_count BIGINT UNSIGNED COMMENT "改变数量";
alter table LogMoneyDetail add column agent_id BIGINT UNSIGNED COMMENT "上级代理ID";
alter table LogMoneyDetail add column ip VARCHAR(128) COMMENT "IP地址";
alter table LogMoneyDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
*/
CREATE TABLE IF NOT EXISTS LogMoneyDetail_9 (
 event_id BIGINT UNSIGNED NOT NULL COMMENT "ID" ,
 sequence INT UNSIGNED ,
 bus_name VARCHAR(128) ,
 event_time VARCHAR(128) COMMENT "时间" ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 desk_id INT UNSIGNED COMMENT "桌子ID" ,
 chair_id INT UNSIGNED COMMENT "椅子ID" ,
 account_type INT UNSIGNED COMMENT "账号类型" ,
 opt_type INT UNSIGNED COMMENT "操作类型" ,
 opt_reason INT UNSIGNED COMMENT "操作缘由" ,
 all_jetton BIGINT UNSIGNED COMMENT "全部金币" ,
 jetton BIGINT UNSIGNED COMMENT "身上金币" ,
 bank_jetton BIGINT UNSIGNED COMMENT "银行金币" ,
 change_count BIGINT UNSIGNED COMMENT "改变数量" ,
 agent_id BIGINT UNSIGNED COMMENT "上级代理ID" ,
 ip VARCHAR(128) COMMENT "IP地址" ,
 record_id BIGINT UNSIGNED COMMENT "游戏记录索引" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(record_id),
 PRIMARY KEY(event_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table LogMoneyDetail add column event_id BIGINT UNSIGNED NOT NULL COMMENT "ID";
alter table LogMoneyDetail add column sequence INT UNSIGNED;
alter table LogMoneyDetail add column bus_name VARCHAR(128);
alter table LogMoneyDetail add column event_time VARCHAR(128) COMMENT "时间";
alter table LogMoneyDetail add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table LogMoneyDetail add column user_name VARCHAR(128) COMMENT "昵称";
alter table LogMoneyDetail add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table LogMoneyDetail add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table LogMoneyDetail add column desk_id INT UNSIGNED COMMENT "桌子ID";
alter table LogMoneyDetail add column chair_id INT UNSIGNED COMMENT "椅子ID";
alter table LogMoneyDetail add column account_type INT UNSIGNED COMMENT "账号类型";
alter table LogMoneyDetail add column opt_type INT UNSIGNED COMMENT "操作类型";
alter table LogMoneyDetail add column opt_reason INT UNSIGNED COMMENT "操作缘由";
alter table LogMoneyDetail add column all_jetton BIGINT UNSIGNED COMMENT "全部金币";
alter table LogMoneyDetail add column jetton BIGINT UNSIGNED COMMENT "身上金币";
alter table LogMoneyDetail add column bank_jetton BIGINT UNSIGNED COMMENT "银行金币";
alter table LogMoneyDetail add column change_count BIGINT UNSIGNED COMMENT "改变数量";
alter table LogMoneyDetail add column agent_id BIGINT UNSIGNED COMMENT "上级代理ID";
alter table LogMoneyDetail add column ip VARCHAR(128) COMMENT "IP地址";
alter table LogMoneyDetail add column record_id BIGINT UNSIGNED COMMENT "游戏记录索引";
*/
