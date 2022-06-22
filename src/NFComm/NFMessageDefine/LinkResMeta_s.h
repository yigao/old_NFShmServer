#pragma once

#include <stdint.h>
#include <NFComm/NFShmCore/NFSizeString.h>
#include <NFComm/NFShmCore/NFArray.h>
#include <NFComm/NFShmCore/NFSeqOP.h>
#include <NFComm/NFShmCore/NFShmMgr.h>
#include "LinkResMeta.pb.h"
#include "LinkResMeta_s.h"
#include "proto_common.pb.h"
#include "proto_common_s.h"

namespace proto_ff_s {

	struct Proto_HMLineRateMgr_item_s : public NFDescStoreSeqOP {
		Proto_HMLineRateMgr_item_s();
		int CreateInit();
		int ResumeInit();
		NFArray<int32_t, 15> item;

		static void write_to_pbmsg(const struct Proto_HMLineRateMgr_item_s & obj, ::proto_ff::Proto_HMLineRateMgr_item & msg);
		static void read_from_pbmsg(const ::proto_ff::Proto_HMLineRateMgr_item & msg, struct Proto_HMLineRateMgr_item_s & obj);
		static ::proto_ff::Proto_HMLineRateMgr_item* new_pbmsg(){ return new ::proto_ff::Proto_HMLineRateMgr_item(); }
		static ::proto_ff::Proto_HMLineRateMgr_item make_pbmsg(){ return ::proto_ff::Proto_HMLineRateMgr_item(); }
	};
	typedef struct Proto_HMLineRateMgr_item_s Proto_HMLineRateMgr_item_t;

	struct Proto_HMLineRateMgr_icon_s : public NFDescStoreSeqOP {
		Proto_HMLineRateMgr_icon_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct Proto_HMLineRateMgr_item_s, 15> icon;

		static void write_to_pbmsg(const struct Proto_HMLineRateMgr_icon_s & obj, ::proto_ff::Proto_HMLineRateMgr_icon & msg);
		static void read_from_pbmsg(const ::proto_ff::Proto_HMLineRateMgr_icon & msg, struct Proto_HMLineRateMgr_icon_s & obj);
		static ::proto_ff::Proto_HMLineRateMgr_icon* new_pbmsg(){ return new ::proto_ff::Proto_HMLineRateMgr_icon(); }
		static ::proto_ff::Proto_HMLineRateMgr_icon make_pbmsg(){ return ::proto_ff::Proto_HMLineRateMgr_icon(); }
	};
	typedef struct Proto_HMLineRateMgr_icon_s Proto_HMLineRateMgr_icon_t;

	struct Proto_HMLineRateMgr_mary_s : public NFDescStoreSeqOP {
		Proto_HMLineRateMgr_mary_s();
		int CreateInit();
		int ResumeInit();
		NFArray<int32_t, 15> IconRight;

		static void write_to_pbmsg(const struct Proto_HMLineRateMgr_mary_s & obj, ::proto_ff::Proto_HMLineRateMgr_mary & msg);
		static void read_from_pbmsg(const ::proto_ff::Proto_HMLineRateMgr_mary & msg, struct Proto_HMLineRateMgr_mary_s & obj);
		static ::proto_ff::Proto_HMLineRateMgr_mary* new_pbmsg(){ return new ::proto_ff::Proto_HMLineRateMgr_mary(); }
		static ::proto_ff::Proto_HMLineRateMgr_mary make_pbmsg(){ return ::proto_ff::Proto_HMLineRateMgr_mary(); }
	};
	typedef struct Proto_HMLineRateMgr_mary_s Proto_HMLineRateMgr_mary_t;

	struct Proto_HMLineRateMgr_s : public NFDescStoreSeqOP {
		Proto_HMLineRateMgr_s();
		int CreateInit();
		int ResumeInit();
		struct Proto_HMLineRateMgr_icon_s main;
		struct Proto_HMLineRateMgr_icon_s free;
		struct Proto_HMLineRateMgr_icon_s shulaibao;
		struct Proto_HMLineRateMgr_mary_s mary;

