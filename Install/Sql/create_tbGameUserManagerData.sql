CREATE TABLE IF NOT EXISTS tbGameUserManagerData (
 id BIGINT UNSIGNED NOT NULL ,
 user_id BIGINT UNSIGNED COMMENT "玩家ID" ,
 user_name VARCHAR(128) COMMENT "昵称" ,
 create_date VARCHAR(128) COMMENT "创建日期" ,
 roster_type INT UNSIGNED COMMENT "类型:0=黑名单,1=白名单" ,
 start_time BIGINT UNSIGNED COMMENT "开始时间" ,
 end_time BIGINT UNSIGNED COMMENT "结束时间" ,
 game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王" ,
 room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场" ,
 state INT UNSIGNED COMMENT "状态:0=不起作用,1=运行中,2=过期,3=完成" ,
 opt_mark BIGINT COMMENT "输盈最大总额" ,
 rate_mark FLOAT UNSIGNED COMMENT "输盈概率" ,
 control_level INT COMMENT "控制等级:-5=难-等级5,-4=难-等级4,-3=非常难,-2=很难,-1=难,0=正常,1=容易,2=很容易,3=非常容易,4=易-等级4,5=易-等级5" ,
 max_win_jetton BIGINT UNSIGNED COMMENT "单次最大赢筹码" ,
 cur_win BIGINT COMMENT "当前输盈总额" ,
 INDEX(user_id),
 INDEX(user_name),
 INDEX(roster_type),
 INDEX(game_id),
 INDEX(room_id),
 PRIMARY KEY(id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table tbGameUserManagerData add column id BIGINT UNSIGNED NOT NULL;
alter table tbGameUserManagerData add column user_id BIGINT UNSIGNED COMMENT "玩家ID";
alter table tbGameUserManagerData add column user_name VARCHAR(128) COMMENT "昵称";
alter table tbGameUserManagerData add column create_date VARCHAR(128) COMMENT "创建日期";
alter table tbGameUserManagerData add column roster_type INT UNSIGNED COMMENT "类型:0=黑名单,1=白名单";
alter table tbGameUserManagerData add column start_time BIGINT UNSIGNED COMMENT "开始时间";
alter table tbGameUserManagerData add column end_time BIGINT UNSIGNED COMMENT "结束时间";
alter table tbGameUserManagerData add column game_id INT UNSIGNED COMMENT "游戏ID:1001=水果玛丽,1002=幸运转轮,1003=水浒传,1004=鼠来宝,1005=福星高照,2001=大闹天空2,2002=大闹天空,2003=欢乐捕鱼3D,2004=海王";
alter table tbGameUserManagerData add column room_id INT UNSIGNED COMMENT "房间ID:1=体验场,2=初级场,3=普通场,4=中级场,5=高级场";
alter table tbGameUserManagerData add column state INT UNSIGNED COMMENT "状态:0=不起作用,1=运行中,2=过期,3=完成";
alter table tbGameUserManagerData add column opt_mark BIGINT COMMENT "输盈最大总额";
alter table tbGameUserManagerData add column rate_mark FLOAT UNSIGNED COMMENT "输盈概率";
alter table tbGameUserManagerData add column control_level INT COMMENT "控制等级:-5=难-等级5,-4=难-等级4,-3=非常难,-2=很难,-1=难,0=正常,1=容易,2=很容易,3=非常容易,4=易-等级4,5=易-等级5";
alter table tbGameUserManagerData add column max_win_jetton BIGINT UNSIGNED COMMENT "单次最大赢筹码";
alter table tbGameUserManagerData add column cur_win BIGINT COMMENT "当前输盈总额";
*/
