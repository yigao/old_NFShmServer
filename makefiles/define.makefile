﻿GAME_NFRAME=..
GAME_SRC_PATH=..
GAME_INSTALL_PATH=${GAME_SRC_PATH}/Install
GAME_BIN_PATH=${GAME_INSTALL_PATH}/Bin
GAME_INSTALL_NEW_PATH=${GAME_SRC_PATH}/mmog
GAME_BIN_NEW_PATH=${GAME_INSTALL_NEW_PATH}/
GAME_DATA_PATH=${GAME_INSTALL_PATH}/Config/Data
GAME_SQL_PATH=${GAME_INSTALL_PATH}/Sql

MAKEFILE_PATH=${GAME_SRC_PATH}/makefiles
MAKE_PROTOC_GEN=${MAKEFILE_PATH}/protoc_gen.makefile
MAKE_EXCEL_GEN=${MAKEFILE_PATH}/excel_gen.makefile
MAKE_SQL_GEN=${MAKEFILE_PATH}/sql_gen.makefile

RESDB_EXCEL_PATH=${GAME_SRC_PATH}/Excel
PROTOCGEN_FILE_PATH=${GAME_SRC_PATH}/makefiles/temp

THIRD_PARTY_PATH=${GAME_SRC_PATH}/thirdparty
THIRD_PARTY_TOOLS_PATH=${THIRD_PARTY_PATH}/tools
THIRD_PARTY_INC_PATH=${THIRD_PARTY_PATH}/
THIRD_PARTY_LIB_PATH=${THIRD_PARTY_PATH}/lib

TOOLS_PATH=${GAME_SRC_PATH}/tools
THIRD_PARTY_TOOLS_PATH=${TOOLS_PATH}
PROTOC=${THIRD_PARTY_TOOLS_PATH}/protoc
PROTO2STRUCT=python ${TOOLS_PATH}/proto_2_struct/proto2struct.py
EXCEL2BIN=python ${TOOLS_PATH}/excel_2_bin/excel2bin_new.py
PROTO2SQL=python ${TOOLS_PATH}/proto_2_sql/proto2sql.py
PROTO2STRUCT_PATH=${TOOLS_PATH}/proto_2_struct/
EXCEL2BIN_PATH=${TOOLS_PATH}/excel_2_bin/
PROTO2SQL_PATH=${TOOLS_PATH}/proto_2_sql/

MAKE_SINGLE_JOB_NUM=4

#######################
#protocol define
#######################

PROTOCOL_PATH=${GAME_SRC_PATH}/Message
PROTOCOL_COMM_PATH=${PROTOCOL_PATH}/common
PROTOCOL_KERNEL_PATH=${PROTOCOL_PATH}/kernel
PROTOCOL_CS_PATH=${PROTOCOL_PATH}/proto_cs
PROTOCOL_STORESVR_PATH=${PROTOCOL_PATH}/storesvr
PROTOCOL_SS_PATH=${PROTOCOL_PATH}/proto_svr

PROTOCOL_COMM_XML=${PROTOCOL_COMM_PATH}/proto_common.proto
PROTOCOL_COMM_H=${PROTOCGEN_FILE_PATH}/proto_common.pb.h ${PROTOCGEN_FILE_PATH}/proto_common_s.h
PROTOCOL_COMM_CPP=${PROTOCGEN_FILE_PATH}/proto_common.pb.cc ${PROTOCGEN_FILE_PATH}/proto_common_s.cpp
PROTOCOL_COMM_DESCRIPTOR=${PROTOCGEN_FILE_PATH}/proto_common.proto.ds
PROTOCOL_COMM_PY=${PROTOCGEN_FILE_PATH}/proto_common_pb2.py

PROTOCOL_EVENT_XML=${PROTOCOL_COMM_PATH}/proto_event.proto
PROTOCOL_EVENT_H=${PROTOCGEN_FILE_PATH}/proto_event.pb.h
PROTOCOL_EVENT_CPP=${PROTOCGEN_FILE_PATH}/proto_event.pb.cc

