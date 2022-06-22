#pragma once

#include <stdint.h>
#include <NFComm/NFShmCore/NFSizeString.h>
#include <NFComm/NFShmCore/NFArray.h>
#include <NFComm/NFShmCore/NFSeqOP.h>
#include <NFComm/NFShmCore/NFShmMgr.h>
#include "FishResMeta.pb.h"
#include "FishResMeta_s.h"
#include "proto_common.pb.h"
#include "proto_common_s.h"

namespace proto_ff_s {

	struct FishLevelDesc_s : public NFDescStoreSeqOP {
		FishLevelDesc_s();
		int CreateInit();
		int ResumeInit();
		int32_t LevelID;
		NFSizeString<128> LevelName;
		NFSizeString<128> CannonLevelVal;
		NFArray<int32_t, 10> VecCannonLevelVal;
		NFSizeString<128> CannonShowNum;
		NFArray<int32_t, 10> VecCannonShowNum;
		int32_t MinMoney;
		int32_t MaxMoney;
		int32_t StartGame;
		int32_t Flag;

		static void write_to_pbmsg(const struct FishLevelDesc_s & obj, ::proto_ff::FishLevelDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::FishLevelDesc & msg, struct FishLevelDesc_s & obj);
		static ::proto_ff::FishLevelDesc* new_pbmsg(){ return new ::proto_ff::FishLevelDesc(); }
		static ::proto_ff::FishLevelDesc make_pbmsg(){ return ::proto_ff::FishLevelDesc(); }
	};
	typedef struct FishLevelDesc_s FishLevelDesc_t;

	struct Sheet_FishLevelDesc_s : public NFDescStoreSeqOP {
		Sheet_FishLevelDesc_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct FishLevelDesc_s, 100> FishLevelDesc_List;

		static void write_to_pbmsg(const struct Sheet_FishLevelDesc_s & obj, ::proto_ff::Sheet_FishLevelDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::Sheet_FishLevelDesc & msg, struct Sheet_FishLevelDesc_s & obj);
		static ::proto_ff::Sheet_FishLevelDesc* new_pbmsg(){ return new ::proto_ff::Sheet_FishLevelDesc(); }
		static ::proto_ff::Sheet_FishLevelDesc make_pbmsg(){ return ::proto_ff::Sheet_FishLevelDesc(); }
	};
	typedef struct Sheet_FishLevelDesc_s Sheet_FishLevelDesc_t;

	struct FishConfigDesc_s : public NFDescStoreSeqOP {
		FishConfigDesc_s();
		int CreateInit();
		int ResumeInit();
		int32_t fish_id;
		int32_t fish_type;
		int32_t build_fish_type;
		int32_t ratio_min;
		int32_t ratio_max;
		int32_t double_award_min_ratio;
		int32_t child_fish_count;
		NFArray<NFSizeString<128>, 6> child_fish_ids;
		int32_t damage_radius;
		NFSizeString<128> damage_fish_ids;

		static void write_to_pbmsg(const struct FishConfigDesc_s & obj, ::proto_ff::FishConfigDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::FishConfigDesc & msg, struct FishConfigDesc_s & obj);
		static ::proto_ff::FishConfigDesc* new_pbmsg(){ return new ::proto_ff::FishConfigDesc(); }
		static ::proto_ff::FishConfigDesc make_pbmsg(){ return ::proto_ff::FishConfigDesc(); }
	};
	typedef struct FishConfigDesc_s FishConfigDesc_t;

	struct Sheet_FishConfigDesc_s : public NFDescStoreSeqOP {
		Sheet_FishConfigDesc_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct FishConfigDesc_s, 500> FishConfigDesc_List;

		static void write_to_pbmsg(const struct Sheet_FishConfigDesc_s & obj, ::proto_ff::Sheet_FishConfigDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::Sheet_FishConfigDesc & msg, struct Sheet_FishConfigDesc_s & obj);
		static ::proto_ff::Sheet_FishConfigDesc* new_pbmsg(){ return new ::proto_ff::Sheet_FishConfigDesc(); }
		static ::proto_ff::Sheet_FishConfigDesc make_pbmsg(){ return ::proto_ff::Sheet_FishConfigDesc(); }
	};
	typedef struct Sheet_FishConfigDesc_s Sheet_FishConfigDesc_t;

	struct GunValueConfig_s : public NFDescStoreSeqOP {
		GunValueConfig_s();
		int CreateInit();
		int ResumeInit();
		int32_t id;
		int32_t value;
		int32_t room_id;
		int32_t gun_id;

		static void write_to_pbmsg(const struct GunValueConfig_s & obj, ::proto_ff::GunValueConfig & msg);
		static void read_from_pbmsg(const ::proto_ff::GunValueConfig & msg, struct GunValueConfig_s & obj);
		static ::proto_ff::GunValueConfig* new_pbmsg(){ return new ::proto_ff::GunValueConfig(); }
		static ::proto_ff::GunValueConfig make_pbmsg(){ return ::proto_ff::GunValueConfig(); }
	};
	typedef struct GunValueConfig_s GunValueConfig_t;

	struct Sheet_GunValueConfig_s : public NFDescStoreSeqOP {
		Sheet_GunValueConfig_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct GunValueConfig_s, 500> GunValueConfig_List;

