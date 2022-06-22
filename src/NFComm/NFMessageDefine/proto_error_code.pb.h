// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: proto_error_code.proto

#ifndef PROTOBUF_proto_5ferror_5fcode_2eproto__INCLUDED
#define PROTOBUF_proto_5ferror_5fcode_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)

namespace proto_ff {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_proto_5ferror_5fcode_2eproto();
void protobuf_AssignDesc_proto_5ferror_5fcode_2eproto();
void protobuf_ShutdownFile_proto_5ferror_5fcode_2eproto();


enum Proto_CS_ErrorCode {
  ERR_CODE_SYSTEM_ERROR = -1,
  ERR_CODE_OK = 0,
  ERR_CODE_SYSTEM_TIMEOUT = 10000,
  ERR_CODE_SYSTEM_DATABASE_ERROR = 10001,
  ERR_CODE_MSG_PARAM_ERROR = 10002,
  ERR_CODE_ACCOUNT_PASSWORD_ERROR = 10101,
  ERR_CODE_NEED_RELOGIN = 10102,
  ERR_CODE_ACCOUNT_NOT_EXIST = 10103,
  ERR_CODE_PLAYER_NOT_EXIST = 10104,
  ERR_CODE_TOKEN_ERROR = 10106,
  ERR_CODE_TOKEN_TIMEOUT = 10107,
  ERR_CODE_ACCOUNT_ALREADY_EXIST_NO_RESITER = 10108,
  ERR_CODE_BIND_PHONE_ALREADY = 10109,
  ERR_CODE_PHONE_AUTO_CODE_ERROR = 10110,
  ERR_CODE_PHONE_AUTO_CODE_TIMEOUT = 10111,
  ERR_CODE_PHONE_SEND_TOO_MUCH = 10112,
  ERR_CODE_PHONE_NOT_RIGHT = 10113,
  ERR_CODE_PHONE_ALREADY_BIND = 10114,
  ERR_CODE_VISITOR_LOGIN_DEVICE_ERROR = 10115,
  ERR_CODE_PASSWORD_NOT_CHANGE = 10120,
  ERR_CODE_OTHER_PLACE_LOGIN_ACCOUNT = 10121,
  ERR_CODE_USER_IS_BAN = 10122,
  ERR_CODE_USER_IS_NO_TRANSFER = 10123,
  ERR_CODE_USER_AGENT_DEAD_CYCLE = 10124,
  ERR_CODE_PLAYER_OFFLINE = 10200,
  ERR_CODE_WORLD_MAX_PLAYER_COUNT = 10201,
  ERR_CODE_GAME_ROOM_NOT_ONLINE = 10202,
  ERR_CODE_GAME_ROOM_NOT_EXIST = 10203,
  ERR_CODE_MAIL_CANT_DEL_NO_READ = 10300,
  ERR_CODE_ROLE_MAIL_NOT_FIND = 10301,
  ERR_CODE_GET_MAIL_FAIL = 10304,
  ERR_CODE_READ_MAIL_FAIL = 10305,
  ERR_CODE_DEL_MAIL_FAIL = 10306,
  ERR_CODE_BANK_PASSWORD_NOT_RIGHT = 10400,
  ERR_CODE_BANK_PASSWORD_FORMAT_NOT_RIGHT = 10401,
  ERR_CODE_FACE_NOT_EXIST = 10402,
  ERR_CODE_BANK_GIVE_MONEY_NOT_TO_MYSELF = 10403,
  ERR_CODE_IN_GAMEING_NOT_BANK = 10404,
  ERR_CODE_FIRST_BIND_PHONE = 10405,
  ERR_CODE_BANK_NOT_VIP_ZHUAN_NOT_VIP = 10406,
  ERR_CODE_BANK_DRAW_MIN_JETTON = 10407,
  ERR_CODE_MODIFY_MONEY_LESS_ZERO = 10501,
  ERR_CODE_MODIFY_MONEY_TIMEOUT = 10502,
  ERR_CODE_PLAYER_ALREADY_BIND_PHONE = 10503,
  ERR_CODE_PLAYER_DONOT_CHANGE_PHONE = 10504,
  ERR_CODE_PLAYER_PHONE_AUTO_CODE_TOO_MUCH = 10505,
  ERR_CODE_EXIT_NOT_PERMITED_WHILE_PLAYING = 10600,
  EOT_CODE_REDEEM_CODE_USED = 10700,
  EOT_CODE_REDEEM_CODE_NOT_EXIST = 10701,
  EOT_CODE_REDEEM_CODE_UNREG_USER = 10702,
  EOT_CODE_REDEEM_CODE_HAS_USED = 10703,
  ERR_CODE_USER_MONEY_NOT_ENOUGH = 11000,
  ERR_CODE_USER_IN_GAMEING = 11001,
  ERR_CODE_CHAIR_HAS_OTHER_PLAYTER = 11002,
  ERR_CODE_CHAIR_NOT_RIGHT = 11003,
  ERR_CODE_USER_MONEY_TOO_MUCH = 11004,
  ERR_CODE_DESK_NOT_EXIST = 11005
};
bool Proto_CS_ErrorCode_IsValid(int value);
const Proto_CS_ErrorCode Proto_CS_ErrorCode_MIN = ERR_CODE_SYSTEM_ERROR;
const Proto_CS_ErrorCode Proto_CS_ErrorCode_MAX = ERR_CODE_DESK_NOT_EXIST;
const int Proto_CS_ErrorCode_ARRAYSIZE = Proto_CS_ErrorCode_MAX + 1;

const ::google::protobuf::EnumDescriptor* Proto_CS_ErrorCode_descriptor();
inline const ::std::string& Proto_CS_ErrorCode_Name(Proto_CS_ErrorCode value) {
  return ::google::protobuf::internal::NameOfEnum(
    Proto_CS_ErrorCode_descriptor(), value);
}
inline bool Proto_CS_ErrorCode_Parse(
    const ::std::string& name, Proto_CS_ErrorCode* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Proto_CS_ErrorCode>(
    Proto_CS_ErrorCode_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto_ff

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto_ff::Proto_CS_ErrorCode>() {
  return ::proto_ff::Proto_CS_ErrorCode_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_proto_5ferror_5fcode_2eproto__INCLUDED
