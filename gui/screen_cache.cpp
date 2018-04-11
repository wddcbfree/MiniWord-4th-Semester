#include "screen_cache.h"

void ScreenCache::RefreshCache(Text text) {
    int lines = text.GetNumOfLines();
    ScreenInfo position = text.GetPosition();
    cache_.clear();
    for (int i = position.screen_y - 1; i < lines; ++i) {
        cache_.push_back(text.GetIthString(i + 1).substr(position.screen_x - 1, COLUME_NUMBER));
    }
    return;
}

std::string ScreenCache::GetCacheIthLines(int i) {
    if (i <= cache_.end() - cache_.begin()) {
        return cache_[i + 1];
    }
    else {
        return std::string();
    }
}

ScreenInfo ScreenCache::GetScreenInfo(Text text) {
    return text.GetPosition();
}
