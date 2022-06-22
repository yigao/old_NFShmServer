include ./define.makefile

.PHONY:all

all:${SQL_FILE}

${GAME_SQL_PATH}/create_tbAccountTable.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbAccountTable --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_tbUserMailInfo.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbUserMailInfo --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_tbUserMailDetail.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbUserMailDetail --out_path=${GAME_SQL_PATH}/

${GAME_SQL_PATH}/create_MailDesc.sql:${RESDB_META_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${RESDB_META_DESCRIPTOR} --message_fullname=proto_ff.MailDesc --out_path=${GAME_SQL_PATH}/

${GAME_SQL_PATH}/create_tbUserDetailData.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbUserDetailData --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_tbUserSimpleData.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbUserSimpleData --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_ConstDesc.sql:${RESDB_META_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${RESDB_META_DESCRIPTOR} --message_fullname=proto_ff.ConstDesc --out_path=${GAME_SQL_PATH}/

${GAME_SQL_PATH}/create_tbGiveBankJetton.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbGiveBankJetton --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_tbUserMiscInfo.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbUserMiscInfo --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_tbEventLog.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbEventLog --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_tbRankCommon.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbRankCommon --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_tbGameRobot.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbGameRobot --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_NameDesc.sql:${RESDB_META_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${RESDB_META_DESCRIPTOR} --message_fullname=proto_ff.NameDesc --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_LogMoneyDetail.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.LogMoneyDetail --table_count=10 --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_LogGameDetail.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.LogGameDetail --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_tbLogGameDay.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbLogGameDay --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_tbGameUserManagerData.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbGameUserManagerData --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_LogGameRecordDetail.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.LogGameRecordDetail --table_count=10 --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_LogVipRechargeRecord.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.LogVipRechargeRecord --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_LogZhuangRecord.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.LogZhuangRecord --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_LogRechargeOrder.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.LogRechargeOrder --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_LogGiveMoneyRecord.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.LogGiveMoneyRecord --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_tbLogSystemDay.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbLogSystemDay --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_tbGmCtrlGiveCtrlData.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbGmCtrlGiveCtrlData --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_tbMachineManagerData.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbMachineManagerData --out_path=${GAME_SQL_PATH}/

${GAME_SQL_PATH}/create_tbRedeemCode.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbRedeemCode --out_path=${GAME_SQL_PATH}/

${GAME_SQL_PATH}/create_LogRedeemCodeRechargeRecord.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.LogRedeemCodeRechargeRecord --out_path=${GAME_SQL_PATH}/

${GAME_SQL_PATH}/create_tbServerMgr.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbServerMgr --out_path=${GAME_SQL_PATH}/

${GAME_SQL_PATH}/create_tbContractMgr.sql:${PROTOCOL_COMM_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${PROTOCOL_COMM_DESCRIPTOR} --message_fullname=proto_ff.tbContractMgr --out_path=${GAME_SQL_PATH}/