		static void write_to_pbmsg(const struct Sheet_GunValueConfig_s & obj, ::proto_ff::Sheet_GunValueConfig & msg);
		static void read_from_pbmsg(const ::proto_ff::Sheet_GunValueConfig & msg, struct Sheet_GunValueConfig_s & obj);
		static ::proto_ff::Sheet_GunValueConfig* new_pbmsg(){ return new ::proto_ff::Sheet_GunValueConfig(); }
		static ::proto_ff::Sheet_GunValueConfig make_pbmsg(){ return ::proto_ff::Sheet_GunValueConfig(); }
	};
	typedef struct Sheet_GunValueConfig_s Sheet_GunValueConfig_t;

	struct FishAlgoDesc_s : public NFDescStoreSeqOP {
		FishAlgoDesc_s();
		int CreateInit();
		int ResumeInit();
		int32_t AlgoID;
		int32_t GamePlatform;
		NFSizeString<64> AlgoName;
		NFSizeString<64> AlgoDesc;
		int64_t ChangeTimes;
		int64_t ChangeLiuShui;
		int64_t Chang1_RangeLow;
		int64_t Chang1_RangeHigh;
		int64_t Chang1_Chi1;
		int64_t Chang1_Chi2;
		int64_t Chang1_Chi3;
		int64_t Chang1_Fang1;
		int64_t Chang1_Fang2;
		int64_t Chang1_Fang3;
		int64_t Chang1_RateChi1;
		int64_t Chang1_RateChi2;
		int64_t Chang1_RateChi3;
		int64_t Chang1_RatePing;
		int64_t Chang1_RateFang1;
		int64_t Chang1_RateFang2;
		int64_t Chang1_RateFang3;
		int64_t Chang2_RangeLow;
		int64_t Chang2_RangeHigh;
		int64_t Chang2_Chi1;
		int64_t Chang2_Chi2;
		int64_t Chang2_Chi3;
		int64_t Chang2_Fang1;
		int64_t Chang2_Fang2;
		int64_t Chang2_Fang3;
		int64_t Chang2_RateChi1;
		int64_t Chang2_RateChi2;
		int64_t Chang2_RateChi3;
		int64_t Chang2_RatePing;
		int64_t Chang2_RateFang1;
		int64_t Chang2_RateFang2;
		int64_t Chang2_RateFang3;
		int64_t Chang3_RangeLow;
		int64_t Chang3_RangeHigh;
		int64_t Chang3_Chi1;
		int64_t Chang3_Chi2;
		int64_t Chang3_Chi3;
		int64_t Chang3_Fang1;
		int64_t Chang3_Fang2;
		int64_t Chang3_Fang3;
		int64_t Chang3_RateChi1;
		int64_t Chang3_RateChi2;
		int64_t Chang3_RateChi3;
		int64_t Chang3_RatePing;
		int64_t Chang3_RateFang1;
		int64_t Chang3_RateFang2;
		int64_t Chang3_RateFang3;
		int64_t Clear_MaxVal;
		int64_t Clear_Fang3Mul;
		int32_t Clear_Chi3Mul;
		int32_t Clear_InitShoot;
		int32_t Clear_InitCapture;
		int32_t Clear_InitDrawRate;
		int32_t Clear_InitPoolRate;
		int32_t Is_delete;
		int32_t FishAlgoType;

		static void write_to_pbmsg(const struct FishAlgoDesc_s & obj, ::proto_ff::FishAlgoDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::FishAlgoDesc & msg, struct FishAlgoDesc_s & obj);
		static ::proto_ff::FishAlgoDesc* new_pbmsg(){ return new ::proto_ff::FishAlgoDesc(); }
		static ::proto_ff::FishAlgoDesc make_pbmsg(){ return ::proto_ff::FishAlgoDesc(); }
	};
	typedef struct FishAlgoDesc_s FishAlgoDesc_t;

	struct Sheet_FishAlgoDesc_s : public NFDescStoreSeqOP {
		Sheet_FishAlgoDesc_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct FishAlgoDesc_s, 200> FishAlgoDesc_List;

		static void write_to_pbmsg(const struct Sheet_FishAlgoDesc_s & obj, ::proto_ff::Sheet_FishAlgoDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::Sheet_FishAlgoDesc & msg, struct Sheet_FishAlgoDesc_s & obj);
		static ::proto_ff::Sheet_FishAlgoDesc* new_pbmsg(){ return new ::proto_ff::Sheet_FishAlgoDesc(); }
		static ::proto_ff::Sheet_FishAlgoDesc make_pbmsg(){ return ::proto_ff::Sheet_FishAlgoDesc(); }
	};
	typedef struct Sheet_FishAlgoDesc_s Sheet_FishAlgoDesc_t;

	struct UserDeskAlgoInfo_s : public NFDescStoreSeqOP {
		UserDeskAlgoInfo_s();
		int CreateInit();
		int ResumeInit();
		int32_t AlgoID;
		float DrawRate;
		double CurTotalShoot;
		double CurTotalCapture;
		int64_t CurAlgoChang;
		int64_t CurAlgoStatus;

