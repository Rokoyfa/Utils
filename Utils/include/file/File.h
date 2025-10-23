#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>


namespace r_utils 
{
	namespace io 
	{

		class File
		{
		public:
			explicit File(std::string filePath);

			[[nodiscard]] bool exists() const;
			[[nodiscard]] std::string read() const;
			bool write(const std::string& content) const;
			bool append(const std::string& content) const;

			bool remove();
			bool create() const;

			std::string getFilePath() const;
		private:
			std::string filePath;
		};
	} // io
} // r_utils