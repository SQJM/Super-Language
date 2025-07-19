#pragma once
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <sstream>
#include <super/type/token.h>
#include <super/config.h>


#define SUPER_ERROR(file, msg, token) \
	Super::Error::NewError(file, msg + L"\n" , token);

#define SUPER_ERROR_CODE(file, code, token) \
	Super::Error::NewError(file, Super::Error::CODE[code] + L"\n" , token);

#define SUPER_ERROR_THROW(file, msg, token) \
	Super::Error::NewError(file, msg + L"\n" , token);exit(0);

#define SUPER_ERROR_THROW_CODE(file, code, token) \
	Super::Error::NewError(file, Super::Error::CODE[code] + L"\n" , token);exit(0);

#define SUPER_ERROR_THROW_CODE_NONE(file, code) \
	Super::Error::NewError(file, Super::Error::CODE[code] + L"\n" , Super::Type::GetNoneToken());exit(0);

namespace Super::Error
{
	extern std::unordered_map<std::wstring, std::wstring> CODE;

	void NewError(const std::wstring &file, const std::wstring &msg, const Super::Type::Token &token);
}