		static void write_to_pbmsg(const struct UserDeskAlgoInfo_s & obj, ::proto_ff::UserDeskAlgoInfo & msg);
		static void read_from_pbmsg(const ::proto_ff::UserDeskAlgoInfo & msg, struct UserDeskAlgoInfo_s & obj);
		static ::proto_ff::UserDeskAlgoInfo* new_pbmsg(){ return new ::proto_ff::UserDeskAlgoInfo(); }
		static ::proto_ff::UserDeskAlgoInfo make_pbmsg(){ return ::proto_ff::UserDeskAlgoInfo(); }
	};
	typedef struct UserDeskAlgoInfo_s UserDeskAlgoInfo_t;

	struct DeskInfoDesc_s : public NFDescStoreSeqOP {
		DeskInfoDesc_s();
		int CreateInit();
		int ResumeInit();
		int32_t id;
		int32_t RoomID;
		int32_t DeskID;
		int32_t AlgoType;
		NFArray<struct UserDeskAlgoInfo_s, 3> AlgoData;
		int32_t GameLevel;
		int64_t YValueA;
		int64_t YValueB;
		int64_t FreePool;
		int64_t YValue;

		static void write_to_pbmsg(const struct DeskInfoDesc_s & obj, ::proto_ff::DeskInfoDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::DeskInfoDesc & msg, struct DeskInfoDesc_s & obj);
		static ::proto_ff::DeskInfoDesc* new_pbmsg(){ return new ::proto_ff::DeskInfoDesc(); }
		static ::proto_ff::DeskInfoDesc make_pbmsg(){ return ::proto_ff::DeskInfoDesc(); }
	};
	typedef struct DeskInfoDesc_s DeskInfoDesc_t;

	struct Sheet_DeskInfoDesc_s : public NFDescStoreSeqOP {
		Sheet_DeskInfoDesc_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct DeskInfoDesc_s, 200> DeskInfoDesc_List;

		static void write_to_pbmsg(const struct Sheet_DeskInfoDesc_s & obj, ::proto_ff::Sheet_DeskInfoDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::Sheet_DeskInfoDesc & msg, struct Sheet_DeskInfoDesc_s & obj);
		static ::proto_ff::Sheet_DeskInfoDesc* new_pbmsg(){ return new ::proto_ff::Sheet_DeskInfoDesc(); }
		static ::proto_ff::Sheet_DeskInfoDesc make_pbmsg(){ return ::proto_ff::Sheet_DeskInfoDesc(); }
	};
	typedef struct Sheet_DeskInfoDesc_s Sheet_DeskInfoDesc_t;

	struct FishInitPoolData_s : public NFDescStoreSeqOP {
		FishInitPoolData_s();
		int CreateInit();
		int ResumeInit();
		int32_t fish_id;
		int32_t num;

		static void write_to_pbmsg(const struct FishInitPoolData_s & obj, ::proto_ff::FishInitPoolData & msg);
		static void read_from_pbmsg(const ::proto_ff::FishInitPoolData & msg, struct FishInitPoolData_s & obj);
		static ::proto_ff::FishInitPoolData* new_pbmsg(){ return new ::proto_ff::FishInitPoolData(); }
		static ::proto_ff::FishInitPoolData make_pbmsg(){ return ::proto_ff::FishInitPoolData(); }
	};
	typedef struct FishInitPoolData_s FishInitPoolData_t;

	struct FishInitPool_s : public NFDescStoreSeqOP {
		FishInitPool_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct FishInitPoolData_s, 100> InitPoolCount;

		static void write_to_pbmsg(const struct FishInitPool_s & obj, ::proto_ff::FishInitPool & msg);
		static void read_from_pbmsg(const ::proto_ff::FishInitPool & msg, struct FishInitPool_s & obj);
		static ::proto_ff::FishInitPool* new_pbmsg(){ return new ::proto_ff::FishInitPool(); }
		static ::proto_ff::FishInitPool make_pbmsg(){ return ::proto_ff::FishInitPool(); }
	};
	typedef struct FishInitPool_s FishInitPool_t;

	struct SeatDangRange_B_s : public NFDescStoreSeqOP {
		SeatDangRange_B_s();
		int CreateInit();
		int ResumeInit();
		NFArray<int64_t, 8> value;

		static void write_to_pbmsg(const struct SeatDangRange_B_s & obj, ::proto_ff::SeatDangRange_B & msg);
		static void read_from_pbmsg(const ::proto_ff::SeatDangRange_B & msg, struct SeatDangRange_B_s & obj);
		static ::proto_ff::SeatDangRange_B* new_pbmsg(){ return new ::proto_ff::SeatDangRange_B(); }
		static ::proto_ff::SeatDangRange_B make_pbmsg(){ return ::proto_ff::SeatDangRange_B(); }
	};
	typedef struct SeatDangRange_B_s SeatDangRange_B_t;

	struct SeatAlgoSetup_s : public NFDescStoreSeqOP {
		SeatAlgoSetup_s();
		int CreateInit();
		int ResumeInit();
		int32_t SeatCtrlIsOpen;
		NFArray<int64_t, 7> SeatDangRange_Def_A;
		NFArray<int64_t, 7> SeatDangRange_Def_B;
		NFArray<int64_t, 7> SeatDangRange_Def_Robot;
		NFArray<struct SeatDangRange_B_s, 10> SeatDangRange_B;
		int64_t ClearDataMaxVal;
		double ClearDataFangCondation;
		double ClearDataChiCondation;

