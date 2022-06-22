include ./fafafa_define.makefile
.PHONY:all clean

all:
	make -f ${FAFAFA_MAKE_PROTOC_GEN} 2>&1 | tee -a ${MAKE_COMPILE_LOG} 2>&1; if [ $${PIPESTATUS[0]} -ne 0 ]; then exit 1;fi;
	make -f ${FAFAFA_MAKE_SQL_GEN} 2>&1 | tee -a ${MAKE_COMPILE_LOG} 2>&1; if [ $${PIPESTATUS[0]} -ne 0 ]; then exit 1;fi;
clean:
	rm ${FAFAFA_PROTOCGEN_FILE} ${FAFAFA_PROTOC_DESCRIPTOR_FILE} -rf
