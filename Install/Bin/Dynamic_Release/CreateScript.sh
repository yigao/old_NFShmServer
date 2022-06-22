BASEPATH=$(cd `dirname $0`; pwd)

log_count=0
log_str=""

do_work()
{
	echo $1 $2 $3 $4
	ln -sdf $BASEPATH/NFPluginLoader $BASEPATH/$1_$2_bin
	#$cp NFPluginLoader $1 -rf
	#chmod a+x $1
	cp AllServer.sh $1_$2_run.sh -rf
	chmod a+x $1_$2_run.sh 
	cp AllServer_log.sh $1_$2_log.sh -rf
	chmod a+x $1_$2_log.sh
	sed -i "s/servername=NFPluginLoader/servername=$1_$2_bin/g" ./$1_$2_run.sh
	sed -i "s/servertype=AllServer/servertype=$1/g" ./$1_$2_run.sh
	#sed -i "s/serverId=.*.1/serverId=$2/g" ./$1_$2_run.sh
	sed -i 's#'''serverId=1.1.1.1'''#'''serverId=$2'''#g' ./$1_$2_run.sh
	sed -i 's#'''serverConfig=../../Config'''#'''serverConfig=$3'''#g' ./$1_$2_run.sh
	sed -i 's#'''serverPlugin=../../Plugin'''#'''serverPlugin=$4'''#g' ./$1_$2_run.sh

	sed -i "s/AllServer_1.1.1.1/AllServer_$2/g" ./$1_$2_log.sh
	sed -i "s/AllServer/$1/g" ./$1_$2_log.sh

	touch Stop.sh
	chmod a+x Stop.sh
	echo "./$1_$2_run.sh stop" >> Stop.sh

	touch ReStart.sh
	chmod a+x ReStart.sh
	echo "./$1_$2_run.sh restart" >> ReStart.sh

	touch Start.sh
	chmod a+x Start.sh
	echo "./$1_$2_run.sh start" >> Start.sh

	touch Clear.sh
	chmod a+x Clear.sh
	echo "rm $1_$2_bin -rf" >> Clear.sh
	echo "rm $1_$2_log.sh -rf" >> Clear.sh
	echo "rm $1_$2_run.sh -rf" >> Clear.sh

	touch Monitor.sh
	chmod a+x Monitor.sh
	echo  "$PWD/$1_$2_bin -d --Server=$1 --ID=$2 --Config=$3 --Plugin=$4 --start" >> Monitor.sh

	let log_count=log_count+1
  touch Alllog.sh
  chmod a+x Alllog.sh

  echo "LOG$log_count=logs/$1_$2/$1.log" >> Alllog.sh
  log_str=$log_str' $'"LOG$log_count "
}

rm Clear.sh
rm Start.sh
rm Stop.sh
rm ReStart.sh
rm Monitor.sh
rm Alllog.sh

echo "main()" >> Alllog.sh
echo "{" >> Alllog.sh

do_work MasterServer 1.1.1.1 ../../Config ../../Plugin
do_work RouteServer 15.100.7.1 ../../Config ../../Plugin
do_work RouteAgentServer 15.100.6.1 ../../Config ../../Plugin
do_work StoreServer 15.100.8.1 ../../Config ../../Plugin
do_work LoginServer 15.100.2.1 ../../Config ../../Plugin
do_work WorldServer 15.100.3.1 ../../Config ../../Plugin
do_work SnsServer 15.100.9.1 ../../Config ../../Plugin
do_work LogicServer 15.100.10.1 ../../Config ../../Plugin
do_work WebServer 15.100.11.1 ../../Config ../../Plugin
do_work ProxyServer 15.100.5.1 ../../Config ../../Plugin
do_work ProxyAgentServer 15.100.13.1 ../../Config ../../Plugin

do_work GameServer 15.2001.4.1 ../../Config2001_1 ../../Config2001_1
do_work GameServer 15.2001.4.2 ../../Config2001_2 ../../Config2001_2
do_work GameServer 15.2001.4.3 ../../Config2001_3 ../../Config2001_3
do_work GameServer 15.2001.4.4 ../../Config2001_4 ../../Config2001_4
do_work GameServer 15.2001.4.5 ../../Config2001_5 ../../Config2001_5
do_work GameServer 15.2002.4.1 ../../Config2002_1 ../../Config2002_1
do_work GameServer 15.2002.4.2 ../../Config2002_2 ../../Config2002_2
do_work GameServer 15.2002.4.3 ../../Config2002_3 ../../Config2002_3
do_work GameServer 15.2002.4.4 ../../Config2002_4 ../../Config2002_4
do_work GameServer 15.2002.4.5 ../../Config2002_5 ../../Config2002_5
do_work GameServer 15.2003.4.1 ../../Config2003_1 ../../Config2003_1
do_work GameServer 15.2003.4.2 ../../Config2003_2 ../../Config2003_2
do_work GameServer 15.2003.4.3 ../../Config2003_3 ../../Config2003_3
do_work GameServer 15.2003.4.4 ../../Config2003_4 ../../Config2003_4
do_work GameServer 15.2003.4.5 ../../Config2003_5 ../../Config2003_5
do_work GameServer 15.2004.4.1 ../../Config2004_1 ../../Config2004_1
do_work GameServer 15.2004.4.2 ../../Config2004_2 ../../Config2004_2
do_work GameServer 15.2004.4.3 ../../Config2004_3 ../../Config2004_3
do_work GameServer 15.2004.4.4 ../../Config2004_4 ../../Config2004_4
do_work GameServer 15.2004.4.5 ../../Config2004_5 ../../Config2004_5
do_work GameServer 15.1001.4.1 ../../Config1001_1 ../../Config1001_1
do_work GameServer 15.1001.4.2 ../../Config1001_2 ../../Config1001_2
do_work GameServer 15.1001.4.3 ../../Config1001_3 ../../Config1001_3
do_work GameServer 15.1001.4.4 ../../Config1001_4 ../../Config1001_4
do_work GameServer 15.1001.4.5 ../../Config1001_5 ../../Config1001_5
do_work GameServer 15.1002.4.1 ../../Config1002_1 ../../Config1002_1
do_work GameServer 15.1002.4.2 ../../Config1002_1 ../../Config1002_2
do_work GameServer 15.1002.4.3 ../../Config1002_1 ../../Config1002_3
do_work GameServer 15.1002.4.4 ../../Config1002_1 ../../Config1002_4
do_work GameServer 15.1002.4.5 ../../Config1002_1 ../../Config1002_5
do_work GameServer 15.1003.4.1 ../../Config1003_1 ../../Config1003_1
do_work GameServer 15.1003.4.2 ../../Config1003_2 ../../Config1003_2
do_work GameServer 15.1003.4.3 ../../Config1003_3 ../../Config1003_3
do_work GameServer 15.1003.4.4 ../../Config1003_4 ../../Config1003_4
do_work GameServer 15.1003.4.5 ../../Config1003_5 ../../Config1003_5
do_work GameServer 15.1004.4.1 ../../Config1004_1 ../../Config1004_1
do_work GameServer 15.1004.4.2 ../../Config1004_2 ../../Config1004_2
do_work GameServer 15.1004.4.3 ../../Config1004_3 ../../Config1004_3
do_work GameServer 15.1004.4.4 ../../Config1004_4 ../../Config1004_4
do_work GameServer 15.1004.4.5 ../../Config1004_5 ../../Config1004_5
do_work GameServer 15.1005.4.1 ../../Config1005_1 ../../Config1005_1
do_work GameServer 15.1005.4.2 ../../Config1005_2 ../../Config1005_2
do_work GameServer 15.1005.4.3 ../../Config1005_3 ../../Config1005_3
do_work GameServer 15.1005.4.4 ../../Config1005_4 ../../Config1005_4
do_work GameServer 15.1005.4.5 ../../Config1005_5 ../../Config1005_5
do_work GameServer 15.1006.4.1 ../../Config1006_1 ../../Config1006_1
do_work GameServer 15.1006.4.2 ../../Config1006_2 ../../Config1006_2
do_work GameServer 15.1006.4.3 ../../Config1006_3 ../../Config1006_3
do_work GameServer 15.1006.4.4 ../../Config1006_4 ../../Config1006_4
do_work GameServer 15.1006.4.5 ../../Config1006_5 ../../Config1006_5
do_work GameServer 15.1007.4.1 ../../Config1007_1 ../../Config1007_1
do_work GameServer 15.1007.4.2 ../../Config1007_2 ../../Config1007_2
do_work GameServer 15.1007.4.3 ../../Config1007_3 ../../Config1007_3
do_work GameServer 15.1007.4.4 ../../Config1007_4 ../../Config1007_4
do_work GameServer 15.1007.4.5 ../../Config1007_5 ../../Config1007_5
do_work GameServer 15.1008.4.1 ../../Config1008_1 ../../Config1008_1
do_work GameServer 15.1008.4.2 ../../Config1008_2 ../../Config1008_2
do_work GameServer 15.1008.4.3 ../../Config1008_3 ../../Config1008_3
do_work GameServer 15.1008.4.4 ../../Config1008_4 ../../Config1008_4
do_work GameServer 15.1008.4.5 ../../Config1008_5 ../../Config1008_5
do_work GameServer 15.3001.4.1 ../../Config3001_1 ../../Config3001_1
do_work GameServer 15.3002.4.1 ../../Config3002_1 ../../Config3002_1
do_work GameServer 15.4001.4.1 ../../Config4001_1 ../../Config4001_1

echo	"tail --follow=name --retry $log_str --max-unchanged-stats=3 -n 5 -q | awk '"'/INFO/ {print "\033[32m" $0 "\033[39m"} /DEBUG/ {print  $0 }  /WARNING/ {print "\033[33m" $0 "\033[39m"} /TRACE/ {print "\033[33m" $0 "\033[39m"} /ERROR/ {print "\033[31m" $0 "\033[39m"} '"'" >> Alllog.sh

echo "}" >> Alllog.sh
echo "main" >> Alllog.sh

echo "./shm_rm.sh" >> Stop.sh

echo "rm Stop.sh -rf" >> Clear.sh
echo "rm Start.sh -rf" >> Clear.sh
echo "rm ReStart.sh -rf" >> Clear.sh
echo "rm Clear.sh -rf" >> Clear.sh
echo "rm Alllog.sh -rf" >> Clear.sh
echo "rm *_globalid -rf" >> Clear.sh
echo "rm *.pid -rf" >> Clear.sh
echo "rm *.uid -rf" >> Clear.sh
echo "rm *_dump.log -rf" >> Clear.sh
echo "rm shmnframe_lib.bin" >> Clear.sh
