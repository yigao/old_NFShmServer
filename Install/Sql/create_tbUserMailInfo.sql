CREATE TABLE IF NOT EXISTS tbUserMailInfo (
 user_id BIGINT UNSIGNED NOT NULL ,
 base_info BLOB /*!99104 COMPRESSED */ ,
 PRIMARY KEY(user_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table tbUserMailInfo add column user_id BIGINT UNSIGNED NOT NULL;
alter table tbUserMailInfo add column base_info BLOB ;
*/