		static void write_to_pbmsg(const struct SeatAlgoSetup_s & obj, ::proto_ff::SeatAlgoSetup & msg);
		static void read_from_pbmsg(const ::proto_ff::SeatAlgoSetup & msg, struct SeatAlgoSetup_s & obj);
		static ::proto_ff::SeatAlgoSetup* new_pbmsg(){ return new ::proto_ff::SeatAlgoSetup(); }
		static ::proto_ff::SeatAlgoSetup make_pbmsg(){ return ::proto_ff::SeatAlgoSetup(); }
	};
	typedef struct SeatAlgoSetup_s SeatAlgoSetup_t;

	struct HuanDangRange_s : public NFDescStoreSeqOP {
		HuanDangRange_s();
		int CreateInit();
		int ResumeInit();
		NFArray<int64_t, 8> value;

		static void write_to_pbmsg(const struct HuanDangRange_s & obj, ::proto_ff::HuanDangRange & msg);
		static void read_from_pbmsg(const ::proto_ff::HuanDangRange & msg, struct HuanDangRange_s & obj);
		static ::proto_ff::HuanDangRange* new_pbmsg(){ return new ::proto_ff::HuanDangRange(); }
		static ::proto_ff::HuanDangRange make_pbmsg(){ return ::proto_ff::HuanDangRange(); }
	};
	typedef struct HuanDangRange_s HuanDangRange_t;

	struct DangChiRange_s : public NFDescStoreSeqOP {
		DangChiRange_s();
		int CreateInit();
		int ResumeInit();
		NFArray<int64_t, 7> value;

		static void write_to_pbmsg(const struct DangChiRange_s & obj, ::proto_ff::DangChiRange & msg);
		static void read_from_pbmsg(const ::proto_ff::DangChiRange & msg, struct DangChiRange_s & obj);
		static ::proto_ff::DangChiRange* new_pbmsg(){ return new ::proto_ff::DangChiRange(); }
		static ::proto_ff::DangChiRange make_pbmsg(){ return ::proto_ff::DangChiRange(); }
	};
	typedef struct DangChiRange_s DangChiRange_t;

	struct FishAlgorithmSetup_s : public NFDescStoreSeqOP {
		FishAlgorithmSetup_s();
		int CreateInit();
		int ResumeInit();
		int64_t HuanChangTimes;
		NFArray<struct HuanDangRange_s, 3> HuanDangRange;
		NFArray<struct DangChiRange_s, 3> DangChiRange;
		int64_t HuanBiaoLiuShuiVal;
		int64_t PoolInitBFB;
		int64_t ClearDataMaxVal;
		double ClearDataFangCondation;
		double ClearDataChiCondation;
		int64_t ClearDataInitShoot;
		int64_t ClearDataInitCapture;
		double ClearDataInitDrawRate;

		static void write_to_pbmsg(const struct FishAlgorithmSetup_s & obj, ::proto_ff::FishAlgorithmSetup & msg);
		static void read_from_pbmsg(const ::proto_ff::FishAlgorithmSetup & msg, struct FishAlgorithmSetup_s & obj);
		static ::proto_ff::FishAlgorithmSetup* new_pbmsg(){ return new ::proto_ff::FishAlgorithmSetup(); }
		static ::proto_ff::FishAlgorithmSetup make_pbmsg(){ return ::proto_ff::FishAlgorithmSetup(); }
	};
	typedef struct FishAlgorithmSetup_s FishAlgorithmSetup_t;

	struct FishAlgorithmFileName_s : public NFDescStoreSeqOP {
		FishAlgorithmFileName_s();
		int CreateInit();
		int ResumeInit();
		NFSizeString<32> FileNameChi1;
		NFSizeString<32> FileNameChi2;
		NFSizeString<32> FileNameChi5;
		NFSizeString<32> FileNameChi10;
		NFSizeString<32> FileNameChi20;
		NFSizeString<32> FileNameChi50;
		NFSizeString<32> FileNameChi100;
		NFSizeString<32> FileNameChi200;
		NFSizeString<32> FileNameFang1;
		NFSizeString<32> FileNameFang2;
		NFSizeString<32> FileNameFang5;
		NFSizeString<32> FileNameFang10;
		NFSizeString<32> FileNameFang20;
		NFSizeString<32> FileNameFang50;
		NFSizeString<32> FileNameFang100;
		NFSizeString<32> FileNameFang200;

		static void write_to_pbmsg(const struct FishAlgorithmFileName_s & obj, ::proto_ff::FishAlgorithmFileName & msg);
		static void read_from_pbmsg(const ::proto_ff::FishAlgorithmFileName & msg, struct FishAlgorithmFileName_s & obj);
		static ::proto_ff::FishAlgorithmFileName* new_pbmsg(){ return new ::proto_ff::FishAlgorithmFileName(); }
		static ::proto_ff::FishAlgorithmFileName make_pbmsg(){ return ::proto_ff::FishAlgorithmFileName(); }
	};
	typedef struct FishAlgorithmFileName_s FishAlgorithmFileName_t;

	struct FishAlgorithmCsvItem_s : public NFDescStoreSeqOP {
		FishAlgorithmCsvItem_s();
		int CreateInit();
		int ResumeInit();
		NFArray<int32_t, 500> value;

