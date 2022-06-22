include ./fafafa_define.makefile
.PHONY:all

all:${FAFAFA_PROTOCGEN_FILE}

${PROTOCOL_CS_EXTEND_FAFAFA_H} ${PROTOCOL_CS_EXTEND_FAFAFA_CPP} : ${PROTOCOL_CS_EXTEND_FAFAFA_XML}
	${PROTOC} $^ -I${THIRD_PARTY_INC_PATH} -I${PROTOCOL_CS_EXTEND_PATH} -I${PROTOCOL_COMM_PATH}   -I${PROTOCOL_KERNEL_PATH}\
			--cpp_out=${PROTOCGEN_FILE_PATH}
	cp ${PROTOCOL_CS_EXTEND_FAFAFA_H} ${PROTOCOL_CS_EXTEND_FAFAFA_CPP} ${GAME_SRC_PATH}/src/NFGameLogic/NFGameFaFaFaPlugin -rf