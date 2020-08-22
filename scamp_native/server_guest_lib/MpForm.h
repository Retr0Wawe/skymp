#pragma once
#include "NiPoint3.h"
#include <cstdint>
#include <string.h>
#include <typeinfo>

class WorldState;

class MpForm
{
  friend class WorldState;

public:
  static const char* PrettifyType(const char* typeidName)
  {
#ifdef WIN32
    return typeidName + strlen("class Mp");
#else
    auto name = typeidName;
    while (memcmp(name, "Mp", 2) != 0)
      ++name;
    return name + 2;
#endif
  }

  template <class F>
  static const char* GetFormType()
  {
    return PrettifyType(typeid(F).name());
  }

  static const char* GetFormType(MpForm* form)
  {
    return PrettifyType(typeid(form).name());
  }

  virtual ~MpForm() = default;

  auto GetFormId() const noexcept { return id; }

  MpForm() = default;
  MpForm(const MpForm&) = delete;
  MpForm& operator=(const MpForm&) = delete;

protected:
  auto GetParent() const { return parent; }

  // See WorldState::AddForm
  virtual void Init(uint32_t formId) { id = formId; };

private:
  virtual void BeforeDestroy(){};

  uint32_t id = 0;
  WorldState* parent = nullptr;
};