		static void write_to_pbmsg(const struct FishAlgorithmCsvItem_s & obj, ::proto_ff::FishAlgorithmCsvItem & msg);
		static void read_from_pbmsg(const ::proto_ff::FishAlgorithmCsvItem & msg, struct FishAlgorithmCsvItem_s & obj);
		static ::proto_ff::FishAlgorithmCsvItem* new_pbmsg(){ return new ::proto_ff::FishAlgorithmCsvItem(); }
		static ::proto_ff::FishAlgorithmCsvItem make_pbmsg(){ return ::proto_ff::FishAlgorithmCsvItem(); }
	};
	typedef struct FishAlgorithmCsvItem_s FishAlgorithmCsvItem_t;

	struct FishAlgorithmCsv_s : public NFDescStoreSeqOP {
		FishAlgorithmCsv_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct FishAlgorithmCsvItem_s, 10> item;

		static void write_to_pbmsg(const struct FishAlgorithmCsv_s & obj, ::proto_ff::FishAlgorithmCsv & msg);
		static void read_from_pbmsg(const ::proto_ff::FishAlgorithmCsv & msg, struct FishAlgorithmCsv_s & obj);
		static ::proto_ff::FishAlgorithmCsv* new_pbmsg(){ return new ::proto_ff::FishAlgorithmCsv(); }
		static ::proto_ff::FishAlgorithmCsv make_pbmsg(){ return ::proto_ff::FishAlgorithmCsv(); }
	};
	typedef struct FishAlgorithmCsv_s FishAlgorithmCsv_t;

	struct FishNormalSetup_s : public NFDescStoreSeqOP {
		FishNormalSetup_s();
		int CreateInit();
		int ResumeInit();
		int32_t SwitchBossTime;
		int32_t SwitchSceneTime;
		int32_t InitSceneIndex;
		int32_t AwardPoolSaveToDBTime;
		int32_t ClearTraceTime;
		NFArray<int32_t, 10> CannonLevelVal;
		NFArray<int32_t, 10> CannonShowNum;
		NFArray<double, 2> BulletHarmAddBFB;
		int32_t BulletCountInScreen;
		int32_t TotalSceneCount;
		int32_t ScreenFishMaxCount;
		int32_t ClientNotOperateTipTimes;
		int32_t ClientExitTimes;
		int32_t TestFishMustKilled;
		int32_t ClientLessMoneyTip;
		int32_t TurnTableCalcMinByOneJu;
		int32_t UserSettlementTimes;
		int32_t TipBaoJiMoney;
		int32_t BatchSendFishesInterval;
		int32_t BatchSendFishesCount;
		int32_t SwitchScenePrepareTime;
		int32_t SwitchSceneFishGoAwayTime;

		static void write_to_pbmsg(const struct FishNormalSetup_s & obj, ::proto_ff::FishNormalSetup & msg);
		static void read_from_pbmsg(const ::proto_ff::FishNormalSetup & msg, struct FishNormalSetup_s & obj);
		static ::proto_ff::FishNormalSetup* new_pbmsg(){ return new ::proto_ff::FishNormalSetup(); }
		static ::proto_ff::FishNormalSetup make_pbmsg(){ return ::proto_ff::FishNormalSetup(); }
	};
	typedef struct FishNormalSetup_s FishNormalSetup_t;

	struct FishPoolSaveBaseMul_s : public NFDescStoreSeqOP {
		FishPoolSaveBaseMul_s();
		int CreateInit();
		int ResumeInit();
		NFArray<int32_t, 10> value;

		static void write_to_pbmsg(const struct FishPoolSaveBaseMul_s & obj, ::proto_ff::FishPoolSaveBaseMul & msg);
		static void read_from_pbmsg(const ::proto_ff::FishPoolSaveBaseMul & msg, struct FishPoolSaveBaseMul_s & obj);
		static ::proto_ff::FishPoolSaveBaseMul* new_pbmsg(){ return new ::proto_ff::FishPoolSaveBaseMul(); }
		static ::proto_ff::FishPoolSaveBaseMul make_pbmsg(){ return ::proto_ff::FishPoolSaveBaseMul(); }
	};
	typedef struct FishPoolSaveBaseMul_s FishPoolSaveBaseMul_t;

	struct FishPoolSaveRelaCount_s : public NFDescStoreSeqOP {
		FishPoolSaveRelaCount_s();
		int CreateInit();
		int ResumeInit();
		NFArray<int32_t, 10> value;

		static void write_to_pbmsg(const struct FishPoolSaveRelaCount_s & obj, ::proto_ff::FishPoolSaveRelaCount & msg);
		static void read_from_pbmsg(const ::proto_ff::FishPoolSaveRelaCount & msg, struct FishPoolSaveRelaCount_s & obj);
		static ::proto_ff::FishPoolSaveRelaCount* new_pbmsg(){ return new ::proto_ff::FishPoolSaveRelaCount(); }
		static ::proto_ff::FishPoolSaveRelaCount make_pbmsg(){ return ::proto_ff::FishPoolSaveRelaCount(); }
	};
	typedef struct FishPoolSaveRelaCount_s FishPoolSaveRelaCount_t;

