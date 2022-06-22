CREATE TABLE IF NOT EXISTS tbLogGameDay (
 date_id VARCHAR(32) NOT NULL COMMENT "ID" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 all_pour BIGINT UNSIGNED COMMENT "总投注" ,
 pour_day BIGINT UNSIGNED COMMENT "今日投注" ,
 pour_week BIGINT UNSIGNED COMMENT "周投注" ,
 pour_month BIGINT UNSIGNED COMMENT "月投注" ,
 all_win BIGINT COMMENT "总输赢" ,
 win_day BIGINT COMMENT "今日输赢" ,
 win_week BIGINT COMMENT "周输赢" ,
 win_month BIGINT COMMENT "月输赢" ,
 all_fee BIGINT UNSIGNED COMMENT "总抽水" ,
 fee_day BIGINT UNSIGNED COMMENT "今日抽水" ,
 fee_week BIGINT UNSIGNED COMMENT "周抽水" ,
 fee_month BIGINT UNSIGNED COMMENT "月抽水" ,
 stat_time VARCHAR(32) COMMENT "统计日期" ,
 INDEX(game_id),
 INDEX(room_id),
 INDEX(stat_time),
 PRIMARY KEY(date_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table tbLogGameDay add column date_id VARCHAR(32) NOT NULL COMMENT "ID";
alter table tbLogGameDay add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table tbLogGameDay add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table tbLogGameDay add column all_pour BIGINT UNSIGNED COMMENT "总投注";
alter table tbLogGameDay add column pour_day BIGINT UNSIGNED COMMENT "今日投注";
alter table tbLogGameDay add column pour_week BIGINT UNSIGNED COMMENT "周投注";
alter table tbLogGameDay add column pour_month BIGINT UNSIGNED COMMENT "月投注";
alter table tbLogGameDay add column all_win BIGINT COMMENT "总输赢";
alter table tbLogGameDay add column win_day BIGINT COMMENT "今日输赢";
alter table tbLogGameDay add column win_week BIGINT COMMENT "周输赢";
alter table tbLogGameDay add column win_month BIGINT COMMENT "月输赢";
alter table tbLogGameDay add column all_fee BIGINT UNSIGNED COMMENT "总抽水";
alter table tbLogGameDay add column fee_day BIGINT UNSIGNED COMMENT "今日抽水";
alter table tbLogGameDay add column fee_week BIGINT UNSIGNED COMMENT "周抽水";
alter table tbLogGameDay add column fee_month BIGINT UNSIGNED COMMENT "月抽水";
alter table tbLogGameDay add column stat_time VARCHAR(32) COMMENT "统计日期";
*/
