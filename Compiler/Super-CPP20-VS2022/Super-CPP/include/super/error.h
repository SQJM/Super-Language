#pragma once
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <sstream>
#include <super/type/token.h>
#include <super/config.h>

// TODO: 我可能需要实现一个 EXIT 功能来替代 exit(0) 这种方式

#define SUPER_ERROR_CACHE(file, msg, token) \
	Super::Error::CacheError(file, msg + L"\n" , token);

#define SUPER_ERROR_CODE_CACHE(file, code, token) \
	Super::Error::CacheError(file, Super::Error::CODE[code] + L"\n" , token);

#define SUPER_ERROR_CACHE_OUT \
	Super::Error::CacheOut();exit(0);

#define SUPER_ERROR_THROW(file, msg, token) \
	Super::Error::NewError(file, msg + L"\n" , token);exit(0);

#define SUPER_ERROR_THROW_CODE(file, code, token) \
	Super::Error::NewError(file, Super::Error::CODE[code] + L"\n" , token);exit(0);

#define SUPER_ERROR_THROW_CODE_NONE(file, code) \
	Super::Error::NewError(file, Super::Error::CODE[code] + L"\n" , Super::Type::GetNoneToken());exit(0);

namespace Super::Error
{
	extern std::unordered_map<std::wstring, std::wstring> CODE;

	extern std::wstring _cacheError;

	void NewError(const std::wstring &file, const std::wstring &msg, const Super::Type::Token &token);

	void CacheError(const std::wstring& file, const std::wstring& msg, const Super::Type::Token& token);

	void CacheOut();
}