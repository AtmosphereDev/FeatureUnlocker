#include "api/memory/Hook.h"
#include "api/Logger.h"
#include "api/Config.h"

#include <functional>
#include <string>
#include "api/memory/android/Memory.h"
#include "mc/FeatureOptionID.h"

#define CONFIG "/storage/emulated/0/games/org.levimc/minecraft/com.mojang.minecraftpe/mods/FeatureUnlocker"

Config config;

bool isEnabled(FeatureOptionID featureID) {
    if (!config.isLoaded()) config.load(CONFIG);
    for (int i : config.getEnabled()) {
        if (i == (int)featureID) return true;
    }
    return false;
}

bool isDisabled(FeatureOptionID featureID) {
    if (!config.isLoaded()) config.load(CONFIG);
    for (int i : config.getDisabled()) {
        if (i == (int)featureID) return true;
    }
    return false;
}

// FeatureToggle::_registerFeature
ATM_AUTO_STATIC_HOOK(
  FeatureToggleRegisterFeatureHook,
  memory::HookPriority::Normal,
  "? ? ? D1 ? ? ? A9 ? ? ? 91 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? D5 F3 03 00 AA ? ? ? F9 ? ? ? 52 F7 03 07 AA F8 03 06 2A",
  void,
  void* ptr,
  int                            tabID,
  FeatureOptionID                featureID,
  std::string const&             locName,
  std::string const&             saveName,
  bool                           defaultValue,
  int                            dependencyFeatureID,
  std::function<void(void)>      setup,
  std::function<void(bool&)>     lock
) {
    if (isEnabled(featureID)) {
        LOGI("[FeatureUnlocker] Enable feature: %s", locName.c_str());
        return origin(ptr, tabID, featureID, locName, saveName, true, dependencyFeatureID, setup, lock);
    }
    if (isDisabled(featureID)) {
        LOGI("[FeatureUnlocker] Disable feature: %s", locName.c_str());
        return origin(ptr, tabID, featureID, locName, saveName, false, dependencyFeatureID, setup, lock);
    }
    return origin(ptr, tabID, featureID, locName, saveName, defaultValue, dependencyFeatureID, setup, lock);
}