CREATE TABLE IF NOT EXISTS tbUserMailDetail (
 id BIGINT UNSIGNED NOT NULL ,
 user_id BIGINT UNSIGNED ,
 send_name VARCHAR(32) ,
 static_id INT ,
 content VARCHAR(1600) ,
 title VARCHAR(64) ,
 send_time BIGINT UNSIGNED ,
 add_gold BIGINT ,
 INDEX(user_id),
 PRIMARY KEY(id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table tbUserMailDetail add column id BIGINT UNSIGNED NOT NULL;
alter table tbUserMailDetail add column user_id BIGINT UNSIGNED;
alter table tbUserMailDetail add column send_name VARCHAR(32);
alter table tbUserMailDetail add column static_id INT;
alter table tbUserMailDetail add column content VARCHAR(1600);
alter table tbUserMailDetail add column title VARCHAR(64);
alter table tbUserMailDetail add column send_time BIGINT UNSIGNED;
alter table tbUserMailDetail add column add_gold BIGINT;
*/
