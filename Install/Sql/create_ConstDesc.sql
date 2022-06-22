CREATE TABLE IF NOT EXISTS ConstDesc (
 id INT NOT NULL AUTO_INCREMENT COMMENT "编号" ,
 value VARCHAR(128) COMMENT "常量值" ,
 type_name VARCHAR(128) COMMENT "类型名称" ,
 PRIMARY KEY(id)) AUTO_INCREMENT = 1 ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*
alter table ConstDesc add column id INT NOT NULL AUTO_INCREMENT COMMENT "编号";
alter table ConstDesc add column value VARCHAR(128) COMMENT "常量值";
alter table ConstDesc add column type_name VARCHAR(128) COMMENT "类型名称";
*/
