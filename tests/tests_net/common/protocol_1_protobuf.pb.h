// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protocol_1_protobuf.proto

#ifndef PROTOBUF_protocol_5f1_5fprotobuf_2eproto__INCLUDED
#define PROTOBUF_protocol_5f1_5fprotobuf_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace tutorial {
class LoginAck;
class LoginAckDefaultTypeInternal;
extern LoginAckDefaultTypeInternal _LoginAck_default_instance_;
class LoginReq;
class LoginReqDefaultTypeInternal;
extern LoginReqDefaultTypeInternal _LoginReq_default_instance_;
}  // namespace tutorial

namespace tutorial {

namespace protobuf_protocol_5f1_5fprotobuf_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static void InitDefaultsImpl();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_protocol_5f1_5fprotobuf_2eproto

// ===================================================================

class LoginReq : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tutorial.LoginReq) */ {
 public:
  LoginReq();
  virtual ~LoginReq();

  LoginReq(const LoginReq& from);

  inline LoginReq& operator=(const LoginReq& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  LoginReq(LoginReq&& from) noexcept
    : LoginReq() {
    *this = ::std::move(from);
  }

  inline LoginReq& operator=(LoginReq&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const LoginReq& default_instance();

  static inline const LoginReq* internal_default_instance() {
    return reinterpret_cast<const LoginReq*>(
               &_LoginReq_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(LoginReq* other);
  friend void swap(LoginReq& a, LoginReq& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline LoginReq* New() const PROTOBUF_FINAL { return New(NULL); }

  LoginReq* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const LoginReq& from);
  void MergeFrom(const LoginReq& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(LoginReq* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string id = 1;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 1;
  const ::std::string& id() const;
  void set_id(const ::std::string& value);
  #if LANG_CXX11
  void set_id(::std::string&& value);
  #endif
  void set_id(const char* value);
  void set_id(const char* value, size_t size);
  ::std::string* mutable_id();
  ::std::string* release_id();
  void set_allocated_id(::std::string* id);

  // @@protoc_insertion_point(class_scope:tutorial.LoginReq)
 private:
  void set_has_id();
  void clear_has_id();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  friend struct protobuf_protocol_5f1_5fprotobuf_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class LoginAck : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tutorial.LoginAck) */ {
 public:
  LoginAck();
  virtual ~LoginAck();

  LoginAck(const LoginAck& from);

  inline LoginAck& operator=(const LoginAck& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  LoginAck(LoginAck&& from) noexcept
    : LoginAck() {
    *this = ::std::move(from);
  }

  inline LoginAck& operator=(LoginAck&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const LoginAck& default_instance();

  static inline const LoginAck* internal_default_instance() {
    return reinterpret_cast<const LoginAck*>(
               &_LoginAck_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(LoginAck* other);
  friend void swap(LoginAck& a, LoginAck& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline LoginAck* New() const PROTOBUF_FINAL { return New(NULL); }

  LoginAck* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const LoginAck& from);
  void MergeFrom(const LoginAck& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(LoginAck* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string name = 1;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // required uint64 accNo = 2;
  bool has_accno() const;
  void clear_accno();
  static const int kAccNoFieldNumber = 2;
  ::google::protobuf::uint64 accno() const;
  void set_accno(::google::protobuf::uint64 value);

  // required uint64 money = 3;
  bool has_money() const;
  void clear_money();
  static const int kMoneyFieldNumber = 3;
  ::google::protobuf::uint64 money() const;
  void set_money(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:tutorial.LoginAck)
 private:
  void set_has_name();
  void clear_has_name();
  void set_has_accno();
  void clear_has_accno();
  void set_has_money();
  void clear_has_money();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::uint64 accno_;
  ::google::protobuf::uint64 money_;
  friend struct protobuf_protocol_5f1_5fprotobuf_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// LoginReq

// required string id = 1;
inline bool LoginReq::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LoginReq::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LoginReq::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LoginReq::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_id();
}
inline const ::std::string& LoginReq::id() const {
  // @@protoc_insertion_point(field_get:tutorial.LoginReq.id)
  return id_.GetNoArena();
}
inline void LoginReq::set_id(const ::std::string& value) {
  set_has_id();
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tutorial.LoginReq.id)
}
#if LANG_CXX11
inline void LoginReq::set_id(::std::string&& value) {
  set_has_id();
  id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:tutorial.LoginReq.id)
}
#endif
inline void LoginReq::set_id(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_id();
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tutorial.LoginReq.id)
}
inline void LoginReq::set_id(const char* value, size_t size) {
  set_has_id();
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tutorial.LoginReq.id)
}
inline ::std::string* LoginReq::mutable_id() {
  set_has_id();
  // @@protoc_insertion_point(field_mutable:tutorial.LoginReq.id)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* LoginReq::release_id() {
  // @@protoc_insertion_point(field_release:tutorial.LoginReq.id)
  clear_has_id();
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void LoginReq::set_allocated_id(::std::string* id) {
  if (id != NULL) {
    set_has_id();
  } else {
    clear_has_id();
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:tutorial.LoginReq.id)
}

// -------------------------------------------------------------------

// LoginAck

// required string name = 1;
inline bool LoginAck::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LoginAck::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LoginAck::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LoginAck::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& LoginAck::name() const {
  // @@protoc_insertion_point(field_get:tutorial.LoginAck.name)
  return name_.GetNoArena();
}
inline void LoginAck::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tutorial.LoginAck.name)
}
#if LANG_CXX11
inline void LoginAck::set_name(::std::string&& value) {
  set_has_name();
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:tutorial.LoginAck.name)
}
#endif
inline void LoginAck::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tutorial.LoginAck.name)
}
inline void LoginAck::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tutorial.LoginAck.name)
}
inline ::std::string* LoginAck::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:tutorial.LoginAck.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* LoginAck::release_name() {
  // @@protoc_insertion_point(field_release:tutorial.LoginAck.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void LoginAck::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:tutorial.LoginAck.name)
}

// required uint64 accNo = 2;
inline bool LoginAck::has_accno() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LoginAck::set_has_accno() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LoginAck::clear_has_accno() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LoginAck::clear_accno() {
  accno_ = GOOGLE_ULONGLONG(0);
  clear_has_accno();
}
inline ::google::protobuf::uint64 LoginAck::accno() const {
  // @@protoc_insertion_point(field_get:tutorial.LoginAck.accNo)
  return accno_;
}
inline void LoginAck::set_accno(::google::protobuf::uint64 value) {
  set_has_accno();
  accno_ = value;
  // @@protoc_insertion_point(field_set:tutorial.LoginAck.accNo)
}

// required uint64 money = 3;
inline bool LoginAck::has_money() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void LoginAck::set_has_money() {
  _has_bits_[0] |= 0x00000004u;
}
inline void LoginAck::clear_has_money() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void LoginAck::clear_money() {
  money_ = GOOGLE_ULONGLONG(0);
  clear_has_money();
}
inline ::google::protobuf::uint64 LoginAck::money() const {
  // @@protoc_insertion_point(field_get:tutorial.LoginAck.money)
  return money_;
}
inline void LoginAck::set_money(::google::protobuf::uint64 value) {
  set_has_money();
  money_ = value;
  // @@protoc_insertion_point(field_set:tutorial.LoginAck.money)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace tutorial

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_protocol_5f1_5fprotobuf_2eproto__INCLUDED