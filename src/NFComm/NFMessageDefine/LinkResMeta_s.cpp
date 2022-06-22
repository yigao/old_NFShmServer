#include "LinkResMeta_s.h"

namespace proto_ff_s {

Proto_HMLineRateMgr_item_s::Proto_HMLineRateMgr_item_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Proto_HMLineRateMgr_item_s::CreateInit() {
	return 0;
}

int Proto_HMLineRateMgr_item_s::ResumeInit() {
	return 0;
}

void Proto_HMLineRateMgr_item_s::write_to_pbmsg(const struct Proto_HMLineRateMgr_item_s & obj, ::proto_ff::Proto_HMLineRateMgr_item & msg) {
	for(int32_t i = 0; i < obj.item.GetSize() && i < obj.item.GetMaxSize(); ++i) {
		msg.add_item((int32_t)obj.item[i]);
	}
}

void Proto_HMLineRateMgr_item_s::read_from_pbmsg(const ::proto_ff::Proto_HMLineRateMgr_item & msg, struct Proto_HMLineRateMgr_item_s & obj) {
	memset(&obj, 0, sizeof(struct Proto_HMLineRateMgr_item_s));
	obj.item.SetSize(msg.item_size() > obj.item.GetMaxSize() ? obj.item.GetMaxSize() : msg.item_size());
	for(int32_t i = 0; i < obj.item.GetSize(); ++i) {
		obj.item[i] = msg.item(i);
	}
}

Proto_HMLineRateMgr_icon_s::Proto_HMLineRateMgr_icon_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Proto_HMLineRateMgr_icon_s::CreateInit() {
	return 0;
}

int Proto_HMLineRateMgr_icon_s::ResumeInit() {
	return 0;
}

void Proto_HMLineRateMgr_icon_s::write_to_pbmsg(const struct Proto_HMLineRateMgr_icon_s & obj, ::proto_ff::Proto_HMLineRateMgr_icon & msg) {
	for(int32_t i = 0; i < obj.icon.GetSize() && i < obj.icon.GetMaxSize(); ++i) {
		::proto_ff::Proto_HMLineRateMgr_item* temp_icon = msg.add_icon();
		Proto_HMLineRateMgr_item_s::write_to_pbmsg(obj.icon[i], *temp_icon);
	}
}

void Proto_HMLineRateMgr_icon_s::read_from_pbmsg(const ::proto_ff::Proto_HMLineRateMgr_icon & msg, struct Proto_HMLineRateMgr_icon_s & obj) {
	memset(&obj, 0, sizeof(struct Proto_HMLineRateMgr_icon_s));
	obj.icon.SetSize(msg.icon_size() > obj.icon.GetMaxSize() ? obj.icon.GetMaxSize() : msg.icon_size());
	for(int32_t i = 0; i < obj.icon.GetSize(); ++i) {
		const ::proto_ff::Proto_HMLineRateMgr_item & temp_icon = msg.icon(i);
		Proto_HMLineRateMgr_item_s::read_from_pbmsg(temp_icon, obj.icon[i]);
	}
}

Proto_HMLineRateMgr_mary_s::Proto_HMLineRateMgr_mary_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Proto_HMLineRateMgr_mary_s::CreateInit() {
	return 0;
}

int Proto_HMLineRateMgr_mary_s::ResumeInit() {
	return 0;
}

void Proto_HMLineRateMgr_mary_s::write_to_pbmsg(const struct Proto_HMLineRateMgr_mary_s & obj, ::proto_ff::Proto_HMLineRateMgr_mary & msg) {
	for(int32_t i = 0; i < obj.IconRight.GetSize() && i < obj.IconRight.GetMaxSize(); ++i) {
		msg.add_iconright((int32_t)obj.IconRight[i]);
	}
}

void Proto_HMLineRateMgr_mary_s::read_from_pbmsg(const ::proto_ff::Proto_HMLineRateMgr_mary & msg, struct Proto_HMLineRateMgr_mary_s & obj) {
	memset(&obj, 0, sizeof(struct Proto_HMLineRateMgr_mary_s));
	obj.IconRight.SetSize(msg.iconright_size() > obj.IconRight.GetMaxSize() ? obj.IconRight.GetMaxSize() : msg.iconright_size());
	for(int32_t i = 0; i < obj.IconRight.GetSize(); ++i) {
		obj.IconRight[i] = msg.iconright(i);
	}
}

Proto_HMLineRateMgr_s::Proto_HMLineRateMgr_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Proto_HMLineRateMgr_s::CreateInit() {
	return 0;
}

int Proto_HMLineRateMgr_s::ResumeInit() {
	return 0;
}

void Proto_HMLineRateMgr_s::write_to_pbmsg(const struct Proto_HMLineRateMgr_s & obj, ::proto_ff::Proto_HMLineRateMgr & msg) {
	::proto_ff::Proto_HMLineRateMgr_icon* temp_main = msg.mutable_main();
	Proto_HMLineRateMgr_icon_s::write_to_pbmsg(obj.main, *temp_main);
	::proto_ff::Proto_HMLineRateMgr_icon* temp_free = msg.mutable_free();
	Proto_HMLineRateMgr_icon_s::write_to_pbmsg(obj.free, *temp_free);
	::proto_ff::Proto_HMLineRateMgr_icon* temp_shulaibao = msg.mutable_shulaibao();
	Proto_HMLineRateMgr_icon_s::write_to_pbmsg(obj.shulaibao, *temp_shulaibao);
	::proto_ff::Proto_HMLineRateMgr_mary* temp_mary = msg.mutable_mary();
	Proto_HMLineRateMgr_mary_s::write_to_pbmsg(obj.mary, *temp_mary);
}

void Proto_HMLineRateMgr_s::read_from_pbmsg(const ::proto_ff::Proto_HMLineRateMgr & msg, struct Proto_HMLineRateMgr_s & obj) {
	memset(&obj, 0, sizeof(struct Proto_HMLineRateMgr_s));
	const ::proto_ff::Proto_HMLineRateMgr_icon & temp_main = msg.main();
	Proto_HMLineRateMgr_icon_s::read_from_pbmsg(temp_main, obj.main);
	const ::proto_ff::Proto_HMLineRateMgr_icon & temp_free = msg.free();
	Proto_HMLineRateMgr_icon_s::read_from_pbmsg(temp_free, obj.free);
	const ::proto_ff::Proto_HMLineRateMgr_icon & temp_shulaibao = msg.shulaibao();
	Proto_HMLineRateMgr_icon_s::read_from_pbmsg(temp_shulaibao, obj.shulaibao);
	const ::proto_ff::Proto_HMLineRateMgr_mary & temp_mary = msg.mary();
	Proto_HMLineRateMgr_mary_s::read_from_pbmsg(temp_mary, obj.mary);
}

Proto_HMRecordItem_Row_s::Proto_HMRecordItem_Row_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Proto_HMRecordItem_Row_s::CreateInit() {
	return 0;
}

int Proto_HMRecordItem_Row_s::ResumeInit() {
	return 0;
}

void Proto_HMRecordItem_Row_s::write_to_pbmsg(const struct Proto_HMRecordItem_Row_s & obj, ::proto_ff::Proto_HMRecordItem_Row & msg) {
	for(int32_t i = 0; i < obj.col.GetSize() && i < obj.col.GetMaxSize(); ++i) {
		msg.add_col((int32_t)obj.col[i]);
	}
}

void Proto_HMRecordItem_Row_s::read_from_pbmsg(const ::proto_ff::Proto_HMRecordItem_Row & msg, struct Proto_HMRecordItem_Row_s & obj) {
	memset(&obj, 0, sizeof(struct Proto_HMRecordItem_Row_s));
	obj.col.SetSize(msg.col_size() > obj.col.GetMaxSize() ? obj.col.GetMaxSize() : msg.col_size());
	for(int32_t i = 0; i < obj.col.GetSize(); ++i) {
		obj.col[i] = msg.col(i);
	}
}

Proto_HMRecordItem_s::Proto_HMRecordItem_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Proto_HMRecordItem_s::CreateInit() {
	return 0;
}

int Proto_HMRecordItem_s::ResumeInit() {
	return 0;
}

void Proto_HMRecordItem_s::write_to_pbmsg(const struct Proto_HMRecordItem_s & obj, ::proto_ff::Proto_HMRecordItem & msg) {
	for(int32_t i = 0; i < obj.row.GetSize() && i < obj.row.GetMaxSize(); ++i) {
		::proto_ff::Proto_HMRecordItem_Row* temp_row = msg.add_row();
		Proto_HMRecordItem_Row_s::write_to_pbmsg(obj.row[i], *temp_row);
	}
}

void Proto_HMRecordItem_s::read_from_pbmsg(const ::proto_ff::Proto_HMRecordItem & msg, struct Proto_HMRecordItem_s & obj) {
	memset(&obj, 0, sizeof(struct Proto_HMRecordItem_s));
	obj.row.SetSize(msg.row_size() > obj.row.GetMaxSize() ? obj.row.GetMaxSize() : msg.row_size());
	for(int32_t i = 0; i < obj.row.GetSize(); ++i) {
		const ::proto_ff::Proto_HMRecordItem_Row & temp_row = msg.row(i);
		Proto_HMRecordItem_Row_s::read_from_pbmsg(temp_row, obj.row[i]);
	}
}

Proto_MaryResult_s::Proto_MaryResult_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Proto_MaryResult_s::CreateInit() {
	outer_value = (int32_t)0;
	mul = (int32_t)0;
	return 0;
}

int Proto_MaryResult_s::ResumeInit() {
	return 0;
}

void Proto_MaryResult_s::write_to_pbmsg(const struct Proto_MaryResult_s & obj, ::proto_ff::Proto_MaryResult & msg) {
	msg.set_outer_value((int32_t)obj.outer_value);
	msg.set_mul((int32_t)obj.mul);
	for(int32_t i = 0; i < obj.vec_inner_value.GetSize() && i < obj.vec_inner_value.GetMaxSize(); ++i) {
		msg.add_vec_inner_value((int32_t)obj.vec_inner_value[i]);
	}
}

void Proto_MaryResult_s::read_from_pbmsg(const ::proto_ff::Proto_MaryResult & msg, struct Proto_MaryResult_s & obj) {
	memset(&obj, 0, sizeof(struct Proto_MaryResult_s));
	obj.outer_value = msg.outer_value();
	obj.mul = msg.mul();
	obj.vec_inner_value.SetSize(msg.vec_inner_value_size() > obj.vec_inner_value.GetMaxSize() ? obj.vec_inner_value.GetMaxSize() : msg.vec_inner_value_size());
	for(int32_t i = 0; i < obj.vec_inner_value.GetSize(); ++i) {
		obj.vec_inner_value[i] = msg.vec_inner_value(i);
	}
}

Proto_LineColCfg_item_s::Proto_LineColCfg_item_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Proto_LineColCfg_item_s::CreateInit() {
	return 0;
}

int Proto_LineColCfg_item_s::ResumeInit() {
	return 0;
}

void Proto_LineColCfg_item_s::write_to_pbmsg(const struct Proto_LineColCfg_item_s & obj, ::proto_ff::Proto_LineColCfg_item & msg) {
	for(int32_t i = 0; i < obj.item.GetSize() && i < obj.item.GetMaxSize(); ++i) {
		msg.add_item((int32_t)obj.item[i]);
	}
}

void Proto_LineColCfg_item_s::read_from_pbmsg(const ::proto_ff::Proto_LineColCfg_item & msg, struct Proto_LineColCfg_item_s & obj) {
	memset(&obj, 0, sizeof(struct Proto_LineColCfg_item_s));
	obj.item.SetSize(msg.item_size() > obj.item.GetMaxSize() ? obj.item.GetMaxSize() : msg.item_size());
	for(int32_t i = 0; i < obj.item.GetSize(); ++i) {
		obj.item[i] = msg.item(i);
	}
}

Proto_LineColCfg_Col_s::Proto_LineColCfg_Col_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Proto_LineColCfg_Col_s::CreateInit() {
	return 0;
}

int Proto_LineColCfg_Col_s::ResumeInit() {
	return 0;
}

void Proto_LineColCfg_Col_s::write_to_pbmsg(const struct Proto_LineColCfg_Col_s & obj, ::proto_ff::Proto_LineColCfg_Col & msg) {
	for(int32_t i = 0; i < obj.Col.GetSize() && i < obj.Col.GetMaxSize(); ++i) {
		::proto_ff::Proto_LineColCfg_item* temp_col = msg.add_col();
		Proto_LineColCfg_item_s::write_to_pbmsg(obj.Col[i], *temp_col);
	}
}

void Proto_LineColCfg_Col_s::read_from_pbmsg(const ::proto_ff::Proto_LineColCfg_Col & msg, struct Proto_LineColCfg_Col_s & obj) {
	memset(&obj, 0, sizeof(struct Proto_LineColCfg_Col_s));
	obj.Col.SetSize(msg.col_size() > obj.Col.GetMaxSize() ? obj.Col.GetMaxSize() : msg.col_size());
	for(int32_t i = 0; i < obj.Col.GetSize(); ++i) {
		const ::proto_ff::Proto_LineColCfg_item & temp_col = msg.col(i);
		Proto_LineColCfg_item_s::read_from_pbmsg(temp_col, obj.Col[i]);
	}
}

Proto_LineColCfg_s::Proto_LineColCfg_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Proto_LineColCfg_s::CreateInit() {
	return 0;
}

int Proto_LineColCfg_s::ResumeInit() {
	return 0;
}

void Proto_LineColCfg_s::write_to_pbmsg(const struct Proto_LineColCfg_s & obj, ::proto_ff::Proto_LineColCfg & msg) {
	::proto_ff::Proto_LineColCfg_Col* temp_main = msg.mutable_main();
	Proto_LineColCfg_Col_s::write_to_pbmsg(obj.main, *temp_main);
	::proto_ff::Proto_LineColCfg_Col* temp_free = msg.mutable_free();
	Proto_LineColCfg_Col_s::write_to_pbmsg(obj.free, *temp_free);
	::proto_ff::Proto_LineColCfg_Col* temp_shulaibao = msg.mutable_shulaibao();
	Proto_LineColCfg_Col_s::write_to_pbmsg(obj.shulaibao, *temp_shulaibao);
	::proto_ff::Proto_LineColCfg_Col* temp_bubugao = msg.mutable_bubugao();
	Proto_LineColCfg_Col_s::write_to_pbmsg(obj.bubugao, *temp_bubugao);
}

void Proto_LineColCfg_s::read_from_pbmsg(const ::proto_ff::Proto_LineColCfg & msg, struct Proto_LineColCfg_s & obj) {
	memset(&obj, 0, sizeof(struct Proto_LineColCfg_s));
	const ::proto_ff::Proto_LineColCfg_Col & temp_main = msg.main();
	Proto_LineColCfg_Col_s::read_from_pbmsg(temp_main, obj.main);
	const ::proto_ff::Proto_LineColCfg_Col & temp_free = msg.free();
	Proto_LineColCfg_Col_s::read_from_pbmsg(temp_free, obj.free);
	const ::proto_ff::Proto_LineColCfg_Col & temp_shulaibao = msg.shulaibao();
	Proto_LineColCfg_Col_s::read_from_pbmsg(temp_shulaibao, obj.shulaibao);
	const ::proto_ff::Proto_LineColCfg_Col & temp_bubugao = msg.bubugao();
	Proto_LineColCfg_Col_s::read_from_pbmsg(temp_bubugao, obj.bubugao);
}

Proto_LinkResult_item_s::Proto_LinkResult_item_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Proto_LinkResult_item_s::CreateInit() {
	return 0;
}

int Proto_LinkResult_item_s::ResumeInit() {
	return 0;
}

void Proto_LinkResult_item_s::write_to_pbmsg(const struct Proto_LinkResult_item_s & obj, ::proto_ff::Proto_LinkResult_item & msg) {
	for(int32_t i = 0; i < obj.item.GetSize() && i < obj.item.GetMaxSize(); ++i) {
		msg.add_item((int32_t)obj.item[i]);
	}
}

void Proto_LinkResult_item_s::read_from_pbmsg(const ::proto_ff::Proto_LinkResult_item & msg, struct Proto_LinkResult_item_s & obj) {
	memset(&obj, 0, sizeof(struct Proto_LinkResult_item_s));
	obj.item.SetSize(msg.item_size() > obj.item.GetMaxSize() ? obj.item.GetMaxSize() : msg.item_size());
	for(int32_t i = 0; i < obj.item.GetSize(); ++i) {
		obj.item[i] = msg.item(i);
	}
}

Proto_LinkResult_Row_s::Proto_LinkResult_Row_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Proto_LinkResult_Row_s::CreateInit() {
	resulttype = (int32_t)0;
	rowcount = (int32_t)0;
	colcount = (int32_t)0;
	return 0;
}

int Proto_LinkResult_Row_s::ResumeInit() {
	return 0;
}

void Proto_LinkResult_Row_s::write_to_pbmsg(const struct Proto_LinkResult_Row_s & obj, ::proto_ff::Proto_LinkResult_Row & msg) {
	for(int32_t i = 0; i < obj.Row.GetSize() && i < obj.Row.GetMaxSize(); ++i) {
		::proto_ff::Proto_LineColCfg_item* temp_row = msg.add_row();
		Proto_LineColCfg_item_s::write_to_pbmsg(obj.Row[i], *temp_row);
	}
	msg.set_resulttype((int32_t)obj.resulttype);
	msg.set_rowcount((int32_t)obj.rowcount);
	msg.set_colcount((int32_t)obj.colcount);
}

void Proto_LinkResult_Row_s::read_from_pbmsg(const ::proto_ff::Proto_LinkResult_Row & msg, struct Proto_LinkResult_Row_s & obj) {
	memset(&obj, 0, sizeof(struct Proto_LinkResult_Row_s));
	obj.Row.SetSize(msg.row_size() > obj.Row.GetMaxSize() ? obj.Row.GetMaxSize() : msg.row_size());
	for(int32_t i = 0; i < obj.Row.GetSize(); ++i) {
		const ::proto_ff::Proto_LineColCfg_item & temp_row = msg.row(i);
		Proto_LineColCfg_item_s::read_from_pbmsg(temp_row, obj.Row[i]);
	}
	obj.resulttype = msg.resulttype();
	obj.rowcount = msg.rowcount();
	obj.colcount = msg.colcount();
}

Proto_LinkResult_s::Proto_LinkResult_s() {
	if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
		CreateInit();
	} else {
		ResumeInit();
	}
}

int Proto_LinkResult_s::CreateInit() {
	return 0;
}

int Proto_LinkResult_s::ResumeInit() {
	return 0;
}

void Proto_LinkResult_s::write_to_pbmsg(const struct Proto_LinkResult_s & obj, ::proto_ff::Proto_LinkResult & msg) {
	::proto_ff::Proto_LinkResult_Row* temp_config = msg.mutable_config();
	Proto_LinkResult_Row_s::write_to_pbmsg(obj.config, *temp_config);
}

void Proto_LinkResult_s::read_from_pbmsg(const ::proto_ff::Proto_LinkResult & msg, struct Proto_LinkResult_s & obj) {
	memset(&obj, 0, sizeof(struct Proto_LinkResult_s));
	const ::proto_ff::Proto_LinkResult_Row & temp_config = msg.config();
	Proto_LinkResult_Row_s::read_from_pbmsg(temp_config, obj.config);
}

}