PROTOCOL_CS_XML=$(wildcard ${PROTOCOL_CS_PATH}/*.proto)
PROTOCOL_CS_H= $(subst $(PROTOCOL_CS_PATH),$(PROTOCGEN_FILE_PATH),$(PROTOCOL_CS_XML:.proto=.pb.h))
PROTOCOL_CS_CPP=$(PROTOCOL_CS_H:.h=.cc)

PROTOCOL_SS_XML=$(wildcard ${PROTOCOL_SS_PATH}/*.proto)
PROTOCOL_SS_H=$(subst $(PROTOCOL_SS_PATH),$(PROTOCGEN_FILE_PATH),$(PROTOCOL_SS_XML:.proto=.pb.h))
PROTOCOL_SS_CPP=$(PROTOCOL_SS_H:.h=.cc)

RESDB_META_PATH=${PROTOCOL_PATH}/ResMetaS/
RESDB_META_CS_XML=${RESDB_META_PATH}/ResMeta.proto
RESDB_META_CS_H=${PROTOCGEN_FILE_PATH}/ResMeta.pb.h ${PROTOCGEN_FILE_PATH}/ResMeta_s.h
RESDB_META_CS_CPP=${PROTOCGEN_FILE_PATH}/ResMeta.pb.cc ${PROTOCGEN_FILE_PATH}/ResMeta_s.cpp
RESDB_META_DESCRIPTOR=${PROTOCGEN_FILE_PATH}/ResMeta.proto.ds

RESDB_DESC_XML=$(wildcard ${RESDB_META_PATH}/*.proto)
RESDB_DESC_H=$(subst $(RESDB_META_PATH),$(PROTOCGEN_FILE_PATH),$(RESDB_DESC_XML:.proto=.pb.h))
RESDB_DESC_CPP=$(RESDB_DESC_H:.h=.cc)
RESDB_DESC_STRUCT_H=$(RESDB_DESC_H:.pb.h=_s.h)
RESDB_DESC_STRUCT_CPP=$(RESDB_DESC_STRUCT_H:.h=.cpp)

PROTOCGEN_CPP=${PROTOCOL_CS_CPP}  ${RESDB_META_CS_CPP} ${PROTOCOL_COMM_CPP} ${PROTOCOL_EVENT_CPP}\
	${PROTOCOL_CS_CMD_CPP} ${PROTOCOL_SS_CPP}

PROTOCGEN_H=${PROTOCOL_CS_H} ${RESDB_META_CS_H} ${PROTOCOL_COMM_H}  ${PROTOCOL_EVENT_H}\
	${PROTOCOL_CS_CMD_H} ${PROTOCOL_SS_H}

ALL_PROTOCGEN_FILE=${PROTOCGEN_CPP} ${PROTOCGEN_H}
ALL_PROTOC_DESCRIPTOR_FILE=${PROTOCOL_COMM_DESCRIPTOR} ${RESDB_META_DESCRIPTOR}
ALL_PROTOCGEN_PY=

NEW_PROTOCGEN_FILE_PATH=${GAME_SRC_PATH}/src/NFComm/NFMessageDefine

SQL_FILE= ${GAME_SQL_PATH}/create_tbAccountTable.sql\
        ${GAME_SQL_PATH}/create_tbUserMailInfo.sql ${GAME_SQL_PATH}/create_tbUserMailDetail.sql ${GAME_SQL_PATH}/create_tbEventLog.sql\
         ${GAME_SQL_PATH}/create_MailDesc.sql ${GAME_SQL_PATH}/create_tbUserDetailData.sql ${GAME_SQL_PATH}/create_tbUserMiscInfo.sql\
         ${GAME_SQL_PATH}/create_tbUserSimpleData.sql ${GAME_SQL_PATH}/create_ConstDesc.sql ${GAME_SQL_PATH}/create_tbGiveBankJetton.sql\
        ${GAME_SQL_PATH}/create_tbRankCommon.sql ${GAME_SQL_PATH}/create_tbGameRobot.sql ${GAME_SQL_PATH}/create_NameDesc.sql\
       ${GAME_SQL_PATH}/create_LogMoneyDetail.sql ${GAME_SQL_PATH}/create_LogGameDetail.sql ${GAME_SQL_PATH}/create_tbLogGameDay.sql\
       ${GAME_SQL_PATH}/create_tbGameUserManagerData.sql ${GAME_SQL_PATH}/create_LogGameRecordDetail.sql ${GAME_SQL_PATH}/create_LogGiveMoneyRecord.sql\
       ${GAME_SQL_PATH}/create_LogVipRechargeRecord.sql ${GAME_SQL_PATH}/create_LogZhuangRecord.sql ${GAME_SQL_PATH}/create_LogRechargeOrder.sql\
       ${GAME_SQL_PATH}/create_tbLogSystemDay.sql ${GAME_SQL_PATH}/create_tbGmCtrlGiveCtrlData.sql ${GAME_SQL_PATH}/create_tbMachineManagerData.sql\
       ${GAME_SQL_PATH}/create_tbRedeemCode.sql ${GAME_SQL_PATH}/create_LogRedeemCodeRechargeRecord.sql ${GAME_SQL_PATH}/create_tbServerMgr.sql\
       ${GAME_SQL_PATH}/create_tbContractMgr.sql\


##########################
#
##########################
MAKE_COMPILE_LOG=./make_compile.log
MAKE_COMPILE_WARNING_LOG=./make_warning.log
MAKE_COMPILE_ERROR_LOG=./make_error.log
MAKE_DEPENDENT_LOG=./make_dependent.log
MAKE_DEPENDENT_ERROR_LOG=./make_dependent_error.log
MAKE_LINK_ERROR_LOG=./make_link_error.log

NEED_CLEAN_FILES=

RESDB_BIN_FILE=
#RESDB_BIN_FILE=${GAME_DATA_PATH}/MailDesc.bin  ${GAME_DATA_PATH}/ConstDesc.bin
