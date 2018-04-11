#pragma once
#ifndef SCRESS_CACHE_CLASS_
#define SCRESS_CACHE_CLASS_

#include <string>
#include <vector>
#include "stl_implement_text_class.h"

class ScreenCache {
public:
    void RefreshCache(Text text);
    std::string GetCacheIthLines(int i);
    ScreenInfo GetScreenInfo(Text text);
private:
    std::vector<std::string> cache_;
};

#endif // !SCRESS_CACHE_CLASS_
