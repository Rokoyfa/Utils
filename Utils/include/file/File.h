#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>


namespace r_utils {
	namespace io {

		class File
		{
		public:
			explicit File(std::string filePath);

			[[nodiscard]] bool exists() const;
			[[nodiscard]] std::string read() const;
			bool write(std::string& content);
			bool append(std::string& content);

			bool remove();
			bool create();

			std::string getFilePath() const;
		private:
			std::string filePath;
		};
	} // io
} // r_utils