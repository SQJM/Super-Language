#pragma once
#include <string>
#include <vector>

namespace Super::Compile
{
	class RemoveNote
	{
	private:
		std::vector<std::string> _data;
	public:
		RemoveNote(const std::string& fileData);
		std::vector<std::string> GetData() const;
	};
}