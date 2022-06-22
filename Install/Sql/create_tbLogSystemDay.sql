CREATE TABLE IF NOT EXISTS tbLogSystemDay (
 date_id VARCHAR(32) NOT NULL COMMENT "统计日期" ,
 active_player INT UNSIGNED COMMENT "活跃玩家" ,
 login_count INT UNSIGNED COMMENT "登录次数" ,
 valid_player INT UNSIGNED COMMENT "有效玩家" ,
 new_player INT UNSIGNED COMMENT "新增玩家" ,
 pay_player INT UNSIGNED COMMENT "付费人数" ,
 pay_times INT UNSIGNED COMMENT "付费次数" ,
 pay_all BIGINT UNSIGNED COMMENT "付费总额" ,
 new_pay_player INT UNSIGNED COMMENT "付费新玩家人数" ,
 new_pay_all INT UNSIGNED COMMENT "付费新玩家总额" ,
 commission_all BIGINT UNSIGNED COMMENT "佣金发放总额" ,
 all_fee BIGINT UNSIGNED COMMENT "税收总和" ,
 all_pour BIGINT UNSIGNED COMMENT "投注总和" ,
 all_win BIGINT COMMENT "系统盈利总和" ,
 jetton_init BIGINT UNSIGNED COMMENT "每日初始值" ,
 all_draw BIGINT UNSIGNED COMMENT "出款总额" ,
 jetton_in BIGINT UNSIGNED COMMENT "系统进项" ,
 jetton_out BIGINT UNSIGNED COMMENT "系统出款总额" ,
 sys_award BIGINT UNSIGNED COMMENT "系统发放奖励总额" ,
 player_jetton BIGINT UNSIGNED COMMENT "玩家金币库存" ,
 trd_pay_all BIGINT UNSIGNED COMMENT "第三方支付总额" ,
 vip_pay_all BIGINT UNSIGNED COMMENT "vip支付总额" ,
 zhuangzhang_all BIGINT UNSIGNED COMMENT "充值转账总额" ,
 activity_award BIGINT UNSIGNED COMMENT "活动奖励总额" ,
 all_bank_jetton BIGINT UNSIGNED COMMENT "全部银行库存" ,
 freeze_jetton BIGINT UNSIGNED COMMENT "被冻结的库存" ,
 all_jetton BIGINT UNSIGNED COMMENT "全部库存" ,
 all_player BIGINT UNSIGNED COMMENT "玩家总数" ,
 active_seven BIGINT UNSIGNED COMMENT "最近7日日活" ,
 active_thirty BIGINT UNSIGNED COMMENT "最近30天日活" ,
 pour_day_all BIGINT UNSIGNED COMMENT "今日投注" ,
 pour_week_all BIGINT UNSIGNED COMMENT "周投注" ,
 pour_month_all BIGINT UNSIGNED COMMENT "月投注" ,
 sys_win_day BIGINT COMMENT "系统今日盈利" ,
 sys_win_week BIGINT COMMENT "系统周盈利" ,
 sys_win_month BIGINT COMMENT "系统月盈利" ,
 fee_day BIGINT UNSIGNED COMMENT "每日抽水" ,
 fee_week BIGINT UNSIGNED COMMENT "每周抽水" ,
 fee_month BIGINT UNSIGNED COMMENT "每月抽水" ,
 commision_all BIGINT UNSIGNED COMMENT "佣金总额" ,
 commision_take BIGINT UNSIGNED COMMENT "取出佣金总额" ,
 commision_day BIGINT UNSIGNED COMMENT "每日佣金" ,
 commision_week BIGINT UNSIGNED COMMENT "每周佣金" ,
 commision_month BIGINT UNSIGNED COMMENT "每月佣金" ,
 max_online BIGINT UNSIGNED COMMENT "当然最大在线人数" ,
 win_cost_value BIGINT UNSIGNED COMMENT "出差值" ,
 day_money_value BIGINT UNSIGNED COMMENT "当日库存" ,
 pay_day BIGINT UNSIGNED COMMENT "每日付费" ,
 pay_week BIGINT UNSIGNED COMMENT "每周付费" ,
 pay_month BIGINT UNSIGNED COMMENT "每月付费" ,
 draw_day BIGINT UNSIGNED COMMENT "每日出款" ,
 draw_week BIGINT UNSIGNED COMMENT "每周出款" ,
 draw_month BIGINT UNSIGNED COMMENT "每月出款" ,
 trd_pay_day BIGINT UNSIGNED COMMENT "每日第三方支付" ,
 trd_pay_week BIGINT UNSIGNED COMMENT "每周第三方支付" ,
 trd_pay_month BIGINT UNSIGNED COMMENT "每月第三方支付" ,
 vip_pay_day BIGINT UNSIGNED COMMENT "每日vip支付" ,
 vip_pay_week BIGINT UNSIGNED COMMENT "每周vip支付" ,
 vip_pay_month BIGINT UNSIGNED COMMENT "每月vip支付" ,
 zhuangzhang_day BIGINT UNSIGNED COMMENT "每日充值转账" ,
 zhuangzhang_week BIGINT UNSIGNED COMMENT "每周充值转账" ,
 zhuangzhang_month BIGINT UNSIGNED COMMENT "每月充值转账" ,
 give_day BIGINT UNSIGNED COMMENT "每日赠送" ,
 give_week BIGINT UNSIGNED COMMENT "每周赠送" ,
 give_month BIGINT UNSIGNED COMMENT "每月赠送" ,
 all_give BIGINT UNSIGNED COMMENT "赠送总额" ,
 all_vip_zhuanru BIGINT UNSIGNED COMMENT "VIP总转入" ,
 today_vip_zhuanru BIGINT UNSIGNED COMMENT "VIP今日转入" ,
 week_vip_zhuanru BIGINT UNSIGNED COMMENT "VIP周转入" ,
 month_vip_zhuanru BIGINT UNSIGNED COMMENT "VIP月转入" ,
 all_vip_zhuanchu BIGINT UNSIGNED COMMENT "VIP总转出" ,
 today_vip_zhuanchu BIGINT UNSIGNED COMMENT "VIP今日转出" ,
 week_vip_zhuanchu BIGINT UNSIGNED COMMENT "VIP周转出" ,
 month_vip_zhuanchu BIGINT UNSIGNED COMMENT "VIP月转出" ,
 PRIMARY KEY(date_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table tbLogSystemDay add column date_id VARCHAR(32) NOT NULL COMMENT "统计日期";
alter table tbLogSystemDay add column active_player INT UNSIGNED COMMENT "活跃玩家";
alter table tbLogSystemDay add column login_count INT UNSIGNED COMMENT "登录次数";
alter table tbLogSystemDay add column valid_player INT UNSIGNED COMMENT "有效玩家";
alter table tbLogSystemDay add column new_player INT UNSIGNED COMMENT "新增玩家";
alter table tbLogSystemDay add column pay_player INT UNSIGNED COMMENT "付费人数";
alter table tbLogSystemDay add column pay_times INT UNSIGNED COMMENT "付费次数";
alter table tbLogSystemDay add column pay_all BIGINT UNSIGNED COMMENT "付费总额";
alter table tbLogSystemDay add column new_pay_player INT UNSIGNED COMMENT "付费新玩家人数";
alter table tbLogSystemDay add column new_pay_all INT UNSIGNED COMMENT "付费新玩家总额";
alter table tbLogSystemDay add column commission_all BIGINT UNSIGNED COMMENT "佣金发放总额";
alter table tbLogSystemDay add column all_fee BIGINT UNSIGNED COMMENT "税收总和";
alter table tbLogSystemDay add column all_pour BIGINT UNSIGNED COMMENT "投注总和";
alter table tbLogSystemDay add column all_win BIGINT COMMENT "系统盈利总和";
alter table tbLogSystemDay add column jetton_init BIGINT UNSIGNED COMMENT "每日初始值";
alter table tbLogSystemDay add column all_draw BIGINT UNSIGNED COMMENT "出款总额";
alter table tbLogSystemDay add column jetton_in BIGINT UNSIGNED COMMENT "系统进项";
alter table tbLogSystemDay add column jetton_out BIGINT UNSIGNED COMMENT "系统出款总额";
alter table tbLogSystemDay add column sys_award BIGINT UNSIGNED COMMENT "系统发放奖励总额";
alter table tbLogSystemDay add column player_jetton BIGINT UNSIGNED COMMENT "玩家金币库存";
alter table tbLogSystemDay add column trd_pay_all BIGINT UNSIGNED COMMENT "第三方支付总额";
alter table tbLogSystemDay add column vip_pay_all BIGINT UNSIGNED COMMENT "vip支付总额";
alter table tbLogSystemDay add column zhuangzhang_all BIGINT UNSIGNED COMMENT "充值转账总额";
alter table tbLogSystemDay add column activity_award BIGINT UNSIGNED COMMENT "活动奖励总额";
alter table tbLogSystemDay add column all_bank_jetton BIGINT UNSIGNED COMMENT "全部银行库存";
alter table tbLogSystemDay add column freeze_jetton BIGINT UNSIGNED COMMENT "被冻结的库存";
alter table tbLogSystemDay add column all_jetton BIGINT UNSIGNED COMMENT "全部库存";
alter table tbLogSystemDay add column all_player BIGINT UNSIGNED COMMENT "玩家总数";
alter table tbLogSystemDay add column active_seven BIGINT UNSIGNED COMMENT "最近7日日活";
alter table tbLogSystemDay add column active_thirty BIGINT UNSIGNED COMMENT "最近30天日活";
alter table tbLogSystemDay add column pour_day_all BIGINT UNSIGNED COMMENT "今日投注";
alter table tbLogSystemDay add column pour_week_all BIGINT UNSIGNED COMMENT "周投注";
alter table tbLogSystemDay add column pour_month_all BIGINT UNSIGNED COMMENT "月投注";
alter table tbLogSystemDay add column sys_win_day BIGINT COMMENT "系统今日盈利";
alter table tbLogSystemDay add column sys_win_week BIGINT COMMENT "系统周盈利";
alter table tbLogSystemDay add column sys_win_month BIGINT COMMENT "系统月盈利";
alter table tbLogSystemDay add column fee_day BIGINT UNSIGNED COMMENT "每日抽水";
alter table tbLogSystemDay add column fee_week BIGINT UNSIGNED COMMENT "每周抽水";
alter table tbLogSystemDay add column fee_month BIGINT UNSIGNED COMMENT "每月抽水";
alter table tbLogSystemDay add column commision_all BIGINT UNSIGNED COMMENT "佣金总额";
alter table tbLogSystemDay add column commision_take BIGINT UNSIGNED COMMENT "取出佣金总额";
alter table tbLogSystemDay add column commision_day BIGINT UNSIGNED COMMENT "每日佣金";
alter table tbLogSystemDay add column commision_week BIGINT UNSIGNED COMMENT "每周佣金";
alter table tbLogSystemDay add column commision_month BIGINT UNSIGNED COMMENT "每月佣金";
alter table tbLogSystemDay add column max_online BIGINT UNSIGNED COMMENT "当然最大在线人数";
alter table tbLogSystemDay add column win_cost_value BIGINT UNSIGNED COMMENT "出差值";
alter table tbLogSystemDay add column day_money_value BIGINT UNSIGNED COMMENT "当日库存";
alter table tbLogSystemDay add column pay_day BIGINT UNSIGNED COMMENT "每日付费";
alter table tbLogSystemDay add column pay_week BIGINT UNSIGNED COMMENT "每周付费";
alter table tbLogSystemDay add column pay_month BIGINT UNSIGNED COMMENT "每月付费";
alter table tbLogSystemDay add column draw_day BIGINT UNSIGNED COMMENT "每日出款";
alter table tbLogSystemDay add column draw_week BIGINT UNSIGNED COMMENT "每周出款";
alter table tbLogSystemDay add column draw_month BIGINT UNSIGNED COMMENT "每月出款";
alter table tbLogSystemDay add column trd_pay_day BIGINT UNSIGNED COMMENT "每日第三方支付";
alter table tbLogSystemDay add column trd_pay_week BIGINT UNSIGNED COMMENT "每周第三方支付";
alter table tbLogSystemDay add column trd_pay_month BIGINT UNSIGNED COMMENT "每月第三方支付";
alter table tbLogSystemDay add column vip_pay_day BIGINT UNSIGNED COMMENT "每日vip支付";
alter table tbLogSystemDay add column vip_pay_week BIGINT UNSIGNED COMMENT "每周vip支付";
alter table tbLogSystemDay add column vip_pay_month BIGINT UNSIGNED COMMENT "每月vip支付";
alter table tbLogSystemDay add column zhuangzhang_day BIGINT UNSIGNED COMMENT "每日充值转账";
alter table tbLogSystemDay add column zhuangzhang_week BIGINT UNSIGNED COMMENT "每周充值转账";
alter table tbLogSystemDay add column zhuangzhang_month BIGINT UNSIGNED COMMENT "每月充值转账";
alter table tbLogSystemDay add column give_day BIGINT UNSIGNED COMMENT "每日赠送";
alter table tbLogSystemDay add column give_week BIGINT UNSIGNED COMMENT "每周赠送";
alter table tbLogSystemDay add column give_month BIGINT UNSIGNED COMMENT "每月赠送";
alter table tbLogSystemDay add column all_give BIGINT UNSIGNED COMMENT "赠送总额";
alter table tbLogSystemDay add column all_vip_zhuanru BIGINT UNSIGNED COMMENT "VIP总转入";
alter table tbLogSystemDay add column today_vip_zhuanru BIGINT UNSIGNED COMMENT "VIP今日转入";
alter table tbLogSystemDay add column week_vip_zhuanru BIGINT UNSIGNED COMMENT "VIP周转入";
alter table tbLogSystemDay add column month_vip_zhuanru BIGINT UNSIGNED COMMENT "VIP月转入";
alter table tbLogSystemDay add column all_vip_zhuanchu BIGINT UNSIGNED COMMENT "VIP总转出";
alter table tbLogSystemDay add column today_vip_zhuanchu BIGINT UNSIGNED COMMENT "VIP今日转出";
alter table tbLogSystemDay add column week_vip_zhuanchu BIGINT UNSIGNED COMMENT "VIP周转出";
alter table tbLogSystemDay add column month_vip_zhuanchu BIGINT UNSIGNED COMMENT "VIP月转出";
*/
