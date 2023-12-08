#pragma once

#include <stdint.h>

using ErrorCode = uint8_t;

static constexpr ErrorCode ERR_OK = 0;
static constexpr ErrorCode ERR_FILENOTEXIST = 1;
static constexpr ErrorCode ERR_FILENOTOPEN = 2;
static constexpr ErrorCode ERR_FILEEMPTY = 3;
static constexpr ErrorCode ERR_FOLDERNOTEXIST = 4;