	struct FishPoolSaveHitCountCfg_s : public NFDescStoreSeqOP {
		FishPoolSaveHitCountCfg_s();
		int CreateInit();
		int ResumeInit();
		NFArray<int32_t, 10> value;

		static void write_to_pbmsg(const struct FishPoolSaveHitCountCfg_s & obj, ::proto_ff::FishPoolSaveHitCountCfg & msg);
		static void read_from_pbmsg(const ::proto_ff::FishPoolSaveHitCountCfg & msg, struct FishPoolSaveHitCountCfg_s & obj);
		static ::proto_ff::FishPoolSaveHitCountCfg* new_pbmsg(){ return new ::proto_ff::FishPoolSaveHitCountCfg(); }
		static ::proto_ff::FishPoolSaveHitCountCfg make_pbmsg(){ return ::proto_ff::FishPoolSaveHitCountCfg(); }
	};
	typedef struct FishPoolSaveHitCountCfg_s FishPoolSaveHitCountCfg_t;

	struct FishPoolSaveConnonHitCount_s : public NFDescStoreSeqOP {
		FishPoolSaveConnonHitCount_s();
		int CreateInit();
		int ResumeInit();
		NFArray<double, 10> value;

		static void write_to_pbmsg(const struct FishPoolSaveConnonHitCount_s & obj, ::proto_ff::FishPoolSaveConnonHitCount & msg);
		static void read_from_pbmsg(const ::proto_ff::FishPoolSaveConnonHitCount & msg, struct FishPoolSaveConnonHitCount_s & obj);
		static ::proto_ff::FishPoolSaveConnonHitCount* new_pbmsg(){ return new ::proto_ff::FishPoolSaveConnonHitCount(); }
		static ::proto_ff::FishPoolSaveConnonHitCount make_pbmsg(){ return ::proto_ff::FishPoolSaveConnonHitCount(); }
	};
	typedef struct FishPoolSaveConnonHitCount_s FishPoolSaveConnonHitCount_t;

	struct FishPoolSave_s : public NFDescStoreSeqOP {
		FishPoolSave_s();
		int CreateInit();
		int ResumeInit();
		int32_t dwFishID;
		int32_t btFishKind;
		int32_t btFishKindGroup1;
		int32_t btFishKindGroup2;
		int32_t btFishKindGroup3;
		int32_t btFishKindGroup4;
		bool bKilled;
		bool bRobotKilled;
		bool bKilledByOtherRela;
		bool bKilledByAlgoA;
		int32_t btKilledCannonIndex;
		bool bFloatMul;
		NFArray<struct FishPoolSaveBaseMul_s, 3> arBaseMul;
		NFArray<struct FishPoolSaveRelaCount_s, 3> arRelaCount;
		NFArray<struct FishPoolSaveHitCountCfg_s, 3> arHitCountCfg;
		NFArray<struct FishPoolSaveConnonHitCount_s, 3> arConnonHitCount;

		static void write_to_pbmsg(const struct FishPoolSave_s & obj, ::proto_ff::FishPoolSave & msg);
		static void read_from_pbmsg(const ::proto_ff::FishPoolSave & msg, struct FishPoolSave_s & obj);
		static ::proto_ff::FishPoolSave* new_pbmsg(){ return new ::proto_ff::FishPoolSave(); }
		static ::proto_ff::FishPoolSave make_pbmsg(){ return ::proto_ff::FishPoolSave(); }
	};
	typedef struct FishPoolSave_s FishPoolSave_t;

	struct FishKindFishPoolSave_s : public NFDescStoreSeqOP {
		FishKindFishPoolSave_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct FishPoolSave_s, 500> fish_pool;

		static void write_to_pbmsg(const struct FishKindFishPoolSave_s & obj, ::proto_ff::FishKindFishPoolSave & msg);
		static void read_from_pbmsg(const ::proto_ff::FishKindFishPoolSave & msg, struct FishKindFishPoolSave_s & obj);
		static ::proto_ff::FishKindFishPoolSave* new_pbmsg(){ return new ::proto_ff::FishKindFishPoolSave(); }
		static ::proto_ff::FishKindFishPoolSave make_pbmsg(){ return ::proto_ff::FishKindFishPoolSave(); }
	};
	typedef struct FishKindFishPoolSave_s FishKindFishPoolSave_t;

	struct FishKindFishPoolSaveArray_s : public NFDescStoreSeqOP {
		FishKindFishPoolSaveArray_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct FishKindFishPoolSave_s, 150> fish_kind;

		static void write_to_pbmsg(const struct FishKindFishPoolSaveArray_s & obj, ::proto_ff::FishKindFishPoolSaveArray & msg);
		static void read_from_pbmsg(const ::proto_ff::FishKindFishPoolSaveArray & msg, struct FishKindFishPoolSaveArray_s & obj);
		static ::proto_ff::FishKindFishPoolSaveArray* new_pbmsg(){ return new ::proto_ff::FishKindFishPoolSaveArray(); }
		static ::proto_ff::FishKindFishPoolSaveArray make_pbmsg(){ return ::proto_ff::FishKindFishPoolSaveArray(); }
	};
	typedef struct FishKindFishPoolSaveArray_s FishKindFishPoolSaveArray_t;

	struct GMCtrlLevelDesc_s : public NFDescStoreSeqOP {
		GMCtrlLevelDesc_s();
		int CreateInit();
		int ResumeInit();
		int32_t ControlLevel;
		NFSizeString<64> Name;
		int32_t ControlRate;