		static void write_to_pbmsg(const struct Proto_HMLineRateMgr_s & obj, ::proto_ff::Proto_HMLineRateMgr & msg);
		static void read_from_pbmsg(const ::proto_ff::Proto_HMLineRateMgr & msg, struct Proto_HMLineRateMgr_s & obj);
		static ::proto_ff::Proto_HMLineRateMgr* new_pbmsg(){ return new ::proto_ff::Proto_HMLineRateMgr(); }
		static ::proto_ff::Proto_HMLineRateMgr make_pbmsg(){ return ::proto_ff::Proto_HMLineRateMgr(); }
	};
	typedef struct Proto_HMLineRateMgr_s Proto_HMLineRateMgr_t;

	struct Proto_HMRecordItem_Row_s : public NFDescStoreSeqOP {
		Proto_HMRecordItem_Row_s();
		int CreateInit();
		int ResumeInit();
		NFArray<int32_t, 5> col;

		static void write_to_pbmsg(const struct Proto_HMRecordItem_Row_s & obj, ::proto_ff::Proto_HMRecordItem_Row & msg);
		static void read_from_pbmsg(const ::proto_ff::Proto_HMRecordItem_Row & msg, struct Proto_HMRecordItem_Row_s & obj);
		static ::proto_ff::Proto_HMRecordItem_Row* new_pbmsg(){ return new ::proto_ff::Proto_HMRecordItem_Row(); }
		static ::proto_ff::Proto_HMRecordItem_Row make_pbmsg(){ return ::proto_ff::Proto_HMRecordItem_Row(); }
	};
	typedef struct Proto_HMRecordItem_Row_s Proto_HMRecordItem_Row_t;

	struct Proto_HMRecordItem_s : public NFDescStoreSeqOP {
		Proto_HMRecordItem_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct Proto_HMRecordItem_Row_s, 5> row;

		static void write_to_pbmsg(const struct Proto_HMRecordItem_s & obj, ::proto_ff::Proto_HMRecordItem & msg);
		static void read_from_pbmsg(const ::proto_ff::Proto_HMRecordItem & msg, struct Proto_HMRecordItem_s & obj);
		static ::proto_ff::Proto_HMRecordItem* new_pbmsg(){ return new ::proto_ff::Proto_HMRecordItem(); }
		static ::proto_ff::Proto_HMRecordItem make_pbmsg(){ return ::proto_ff::Proto_HMRecordItem(); }
	};
	typedef struct Proto_HMRecordItem_s Proto_HMRecordItem_t;

	struct Proto_MaryResult_s : public NFDescStoreSeqOP {
		Proto_MaryResult_s();
		int CreateInit();
		int ResumeInit();
		int32_t outer_value;
		int32_t mul;
		NFArray<int32_t, 10> vec_inner_value;

		static void write_to_pbmsg(const struct Proto_MaryResult_s & obj, ::proto_ff::Proto_MaryResult & msg);
		static void read_from_pbmsg(const ::proto_ff::Proto_MaryResult & msg, struct Proto_MaryResult_s & obj);
		static ::proto_ff::Proto_MaryResult* new_pbmsg(){ return new ::proto_ff::Proto_MaryResult(); }
		static ::proto_ff::Proto_MaryResult make_pbmsg(){ return ::proto_ff::Proto_MaryResult(); }
	};
	typedef struct Proto_MaryResult_s Proto_MaryResult_t;

	struct Proto_LineColCfg_item_s : public NFDescStoreSeqOP {
		Proto_LineColCfg_item_s();
		int CreateInit();
		int ResumeInit();
		NFArray<int32_t, 15> item;

		static void write_to_pbmsg(const struct Proto_LineColCfg_item_s & obj, ::proto_ff::Proto_LineColCfg_item & msg);
		static void read_from_pbmsg(const ::proto_ff::Proto_LineColCfg_item & msg, struct Proto_LineColCfg_item_s & obj);
		static ::proto_ff::Proto_LineColCfg_item* new_pbmsg(){ return new ::proto_ff::Proto_LineColCfg_item(); }
		static ::proto_ff::Proto_LineColCfg_item make_pbmsg(){ return ::proto_ff::Proto_LineColCfg_item(); }
	};
	typedef struct Proto_LineColCfg_item_s Proto_LineColCfg_item_t;

	struct Proto_LineColCfg_Col_s : public NFDescStoreSeqOP {
		Proto_LineColCfg_Col_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct Proto_LineColCfg_item_s, 15> Col;

