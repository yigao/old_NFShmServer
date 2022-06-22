include ./fish_define.makefile
.PHONY:all clean

all:
	make -f ${FISH_MAKE_PROTOC_GEN} 2>&1 | tee -a ${MAKE_COMPILE_LOG} 2>&1; if [ $${PIPESTATUS[0]} -ne 0 ]; then exit 1;fi;
	make -f ${FISH_MAKE_SQL_GEN} 2>&1 | tee -a ${MAKE_COMPILE_LOG} 2>&1; if [ $${PIPESTATUS[0]} -ne 0 ]; then exit 1;fi;
clean:
	rm ${FISH_PROTOCGEN_FILE} ${FISH_PROTOC_DESCRIPTOR_FILE} -rf
