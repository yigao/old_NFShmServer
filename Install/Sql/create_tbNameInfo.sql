CREATE TABLE IF NOT EXISTS tbNameInfo (
 id BIGINT UNSIGNED NOT NULL AUTO_INCREMENT ,
 name VARCHAR(64) ,
 INDEX(name),
 PRIMARY KEY(id)) AUTO_INCREMENT = 1 ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table tbNameInfo add column id BIGINT UNSIGNED NOT NULL AUTO_INCREMENT;
alter table tbNameInfo add column name VARCHAR(64);
*/