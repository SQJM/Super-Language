#pragma once
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <sstream>
#include <super/type/token.h>

#define SUPER_ERROR(file, msg, token) \
	throw Super::Error::NewError(file, msg + "\n" + __FILE__ + ":" + std::to_string(__LINE__), token)

#define SUPER_ERROR_A(file, code, token) \
	throw Super::Error::NewError(file, Super::Error::A[code] + "\n" + __FILE__ + ":" + std::to_string(__LINE__), token)

#define SUPER_ERROR_MSG(msg) \
	throw Super::Error::NewError(msg + "\n" + __FILE__ + ":" + std::to_string(__LINE__))

namespace Super::Error
{
	extern std::unordered_map<std::string, std::string> A;

	std::string AddIndicate(const std::string &file, const Super::Type::Token &token);
	std::exception NewError(const std::string &file, const std::string &msg, const Super::Type::Token &token);
	std::exception NewError(const std::string &file, const std::string &msg, const std::vector<Super::Type::Token> &tokens);
	std::exception NewError(const std::string &msg);
}