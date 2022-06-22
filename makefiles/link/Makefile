include ./link_define.makefile
.PHONY:all clean

all:
	make -f ${LINK_MAKE_PROTOC_GEN} 2>&1 | tee -a ${MAKE_COMPILE_LOG} 2>&1; if [ $${PIPESTATUS[0]} -ne 0 ]; then exit 1;fi;
	make -f ${LINK_MAKE_SQL_GEN} 2>&1 | tee -a ${MAKE_COMPILE_LOG} 2>&1; if [ $${PIPESTATUS[0]} -ne 0 ]; then exit 1;fi;
clean:
	rm ${LINK_PROTOCGEN_FILE} ${LINK_PROTOC_DESCRIPTOR_FILE} -rf
