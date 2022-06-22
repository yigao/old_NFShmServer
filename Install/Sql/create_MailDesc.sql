CREATE TABLE IF NOT EXISTS MailDesc (
 id INT NOT NULL AUTO_INCREMENT COMMENT "编号" ,
 title VARCHAR(64) COMMENT "标题" ,
 type INT COMMENT "类型" ,
 content VARCHAR(512) COMMENT "内容" ,
 send_name VARCHAR(32) COMMENT "发件人" ,
 start_time_str VARCHAR(32) COMMENT "生效时间" ,
 end_time_str VARCHAR(32) COMMENT "结束时间" ,
 add_gold INT COMMENT "赠送金币" ,
 PRIMARY KEY(id)) AUTO_INCREMENT = 1 ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table MailDesc add column id INT NOT NULL AUTO_INCREMENT COMMENT "编号";
alter table MailDesc add column title VARCHAR(64) COMMENT "标题";
alter table MailDesc add column type INT COMMENT "类型";
alter table MailDesc add column content VARCHAR(512) COMMENT "内容";
alter table MailDesc add column send_name VARCHAR(32) COMMENT "发件人";
alter table MailDesc add column start_time_str VARCHAR(32) COMMENT "生效时间";
alter table MailDesc add column end_time_str VARCHAR(32) COMMENT "结束时间";
alter table MailDesc add column add_gold INT COMMENT "赠送金币";
*/
