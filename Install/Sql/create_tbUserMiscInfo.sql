CREATE TABLE IF NOT EXISTS tbUserMiscInfo (
 user_id BIGINT UNSIGNED NOT NULL ,
 bank_info BLOB /*!99104 COMPRESSED */ ,
 PRIMARY KEY(user_id))  ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table tbUserMiscInfo add column user_id BIGINT UNSIGNED NOT NULL;
alter table tbUserMiscInfo add column bank_info BLOB ;
*/
