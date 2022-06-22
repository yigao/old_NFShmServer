USR="root"
PASSWRD="root"

MYSQL=mysql

mysql -u${USR} -p${PASSWRD} -e "drop database proto_ff"
mysql -u${USR} -p${PASSWRD} -e "create database proto_ff"

${MYSQL}  -u${USR} -p${PASSWRD} proto_ff < proto_ff.sql

mysql -u${USR} -p${PASSWRD} -e "drop database www_proto_ff"
mysql -u${USR} -p${PASSWRD} -e "create database www_proto_ff"

${MYSQL}  -u${USR} -p${PASSWRD} www_proto_ff < www_proto_ff.sql

mysql -u${USR} -p${PASSWRD} -e "drop database GameConfig_1001"
mysql -u${USR} -p${PASSWRD} -e "create database GameConfig_1001"

${MYSQL}  -u${USR} -p${PASSWRD} GameConfig_1001 < GameConfig_1001.sql

mysql -u${USR} -p${PASSWRD} -e "drop database GameConfig_1002"
mysql -u${USR} -p${PASSWRD} -e "create database GameConfig_1002"

${MYSQL}  -u${USR} -p${PASSWRD} GameConfig_1002 < GameConfig_1002.sql

mysql -u${USR} -p${PASSWRD} -e "drop database GameConfig_1003"
mysql -u${USR} -p${PASSWRD} -e "create database GameConfig_1003"

${MYSQL}  -u${USR} -p${PASSWRD} GameConfig_1003 < GameConfig_1003.sql

mysql -u${USR} -p${PASSWRD} -e "drop database GameConfig_1004"
mysql -u${USR} -p${PASSWRD} -e "create database GameConfig_1004"

${MYSQL}  -u${USR} -p${PASSWRD} GameConfig_1004 < GameConfig_1004.sql

mysql -u${USR} -p${PASSWRD} -e "drop database GameConfig_1005"
mysql -u${USR} -p${PASSWRD} -e "create database GameConfig_1005"

${MYSQL}  -u${USR} -p${PASSWRD} GameConfig_1005 < GameConfig_1005.sql

mysql -u${USR} -p${PASSWRD} -e "drop database GameConfig_2001"
mysql -u${USR} -p${PASSWRD} -e "create database GameConfig_2001"

${MYSQL}  -u${USR} -p${PASSWRD} GameConfig_2001 < GameConfig_2001.sql

mysql -u${USR} -p${PASSWRD} -e "drop database GameConfig_2002"
mysql -u${USR} -p${PASSWRD} -e "create database GameConfig_2002"

${MYSQL}  -u${USR} -p${PASSWRD} GameConfig_2002 < GameConfig_2002.sql

mysql -u${USR} -p${PASSWRD} -e "drop database GameConfig_2003"
mysql -u${USR} -p${PASSWRD} -e "create database GameConfig_2003"

${MYSQL}  -u${USR} -p${PASSWRD} GameConfig_2003 < GameConfig_2003.sql

mysql -u${USR} -p${PASSWRD} -e "drop database GameConfig_2004"
mysql -u${USR} -p${PASSWRD} -e "create database GameConfig_2004"

${MYSQL}  -u${USR} -p${PASSWRD} GameConfig_2004 < GameConfig_2004.sql