		static void write_to_pbmsg(const struct GMCtrlLevelDesc_s & obj, ::proto_ff::GMCtrlLevelDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::GMCtrlLevelDesc & msg, struct GMCtrlLevelDesc_s & obj);
		static ::proto_ff::GMCtrlLevelDesc* new_pbmsg(){ return new ::proto_ff::GMCtrlLevelDesc(); }
		static ::proto_ff::GMCtrlLevelDesc make_pbmsg(){ return ::proto_ff::GMCtrlLevelDesc(); }
	};
	typedef struct GMCtrlLevelDesc_s GMCtrlLevelDesc_t;

	struct Sheet_GMCtrlLevelDesc_s : public NFDescStoreSeqOP {
		Sheet_GMCtrlLevelDesc_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct GMCtrlLevelDesc_s, 20> GMCtrlLevelDesc_List;

		static void write_to_pbmsg(const struct Sheet_GMCtrlLevelDesc_s & obj, ::proto_ff::Sheet_GMCtrlLevelDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::Sheet_GMCtrlLevelDesc & msg, struct Sheet_GMCtrlLevelDesc_s & obj);
		static ::proto_ff::Sheet_GMCtrlLevelDesc* new_pbmsg(){ return new ::proto_ff::Sheet_GMCtrlLevelDesc(); }
		static ::proto_ff::Sheet_GMCtrlLevelDesc make_pbmsg(){ return ::proto_ff::Sheet_GMCtrlLevelDesc(); }
	};
	typedef struct Sheet_GMCtrlLevelDesc_s Sheet_GMCtrlLevelDesc_t;

	struct LineGameSystemControlInfo_s : public NFDescStoreSeqOP {
		LineGameSystemControlInfo_s();
		int CreateInit();
		int ResumeInit();
		int32_t RoomID;
		int32_t AreaID;
		int64_t TotalProfit;
		int32_t CurrentSystemControl;

		static void write_to_pbmsg(const struct LineGameSystemControlInfo_s & obj, ::proto_ff::LineGameSystemControlInfo & msg);
		static void read_from_pbmsg(const ::proto_ff::LineGameSystemControlInfo & msg, struct LineGameSystemControlInfo_s & obj);
		static ::proto_ff::LineGameSystemControlInfo* new_pbmsg(){ return new ::proto_ff::LineGameSystemControlInfo(); }
		static ::proto_ff::LineGameSystemControlInfo make_pbmsg(){ return ::proto_ff::LineGameSystemControlInfo(); }
	};
	typedef struct LineGameSystemControlInfo_s LineGameSystemControlInfo_t;

	struct Sheet_LineGameSystemControlInfo_s : public NFDescStoreSeqOP {
		Sheet_LineGameSystemControlInfo_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct LineGameSystemControlInfo_s, 20> LineGameSystemControlInfo_List;

		static void write_to_pbmsg(const struct Sheet_LineGameSystemControlInfo_s & obj, ::proto_ff::Sheet_LineGameSystemControlInfo & msg);
		static void read_from_pbmsg(const ::proto_ff::Sheet_LineGameSystemControlInfo & msg, struct Sheet_LineGameSystemControlInfo_s & obj);
		static ::proto_ff::Sheet_LineGameSystemControlInfo* new_pbmsg(){ return new ::proto_ff::Sheet_LineGameSystemControlInfo(); }
		static ::proto_ff::Sheet_LineGameSystemControlInfo make_pbmsg(){ return ::proto_ff::Sheet_LineGameSystemControlInfo(); }
	};
	typedef struct Sheet_LineGameSystemControlInfo_s Sheet_LineGameSystemControlInfo_t;

	struct LineLevelDesc_s : public NFDescStoreSeqOP {
		LineLevelDesc_s();
		int CreateInit();
		int ResumeInit();
		int32_t LevelID;
		NFSizeString<128> LevelName;
		NFSizeString<128> CannonLevelVal;
		NFArray<int32_t, 10> VecCannonLevelVal;
		NFSizeString<128> CannonShowNum;
		NFArray<int32_t, 10> VecCannonShowNum;
		int32_t MinMoney;
		int32_t MaxMoney;
		int32_t StartGame;
		int32_t Flag;
		int32_t MaxWinTimes;
		NFSizeString<128> Chip;
		NFArray<int64_t, 10> VecChips;
		NFSizeString<128> GMLevelRate;
		NFArray<int32_t, 10> VecGMLevelRate;

		static void write_to_pbmsg(const struct LineLevelDesc_s & obj, ::proto_ff::LineLevelDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::LineLevelDesc & msg, struct LineLevelDesc_s & obj);
		static ::proto_ff::LineLevelDesc* new_pbmsg(){ return new ::proto_ff::LineLevelDesc(); }
		static ::proto_ff::LineLevelDesc make_pbmsg(){ return ::proto_ff::LineLevelDesc(); }
	};
	typedef struct LineLevelDesc_s LineLevelDesc_t;

	struct Sheet_LineLevelDesc_s : public NFDescStoreSeqOP {
		Sheet_LineLevelDesc_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct LineLevelDesc_s, 100> LineLevelDesc_List;

