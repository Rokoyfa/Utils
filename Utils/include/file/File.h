#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>

namespace r_utils {
	namespace io {

		class File
		{
		public:
			File(std::string filePath);

			bool exists() const;
			std::string read() const;
			bool write(std::string content);
			bool append(std::string content);

			bool remove();
			bool create();

			std::string getFilePath() const;
		private:
			std::string filePath;
		};
	}
}