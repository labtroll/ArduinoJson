// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2023, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Variant/VariantRefBase.hpp>

ARDUINOJSON_BEGIN_PRIVATE_NAMESPACE

// A proxy class to get or set a member of an object.
// https://arduinojson.org/v7/api/jsonobject/subscript/
template <typename TUpstream, typename TStringRef>
class MemberProxy
    : public VariantRefBase<MemberProxy<TUpstream, TStringRef>>,
      public VariantOperators<MemberProxy<TUpstream, TStringRef>> {
  friend class VariantAttorney;

 public:
  FORCE_INLINE MemberProxy(TUpstream upstream, TStringRef key)
      : upstream_(upstream), key_(key) {}

  MemberProxy(const MemberProxy& src)
      : upstream_(src.upstream_), key_(src.key_) {}

  FORCE_INLINE MemberProxy& operator=(const MemberProxy& src) {
    this->set(src);
    return *this;
  }

  template <typename T>
  FORCE_INLINE MemberProxy& operator=(const T& src) {
    this->set(src);
    return *this;
  }

  template <typename T>
  FORCE_INLINE MemberProxy& operator=(T* src) {
    this->set(src);
    return *this;
  }

 private:
  FORCE_INLINE ResourceManager* getResourceManager() const {
    return VariantAttorney::getResourceManager(upstream_);
  }

  FORCE_INLINE VariantData* getData() const {
    return VariantData::getMember(
        VariantAttorney::getData(upstream_), adaptString(key_),
        VariantAttorney::getResourceManager(upstream_));
  }

  FORCE_INLINE VariantData* getOrCreateData() const {
    auto data = VariantAttorney::getOrCreateData(upstream_);
    if (!data)
      return nullptr;
    return data->getOrAddMember(adaptString(key_),
                                VariantAttorney::getResourceManager(upstream_));
  }

 private:
  TUpstream upstream_;
  TStringRef key_;
};

ARDUINOJSON_END_PRIVATE_NAMESPACE
