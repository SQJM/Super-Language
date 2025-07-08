#pragma once
#include <string>
#include <vector>

namespace Super::Compile
{
	class RemoveNote
	{
	private:
		std::vector<std::wstring> _data;
	public:
		RemoveNote(const std::wstring& fileData);
		std::vector<std::wstring> GetData() const;
	};
}