#pragma once
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <sstream>
#include <super/type/token.h>
#include <super/config.h>

#if SUPER_DEBUG == 1
#define SUPER_ERROR_SHOW_FILE_LINE __FILE__ + ":" + std::to_string(__LINE__)
#endif
#if SUPER_DEBUG == 0
#define SUPER_ERROR_SHOW_FILE_LINE ""
#endif

#define SUPER_ERROR(file, msg, token) \
	throw Super::Error::NewError(file, msg + "\n" + SUPER_ERROR_SHOW_FILE_LINE, token)

#define SUPER_ERROR_A(file, code, token) \
	throw Super::Error::NewError(file, Super::Error::A[code] + "\n" + SUPER_ERROR_SHOW_FILE_LINE, token)

#define SUPER_ERROR_MSG(msg) \
	throw Super::Error::NewError(msg + "\n" + SUPER_ERROR_SHOW_FILE_LINE)

namespace Super::Error
{
	extern std::unordered_map<std::string, std::string> A;

	std::string AddIndicate(const std::string &file, const Super::Type::Token &token);
	std::exception NewError(const std::string &file, const std::string &msg, const Super::Type::Token &token);
	std::exception NewError(const std::string &file, const std::string &msg, const std::vector<Super::Type::Token> &tokens);
	std::exception NewError(const std::string &msg);
}