		static void write_to_pbmsg(const struct Sheet_LineLevelDesc_s & obj, ::proto_ff::Sheet_LineLevelDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::Sheet_LineLevelDesc & msg, struct Sheet_LineLevelDesc_s & obj);
		static ::proto_ff::Sheet_LineLevelDesc* new_pbmsg(){ return new ::proto_ff::Sheet_LineLevelDesc(); }
		static ::proto_ff::Sheet_LineLevelDesc make_pbmsg(){ return ::proto_ff::Sheet_LineLevelDesc(); }
	};
	typedef struct Sheet_LineLevelDesc_s Sheet_LineLevelDesc_t;

	struct LineDeskInfoDesc_s : public NFDescStoreSeqOP {
		LineDeskInfoDesc_s();
		int CreateInit();
		int ResumeInit();
		int32_t id;
		int32_t RoomID;
		int32_t DeskID;
		int32_t AlgoID;
		int32_t DrawRate;

		static void write_to_pbmsg(const struct LineDeskInfoDesc_s & obj, ::proto_ff::LineDeskInfoDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::LineDeskInfoDesc & msg, struct LineDeskInfoDesc_s & obj);
		static ::proto_ff::LineDeskInfoDesc* new_pbmsg(){ return new ::proto_ff::LineDeskInfoDesc(); }
		static ::proto_ff::LineDeskInfoDesc make_pbmsg(){ return ::proto_ff::LineDeskInfoDesc(); }
	};
	typedef struct LineDeskInfoDesc_s LineDeskInfoDesc_t;

	struct Sheet_LineDeskInfoDesc_s : public NFDescStoreSeqOP {
		Sheet_LineDeskInfoDesc_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct LineDeskInfoDesc_s, 200> LineDeskInfoDesc_List;

		static void write_to_pbmsg(const struct Sheet_LineDeskInfoDesc_s & obj, ::proto_ff::Sheet_LineDeskInfoDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::Sheet_LineDeskInfoDesc & msg, struct Sheet_LineDeskInfoDesc_s & obj);
		static ::proto_ff::Sheet_LineDeskInfoDesc* new_pbmsg(){ return new ::proto_ff::Sheet_LineDeskInfoDesc(); }
		static ::proto_ff::Sheet_LineDeskInfoDesc make_pbmsg(){ return ::proto_ff::Sheet_LineDeskInfoDesc(); }
	};
	typedef struct Sheet_LineDeskInfoDesc_s Sheet_LineDeskInfoDesc_t;

	struct LineAlgoDesc_s : public NFDescStoreSeqOP {
		LineAlgoDesc_s();
		int CreateInit();
		int ResumeInit();
		int32_t AlgoID;
		NFSizeString<32> AlgoName;
		NFSizeString<32> AlgoDesc;
		int64_t Level_Chi5;
		int64_t Level_Chi4;
		int64_t Level_Chi3;
		int64_t Level_Chi2;
		int64_t Level_Chi1;
		int64_t Level_Fang1;
		int64_t Level_Fang2;
		int64_t Level_Fang3;
		int64_t Level_Fang4;
		int64_t Level_Fang5;
		NFSizeString<64> UserLuckSection;
		NFArray<int32_t, 5> VecUserLuckSection;
		NFSizeString<64> UserNewSection;
		NFArray<int32_t, 5> VecUserNewSection;
		NFSizeString<64> UserNewLuckVal;
		NFArray<int32_t, 5> VecUserNewLuckVal;
		NFSizeString<64> UserRechargeSection;
		NFArray<int32_t, 5> VecUserRechargeSection;
		NFSizeString<64> UserRechargeLuckyVal;
		NFArray<int32_t, 5> VecUserRechargeLuckyVal;
		int32_t UserLuceFlag;

		static void write_to_pbmsg(const struct LineAlgoDesc_s & obj, ::proto_ff::LineAlgoDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::LineAlgoDesc & msg, struct LineAlgoDesc_s & obj);
		static ::proto_ff::LineAlgoDesc* new_pbmsg(){ return new ::proto_ff::LineAlgoDesc(); }
		static ::proto_ff::LineAlgoDesc make_pbmsg(){ return ::proto_ff::LineAlgoDesc(); }
	};
	typedef struct LineAlgoDesc_s LineAlgoDesc_t;

	struct Sheet_LineAlgoDesc_s : public NFDescStoreSeqOP {
		Sheet_LineAlgoDesc_s();
		int CreateInit();
		int ResumeInit();
		NFArray<struct LineAlgoDesc_s, 10> LineAlgoDesc_List;

		static void write_to_pbmsg(const struct Sheet_LineAlgoDesc_s & obj, ::proto_ff::Sheet_LineAlgoDesc & msg);
		static void read_from_pbmsg(const ::proto_ff::Sheet_LineAlgoDesc & msg, struct Sheet_LineAlgoDesc_s & obj);
		static ::proto_ff::Sheet_LineAlgoDesc* new_pbmsg(){ return new ::proto_ff::Sheet_LineAlgoDesc(); }
		static ::proto_ff::Sheet_LineAlgoDesc make_pbmsg(){ return ::proto_ff::Sheet_LineAlgoDesc(); }
	};
	typedef struct Sheet_LineAlgoDesc_s Sheet_LineAlgoDesc_t;

}

