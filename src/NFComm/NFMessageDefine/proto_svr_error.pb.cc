// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: proto_svr_error.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "proto_svr_error.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace proto_ff {

namespace {

const ::google::protobuf::EnumDescriptor* Proto_SVR_ErrorCode_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_proto_5fsvr_5ferror_2eproto() {
  protobuf_AddDesc_proto_5fsvr_5ferror_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "proto_svr_error.proto");
  GOOGLE_CHECK(file != NULL);
  Proto_SVR_ErrorCode_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_proto_5fsvr_5ferror_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_proto_5fsvr_5ferror_2eproto() {
}

void protobuf_AddDesc_proto_5fsvr_5ferror_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\025proto_svr_error.proto\022\010proto_ff*X\n\023Pro"
    "to_SVR_ErrorCode\022)\n\034ERR_CODE_SERVER_SYST"
    "EM_ERROR\020\377\377\377\377\377\377\377\377\377\001\022\026\n\022ERR_CODE_SERVER_O"
    "K\020\000", 123);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "proto_svr_error.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_proto_5fsvr_5ferror_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_proto_5fsvr_5ferror_2eproto {
  StaticDescriptorInitializer_proto_5fsvr_5ferror_2eproto() {
    protobuf_AddDesc_proto_5fsvr_5ferror_2eproto();
  }
} static_descriptor_initializer_proto_5fsvr_5ferror_2eproto_;
const ::google::protobuf::EnumDescriptor* Proto_SVR_ErrorCode_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Proto_SVR_ErrorCode_descriptor_;
}
bool Proto_SVR_ErrorCode_IsValid(int value) {
  switch(value) {
    case -1:
    case 0:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto_ff

// @@protoc_insertion_point(global_scope)
