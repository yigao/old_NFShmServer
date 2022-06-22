CREATE TABLE IF NOT EXISTS tbGmCtrlGiveCtrlData (
 id BIGINT UNSIGNED NOT NULL ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 create_date VARCHAR(128) COMMENT "创建日期" ,
 control_type INT UNSIGNED COMMENT "类型:0=游戏内送彩金,1=送bouns,2=送免费小游戏" ,
 start_time BIGINT UNSIGNED COMMENT "开始时间" ,
 end_time BIGINT UNSIGNED COMMENT "结束时间" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,1006=跳高高,1007=女赌神,1008=疯狂的猴子" ,
 state INT UNSIGNED COMMENT "状态:0=不起作用,1=待送,2=过期,3=已送" ,
 jackpot_type INT COMMENT "送彩金类型:0=普通彩金, 1=小彩金, 2=中彩金, 3=大彩金, 4=超级彩金" ,
 jackpot_rate FLOAT UNSIGNED COMMENT "送彩金的百分比" ,
 jackpot_jetton BIGINT UNSIGNED COMMENT "送彩金金额" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(control_type),
 INDEX(game_id),
 PRIMARY KEY(id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table tbGmCtrlGiveCtrlData add column id BIGINT UNSIGNED NOT NULL;
alter table tbGmCtrlGiveCtrlData add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table tbGmCtrlGiveCtrlData add column user_name VARCHAR(128) COMMENT "昵称";
alter table tbGmCtrlGiveCtrlData add column create_date VARCHAR(128) COMMENT "创建日期";
alter table tbGmCtrlGiveCtrlData add column control_type INT UNSIGNED COMMENT "类型:0=游戏内送彩金,1=送bouns,2=送免费小游戏";
alter table tbGmCtrlGiveCtrlData add column start_time BIGINT UNSIGNED COMMENT "开始时间";
alter table tbGmCtrlGiveCtrlData add column end_time BIGINT UNSIGNED COMMENT "结束时间";
alter table tbGmCtrlGiveCtrlData add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,1006=跳高高,1007=女赌神,1008=疯狂的猴子";
alter table tbGmCtrlGiveCtrlData add column state INT UNSIGNED COMMENT "状态:0=不起作用,1=待送,2=过期,3=已送";
alter table tbGmCtrlGiveCtrlData add column jackpot_type INT COMMENT "送彩金类型:0=普通彩金, 1=小彩金, 2=中彩金, 3=大彩金, 4=超级彩金";
alter table tbGmCtrlGiveCtrlData add column jackpot_rate FLOAT UNSIGNED COMMENT "送彩金的百分比";
alter table tbGmCtrlGiveCtrlData add column jackpot_jetton BIGINT UNSIGNED COMMENT "送彩金金额";
*/
