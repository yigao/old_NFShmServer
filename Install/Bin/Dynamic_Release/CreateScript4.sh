BASEPATH=$(cd `dirname $0`; pwd)

log_count=0
log_str=""

do_work()
{
	echo $1 $2 $3 $4 $5
	ln -sdf $BASEPATH/NFPluginLoader $BASEPATH/$1_$2_bin
	#$cp NFPluginLoader $1 -rf
	#chmod a+x $1
	cp RobotServer.sh $1_$2_run.sh -rf
	chmod a+x $1_$2_run.sh 
	cp RobotServer_log.sh $1_$2_log.sh -rf
	chmod a+x $1_$2_log.sh
	sed -i "s/servername=NFPluginLoader/servername=$1_$2_bin/g" ./$1_$2_run.sh
	sed -i "s/servertype=RobotServer/servertype=$1/g" ./$1_$2_run.sh
	#sed -i "s/serverId=.*.1/serverId=$2/g" ./$1_$2_run.sh
	sed -i 's#'''serverId=1.1.1.1'''#'''serverId=$2'''#g' ./$1_$2_run.sh
	sed -i 's#'''serverConfig=../../Config'''#'''serverConfig=$3'''#g' ./$1_$2_run.sh
	sed -i 's#'''serverPlugin=../../Plugin'''#'''serverPlugin=$4'''#g' ./$1_$2_run.sh

	sed -i "s/RobotServer_1.1.1.1/RobotServer_$2/g" ./$1_$2_log.sh
	sed -i "s/RobotServer/$1/g" ./$1_$2_log.sh

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
	echo "rm $1_$2 -rf" >> Clear.sh
	echo "rm $1_$2_log.sh -rf" >> Clear.sh
	echo "rm $1_$2_run.sh -rf" >> Clear.sh

  touch Monitor.sh
  chmod a+x Monitor.sh
  echo  "$PWD/$1_$2_bin -d --Server=$1 --ID=$2 --Config=$3 --Plugin=$4 --Param=$5 --start" >> Monitor.sh

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
do_work RobotServer 1.1.1.2 ../../Config ../../Plugin2 10000,1000
do_work RobotServer 1.1.1.3 ../../Config ../../Plugin2 11000,1000
do_work RobotServer 1.1.1.4 ../../Config ../../Plugin2 12000,1000
do_work RobotServer 1.1.1.5 ../../Config ../../Plugin2 13000,1000
do_work RobotServer 1.1.1.6 ../../Config ../../Plugin2 14000,1000
do_work RobotServer 1.1.1.7 ../../Config ../../Plugin2 15000,1000
do_work RobotServer 1.1.1.8 ../../Config ../../Plugin2 16000,1000
do_work RobotServer 1.1.1.9 ../../Config ../../Plugin2 17000,1000
do_work RobotServer 1.1.1.10 ../../Config ../../Plugin2 18000,1000
do_work RobotServer 1.1.1.11 ../../Config ../../Plugin2 19000,1000
do_work RobotServer 1.1.1.12 ../../Config ../../Plugin2 20000,1000

echo	"tail --follow=name --retry $log_str --max-unchanged-stats=3 -n 5 -q | awk '"'/INFO/ {print "\033[32m" $0 "\033[39m"} /DEBUG/ {print  $0 }  /WARNING/ {print "\033[33m" $0 "\033[39m"} /TRACE/ {print "\033[33m" $0 "\033[39m"} /ERROR/ {print "\033[31m" $0 "\033[39m"} '"'" >> Alllog.sh

echo "}" >> Alllog.sh
echo "main" >> Alllog.sh

echo "./shm_rm.sh" >> Stop.sh

echo "rm Stop.sh -rf" >> Clear.sh
echo "rm Start.sh -rf" >> Clear.sh
echo "rm ReStart.sh -rf" >> Clear.sh
echo "rm Clear.sh -rf" >> Clear.sh
echo "rm Alllog.sh -rf" >> Clear.sh
