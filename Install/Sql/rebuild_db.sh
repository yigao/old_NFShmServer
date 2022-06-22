
USR="root"
PASSWRD="root"
DBNAME="proto_ff"

MYSQL=mysql

cd ../Install/Config/Sql/

mysqldump -u${USR} -p${PASSWRD} ${DBNAME} > ${DBNAME}.sql
mysql -u${USR} -p${PASSWRD} -e "drop database proto_ff"
mysql -u${USR} -p${PASSWRD} -e "create database proto_ff"

TABLE_LIST="tbAccountTable tbUserMailDetail tbUserMailInfo MailDesc tbUserDetailData tbUserSimpleData tbGiveBankJetton tbUserMiscInfo tbEventLog tbRankCommon ConstDesc"

for table in ${TABLE_LIST}
do
    SQL=create_${table}.sql
    ${MYSQL}  -u${USR} -p${PASSWRD} ${DBNAME} < ${SQL}
done
