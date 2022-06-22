#include "FishResMeta_s.h"

namespace proto_ff_s {

FishLevelDesc_s::FishLevelDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishLevelDesc_s::CreateInit() {
	LevelID = (int32_t)0;
	MinMoney = (int32_t)0;
	MaxMoney = (int32_t)0;
	StartGame = (int32_t)0;
	Flag = (int32_t)0;
	return 0;
}

int FishLevelDesc_s::ResumeInit() {
	return 0;
}

void FishLevelDesc_s::write_to_pbmsg(const struct FishLevelDesc_s & obj, ::proto_ff::FishLevelDesc & msg) {
	msg.set_levelid((int32_t)obj.LevelID);
	msg.set_levelname((const char*)obj.LevelName.Get());
	msg.set_cannonlevelval((const char*)obj.CannonLevelVal.Get());
	for(int32_t i = 0; i < obj.VecCannonLevelVal.GetSize() && i < obj.VecCannonLevelVal.GetMaxSize(); ++i) {
		msg.add_veccannonlevelval((int32_t)obj.VecCannonLevelVal[i]);
	}
	msg.set_cannonshownum((const char*)obj.CannonShowNum.Get());
	for(int32_t i = 0; i < obj.VecCannonShowNum.GetSize() && i < obj.VecCannonShowNum.GetMaxSize(); ++i) {
		msg.add_veccannonshownum((int32_t)obj.VecCannonShowNum[i]);
	}
	msg.set_minmoney((int32_t)obj.MinMoney);
	msg.set_maxmoney((int32_t)obj.MaxMoney);
	msg.set_startgame((int32_t)obj.StartGame);
	msg.set_flag((int32_t)obj.Flag);
}

void FishLevelDesc_s::read_from_pbmsg(const ::proto_ff::FishLevelDesc & msg, struct FishLevelDesc_s & obj) {
	memset(&obj, 0, sizeof(struct FishLevelDesc_s));
	obj.LevelID = msg.levelid();
	obj.LevelName.Copy(msg.levelname());
	obj.CannonLevelVal.Copy(msg.cannonlevelval());
	obj.VecCannonLevelVal.SetSize(msg.veccannonlevelval_size() > obj.VecCannonLevelVal.GetMaxSize() ? obj.VecCannonLevelVal.GetMaxSize() : msg.veccannonlevelval_size());
	for(int32_t i = 0; i < obj.VecCannonLevelVal.GetSize(); ++i) {
		obj.VecCannonLevelVal[i] = msg.veccannonlevelval(i);
	}
	obj.CannonShowNum.Copy(msg.cannonshownum());
	obj.VecCannonShowNum.SetSize(msg.veccannonshownum_size() > obj.VecCannonShowNum.GetMaxSize() ? obj.VecCannonShowNum.GetMaxSize() : msg.veccannonshownum_size());
	for(int32_t i = 0; i < obj.VecCannonShowNum.GetSize(); ++i) {
		obj.VecCannonShowNum[i] = msg.veccannonshownum(i);
	}
	obj.MinMoney = msg.minmoney();
	obj.MaxMoney = msg.maxmoney();
	obj.StartGame = msg.startgame();
	obj.Flag = msg.flag();
}

Sheet_FishLevelDesc_s::Sheet_FishLevelDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Sheet_FishLevelDesc_s::CreateInit() {
	return 0;
}

int Sheet_FishLevelDesc_s::ResumeInit() {
	return 0;
}

void Sheet_FishLevelDesc_s::write_to_pbmsg(const struct Sheet_FishLevelDesc_s & obj, ::proto_ff::Sheet_FishLevelDesc & msg) {
	for(int32_t i = 0; i < obj.FishLevelDesc_List.GetSize() && i < obj.FishLevelDesc_List.GetMaxSize(); ++i) {
		::proto_ff::FishLevelDesc* temp_fishleveldesc_list = msg.add_fishleveldesc_list();
		FishLevelDesc_s::write_to_pbmsg(obj.FishLevelDesc_List[i], *temp_fishleveldesc_list);
	}
}

void Sheet_FishLevelDesc_s::read_from_pbmsg(const ::proto_ff::Sheet_FishLevelDesc & msg, struct Sheet_FishLevelDesc_s & obj) {
	memset(&obj, 0, sizeof(struct Sheet_FishLevelDesc_s));
	obj.FishLevelDesc_List.SetSize(msg.fishleveldesc_list_size() > obj.FishLevelDesc_List.GetMaxSize() ? obj.FishLevelDesc_List.GetMaxSize() : msg.fishleveldesc_list_size());
	for(int32_t i = 0; i < obj.FishLevelDesc_List.GetSize(); ++i) {
		const ::proto_ff::FishLevelDesc & temp_fishleveldesc_list = msg.fishleveldesc_list(i);
		FishLevelDesc_s::read_from_pbmsg(temp_fishleveldesc_list, obj.FishLevelDesc_List[i]);
	}
}

FishConfigDesc_s::FishConfigDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishConfigDesc_s::CreateInit() {
	fish_id = (int32_t)0;
	fish_type = (int32_t)0;
	build_fish_type = (int32_t)0;
	ratio_min = (int32_t)0;
	ratio_max = (int32_t)0;
	double_award_min_ratio = (int32_t)0;
	child_fish_count = (int32_t)0;
	damage_radius = (int32_t)0;
	return 0;
}

int FishConfigDesc_s::ResumeInit() {
	return 0;
}

void FishConfigDesc_s::write_to_pbmsg(const struct FishConfigDesc_s & obj, ::proto_ff::FishConfigDesc & msg) {
	msg.set_fish_id((int32_t)obj.fish_id);
	msg.set_fish_type((int32_t)obj.fish_type);
	msg.set_build_fish_type((int32_t)obj.build_fish_type);
	msg.set_ratio_min((int32_t)obj.ratio_min);
	msg.set_ratio_max((int32_t)obj.ratio_max);
	msg.set_double_award_min_ratio((int32_t)obj.double_award_min_ratio);
	msg.set_child_fish_count((int32_t)obj.child_fish_count);
	for(int32_t i = 0; i < obj.child_fish_ids.GetSize() && i < obj.child_fish_ids.GetMaxSize(); ++i) {
		msg.add_child_fish_ids((const char*)obj.child_fish_ids[i].Get());
	}
	msg.set_damage_radius((int32_t)obj.damage_radius);
	msg.set_damage_fish_ids((const char*)obj.damage_fish_ids.Get());
}

void FishConfigDesc_s::read_from_pbmsg(const ::proto_ff::FishConfigDesc & msg, struct FishConfigDesc_s & obj) {
	memset(&obj, 0, sizeof(struct FishConfigDesc_s));
	obj.fish_id = msg.fish_id();
	obj.fish_type = msg.fish_type();
	obj.build_fish_type = msg.build_fish_type();
	obj.ratio_min = msg.ratio_min();
	obj.ratio_max = msg.ratio_max();
	obj.double_award_min_ratio = msg.double_award_min_ratio();
	obj.child_fish_count = msg.child_fish_count();
	obj.child_fish_ids.SetSize(msg.child_fish_ids_size() > obj.child_fish_ids.GetMaxSize() ? obj.child_fish_ids.GetMaxSize() : msg.child_fish_ids_size());
	for(int32_t i = 0; i < obj.child_fish_ids.GetSize(); ++i) {
		obj.child_fish_ids[i].Copy(msg.child_fish_ids(i));
	}
	obj.damage_radius = msg.damage_radius();
	obj.damage_fish_ids.Copy(msg.damage_fish_ids());
}

Sheet_FishConfigDesc_s::Sheet_FishConfigDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Sheet_FishConfigDesc_s::CreateInit() {
	return 0;
}

int Sheet_FishConfigDesc_s::ResumeInit() {
	return 0;
}

void Sheet_FishConfigDesc_s::write_to_pbmsg(const struct Sheet_FishConfigDesc_s & obj, ::proto_ff::Sheet_FishConfigDesc & msg) {
	for(int32_t i = 0; i < obj.FishConfigDesc_List.GetSize() && i < obj.FishConfigDesc_List.GetMaxSize(); ++i) {
		::proto_ff::FishConfigDesc* temp_fishconfigdesc_list = msg.add_fishconfigdesc_list();
		FishConfigDesc_s::write_to_pbmsg(obj.FishConfigDesc_List[i], *temp_fishconfigdesc_list);
	}
}

void Sheet_FishConfigDesc_s::read_from_pbmsg(const ::proto_ff::Sheet_FishConfigDesc & msg, struct Sheet_FishConfigDesc_s & obj) {
	memset(&obj, 0, sizeof(struct Sheet_FishConfigDesc_s));
	obj.FishConfigDesc_List.SetSize(msg.fishconfigdesc_list_size() > obj.FishConfigDesc_List.GetMaxSize() ? obj.FishConfigDesc_List.GetMaxSize() : msg.fishconfigdesc_list_size());
	for(int32_t i = 0; i < obj.FishConfigDesc_List.GetSize(); ++i) {
		const ::proto_ff::FishConfigDesc & temp_fishconfigdesc_list = msg.fishconfigdesc_list(i);
		FishConfigDesc_s::read_from_pbmsg(temp_fishconfigdesc_list, obj.FishConfigDesc_List[i]);
	}
}

GunValueConfig_s::GunValueConfig_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int GunValueConfig_s::CreateInit() {
	id = (int32_t)0;
	value = (int32_t)0;
	room_id = (int32_t)0;
	gun_id = (int32_t)0;
	return 0;
}

int GunValueConfig_s::ResumeInit() {
	return 0;
}

void GunValueConfig_s::write_to_pbmsg(const struct GunValueConfig_s & obj, ::proto_ff::GunValueConfig & msg) {
	msg.set_id((int32_t)obj.id);
	msg.set_value((int32_t)obj.value);
	msg.set_room_id((int32_t)obj.room_id);
	msg.set_gun_id((int32_t)obj.gun_id);
}

void GunValueConfig_s::read_from_pbmsg(const ::proto_ff::GunValueConfig & msg, struct GunValueConfig_s & obj) {
	memset(&obj, 0, sizeof(struct GunValueConfig_s));
	obj.id = msg.id();
	obj.value = msg.value();
	obj.room_id = msg.room_id();
	obj.gun_id = msg.gun_id();
}

Sheet_GunValueConfig_s::Sheet_GunValueConfig_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Sheet_GunValueConfig_s::CreateInit() {
	return 0;
}

int Sheet_GunValueConfig_s::ResumeInit() {
	return 0;
}

void Sheet_GunValueConfig_s::write_to_pbmsg(const struct Sheet_GunValueConfig_s & obj, ::proto_ff::Sheet_GunValueConfig & msg) {
	for(int32_t i = 0; i < obj.GunValueConfig_List.GetSize() && i < obj.GunValueConfig_List.GetMaxSize(); ++i) {
		::proto_ff::GunValueConfig* temp_gunvalueconfig_list = msg.add_gunvalueconfig_list();
		GunValueConfig_s::write_to_pbmsg(obj.GunValueConfig_List[i], *temp_gunvalueconfig_list);
	}
}

void Sheet_GunValueConfig_s::read_from_pbmsg(const ::proto_ff::Sheet_GunValueConfig & msg, struct Sheet_GunValueConfig_s & obj) {
	memset(&obj, 0, sizeof(struct Sheet_GunValueConfig_s));
	obj.GunValueConfig_List.SetSize(msg.gunvalueconfig_list_size() > obj.GunValueConfig_List.GetMaxSize() ? obj.GunValueConfig_List.GetMaxSize() : msg.gunvalueconfig_list_size());
	for(int32_t i = 0; i < obj.GunValueConfig_List.GetSize(); ++i) {
		const ::proto_ff::GunValueConfig & temp_gunvalueconfig_list = msg.gunvalueconfig_list(i);
		GunValueConfig_s::read_from_pbmsg(temp_gunvalueconfig_list, obj.GunValueConfig_List[i]);
	}
}

FishAlgoDesc_s::FishAlgoDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishAlgoDesc_s::CreateInit() {
	AlgoID = (int32_t)0;
	GamePlatform = (int32_t)0;
	ChangeTimes = (int64_t)0;
	ChangeLiuShui = (int64_t)0;
	Chang1_RangeLow = (int64_t)0;
	Chang1_RangeHigh = (int64_t)0;
	Chang1_Chi1 = (int64_t)0;
	Chang1_Chi2 = (int64_t)0;
	Chang1_Chi3 = (int64_t)0;
	Chang1_Fang1 = (int64_t)0;
	Chang1_Fang2 = (int64_t)0;
	Chang1_Fang3 = (int64_t)0;
	Chang1_RateChi1 = (int64_t)0;
	Chang1_RateChi2 = (int64_t)0;
	Chang1_RateChi3 = (int64_t)0;
	Chang1_RatePing = (int64_t)0;
	Chang1_RateFang1 = (int64_t)0;
	Chang1_RateFang2 = (int64_t)0;
	Chang1_RateFang3 = (int64_t)0;
	Chang2_RangeLow = (int64_t)0;
	Chang2_RangeHigh = (int64_t)0;
	Chang2_Chi1 = (int64_t)0;
	Chang2_Chi2 = (int64_t)0;
	Chang2_Chi3 = (int64_t)0;
	Chang2_Fang1 = (int64_t)0;
	Chang2_Fang2 = (int64_t)0;
	Chang2_Fang3 = (int64_t)0;
	Chang2_RateChi1 = (int64_t)0;
	Chang2_RateChi2 = (int64_t)0;
	Chang2_RateChi3 = (int64_t)0;
	Chang2_RatePing = (int64_t)0;
	Chang2_RateFang1 = (int64_t)0;
	Chang2_RateFang2 = (int64_t)0;
	Chang2_RateFang3 = (int64_t)0;
	Chang3_RangeLow = (int64_t)0;
	Chang3_RangeHigh = (int64_t)0;
	Chang3_Chi1 = (int64_t)0;
	Chang3_Chi2 = (int64_t)0;
	Chang3_Chi3 = (int64_t)0;
	Chang3_Fang1 = (int64_t)0;
	Chang3_Fang2 = (int64_t)0;
	Chang3_Fang3 = (int64_t)0;
	Chang3_RateChi1 = (int64_t)0;
	Chang3_RateChi2 = (int64_t)0;
	Chang3_RateChi3 = (int64_t)0;
	Chang3_RatePing = (int64_t)0;
	Chang3_RateFang1 = (int64_t)0;
	Chang3_RateFang2 = (int64_t)0;
	Chang3_RateFang3 = (int64_t)0;
	Clear_MaxVal = (int64_t)0;
	Clear_Fang3Mul = (int64_t)0;
	Clear_Chi3Mul = (int32_t)0;
	Clear_InitShoot = (int32_t)0;
	Clear_InitCapture = (int32_t)0;
	Clear_InitDrawRate = (int32_t)0;
	Clear_InitPoolRate = (int32_t)0;
	Is_delete = (int32_t)0;
	FishAlgoType = (int32_t)0;
	return 0;
}

int FishAlgoDesc_s::ResumeInit() {
	return 0;
}

void FishAlgoDesc_s::write_to_pbmsg(const struct FishAlgoDesc_s & obj, ::proto_ff::FishAlgoDesc & msg) {
	msg.set_algoid((int32_t)obj.AlgoID);
	msg.set_gameplatform((int32_t)obj.GamePlatform);
	msg.set_algoname((const char*)obj.AlgoName.Get());
	msg.set_algodesc((const char*)obj.AlgoDesc.Get());
	msg.set_changetimes((int64_t)obj.ChangeTimes);
	msg.set_changeliushui((int64_t)obj.ChangeLiuShui);
	msg.set_chang1_rangelow((int64_t)obj.Chang1_RangeLow);
	msg.set_chang1_rangehigh((int64_t)obj.Chang1_RangeHigh);
	msg.set_chang1_chi1((int64_t)obj.Chang1_Chi1);
	msg.set_chang1_chi2((int64_t)obj.Chang1_Chi2);
	msg.set_chang1_chi3((int64_t)obj.Chang1_Chi3);
	msg.set_chang1_fang1((int64_t)obj.Chang1_Fang1);
	msg.set_chang1_fang2((int64_t)obj.Chang1_Fang2);
	msg.set_chang1_fang3((int64_t)obj.Chang1_Fang3);
	msg.set_chang1_ratechi1((int64_t)obj.Chang1_RateChi1);
	msg.set_chang1_ratechi2((int64_t)obj.Chang1_RateChi2);
	msg.set_chang1_ratechi3((int64_t)obj.Chang1_RateChi3);
	msg.set_chang1_rateping((int64_t)obj.Chang1_RatePing);
	msg.set_chang1_ratefang1((int64_t)obj.Chang1_RateFang1);
	msg.set_chang1_ratefang2((int64_t)obj.Chang1_RateFang2);
	msg.set_chang1_ratefang3((int64_t)obj.Chang1_RateFang3);
	msg.set_chang2_rangelow((int64_t)obj.Chang2_RangeLow);
	msg.set_chang2_rangehigh((int64_t)obj.Chang2_RangeHigh);
	msg.set_chang2_chi1((int64_t)obj.Chang2_Chi1);
	msg.set_chang2_chi2((int64_t)obj.Chang2_Chi2);
	msg.set_chang2_chi3((int64_t)obj.Chang2_Chi3);
	msg.set_chang2_fang1((int64_t)obj.Chang2_Fang1);
	msg.set_chang2_fang2((int64_t)obj.Chang2_Fang2);
	msg.set_chang2_fang3((int64_t)obj.Chang2_Fang3);
	msg.set_chang2_ratechi1((int64_t)obj.Chang2_RateChi1);
	msg.set_chang2_ratechi2((int64_t)obj.Chang2_RateChi2);
	msg.set_chang2_ratechi3((int64_t)obj.Chang2_RateChi3);
	msg.set_chang2_rateping((int64_t)obj.Chang2_RatePing);
	msg.set_chang2_ratefang1((int64_t)obj.Chang2_RateFang1);
	msg.set_chang2_ratefang2((int64_t)obj.Chang2_RateFang2);
	msg.set_chang2_ratefang3((int64_t)obj.Chang2_RateFang3);
	msg.set_chang3_rangelow((int64_t)obj.Chang3_RangeLow);
	msg.set_chang3_rangehigh((int64_t)obj.Chang3_RangeHigh);
	msg.set_chang3_chi1((int64_t)obj.Chang3_Chi1);
	msg.set_chang3_chi2((int64_t)obj.Chang3_Chi2);
	msg.set_chang3_chi3((int64_t)obj.Chang3_Chi3);
	msg.set_chang3_fang1((int64_t)obj.Chang3_Fang1);
	msg.set_chang3_fang2((int64_t)obj.Chang3_Fang2);
	msg.set_chang3_fang3((int64_t)obj.Chang3_Fang3);
	msg.set_chang3_ratechi1((int64_t)obj.Chang3_RateChi1);
	msg.set_chang3_ratechi2((int64_t)obj.Chang3_RateChi2);
	msg.set_chang3_ratechi3((int64_t)obj.Chang3_RateChi3);
	msg.set_chang3_rateping((int64_t)obj.Chang3_RatePing);
	msg.set_chang3_ratefang1((int64_t)obj.Chang3_RateFang1);
	msg.set_chang3_ratefang2((int64_t)obj.Chang3_RateFang2);
	msg.set_chang3_ratefang3((int64_t)obj.Chang3_RateFang3);
	msg.set_clear_maxval((int64_t)obj.Clear_MaxVal);
	msg.set_clear_fang3mul((int64_t)obj.Clear_Fang3Mul);
	msg.set_clear_chi3mul((int32_t)obj.Clear_Chi3Mul);
	msg.set_clear_initshoot((int32_t)obj.Clear_InitShoot);
	msg.set_clear_initcapture((int32_t)obj.Clear_InitCapture);
	msg.set_clear_initdrawrate((int32_t)obj.Clear_InitDrawRate);
	msg.set_clear_initpoolrate((int32_t)obj.Clear_InitPoolRate);
	msg.set_is_delete((int32_t)obj.Is_delete);
	msg.set_fishalgotype((int32_t)obj.FishAlgoType);
}

void FishAlgoDesc_s::read_from_pbmsg(const ::proto_ff::FishAlgoDesc & msg, struct FishAlgoDesc_s & obj) {
	memset(&obj, 0, sizeof(struct FishAlgoDesc_s));
	obj.AlgoID = msg.algoid();
	obj.GamePlatform = msg.gameplatform();
	obj.AlgoName.Copy(msg.algoname());
	obj.AlgoDesc.Copy(msg.algodesc());
	obj.ChangeTimes = msg.changetimes();
	obj.ChangeLiuShui = msg.changeliushui();
	obj.Chang1_RangeLow = msg.chang1_rangelow();
	obj.Chang1_RangeHigh = msg.chang1_rangehigh();
	obj.Chang1_Chi1 = msg.chang1_chi1();
	obj.Chang1_Chi2 = msg.chang1_chi2();
	obj.Chang1_Chi3 = msg.chang1_chi3();
	obj.Chang1_Fang1 = msg.chang1_fang1();
	obj.Chang1_Fang2 = msg.chang1_fang2();
	obj.Chang1_Fang3 = msg.chang1_fang3();
	obj.Chang1_RateChi1 = msg.chang1_ratechi1();
	obj.Chang1_RateChi2 = msg.chang1_ratechi2();
	obj.Chang1_RateChi3 = msg.chang1_ratechi3();
	obj.Chang1_RatePing = msg.chang1_rateping();
	obj.Chang1_RateFang1 = msg.chang1_ratefang1();
	obj.Chang1_RateFang2 = msg.chang1_ratefang2();
	obj.Chang1_RateFang3 = msg.chang1_ratefang3();
	obj.Chang2_RangeLow = msg.chang2_rangelow();
	obj.Chang2_RangeHigh = msg.chang2_rangehigh();
	obj.Chang2_Chi1 = msg.chang2_chi1();
	obj.Chang2_Chi2 = msg.chang2_chi2();
	obj.Chang2_Chi3 = msg.chang2_chi3();
	obj.Chang2_Fang1 = msg.chang2_fang1();
	obj.Chang2_Fang2 = msg.chang2_fang2();
	obj.Chang2_Fang3 = msg.chang2_fang3();
	obj.Chang2_RateChi1 = msg.chang2_ratechi1();
	obj.Chang2_RateChi2 = msg.chang2_ratechi2();
	obj.Chang2_RateChi3 = msg.chang2_ratechi3();
	obj.Chang2_RatePing = msg.chang2_rateping();
	obj.Chang2_RateFang1 = msg.chang2_ratefang1();
	obj.Chang2_RateFang2 = msg.chang2_ratefang2();
	obj.Chang2_RateFang3 = msg.chang2_ratefang3();
	obj.Chang3_RangeLow = msg.chang3_rangelow();
	obj.Chang3_RangeHigh = msg.chang3_rangehigh();
	obj.Chang3_Chi1 = msg.chang3_chi1();
	obj.Chang3_Chi2 = msg.chang3_chi2();
	obj.Chang3_Chi3 = msg.chang3_chi3();
	obj.Chang3_Fang1 = msg.chang3_fang1();
	obj.Chang3_Fang2 = msg.chang3_fang2();
	obj.Chang3_Fang3 = msg.chang3_fang3();
	obj.Chang3_RateChi1 = msg.chang3_ratechi1();
	obj.Chang3_RateChi2 = msg.chang3_ratechi2();
	obj.Chang3_RateChi3 = msg.chang3_ratechi3();
	obj.Chang3_RatePing = msg.chang3_rateping();
	obj.Chang3_RateFang1 = msg.chang3_ratefang1();
	obj.Chang3_RateFang2 = msg.chang3_ratefang2();
	obj.Chang3_RateFang3 = msg.chang3_ratefang3();
	obj.Clear_MaxVal = msg.clear_maxval();
	obj.Clear_Fang3Mul = msg.clear_fang3mul();
	obj.Clear_Chi3Mul = msg.clear_chi3mul();
	obj.Clear_InitShoot = msg.clear_initshoot();
	obj.Clear_InitCapture = msg.clear_initcapture();
	obj.Clear_InitDrawRate = msg.clear_initdrawrate();
	obj.Clear_InitPoolRate = msg.clear_initpoolrate();
	obj.Is_delete = msg.is_delete();
	obj.FishAlgoType = msg.fishalgotype();
}

Sheet_FishAlgoDesc_s::Sheet_FishAlgoDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Sheet_FishAlgoDesc_s::CreateInit() {
	return 0;
}

int Sheet_FishAlgoDesc_s::ResumeInit() {
	return 0;
}

void Sheet_FishAlgoDesc_s::write_to_pbmsg(const struct Sheet_FishAlgoDesc_s & obj, ::proto_ff::Sheet_FishAlgoDesc & msg) {
	for(int32_t i = 0; i < obj.FishAlgoDesc_List.GetSize() && i < obj.FishAlgoDesc_List.GetMaxSize(); ++i) {
		::proto_ff::FishAlgoDesc* temp_fishalgodesc_list = msg.add_fishalgodesc_list();
		FishAlgoDesc_s::write_to_pbmsg(obj.FishAlgoDesc_List[i], *temp_fishalgodesc_list);
	}
}

void Sheet_FishAlgoDesc_s::read_from_pbmsg(const ::proto_ff::Sheet_FishAlgoDesc & msg, struct Sheet_FishAlgoDesc_s & obj) {
	memset(&obj, 0, sizeof(struct Sheet_FishAlgoDesc_s));
	obj.FishAlgoDesc_List.SetSize(msg.fishalgodesc_list_size() > obj.FishAlgoDesc_List.GetMaxSize() ? obj.FishAlgoDesc_List.GetMaxSize() : msg.fishalgodesc_list_size());
	for(int32_t i = 0; i < obj.FishAlgoDesc_List.GetSize(); ++i) {
		const ::proto_ff::FishAlgoDesc & temp_fishalgodesc_list = msg.fishalgodesc_list(i);
		FishAlgoDesc_s::read_from_pbmsg(temp_fishalgodesc_list, obj.FishAlgoDesc_List[i]);
	}
}

UserDeskAlgoInfo_s::UserDeskAlgoInfo_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int UserDeskAlgoInfo_s::CreateInit() {
	AlgoID = (int32_t)0;
	DrawRate = (float)0;
	CurTotalShoot = (double)0;
	CurTotalCapture = (double)0;
	CurAlgoChang = (int64_t)0;
	CurAlgoStatus = (int64_t)0;
	return 0;
}

int UserDeskAlgoInfo_s::ResumeInit() {
	return 0;
}

void UserDeskAlgoInfo_s::write_to_pbmsg(const struct UserDeskAlgoInfo_s & obj, ::proto_ff::UserDeskAlgoInfo & msg) {
	msg.set_algoid((int32_t)obj.AlgoID);
	msg.set_drawrate((float)obj.DrawRate);
	msg.set_curtotalshoot((double)obj.CurTotalShoot);
	msg.set_curtotalcapture((double)obj.CurTotalCapture);
	msg.set_curalgochang((int64_t)obj.CurAlgoChang);
	msg.set_curalgostatus((int64_t)obj.CurAlgoStatus);
}

void UserDeskAlgoInfo_s::read_from_pbmsg(const ::proto_ff::UserDeskAlgoInfo & msg, struct UserDeskAlgoInfo_s & obj) {
	memset(&obj, 0, sizeof(struct UserDeskAlgoInfo_s));
	obj.AlgoID = msg.algoid();
	obj.DrawRate = msg.drawrate();
	obj.CurTotalShoot = msg.curtotalshoot();
	obj.CurTotalCapture = msg.curtotalcapture();
	obj.CurAlgoChang = msg.curalgochang();
	obj.CurAlgoStatus = msg.curalgostatus();
}

DeskInfoDesc_s::DeskInfoDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int DeskInfoDesc_s::CreateInit() {
	id = (int32_t)0;
	RoomID = (int32_t)0;
	DeskID = (int32_t)0;
	AlgoType = (int32_t)0;
	GameLevel = (int32_t)0;
	YValueA = (int64_t)0;
	YValueB = (int64_t)0;
	FreePool = (int64_t)0;
	YValue = (int64_t)0;
	return 0;
}

int DeskInfoDesc_s::ResumeInit() {
	return 0;
}

void DeskInfoDesc_s::write_to_pbmsg(const struct DeskInfoDesc_s & obj, ::proto_ff::DeskInfoDesc & msg) {
	msg.set_id((int32_t)obj.id);
	msg.set_roomid((int32_t)obj.RoomID);
	msg.set_deskid((int32_t)obj.DeskID);
	msg.set_algotype((int32_t)obj.AlgoType);
	for(int32_t i = 0; i < obj.AlgoData.GetSize() && i < obj.AlgoData.GetMaxSize(); ++i) {
		::proto_ff::UserDeskAlgoInfo* temp_algodata = msg.add_algodata();
		UserDeskAlgoInfo_s::write_to_pbmsg(obj.AlgoData[i], *temp_algodata);
	}
	msg.set_gamelevel((int32_t)obj.GameLevel);
	msg.set_yvaluea((int64_t)obj.YValueA);
	msg.set_yvalueb((int64_t)obj.YValueB);
	msg.set_freepool((int64_t)obj.FreePool);
	msg.set_yvalue((int64_t)obj.YValue);
}

void DeskInfoDesc_s::read_from_pbmsg(const ::proto_ff::DeskInfoDesc & msg, struct DeskInfoDesc_s & obj) {
	memset(&obj, 0, sizeof(struct DeskInfoDesc_s));
	obj.id = msg.id();
	obj.RoomID = msg.roomid();
	obj.DeskID = msg.deskid();
	obj.AlgoType = msg.algotype();
	obj.AlgoData.SetSize(msg.algodata_size() > obj.AlgoData.GetMaxSize() ? obj.AlgoData.GetMaxSize() : msg.algodata_size());
	for(int32_t i = 0; i < obj.AlgoData.GetSize(); ++i) {
		const ::proto_ff::UserDeskAlgoInfo & temp_algodata = msg.algodata(i);
		UserDeskAlgoInfo_s::read_from_pbmsg(temp_algodata, obj.AlgoData[i]);
	}
	obj.GameLevel = msg.gamelevel();
	obj.YValueA = msg.yvaluea();
	obj.YValueB = msg.yvalueb();
	obj.FreePool = msg.freepool();
	obj.YValue = msg.yvalue();
}

Sheet_DeskInfoDesc_s::Sheet_DeskInfoDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Sheet_DeskInfoDesc_s::CreateInit() {
	return 0;
}

int Sheet_DeskInfoDesc_s::ResumeInit() {
	return 0;
}

void Sheet_DeskInfoDesc_s::write_to_pbmsg(const struct Sheet_DeskInfoDesc_s & obj, ::proto_ff::Sheet_DeskInfoDesc & msg) {
	for(int32_t i = 0; i < obj.DeskInfoDesc_List.GetSize() && i < obj.DeskInfoDesc_List.GetMaxSize(); ++i) {
		::proto_ff::DeskInfoDesc* temp_deskinfodesc_list = msg.add_deskinfodesc_list();
		DeskInfoDesc_s::write_to_pbmsg(obj.DeskInfoDesc_List[i], *temp_deskinfodesc_list);
	}
}

void Sheet_DeskInfoDesc_s::read_from_pbmsg(const ::proto_ff::Sheet_DeskInfoDesc & msg, struct Sheet_DeskInfoDesc_s & obj) {
	memset(&obj, 0, sizeof(struct Sheet_DeskInfoDesc_s));
	obj.DeskInfoDesc_List.SetSize(msg.deskinfodesc_list_size() > obj.DeskInfoDesc_List.GetMaxSize() ? obj.DeskInfoDesc_List.GetMaxSize() : msg.deskinfodesc_list_size());
	for(int32_t i = 0; i < obj.DeskInfoDesc_List.GetSize(); ++i) {
		const ::proto_ff::DeskInfoDesc & temp_deskinfodesc_list = msg.deskinfodesc_list(i);
		DeskInfoDesc_s::read_from_pbmsg(temp_deskinfodesc_list, obj.DeskInfoDesc_List[i]);
	}
}

FishInitPoolData_s::FishInitPoolData_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishInitPoolData_s::CreateInit() {
	fish_id = (int32_t)0;
	num = (int32_t)0;
	return 0;
}

int FishInitPoolData_s::ResumeInit() {
	return 0;
}

void FishInitPoolData_s::write_to_pbmsg(const struct FishInitPoolData_s & obj, ::proto_ff::FishInitPoolData & msg) {
	msg.set_fish_id((int32_t)obj.fish_id);
	msg.set_num((int32_t)obj.num);
}

void FishInitPoolData_s::read_from_pbmsg(const ::proto_ff::FishInitPoolData & msg, struct FishInitPoolData_s & obj) {
	memset(&obj, 0, sizeof(struct FishInitPoolData_s));
	obj.fish_id = msg.fish_id();
	obj.num = msg.num();
}

FishInitPool_s::FishInitPool_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishInitPool_s::CreateInit() {
	return 0;
}

int FishInitPool_s::ResumeInit() {
	return 0;
}

void FishInitPool_s::write_to_pbmsg(const struct FishInitPool_s & obj, ::proto_ff::FishInitPool & msg) {
	for(int32_t i = 0; i < obj.InitPoolCount.GetSize() && i < obj.InitPoolCount.GetMaxSize(); ++i) {
		::proto_ff::FishInitPoolData* temp_initpoolcount = msg.add_initpoolcount();
		FishInitPoolData_s::write_to_pbmsg(obj.InitPoolCount[i], *temp_initpoolcount);
	}
}

void FishInitPool_s::read_from_pbmsg(const ::proto_ff::FishInitPool & msg, struct FishInitPool_s & obj) {
	memset(&obj, 0, sizeof(struct FishInitPool_s));
	obj.InitPoolCount.SetSize(msg.initpoolcount_size() > obj.InitPoolCount.GetMaxSize() ? obj.InitPoolCount.GetMaxSize() : msg.initpoolcount_size());
	for(int32_t i = 0; i < obj.InitPoolCount.GetSize(); ++i) {
		const ::proto_ff::FishInitPoolData & temp_initpoolcount = msg.initpoolcount(i);
		FishInitPoolData_s::read_from_pbmsg(temp_initpoolcount, obj.InitPoolCount[i]);
	}
}

SeatDangRange_B_s::SeatDangRange_B_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int SeatDangRange_B_s::CreateInit() {
	return 0;
}

int SeatDangRange_B_s::ResumeInit() {
	return 0;
}

void SeatDangRange_B_s::write_to_pbmsg(const struct SeatDangRange_B_s & obj, ::proto_ff::SeatDangRange_B & msg) {
	for(int32_t i = 0; i < obj.value.GetSize() && i < obj.value.GetMaxSize(); ++i) {
		msg.add_value((int64_t)obj.value[i]);
	}
}

void SeatDangRange_B_s::read_from_pbmsg(const ::proto_ff::SeatDangRange_B & msg, struct SeatDangRange_B_s & obj) {
	memset(&obj, 0, sizeof(struct SeatDangRange_B_s));
	obj.value.SetSize(msg.value_size() > obj.value.GetMaxSize() ? obj.value.GetMaxSize() : msg.value_size());
	for(int32_t i = 0; i < obj.value.GetSize(); ++i) {
		obj.value[i] = msg.value(i);
	}
}

SeatAlgoSetup_s::SeatAlgoSetup_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int SeatAlgoSetup_s::CreateInit() {
	SeatCtrlIsOpen = (int32_t)0;
	ClearDataMaxVal = (int64_t)0;
	ClearDataFangCondation = (double)0;
	ClearDataChiCondation = (double)0;
	return 0;
}

int SeatAlgoSetup_s::ResumeInit() {
	return 0;
}

void SeatAlgoSetup_s::write_to_pbmsg(const struct SeatAlgoSetup_s & obj, ::proto_ff::SeatAlgoSetup & msg) {
	msg.set_seatctrlisopen((int32_t)obj.SeatCtrlIsOpen);
	for(int32_t i = 0; i < obj.SeatDangRange_Def_A.GetSize() && i < obj.SeatDangRange_Def_A.GetMaxSize(); ++i) {
		msg.add_seatdangrange_def_a((int64_t)obj.SeatDangRange_Def_A[i]);
	}
	for(int32_t i = 0; i < obj.SeatDangRange_Def_B.GetSize() && i < obj.SeatDangRange_Def_B.GetMaxSize(); ++i) {
		msg.add_seatdangrange_def_b((int64_t)obj.SeatDangRange_Def_B[i]);
	}
	for(int32_t i = 0; i < obj.SeatDangRange_Def_Robot.GetSize() && i < obj.SeatDangRange_Def_Robot.GetMaxSize(); ++i) {
		msg.add_seatdangrange_def_robot((int64_t)obj.SeatDangRange_Def_Robot[i]);
	}
	for(int32_t i = 0; i < obj.SeatDangRange_B.GetSize() && i < obj.SeatDangRange_B.GetMaxSize(); ++i) {
		::proto_ff::SeatDangRange_B* temp_seatdangrange_b = msg.add_seatdangrange_b();
		SeatDangRange_B_s::write_to_pbmsg(obj.SeatDangRange_B[i], *temp_seatdangrange_b);
	}
	msg.set_cleardatamaxval((int64_t)obj.ClearDataMaxVal);
	msg.set_cleardatafangcondation((double)obj.ClearDataFangCondation);
	msg.set_cleardatachicondation((double)obj.ClearDataChiCondation);
}

void SeatAlgoSetup_s::read_from_pbmsg(const ::proto_ff::SeatAlgoSetup & msg, struct SeatAlgoSetup_s & obj) {
	memset(&obj, 0, sizeof(struct SeatAlgoSetup_s));
	obj.SeatCtrlIsOpen = msg.seatctrlisopen();
	obj.SeatDangRange_Def_A.SetSize(msg.seatdangrange_def_a_size() > obj.SeatDangRange_Def_A.GetMaxSize() ? obj.SeatDangRange_Def_A.GetMaxSize() : msg.seatdangrange_def_a_size());
	for(int32_t i = 0; i < obj.SeatDangRange_Def_A.GetSize(); ++i) {
		obj.SeatDangRange_Def_A[i] = msg.seatdangrange_def_a(i);
	}
	obj.SeatDangRange_Def_B.SetSize(msg.seatdangrange_def_b_size() > obj.SeatDangRange_Def_B.GetMaxSize() ? obj.SeatDangRange_Def_B.GetMaxSize() : msg.seatdangrange_def_b_size());
	for(int32_t i = 0; i < obj.SeatDangRange_Def_B.GetSize(); ++i) {
		obj.SeatDangRange_Def_B[i] = msg.seatdangrange_def_b(i);
	}
	obj.SeatDangRange_Def_Robot.SetSize(msg.seatdangrange_def_robot_size() > obj.SeatDangRange_Def_Robot.GetMaxSize() ? obj.SeatDangRange_Def_Robot.GetMaxSize() : msg.seatdangrange_def_robot_size());
	for(int32_t i = 0; i < obj.SeatDangRange_Def_Robot.GetSize(); ++i) {
		obj.SeatDangRange_Def_Robot[i] = msg.seatdangrange_def_robot(i);
	}
	obj.SeatDangRange_B.SetSize(msg.seatdangrange_b_size() > obj.SeatDangRange_B.GetMaxSize() ? obj.SeatDangRange_B.GetMaxSize() : msg.seatdangrange_b_size());
	for(int32_t i = 0; i < obj.SeatDangRange_B.GetSize(); ++i) {
		const ::proto_ff::SeatDangRange_B & temp_seatdangrange_b = msg.seatdangrange_b(i);
		SeatDangRange_B_s::read_from_pbmsg(temp_seatdangrange_b, obj.SeatDangRange_B[i]);
	}
	obj.ClearDataMaxVal = msg.cleardatamaxval();
	obj.ClearDataFangCondation = msg.cleardatafangcondation();
	obj.ClearDataChiCondation = msg.cleardatachicondation();
}

HuanDangRange_s::HuanDangRange_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int HuanDangRange_s::CreateInit() {
	return 0;
}

int HuanDangRange_s::ResumeInit() {
	return 0;
}

void HuanDangRange_s::write_to_pbmsg(const struct HuanDangRange_s & obj, ::proto_ff::HuanDangRange & msg) {
	for(int32_t i = 0; i < obj.value.GetSize() && i < obj.value.GetMaxSize(); ++i) {
		msg.add_value((int64_t)obj.value[i]);
	}
}

void HuanDangRange_s::read_from_pbmsg(const ::proto_ff::HuanDangRange & msg, struct HuanDangRange_s & obj) {
	memset(&obj, 0, sizeof(struct HuanDangRange_s));
	obj.value.SetSize(msg.value_size() > obj.value.GetMaxSize() ? obj.value.GetMaxSize() : msg.value_size());
	for(int32_t i = 0; i < obj.value.GetSize(); ++i) {
		obj.value[i] = msg.value(i);
	}
}

DangChiRange_s::DangChiRange_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int DangChiRange_s::CreateInit() {
	return 0;
}

int DangChiRange_s::ResumeInit() {
	return 0;
}

void DangChiRange_s::write_to_pbmsg(const struct DangChiRange_s & obj, ::proto_ff::DangChiRange & msg) {
	for(int32_t i = 0; i < obj.value.GetSize() && i < obj.value.GetMaxSize(); ++i) {
		msg.add_value((int64_t)obj.value[i]);
	}
}

void DangChiRange_s::read_from_pbmsg(const ::proto_ff::DangChiRange & msg, struct DangChiRange_s & obj) {
	memset(&obj, 0, sizeof(struct DangChiRange_s));
	obj.value.SetSize(msg.value_size() > obj.value.GetMaxSize() ? obj.value.GetMaxSize() : msg.value_size());
	for(int32_t i = 0; i < obj.value.GetSize(); ++i) {
		obj.value[i] = msg.value(i);
	}
}

FishAlgorithmSetup_s::FishAlgorithmSetup_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishAlgorithmSetup_s::CreateInit() {
	HuanChangTimes = (int64_t)0;
	HuanBiaoLiuShuiVal = (int64_t)0;
	PoolInitBFB = (int64_t)0;
	ClearDataMaxVal = (int64_t)0;
	ClearDataFangCondation = (double)0;
	ClearDataChiCondation = (double)0;
	ClearDataInitShoot = (int64_t)0;
	ClearDataInitCapture = (int64_t)0;
	ClearDataInitDrawRate = (double)0;
	return 0;
}

int FishAlgorithmSetup_s::ResumeInit() {
	return 0;
}

void FishAlgorithmSetup_s::write_to_pbmsg(const struct FishAlgorithmSetup_s & obj, ::proto_ff::FishAlgorithmSetup & msg) {
	msg.set_huanchangtimes((int64_t)obj.HuanChangTimes);
	for(int32_t i = 0; i < obj.HuanDangRange.GetSize() && i < obj.HuanDangRange.GetMaxSize(); ++i) {
		::proto_ff::HuanDangRange* temp_huandangrange = msg.add_huandangrange();
		HuanDangRange_s::write_to_pbmsg(obj.HuanDangRange[i], *temp_huandangrange);
	}
	for(int32_t i = 0; i < obj.DangChiRange.GetSize() && i < obj.DangChiRange.GetMaxSize(); ++i) {
		::proto_ff::DangChiRange* temp_dangchirange = msg.add_dangchirange();
		DangChiRange_s::write_to_pbmsg(obj.DangChiRange[i], *temp_dangchirange);
	}
	msg.set_huanbiaoliushuival((int64_t)obj.HuanBiaoLiuShuiVal);
	msg.set_poolinitbfb((int64_t)obj.PoolInitBFB);
	msg.set_cleardatamaxval((int64_t)obj.ClearDataMaxVal);
	msg.set_cleardatafangcondation((double)obj.ClearDataFangCondation);
	msg.set_cleardatachicondation((double)obj.ClearDataChiCondation);
	msg.set_cleardatainitshoot((int64_t)obj.ClearDataInitShoot);
	msg.set_cleardatainitcapture((int64_t)obj.ClearDataInitCapture);
	msg.set_cleardatainitdrawrate((double)obj.ClearDataInitDrawRate);
}

void FishAlgorithmSetup_s::read_from_pbmsg(const ::proto_ff::FishAlgorithmSetup & msg, struct FishAlgorithmSetup_s & obj) {
	memset(&obj, 0, sizeof(struct FishAlgorithmSetup_s));
	obj.HuanChangTimes = msg.huanchangtimes();
	obj.HuanDangRange.SetSize(msg.huandangrange_size() > obj.HuanDangRange.GetMaxSize() ? obj.HuanDangRange.GetMaxSize() : msg.huandangrange_size());
	for(int32_t i = 0; i < obj.HuanDangRange.GetSize(); ++i) {
		const ::proto_ff::HuanDangRange & temp_huandangrange = msg.huandangrange(i);
		HuanDangRange_s::read_from_pbmsg(temp_huandangrange, obj.HuanDangRange[i]);
	}
	obj.DangChiRange.SetSize(msg.dangchirange_size() > obj.DangChiRange.GetMaxSize() ? obj.DangChiRange.GetMaxSize() : msg.dangchirange_size());
	for(int32_t i = 0; i < obj.DangChiRange.GetSize(); ++i) {
		const ::proto_ff::DangChiRange & temp_dangchirange = msg.dangchirange(i);
		DangChiRange_s::read_from_pbmsg(temp_dangchirange, obj.DangChiRange[i]);
	}
	obj.HuanBiaoLiuShuiVal = msg.huanbiaoliushuival();
	obj.PoolInitBFB = msg.poolinitbfb();
	obj.ClearDataMaxVal = msg.cleardatamaxval();
	obj.ClearDataFangCondation = msg.cleardatafangcondation();
	obj.ClearDataChiCondation = msg.cleardatachicondation();
	obj.ClearDataInitShoot = msg.cleardatainitshoot();
	obj.ClearDataInitCapture = msg.cleardatainitcapture();
	obj.ClearDataInitDrawRate = msg.cleardatainitdrawrate();
}

FishAlgorithmFileName_s::FishAlgorithmFileName_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishAlgorithmFileName_s::CreateInit() {
	return 0;
}

int FishAlgorithmFileName_s::ResumeInit() {
	return 0;
}

void FishAlgorithmFileName_s::write_to_pbmsg(const struct FishAlgorithmFileName_s & obj, ::proto_ff::FishAlgorithmFileName & msg) {
	msg.set_filenamechi1((const char*)obj.FileNameChi1.Get());
	msg.set_filenamechi2((const char*)obj.FileNameChi2.Get());
	msg.set_filenamechi5((const char*)obj.FileNameChi5.Get());
	msg.set_filenamechi10((const char*)obj.FileNameChi10.Get());
	msg.set_filenamechi20((const char*)obj.FileNameChi20.Get());
	msg.set_filenamechi50((const char*)obj.FileNameChi50.Get());
	msg.set_filenamechi100((const char*)obj.FileNameChi100.Get());
	msg.set_filenamechi200((const char*)obj.FileNameChi200.Get());
	msg.set_filenamefang1((const char*)obj.FileNameFang1.Get());
	msg.set_filenamefang2((const char*)obj.FileNameFang2.Get());
	msg.set_filenamefang5((const char*)obj.FileNameFang5.Get());
	msg.set_filenamefang10((const char*)obj.FileNameFang10.Get());
	msg.set_filenamefang20((const char*)obj.FileNameFang20.Get());
	msg.set_filenamefang50((const char*)obj.FileNameFang50.Get());
	msg.set_filenamefang100((const char*)obj.FileNameFang100.Get());
	msg.set_filenamefang200((const char*)obj.FileNameFang200.Get());
}

void FishAlgorithmFileName_s::read_from_pbmsg(const ::proto_ff::FishAlgorithmFileName & msg, struct FishAlgorithmFileName_s & obj) {
	memset(&obj, 0, sizeof(struct FishAlgorithmFileName_s));
	obj.FileNameChi1.Copy(msg.filenamechi1());
	obj.FileNameChi2.Copy(msg.filenamechi2());
	obj.FileNameChi5.Copy(msg.filenamechi5());
	obj.FileNameChi10.Copy(msg.filenamechi10());
	obj.FileNameChi20.Copy(msg.filenamechi20());
	obj.FileNameChi50.Copy(msg.filenamechi50());
	obj.FileNameChi100.Copy(msg.filenamechi100());
	obj.FileNameChi200.Copy(msg.filenamechi200());
	obj.FileNameFang1.Copy(msg.filenamefang1());
	obj.FileNameFang2.Copy(msg.filenamefang2());
	obj.FileNameFang5.Copy(msg.filenamefang5());
	obj.FileNameFang10.Copy(msg.filenamefang10());
	obj.FileNameFang20.Copy(msg.filenamefang20());
	obj.FileNameFang50.Copy(msg.filenamefang50());
	obj.FileNameFang100.Copy(msg.filenamefang100());
	obj.FileNameFang200.Copy(msg.filenamefang200());
}

FishAlgorithmCsvItem_s::FishAlgorithmCsvItem_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishAlgorithmCsvItem_s::CreateInit() {
	return 0;
}

int FishAlgorithmCsvItem_s::ResumeInit() {
	return 0;
}

void FishAlgorithmCsvItem_s::write_to_pbmsg(const struct FishAlgorithmCsvItem_s & obj, ::proto_ff::FishAlgorithmCsvItem & msg) {
	for(int32_t i = 0; i < obj.value.GetSize() && i < obj.value.GetMaxSize(); ++i) {
		msg.add_value((int32_t)obj.value[i]);
	}
}

void FishAlgorithmCsvItem_s::read_from_pbmsg(const ::proto_ff::FishAlgorithmCsvItem & msg, struct FishAlgorithmCsvItem_s & obj) {
	memset(&obj, 0, sizeof(struct FishAlgorithmCsvItem_s));
	obj.value.SetSize(msg.value_size() > obj.value.GetMaxSize() ? obj.value.GetMaxSize() : msg.value_size());
	for(int32_t i = 0; i < obj.value.GetSize(); ++i) {
		obj.value[i] = msg.value(i);
	}
}

FishAlgorithmCsv_s::FishAlgorithmCsv_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishAlgorithmCsv_s::CreateInit() {
	return 0;
}

int FishAlgorithmCsv_s::ResumeInit() {
	return 0;
}

void FishAlgorithmCsv_s::write_to_pbmsg(const struct FishAlgorithmCsv_s & obj, ::proto_ff::FishAlgorithmCsv & msg) {
	for(int32_t i = 0; i < obj.item.GetSize() && i < obj.item.GetMaxSize(); ++i) {
		::proto_ff::FishAlgorithmCsvItem* temp_item = msg.add_item();
		FishAlgorithmCsvItem_s::write_to_pbmsg(obj.item[i], *temp_item);
	}
}

void FishAlgorithmCsv_s::read_from_pbmsg(const ::proto_ff::FishAlgorithmCsv & msg, struct FishAlgorithmCsv_s & obj) {
	memset(&obj, 0, sizeof(struct FishAlgorithmCsv_s));
	obj.item.SetSize(msg.item_size() > obj.item.GetMaxSize() ? obj.item.GetMaxSize() : msg.item_size());
	for(int32_t i = 0; i < obj.item.GetSize(); ++i) {
		const ::proto_ff::FishAlgorithmCsvItem & temp_item = msg.item(i);
		FishAlgorithmCsvItem_s::read_from_pbmsg(temp_item, obj.item[i]);
	}
}

FishNormalSetup_s::FishNormalSetup_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishNormalSetup_s::CreateInit() {
	SwitchBossTime = (int32_t)0;
	SwitchSceneTime = (int32_t)0;
	InitSceneIndex = (int32_t)0;
	AwardPoolSaveToDBTime = (int32_t)0;
	ClearTraceTime = (int32_t)0;
	BulletCountInScreen = (int32_t)0;
	TotalSceneCount = (int32_t)0;
	ScreenFishMaxCount = (int32_t)0;
	ClientNotOperateTipTimes = (int32_t)0;
	ClientExitTimes = (int32_t)0;
	TestFishMustKilled = (int32_t)0;
	ClientLessMoneyTip = (int32_t)0;
	TurnTableCalcMinByOneJu = (int32_t)0;
	UserSettlementTimes = (int32_t)0;
	TipBaoJiMoney = (int32_t)0;
	BatchSendFishesInterval = (int32_t)0;
	BatchSendFishesCount = (int32_t)0;
	SwitchScenePrepareTime = (int32_t)0;
	SwitchSceneFishGoAwayTime = (int32_t)0;
	return 0;
}

int FishNormalSetup_s::ResumeInit() {
	return 0;
}

void FishNormalSetup_s::write_to_pbmsg(const struct FishNormalSetup_s & obj, ::proto_ff::FishNormalSetup & msg) {
	msg.set_switchbosstime((int32_t)obj.SwitchBossTime);
	msg.set_switchscenetime((int32_t)obj.SwitchSceneTime);
	msg.set_initsceneindex((int32_t)obj.InitSceneIndex);
	msg.set_awardpoolsavetodbtime((int32_t)obj.AwardPoolSaveToDBTime);
	msg.set_cleartracetime((int32_t)obj.ClearTraceTime);
	for(int32_t i = 0; i < obj.CannonLevelVal.GetSize() && i < obj.CannonLevelVal.GetMaxSize(); ++i) {
		msg.add_cannonlevelval((int32_t)obj.CannonLevelVal[i]);
	}
	for(int32_t i = 0; i < obj.CannonShowNum.GetSize() && i < obj.CannonShowNum.GetMaxSize(); ++i) {
		msg.add_cannonshownum((int32_t)obj.CannonShowNum[i]);
	}
	for(int32_t i = 0; i < obj.BulletHarmAddBFB.GetSize() && i < obj.BulletHarmAddBFB.GetMaxSize(); ++i) {
		msg.add_bulletharmaddbfb((double)obj.BulletHarmAddBFB[i]);
	}
	msg.set_bulletcountinscreen((int32_t)obj.BulletCountInScreen);
	msg.set_totalscenecount((int32_t)obj.TotalSceneCount);
	msg.set_screenfishmaxcount((int32_t)obj.ScreenFishMaxCount);
	msg.set_clientnotoperatetiptimes((int32_t)obj.ClientNotOperateTipTimes);
	msg.set_clientexittimes((int32_t)obj.ClientExitTimes);
	msg.set_testfishmustkilled((int32_t)obj.TestFishMustKilled);
	msg.set_clientlessmoneytip((int32_t)obj.ClientLessMoneyTip);
	msg.set_turntablecalcminbyoneju((int32_t)obj.TurnTableCalcMinByOneJu);
	msg.set_usersettlementtimes((int32_t)obj.UserSettlementTimes);
	msg.set_tipbaojimoney((int32_t)obj.TipBaoJiMoney);
	msg.set_batchsendfishesinterval((int32_t)obj.BatchSendFishesInterval);
	msg.set_batchsendfishescount((int32_t)obj.BatchSendFishesCount);
	msg.set_switchscenepreparetime((int32_t)obj.SwitchScenePrepareTime);
	msg.set_switchscenefishgoawaytime((int32_t)obj.SwitchSceneFishGoAwayTime);
}

void FishNormalSetup_s::read_from_pbmsg(const ::proto_ff::FishNormalSetup & msg, struct FishNormalSetup_s & obj) {
	memset(&obj, 0, sizeof(struct FishNormalSetup_s));
	obj.SwitchBossTime = msg.switchbosstime();
	obj.SwitchSceneTime = msg.switchscenetime();
	obj.InitSceneIndex = msg.initsceneindex();
	obj.AwardPoolSaveToDBTime = msg.awardpoolsavetodbtime();
	obj.ClearTraceTime = msg.cleartracetime();
	obj.CannonLevelVal.SetSize(msg.cannonlevelval_size() > obj.CannonLevelVal.GetMaxSize() ? obj.CannonLevelVal.GetMaxSize() : msg.cannonlevelval_size());
	for(int32_t i = 0; i < obj.CannonLevelVal.GetSize(); ++i) {
		obj.CannonLevelVal[i] = msg.cannonlevelval(i);
	}
	obj.CannonShowNum.SetSize(msg.cannonshownum_size() > obj.CannonShowNum.GetMaxSize() ? obj.CannonShowNum.GetMaxSize() : msg.cannonshownum_size());
	for(int32_t i = 0; i < obj.CannonShowNum.GetSize(); ++i) {
		obj.CannonShowNum[i] = msg.cannonshownum(i);
	}
	obj.BulletHarmAddBFB.SetSize(msg.bulletharmaddbfb_size() > obj.BulletHarmAddBFB.GetMaxSize() ? obj.BulletHarmAddBFB.GetMaxSize() : msg.bulletharmaddbfb_size());
	for(int32_t i = 0; i < obj.BulletHarmAddBFB.GetSize(); ++i) {
		obj.BulletHarmAddBFB[i] = msg.bulletharmaddbfb(i);
	}
	obj.BulletCountInScreen = msg.bulletcountinscreen();
	obj.TotalSceneCount = msg.totalscenecount();
	obj.ScreenFishMaxCount = msg.screenfishmaxcount();
	obj.ClientNotOperateTipTimes = msg.clientnotoperatetiptimes();
	obj.ClientExitTimes = msg.clientexittimes();
	obj.TestFishMustKilled = msg.testfishmustkilled();
	obj.ClientLessMoneyTip = msg.clientlessmoneytip();
	obj.TurnTableCalcMinByOneJu = msg.turntablecalcminbyoneju();
	obj.UserSettlementTimes = msg.usersettlementtimes();
	obj.TipBaoJiMoney = msg.tipbaojimoney();
	obj.BatchSendFishesInterval = msg.batchsendfishesinterval();
	obj.BatchSendFishesCount = msg.batchsendfishescount();
	obj.SwitchScenePrepareTime = msg.switchscenepreparetime();
	obj.SwitchSceneFishGoAwayTime = msg.switchscenefishgoawaytime();
}

FishPoolSaveBaseMul_s::FishPoolSaveBaseMul_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishPoolSaveBaseMul_s::CreateInit() {
	return 0;
}

int FishPoolSaveBaseMul_s::ResumeInit() {
	return 0;
}

void FishPoolSaveBaseMul_s::write_to_pbmsg(const struct FishPoolSaveBaseMul_s & obj, ::proto_ff::FishPoolSaveBaseMul & msg) {
	for(int32_t i = 0; i < obj.value.GetSize() && i < obj.value.GetMaxSize(); ++i) {
		msg.add_value((int32_t)obj.value[i]);
	}
}

void FishPoolSaveBaseMul_s::read_from_pbmsg(const ::proto_ff::FishPoolSaveBaseMul & msg, struct FishPoolSaveBaseMul_s & obj) {
	memset(&obj, 0, sizeof(struct FishPoolSaveBaseMul_s));
	obj.value.SetSize(msg.value_size() > obj.value.GetMaxSize() ? obj.value.GetMaxSize() : msg.value_size());
	for(int32_t i = 0; i < obj.value.GetSize(); ++i) {
		obj.value[i] = msg.value(i);
	}
}

FishPoolSaveRelaCount_s::FishPoolSaveRelaCount_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishPoolSaveRelaCount_s::CreateInit() {
	return 0;
}

int FishPoolSaveRelaCount_s::ResumeInit() {
	return 0;
}

void FishPoolSaveRelaCount_s::write_to_pbmsg(const struct FishPoolSaveRelaCount_s & obj, ::proto_ff::FishPoolSaveRelaCount & msg) {
	for(int32_t i = 0; i < obj.value.GetSize() && i < obj.value.GetMaxSize(); ++i) {
		msg.add_value((int32_t)obj.value[i]);
	}
}

void FishPoolSaveRelaCount_s::read_from_pbmsg(const ::proto_ff::FishPoolSaveRelaCount & msg, struct FishPoolSaveRelaCount_s & obj) {
	memset(&obj, 0, sizeof(struct FishPoolSaveRelaCount_s));
	obj.value.SetSize(msg.value_size() > obj.value.GetMaxSize() ? obj.value.GetMaxSize() : msg.value_size());
	for(int32_t i = 0; i < obj.value.GetSize(); ++i) {
		obj.value[i] = msg.value(i);
	}
}

FishPoolSaveHitCountCfg_s::FishPoolSaveHitCountCfg_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishPoolSaveHitCountCfg_s::CreateInit() {
	return 0;
}

int FishPoolSaveHitCountCfg_s::ResumeInit() {
	return 0;
}

void FishPoolSaveHitCountCfg_s::write_to_pbmsg(const struct FishPoolSaveHitCountCfg_s & obj, ::proto_ff::FishPoolSaveHitCountCfg & msg) {
	for(int32_t i = 0; i < obj.value.GetSize() && i < obj.value.GetMaxSize(); ++i) {
		msg.add_value((int32_t)obj.value[i]);
	}
}

void FishPoolSaveHitCountCfg_s::read_from_pbmsg(const ::proto_ff::FishPoolSaveHitCountCfg & msg, struct FishPoolSaveHitCountCfg_s & obj) {
	memset(&obj, 0, sizeof(struct FishPoolSaveHitCountCfg_s));
	obj.value.SetSize(msg.value_size() > obj.value.GetMaxSize() ? obj.value.GetMaxSize() : msg.value_size());
	for(int32_t i = 0; i < obj.value.GetSize(); ++i) {
		obj.value[i] = msg.value(i);
	}
}

FishPoolSaveConnonHitCount_s::FishPoolSaveConnonHitCount_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishPoolSaveConnonHitCount_s::CreateInit() {
	return 0;
}

int FishPoolSaveConnonHitCount_s::ResumeInit() {
	return 0;
}

void FishPoolSaveConnonHitCount_s::write_to_pbmsg(const struct FishPoolSaveConnonHitCount_s & obj, ::proto_ff::FishPoolSaveConnonHitCount & msg) {
	for(int32_t i = 0; i < obj.value.GetSize() && i < obj.value.GetMaxSize(); ++i) {
		msg.add_value((double)obj.value[i]);
	}
}

void FishPoolSaveConnonHitCount_s::read_from_pbmsg(const ::proto_ff::FishPoolSaveConnonHitCount & msg, struct FishPoolSaveConnonHitCount_s & obj) {
	memset(&obj, 0, sizeof(struct FishPoolSaveConnonHitCount_s));
	obj.value.SetSize(msg.value_size() > obj.value.GetMaxSize() ? obj.value.GetMaxSize() : msg.value_size());
	for(int32_t i = 0; i < obj.value.GetSize(); ++i) {
		obj.value[i] = msg.value(i);
	}
}

FishPoolSave_s::FishPoolSave_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishPoolSave_s::CreateInit() {
	dwFishID = (int32_t)0;
	btFishKind = (int32_t)0;
	btFishKindGroup1 = (int32_t)0;
	btFishKindGroup2 = (int32_t)0;
	btFishKindGroup3 = (int32_t)0;
	btFishKindGroup4 = (int32_t)0;
	bKilled = (bool)0;
	bRobotKilled = (bool)0;
	bKilledByOtherRela = (bool)0;
	bKilledByAlgoA = (bool)0;
	btKilledCannonIndex = (int32_t)0;
	bFloatMul = (bool)0;
	return 0;
}

int FishPoolSave_s::ResumeInit() {
	return 0;
}

void FishPoolSave_s::write_to_pbmsg(const struct FishPoolSave_s & obj, ::proto_ff::FishPoolSave & msg) {
	msg.set_dwfishid((int32_t)obj.dwFishID);
	msg.set_btfishkind((int32_t)obj.btFishKind);
	msg.set_btfishkindgroup1((int32_t)obj.btFishKindGroup1);
	msg.set_btfishkindgroup2((int32_t)obj.btFishKindGroup2);
	msg.set_btfishkindgroup3((int32_t)obj.btFishKindGroup3);
	msg.set_btfishkindgroup4((int32_t)obj.btFishKindGroup4);
	msg.set_bkilled((bool)obj.bKilled);
	msg.set_brobotkilled((bool)obj.bRobotKilled);
	msg.set_bkilledbyotherrela((bool)obj.bKilledByOtherRela);
	msg.set_bkilledbyalgoa((bool)obj.bKilledByAlgoA);
	msg.set_btkilledcannonindex((int32_t)obj.btKilledCannonIndex);
	msg.set_bfloatmul((bool)obj.bFloatMul);
	for(int32_t i = 0; i < obj.arBaseMul.GetSize() && i < obj.arBaseMul.GetMaxSize(); ++i) {
		::proto_ff::FishPoolSaveBaseMul* temp_arbasemul = msg.add_arbasemul();
		FishPoolSaveBaseMul_s::write_to_pbmsg(obj.arBaseMul[i], *temp_arbasemul);
	}
	for(int32_t i = 0; i < obj.arRelaCount.GetSize() && i < obj.arRelaCount.GetMaxSize(); ++i) {
		::proto_ff::FishPoolSaveRelaCount* temp_arrelacount = msg.add_arrelacount();
		FishPoolSaveRelaCount_s::write_to_pbmsg(obj.arRelaCount[i], *temp_arrelacount);
	}
	for(int32_t i = 0; i < obj.arHitCountCfg.GetSize() && i < obj.arHitCountCfg.GetMaxSize(); ++i) {
		::proto_ff::FishPoolSaveHitCountCfg* temp_arhitcountcfg = msg.add_arhitcountcfg();
		FishPoolSaveHitCountCfg_s::write_to_pbmsg(obj.arHitCountCfg[i], *temp_arhitcountcfg);
	}
	for(int32_t i = 0; i < obj.arConnonHitCount.GetSize() && i < obj.arConnonHitCount.GetMaxSize(); ++i) {
		::proto_ff::FishPoolSaveConnonHitCount* temp_arconnonhitcount = msg.add_arconnonhitcount();
		FishPoolSaveConnonHitCount_s::write_to_pbmsg(obj.arConnonHitCount[i], *temp_arconnonhitcount);
	}
}

void FishPoolSave_s::read_from_pbmsg(const ::proto_ff::FishPoolSave & msg, struct FishPoolSave_s & obj) {
	memset(&obj, 0, sizeof(struct FishPoolSave_s));
	obj.dwFishID = msg.dwfishid();
	obj.btFishKind = msg.btfishkind();
	obj.btFishKindGroup1 = msg.btfishkindgroup1();
	obj.btFishKindGroup2 = msg.btfishkindgroup2();
	obj.btFishKindGroup3 = msg.btfishkindgroup3();
	obj.btFishKindGroup4 = msg.btfishkindgroup4();
	obj.bKilled = msg.bkilled();
	obj.bRobotKilled = msg.brobotkilled();
	obj.bKilledByOtherRela = msg.bkilledbyotherrela();
	obj.bKilledByAlgoA = msg.bkilledbyalgoa();
	obj.btKilledCannonIndex = msg.btkilledcannonindex();
	obj.bFloatMul = msg.bfloatmul();
	obj.arBaseMul.SetSize(msg.arbasemul_size() > obj.arBaseMul.GetMaxSize() ? obj.arBaseMul.GetMaxSize() : msg.arbasemul_size());
	for(int32_t i = 0; i < obj.arBaseMul.GetSize(); ++i) {
		const ::proto_ff::FishPoolSaveBaseMul & temp_arbasemul = msg.arbasemul(i);
		FishPoolSaveBaseMul_s::read_from_pbmsg(temp_arbasemul, obj.arBaseMul[i]);
	}
	obj.arRelaCount.SetSize(msg.arrelacount_size() > obj.arRelaCount.GetMaxSize() ? obj.arRelaCount.GetMaxSize() : msg.arrelacount_size());
	for(int32_t i = 0; i < obj.arRelaCount.GetSize(); ++i) {
		const ::proto_ff::FishPoolSaveRelaCount & temp_arrelacount = msg.arrelacount(i);
		FishPoolSaveRelaCount_s::read_from_pbmsg(temp_arrelacount, obj.arRelaCount[i]);
	}
	obj.arHitCountCfg.SetSize(msg.arhitcountcfg_size() > obj.arHitCountCfg.GetMaxSize() ? obj.arHitCountCfg.GetMaxSize() : msg.arhitcountcfg_size());
	for(int32_t i = 0; i < obj.arHitCountCfg.GetSize(); ++i) {
		const ::proto_ff::FishPoolSaveHitCountCfg & temp_arhitcountcfg = msg.arhitcountcfg(i);
		FishPoolSaveHitCountCfg_s::read_from_pbmsg(temp_arhitcountcfg, obj.arHitCountCfg[i]);
	}
	obj.arConnonHitCount.SetSize(msg.arconnonhitcount_size() > obj.arConnonHitCount.GetMaxSize() ? obj.arConnonHitCount.GetMaxSize() : msg.arconnonhitcount_size());
	for(int32_t i = 0; i < obj.arConnonHitCount.GetSize(); ++i) {
		const ::proto_ff::FishPoolSaveConnonHitCount & temp_arconnonhitcount = msg.arconnonhitcount(i);
		FishPoolSaveConnonHitCount_s::read_from_pbmsg(temp_arconnonhitcount, obj.arConnonHitCount[i]);
	}
}

FishKindFishPoolSave_s::FishKindFishPoolSave_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishKindFishPoolSave_s::CreateInit() {
	return 0;
}

int FishKindFishPoolSave_s::ResumeInit() {
	return 0;
}

void FishKindFishPoolSave_s::write_to_pbmsg(const struct FishKindFishPoolSave_s & obj, ::proto_ff::FishKindFishPoolSave & msg) {
	for(int32_t i = 0; i < obj.fish_pool.GetSize() && i < obj.fish_pool.GetMaxSize(); ++i) {
		::proto_ff::FishPoolSave* temp_fish_pool = msg.add_fish_pool();
		FishPoolSave_s::write_to_pbmsg(obj.fish_pool[i], *temp_fish_pool);
	}
}

void FishKindFishPoolSave_s::read_from_pbmsg(const ::proto_ff::FishKindFishPoolSave & msg, struct FishKindFishPoolSave_s & obj) {
	memset(&obj, 0, sizeof(struct FishKindFishPoolSave_s));
	obj.fish_pool.SetSize(msg.fish_pool_size() > obj.fish_pool.GetMaxSize() ? obj.fish_pool.GetMaxSize() : msg.fish_pool_size());
	for(int32_t i = 0; i < obj.fish_pool.GetSize(); ++i) {
		const ::proto_ff::FishPoolSave & temp_fish_pool = msg.fish_pool(i);
		FishPoolSave_s::read_from_pbmsg(temp_fish_pool, obj.fish_pool[i]);
	}
}

FishKindFishPoolSaveArray_s::FishKindFishPoolSaveArray_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int FishKindFishPoolSaveArray_s::CreateInit() {
	return 0;
}

int FishKindFishPoolSaveArray_s::ResumeInit() {
	return 0;
}

void FishKindFishPoolSaveArray_s::write_to_pbmsg(const struct FishKindFishPoolSaveArray_s & obj, ::proto_ff::FishKindFishPoolSaveArray & msg) {
	for(int32_t i = 0; i < obj.fish_kind.GetSize() && i < obj.fish_kind.GetMaxSize(); ++i) {
		::proto_ff::FishKindFishPoolSave* temp_fish_kind = msg.add_fish_kind();
		FishKindFishPoolSave_s::write_to_pbmsg(obj.fish_kind[i], *temp_fish_kind);
	}
}

void FishKindFishPoolSaveArray_s::read_from_pbmsg(const ::proto_ff::FishKindFishPoolSaveArray & msg, struct FishKindFishPoolSaveArray_s & obj) {
	memset(&obj, 0, sizeof(struct FishKindFishPoolSaveArray_s));
	obj.fish_kind.SetSize(msg.fish_kind_size() > obj.fish_kind.GetMaxSize() ? obj.fish_kind.GetMaxSize() : msg.fish_kind_size());
	for(int32_t i = 0; i < obj.fish_kind.GetSize(); ++i) {
		const ::proto_ff::FishKindFishPoolSave & temp_fish_kind = msg.fish_kind(i);
		FishKindFishPoolSave_s::read_from_pbmsg(temp_fish_kind, obj.fish_kind[i]);
	}
}

GMCtrlLevelDesc_s::GMCtrlLevelDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int GMCtrlLevelDesc_s::CreateInit() {
	ControlLevel = (int32_t)0;
	ControlRate = (int32_t)0;
	return 0;
}

int GMCtrlLevelDesc_s::ResumeInit() {
	return 0;
}

void GMCtrlLevelDesc_s::write_to_pbmsg(const struct GMCtrlLevelDesc_s & obj, ::proto_ff::GMCtrlLevelDesc & msg) {
	msg.set_controllevel((int32_t)obj.ControlLevel);
	msg.set_name((const char*)obj.Name.Get());
	msg.set_controlrate((int32_t)obj.ControlRate);
}

void GMCtrlLevelDesc_s::read_from_pbmsg(const ::proto_ff::GMCtrlLevelDesc & msg, struct GMCtrlLevelDesc_s & obj) {
	memset(&obj, 0, sizeof(struct GMCtrlLevelDesc_s));
	obj.ControlLevel = msg.controllevel();
	obj.Name.Copy(msg.name());
	obj.ControlRate = msg.controlrate();
}

Sheet_GMCtrlLevelDesc_s::Sheet_GMCtrlLevelDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Sheet_GMCtrlLevelDesc_s::CreateInit() {
	return 0;
}

int Sheet_GMCtrlLevelDesc_s::ResumeInit() {
	return 0;
}

void Sheet_GMCtrlLevelDesc_s::write_to_pbmsg(const struct Sheet_GMCtrlLevelDesc_s & obj, ::proto_ff::Sheet_GMCtrlLevelDesc & msg) {
	for(int32_t i = 0; i < obj.GMCtrlLevelDesc_List.GetSize() && i < obj.GMCtrlLevelDesc_List.GetMaxSize(); ++i) {
		::proto_ff::GMCtrlLevelDesc* temp_gmctrlleveldesc_list = msg.add_gmctrlleveldesc_list();
		GMCtrlLevelDesc_s::write_to_pbmsg(obj.GMCtrlLevelDesc_List[i], *temp_gmctrlleveldesc_list);
	}
}

void Sheet_GMCtrlLevelDesc_s::read_from_pbmsg(const ::proto_ff::Sheet_GMCtrlLevelDesc & msg, struct Sheet_GMCtrlLevelDesc_s & obj) {
	memset(&obj, 0, sizeof(struct Sheet_GMCtrlLevelDesc_s));
	obj.GMCtrlLevelDesc_List.SetSize(msg.gmctrlleveldesc_list_size() > obj.GMCtrlLevelDesc_List.GetMaxSize() ? obj.GMCtrlLevelDesc_List.GetMaxSize() : msg.gmctrlleveldesc_list_size());
	for(int32_t i = 0; i < obj.GMCtrlLevelDesc_List.GetSize(); ++i) {
		const ::proto_ff::GMCtrlLevelDesc & temp_gmctrlleveldesc_list = msg.gmctrlleveldesc_list(i);
		GMCtrlLevelDesc_s::read_from_pbmsg(temp_gmctrlleveldesc_list, obj.GMCtrlLevelDesc_List[i]);
	}
}

LineGameSystemControlInfo_s::LineGameSystemControlInfo_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int LineGameSystemControlInfo_s::CreateInit() {
	RoomID = (int32_t)0;
	AreaID = (int32_t)0;
	TotalProfit = (int64_t)0;
	CurrentSystemControl = (int32_t)0;
	return 0;
}

int LineGameSystemControlInfo_s::ResumeInit() {
	return 0;
}

void LineGameSystemControlInfo_s::write_to_pbmsg(const struct LineGameSystemControlInfo_s & obj, ::proto_ff::LineGameSystemControlInfo & msg) {
	msg.set_roomid((int32_t)obj.RoomID);
	msg.set_areaid((int32_t)obj.AreaID);
	msg.set_totalprofit((int64_t)obj.TotalProfit);
	msg.set_currentsystemcontrol((int32_t)obj.CurrentSystemControl);
}

void LineGameSystemControlInfo_s::read_from_pbmsg(const ::proto_ff::LineGameSystemControlInfo & msg, struct LineGameSystemControlInfo_s & obj) {
	memset(&obj, 0, sizeof(struct LineGameSystemControlInfo_s));
	obj.RoomID = msg.roomid();
	obj.AreaID = msg.areaid();
	obj.TotalProfit = msg.totalprofit();
	obj.CurrentSystemControl = msg.currentsystemcontrol();
}

Sheet_LineGameSystemControlInfo_s::Sheet_LineGameSystemControlInfo_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Sheet_LineGameSystemControlInfo_s::CreateInit() {
	return 0;
}

int Sheet_LineGameSystemControlInfo_s::ResumeInit() {
	return 0;
}

void Sheet_LineGameSystemControlInfo_s::write_to_pbmsg(const struct Sheet_LineGameSystemControlInfo_s & obj, ::proto_ff::Sheet_LineGameSystemControlInfo & msg) {
	for(int32_t i = 0; i < obj.LineGameSystemControlInfo_List.GetSize() && i < obj.LineGameSystemControlInfo_List.GetMaxSize(); ++i) {
		::proto_ff::LineGameSystemControlInfo* temp_linegamesystemcontrolinfo_list = msg.add_linegamesystemcontrolinfo_list();
		LineGameSystemControlInfo_s::write_to_pbmsg(obj.LineGameSystemControlInfo_List[i], *temp_linegamesystemcontrolinfo_list);
	}
}

void Sheet_LineGameSystemControlInfo_s::read_from_pbmsg(const ::proto_ff::Sheet_LineGameSystemControlInfo & msg, struct Sheet_LineGameSystemControlInfo_s & obj) {
	memset(&obj, 0, sizeof(struct Sheet_LineGameSystemControlInfo_s));
	obj.LineGameSystemControlInfo_List.SetSize(msg.linegamesystemcontrolinfo_list_size() > obj.LineGameSystemControlInfo_List.GetMaxSize() ? obj.LineGameSystemControlInfo_List.GetMaxSize() : msg.linegamesystemcontrolinfo_list_size());
	for(int32_t i = 0; i < obj.LineGameSystemControlInfo_List.GetSize(); ++i) {
		const ::proto_ff::LineGameSystemControlInfo & temp_linegamesystemcontrolinfo_list = msg.linegamesystemcontrolinfo_list(i);
		LineGameSystemControlInfo_s::read_from_pbmsg(temp_linegamesystemcontrolinfo_list, obj.LineGameSystemControlInfo_List[i]);
	}
}

LineLevelDesc_s::LineLevelDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int LineLevelDesc_s::CreateInit() {
	LevelID = (int32_t)0;
	MinMoney = (int32_t)0;
	MaxMoney = (int32_t)0;
	StartGame = (int32_t)0;
	Flag = (int32_t)0;
	MaxWinTimes = (int32_t)0;
	return 0;
}

int LineLevelDesc_s::ResumeInit() {
	return 0;
}

void LineLevelDesc_s::write_to_pbmsg(const struct LineLevelDesc_s & obj, ::proto_ff::LineLevelDesc & msg) {
	msg.set_levelid((int32_t)obj.LevelID);
	msg.set_levelname((const char*)obj.LevelName.Get());
	msg.set_cannonlevelval((const char*)obj.CannonLevelVal.Get());
	for(int32_t i = 0; i < obj.VecCannonLevelVal.GetSize() && i < obj.VecCannonLevelVal.GetMaxSize(); ++i) {
		msg.add_veccannonlevelval((int32_t)obj.VecCannonLevelVal[i]);
	}
	msg.set_cannonshownum((const char*)obj.CannonShowNum.Get());
	for(int32_t i = 0; i < obj.VecCannonShowNum.GetSize() && i < obj.VecCannonShowNum.GetMaxSize(); ++i) {
		msg.add_veccannonshownum((int32_t)obj.VecCannonShowNum[i]);
	}
	msg.set_minmoney((int32_t)obj.MinMoney);
	msg.set_maxmoney((int32_t)obj.MaxMoney);
	msg.set_startgame((int32_t)obj.StartGame);
	msg.set_flag((int32_t)obj.Flag);
	msg.set_maxwintimes((int32_t)obj.MaxWinTimes);
	msg.set_chip((const char*)obj.Chip.Get());
	for(int32_t i = 0; i < obj.VecChips.GetSize() && i < obj.VecChips.GetMaxSize(); ++i) {
		msg.add_vecchips((int64_t)obj.VecChips[i]);
	}
	msg.set_gmlevelrate((const char*)obj.GMLevelRate.Get());
	for(int32_t i = 0; i < obj.VecGMLevelRate.GetSize() && i < obj.VecGMLevelRate.GetMaxSize(); ++i) {
		msg.add_vecgmlevelrate((int32_t)obj.VecGMLevelRate[i]);
	}
}

void LineLevelDesc_s::read_from_pbmsg(const ::proto_ff::LineLevelDesc & msg, struct LineLevelDesc_s & obj) {
	memset(&obj, 0, sizeof(struct LineLevelDesc_s));
	obj.LevelID = msg.levelid();
	obj.LevelName.Copy(msg.levelname());
	obj.CannonLevelVal.Copy(msg.cannonlevelval());
	obj.VecCannonLevelVal.SetSize(msg.veccannonlevelval_size() > obj.VecCannonLevelVal.GetMaxSize() ? obj.VecCannonLevelVal.GetMaxSize() : msg.veccannonlevelval_size());
	for(int32_t i = 0; i < obj.VecCannonLevelVal.GetSize(); ++i) {
		obj.VecCannonLevelVal[i] = msg.veccannonlevelval(i);
	}
	obj.CannonShowNum.Copy(msg.cannonshownum());
	obj.VecCannonShowNum.SetSize(msg.veccannonshownum_size() > obj.VecCannonShowNum.GetMaxSize() ? obj.VecCannonShowNum.GetMaxSize() : msg.veccannonshownum_size());
	for(int32_t i = 0; i < obj.VecCannonShowNum.GetSize(); ++i) {
		obj.VecCannonShowNum[i] = msg.veccannonshownum(i);
	}
	obj.MinMoney = msg.minmoney();
	obj.MaxMoney = msg.maxmoney();
	obj.StartGame = msg.startgame();
	obj.Flag = msg.flag();
	obj.MaxWinTimes = msg.maxwintimes();
	obj.Chip.Copy(msg.chip());
	obj.VecChips.SetSize(msg.vecchips_size() > obj.VecChips.GetMaxSize() ? obj.VecChips.GetMaxSize() : msg.vecchips_size());
	for(int32_t i = 0; i < obj.VecChips.GetSize(); ++i) {
		obj.VecChips[i] = msg.vecchips(i);
	}
	obj.GMLevelRate.Copy(msg.gmlevelrate());
	obj.VecGMLevelRate.SetSize(msg.vecgmlevelrate_size() > obj.VecGMLevelRate.GetMaxSize() ? obj.VecGMLevelRate.GetMaxSize() : msg.vecgmlevelrate_size());
	for(int32_t i = 0; i < obj.VecGMLevelRate.GetSize(); ++i) {
		obj.VecGMLevelRate[i] = msg.vecgmlevelrate(i);
	}
}

Sheet_LineLevelDesc_s::Sheet_LineLevelDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Sheet_LineLevelDesc_s::CreateInit() {
	return 0;
}

int Sheet_LineLevelDesc_s::ResumeInit() {
	return 0;
}

void Sheet_LineLevelDesc_s::write_to_pbmsg(const struct Sheet_LineLevelDesc_s & obj, ::proto_ff::Sheet_LineLevelDesc & msg) {
	for(int32_t i = 0; i < obj.LineLevelDesc_List.GetSize() && i < obj.LineLevelDesc_List.GetMaxSize(); ++i) {
		::proto_ff::LineLevelDesc* temp_lineleveldesc_list = msg.add_lineleveldesc_list();
		LineLevelDesc_s::write_to_pbmsg(obj.LineLevelDesc_List[i], *temp_lineleveldesc_list);
	}
}

void Sheet_LineLevelDesc_s::read_from_pbmsg(const ::proto_ff::Sheet_LineLevelDesc & msg, struct Sheet_LineLevelDesc_s & obj) {
	memset(&obj, 0, sizeof(struct Sheet_LineLevelDesc_s));
	obj.LineLevelDesc_List.SetSize(msg.lineleveldesc_list_size() > obj.LineLevelDesc_List.GetMaxSize() ? obj.LineLevelDesc_List.GetMaxSize() : msg.lineleveldesc_list_size());
	for(int32_t i = 0; i < obj.LineLevelDesc_List.GetSize(); ++i) {
		const ::proto_ff::LineLevelDesc & temp_lineleveldesc_list = msg.lineleveldesc_list(i);
		LineLevelDesc_s::read_from_pbmsg(temp_lineleveldesc_list, obj.LineLevelDesc_List[i]);
	}
}

LineDeskInfoDesc_s::LineDeskInfoDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int LineDeskInfoDesc_s::CreateInit() {
	id = (int32_t)0;
	RoomID = (int32_t)0;
	DeskID = (int32_t)0;
	AlgoID = (int32_t)0;
	DrawRate = (int32_t)0;
	return 0;
}

int LineDeskInfoDesc_s::ResumeInit() {
	return 0;
}

void LineDeskInfoDesc_s::write_to_pbmsg(const struct LineDeskInfoDesc_s & obj, ::proto_ff::LineDeskInfoDesc & msg) {
	msg.set_id((int32_t)obj.id);
	msg.set_roomid((int32_t)obj.RoomID);
	msg.set_deskid((int32_t)obj.DeskID);
	msg.set_algoid((int32_t)obj.AlgoID);
	msg.set_drawrate((int32_t)obj.DrawRate);
}

void LineDeskInfoDesc_s::read_from_pbmsg(const ::proto_ff::LineDeskInfoDesc & msg, struct LineDeskInfoDesc_s & obj) {
	memset(&obj, 0, sizeof(struct LineDeskInfoDesc_s));
	obj.id = msg.id();
	obj.RoomID = msg.roomid();
	obj.DeskID = msg.deskid();
	obj.AlgoID = msg.algoid();
	obj.DrawRate = msg.drawrate();
}

Sheet_LineDeskInfoDesc_s::Sheet_LineDeskInfoDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Sheet_LineDeskInfoDesc_s::CreateInit() {
	return 0;
}

int Sheet_LineDeskInfoDesc_s::ResumeInit() {
	return 0;
}

void Sheet_LineDeskInfoDesc_s::write_to_pbmsg(const struct Sheet_LineDeskInfoDesc_s & obj, ::proto_ff::Sheet_LineDeskInfoDesc & msg) {
	for(int32_t i = 0; i < obj.LineDeskInfoDesc_List.GetSize() && i < obj.LineDeskInfoDesc_List.GetMaxSize(); ++i) {
		::proto_ff::LineDeskInfoDesc* temp_linedeskinfodesc_list = msg.add_linedeskinfodesc_list();
		LineDeskInfoDesc_s::write_to_pbmsg(obj.LineDeskInfoDesc_List[i], *temp_linedeskinfodesc_list);
	}
}

void Sheet_LineDeskInfoDesc_s::read_from_pbmsg(const ::proto_ff::Sheet_LineDeskInfoDesc & msg, struct Sheet_LineDeskInfoDesc_s & obj) {
	memset(&obj, 0, sizeof(struct Sheet_LineDeskInfoDesc_s));
	obj.LineDeskInfoDesc_List.SetSize(msg.linedeskinfodesc_list_size() > obj.LineDeskInfoDesc_List.GetMaxSize() ? obj.LineDeskInfoDesc_List.GetMaxSize() : msg.linedeskinfodesc_list_size());
	for(int32_t i = 0; i < obj.LineDeskInfoDesc_List.GetSize(); ++i) {
		const ::proto_ff::LineDeskInfoDesc & temp_linedeskinfodesc_list = msg.linedeskinfodesc_list(i);
		LineDeskInfoDesc_s::read_from_pbmsg(temp_linedeskinfodesc_list, obj.LineDeskInfoDesc_List[i]);
	}
}

LineAlgoDesc_s::LineAlgoDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int LineAlgoDesc_s::CreateInit() {
	AlgoID = (int32_t)0;
	Level_Chi5 = (int64_t)0;
	Level_Chi4 = (int64_t)0;
	Level_Chi3 = (int64_t)0;
	Level_Chi2 = (int64_t)0;
	Level_Chi1 = (int64_t)0;
	Level_Fang1 = (int64_t)0;
	Level_Fang2 = (int64_t)0;
	Level_Fang3 = (int64_t)0;
	Level_Fang4 = (int64_t)0;
	Level_Fang5 = (int64_t)0;
	UserLuceFlag = (int32_t)0;
	return 0;
}

int LineAlgoDesc_s::ResumeInit() {
	return 0;
}

void LineAlgoDesc_s::write_to_pbmsg(const struct LineAlgoDesc_s & obj, ::proto_ff::LineAlgoDesc & msg) {
	msg.set_algoid((int32_t)obj.AlgoID);
	msg.set_algoname((const char*)obj.AlgoName.Get());
	msg.set_algodesc((const char*)obj.AlgoDesc.Get());
	msg.set_level_chi5((int64_t)obj.Level_Chi5);
	msg.set_level_chi4((int64_t)obj.Level_Chi4);
	msg.set_level_chi3((int64_t)obj.Level_Chi3);
	msg.set_level_chi2((int64_t)obj.Level_Chi2);
	msg.set_level_chi1((int64_t)obj.Level_Chi1);
	msg.set_level_fang1((int64_t)obj.Level_Fang1);
	msg.set_level_fang2((int64_t)obj.Level_Fang2);
	msg.set_level_fang3((int64_t)obj.Level_Fang3);
	msg.set_level_fang4((int64_t)obj.Level_Fang4);
	msg.set_level_fang5((int64_t)obj.Level_Fang5);
	msg.set_userlucksection((const char*)obj.UserLuckSection.Get());
	for(int32_t i = 0; i < obj.VecUserLuckSection.GetSize() && i < obj.VecUserLuckSection.GetMaxSize(); ++i) {
		msg.add_vecuserlucksection((int32_t)obj.VecUserLuckSection[i]);
	}
	msg.set_usernewsection((const char*)obj.UserNewSection.Get());
	for(int32_t i = 0; i < obj.VecUserNewSection.GetSize() && i < obj.VecUserNewSection.GetMaxSize(); ++i) {
		msg.add_vecusernewsection((int32_t)obj.VecUserNewSection[i]);
	}
	msg.set_usernewluckval((const char*)obj.UserNewLuckVal.Get());
	for(int32_t i = 0; i < obj.VecUserNewLuckVal.GetSize() && i < obj.VecUserNewLuckVal.GetMaxSize(); ++i) {
		msg.add_vecusernewluckval((int32_t)obj.VecUserNewLuckVal[i]);
	}
	msg.set_userrechargesection((const char*)obj.UserRechargeSection.Get());
	for(int32_t i = 0; i < obj.VecUserRechargeSection.GetSize() && i < obj.VecUserRechargeSection.GetMaxSize(); ++i) {
		msg.add_vecuserrechargesection((int32_t)obj.VecUserRechargeSection[i]);
	}
	msg.set_userrechargeluckyval((const char*)obj.UserRechargeLuckyVal.Get());
	for(int32_t i = 0; i < obj.VecUserRechargeLuckyVal.GetSize() && i < obj.VecUserRechargeLuckyVal.GetMaxSize(); ++i) {
		msg.add_vecuserrechargeluckyval((int32_t)obj.VecUserRechargeLuckyVal[i]);
	}
	msg.set_userluceflag((int32_t)obj.UserLuceFlag);
}

void LineAlgoDesc_s::read_from_pbmsg(const ::proto_ff::LineAlgoDesc & msg, struct LineAlgoDesc_s & obj) {
	memset(&obj, 0, sizeof(struct LineAlgoDesc_s));
	obj.AlgoID = msg.algoid();
	obj.AlgoName.Copy(msg.algoname());
	obj.AlgoDesc.Copy(msg.algodesc());
	obj.Level_Chi5 = msg.level_chi5();
	obj.Level_Chi4 = msg.level_chi4();
	obj.Level_Chi3 = msg.level_chi3();
	obj.Level_Chi2 = msg.level_chi2();
	obj.Level_Chi1 = msg.level_chi1();
	obj.Level_Fang1 = msg.level_fang1();
	obj.Level_Fang2 = msg.level_fang2();
	obj.Level_Fang3 = msg.level_fang3();
	obj.Level_Fang4 = msg.level_fang4();
	obj.Level_Fang5 = msg.level_fang5();
	obj.UserLuckSection.Copy(msg.userlucksection());
	obj.VecUserLuckSection.SetSize(msg.vecuserlucksection_size() > obj.VecUserLuckSection.GetMaxSize() ? obj.VecUserLuckSection.GetMaxSize() : msg.vecuserlucksection_size());
	for(int32_t i = 0; i < obj.VecUserLuckSection.GetSize(); ++i) {
		obj.VecUserLuckSection[i] = msg.vecuserlucksection(i);
	}
	obj.UserNewSection.Copy(msg.usernewsection());
	obj.VecUserNewSection.SetSize(msg.vecusernewsection_size() > obj.VecUserNewSection.GetMaxSize() ? obj.VecUserNewSection.GetMaxSize() : msg.vecusernewsection_size());
	for(int32_t i = 0; i < obj.VecUserNewSection.GetSize(); ++i) {
		obj.VecUserNewSection[i] = msg.vecusernewsection(i);
	}
	obj.UserNewLuckVal.Copy(msg.usernewluckval());
	obj.VecUserNewLuckVal.SetSize(msg.vecusernewluckval_size() > obj.VecUserNewLuckVal.GetMaxSize() ? obj.VecUserNewLuckVal.GetMaxSize() : msg.vecusernewluckval_size());
	for(int32_t i = 0; i < obj.VecUserNewLuckVal.GetSize(); ++i) {
		obj.VecUserNewLuckVal[i] = msg.vecusernewluckval(i);
	}
	obj.UserRechargeSection.Copy(msg.userrechargesection());
	obj.VecUserRechargeSection.SetSize(msg.vecuserrechargesection_size() > obj.VecUserRechargeSection.GetMaxSize() ? obj.VecUserRechargeSection.GetMaxSize() : msg.vecuserrechargesection_size());
	for(int32_t i = 0; i < obj.VecUserRechargeSection.GetSize(); ++i) {
		obj.VecUserRechargeSection[i] = msg.vecuserrechargesection(i);
	}
	obj.UserRechargeLuckyVal.Copy(msg.userrechargeluckyval());
	obj.VecUserRechargeLuckyVal.SetSize(msg.vecuserrechargeluckyval_size() > obj.VecUserRechargeLuckyVal.GetMaxSize() ? obj.VecUserRechargeLuckyVal.GetMaxSize() : msg.vecuserrechargeluckyval_size());
	for(int32_t i = 0; i < obj.VecUserRechargeLuckyVal.GetSize(); ++i) {
		obj.VecUserRechargeLuckyVal[i] = msg.vecuserrechargeluckyval(i);
	}
	obj.UserLuceFlag = msg.userluceflag();
}

Sheet_LineAlgoDesc_s::Sheet_LineAlgoDesc_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Sheet_LineAlgoDesc_s::CreateInit() {
	return 0;
}

int Sheet_LineAlgoDesc_s::ResumeInit() {
	return 0;
}

void Sheet_LineAlgoDesc_s::write_to_pbmsg(const struct Sheet_LineAlgoDesc_s & obj, ::proto_ff::Sheet_LineAlgoDesc & msg) {
	for(int32_t i = 0; i < obj.LineAlgoDesc_List.GetSize() && i < obj.LineAlgoDesc_List.GetMaxSize(); ++i) {
		::proto_ff::LineAlgoDesc* temp_linealgodesc_list = msg.add_linealgodesc_list();
		LineAlgoDesc_s::write_to_pbmsg(obj.LineAlgoDesc_List[i], *temp_linealgodesc_list);
	}
}

void Sheet_LineAlgoDesc_s::read_from_pbmsg(const ::proto_ff::Sheet_LineAlgoDesc & msg, struct Sheet_LineAlgoDesc_s & obj) {
	memset(&obj, 0, sizeof(struct Sheet_LineAlgoDesc_s));
	obj.LineAlgoDesc_List.SetSize(msg.linealgodesc_list_size() > obj.LineAlgoDesc_List.GetMaxSize() ? obj.LineAlgoDesc_List.GetMaxSize() : msg.linealgodesc_list_size());
	for(int32_t i = 0; i < obj.LineAlgoDesc_List.GetSize(); ++i) {
		const ::proto_ff::LineAlgoDesc & temp_linealgodesc_list = msg.linealgodesc_list(i);
		LineAlgoDesc_s::read_from_pbmsg(temp_linealgodesc_list, obj.LineAlgoDesc_List[i]);
	}
}

}