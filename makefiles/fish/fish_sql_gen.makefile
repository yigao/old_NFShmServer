include ./fish_define.makefile

.PHONY:all

all:${FISH_SQL_FILE}

${GAME_SQL_PATH}/create_FishConfigDesc.sql:${FISH_RESDB_META_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${FISH_RESDB_META_DESCRIPTOR} --message_fullname=proto_ff.FishConfigDesc --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_FishAlgoDesc.sql:${FISH_RESDB_META_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${FISH_RESDB_META_DESCRIPTOR} --message_fullname=proto_ff.FishAlgoDesc --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_GunValueConfig.sql:${FISH_RESDB_META_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${FISH_RESDB_META_DESCRIPTOR} --message_fullname=proto_ff.GunValueConfig --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_DeskInfoDesc.sql:${FISH_RESDB_META_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${FISH_RESDB_META_DESCRIPTOR} --message_fullname=proto_ff.DeskInfoDesc --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_FishLevelDesc.sql:${FISH_RESDB_META_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${FISH_RESDB_META_DESCRIPTOR} --message_fullname=proto_ff.FishLevelDesc --out_path=${GAME_SQL_PATH}/ \

${GAME_SQL_PATH}/create_GMCtrlLevelDesc.sql:${FISH_RESDB_META_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${FISH_RESDB_META_DESCRIPTOR} --message_fullname=proto_ff.GMCtrlLevelDesc --out_path=${GAME_SQL_PATH}/ \
	
${GAME_SQL_PATH}/create_LineGameSystemControlInfo.sql:${FISH_RESDB_META_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${FISH_RESDB_META_DESCRIPTOR} --message_fullname=proto_ff.LineGameSystemControlInfo --out_path=${GAME_SQL_PATH}/ \
	
${GAME_SQL_PATH}/create_LineLevelDesc.sql:${FISH_RESDB_META_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${FISH_RESDB_META_DESCRIPTOR} --message_fullname=proto_ff.LineLevelDesc --out_path=${GAME_SQL_PATH}/ \
	
${GAME_SQL_PATH}/create_LineDeskInfoDesc.sql:${FISH_RESDB_META_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${FISH_RESDB_META_DESCRIPTOR} --message_fullname=proto_ff.LineDeskInfoDesc --out_path=${GAME_SQL_PATH}/ \
	
${GAME_SQL_PATH}/create_LineAlgoDesc.sql:${FISH_RESDB_META_DESCRIPTOR}
	${PROTO2SQL} --proto_ds=${FISH_RESDB_META_DESCRIPTOR} --message_fullname=proto_ff.LineAlgoDesc --out_path=${GAME_SQL_PATH}/ \