		static void write_to_pbmsg(const struct Proto_LineColCfg_Col_s & obj, ::proto_ff::Proto_LineColCfg_Col & msg);
		static void read_from_pbmsg(const ::proto_ff::Proto_LineColCfg_Col & msg, struct Proto_LineColCfg_Col_s & obj);
		static ::proto_ff::Proto_LineColCfg_Col* new_pbmsg(){ return new ::proto_ff::Proto_LineColCfg_Col(); }
		static ::proto_ff::Proto_LineColCfg_Col make_pbmsg(){ return ::proto_ff::Proto_LineColCfg_Col(); }
	};
	typedef struct Proto_LineColCfg_Col_s Proto_LineColCfg_Col_t;

	struct Proto_LineColCfg_s : public NFDescStoreSeqOP {
		Proto_LineColCfg_s();
		int CreateInit();
		int ResumeInit();
		struct Proto_LineColCfg_Col_s main;
		struct Proto_LineColCfg_Col_s free;
		struct Proto_LineColCfg_Col_s shulaibao;
		struct Proto_LineColCfg_Col_s bubugao;

		static void write_to_pbmsg(const struct Proto_LineColCfg_s & obj, ::proto_ff::Proto_LineColCfg & msg);
		static void read_from_pbmsg(const ::proto_ff::Proto_LineColCfg & msg, struct Proto_LineColCfg_s & obj);
		static ::proto_ff::Proto_LineColCfg* new_pbmsg(){ return new ::proto_ff::Proto_LineColCfg(); }
		static ::proto_ff::Proto_LineColCfg make_pbmsg(){ return ::proto_ff::Proto_LineColCfg(); }
	};
	typedef struct Proto_LineColCfg_s Proto_LineColCfg_t;

	struct Proto_LinkResult_item_s : public NFDescStoreSeqOP {
		Proto_LinkResult_item_s();
		int CreateInit();
		int ResumeInit();
		NFArray<int32_t, 10> item;

		static void write_to_pbmsg(const struct Proto_LinkResult_item_s & obj, ::proto_ff::Proto_LinkResult_item & msg);
		static void read_from_pbmsg(const ::proto_ff::Proto_LinkResult_item & msg, struct Proto_LinkResult_item_s & obj);
		static ::proto_ff::Proto_LinkResult_item* new_pbmsg(){ return new ::proto_ff::Proto_LinkResult_item(); }
		static ::proto_ff::Proto_LinkResult_item make_pbmsg(){ return ::proto_ff::Proto_LinkResult_item(); }
	};
	typedef struct Proto_LinkResult_item_s Proto_LinkResult_item_t;

	struct Proto_LinkResult_Row_s : public NFDescStoreSeqOP {
		Proto_LinkResult_Row_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct Proto_LineColCfg_item_s, 10> Row;
		int32_t resulttype;
		int32_t rowcount;
		int32_t colcount;

		static void write_to_pbmsg(const struct Proto_LinkResult_Row_s & obj, ::proto_ff::Proto_LinkResult_Row & msg);
		static void read_from_pbmsg(const ::proto_ff::Proto_LinkResult_Row & msg, struct Proto_LinkResult_Row_s & obj);
		static ::proto_ff::Proto_LinkResult_Row* new_pbmsg(){ return new ::proto_ff::Proto_LinkResult_Row(); }
		static ::proto_ff::Proto_LinkResult_Row make_pbmsg(){ return ::proto_ff::Proto_LinkResult_Row(); }
	};
	typedef struct Proto_LinkResult_Row_s Proto_LinkResult_Row_t;

	struct Proto_LinkResult_s : public NFDescStoreSeqOP {
		Proto_LinkResult_s();
		int CreateInit();
		int ResumeInit();
		struct Proto_LinkResult_Row_s config;

		static void write_to_pbmsg(const struct Proto_LinkResult_s & obj, ::proto_ff::Proto_LinkResult & msg);
		static void read_from_pbmsg(const ::proto_ff::Proto_LinkResult & msg, struct Proto_LinkResult_s & obj);
		static ::proto_ff::Proto_LinkResult* new_pbmsg(){ return new ::proto_ff::Proto_LinkResult(); }
		static ::proto_ff::Proto_LinkResult make_pbmsg(){ return ::proto_ff::Proto_LinkResult(); }
	};
	typedef struct Proto_LinkResult_s Proto_LinkResult_t;

}

