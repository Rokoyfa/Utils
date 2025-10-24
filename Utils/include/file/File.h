#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>

namespace r_utils
{
	namespace io
	{

		/**
		 * @brief Represents a file and provides basic file I/O operations.
		 *
		 * This class encapsulates a file path and offers methods to check existence,
		 * read the entire file, write (overwrite), append, create, and remove the file.
		 *
		 * All operations throw r_utils::exception::FileException on error.
		 */
		class File
		{
		public:
			/**
			 * @brief Constructs a File object for the specified path.
			 * @param filePath The path to the file. Must not be empty.
			 * @throws r_utils::exception::FileException if filePath is empty.
			 */
			explicit File(std::string filePath);

			/**
			 * @brief Checks whether the file exists in the filesystem.
			 * @return true if the file exists, otherwise false.
			 * @throws r_utils::exception::FileException for filesystem-related errors.
			 */
			[[nodiscard]] bool exists() const;

			/**
			 * @brief Reads the entire contents of the file.
			 * @return The file contents as a std::string.
			 * @throws r_utils::exception::FileException if the file cannot be opened.
			 */
			[[nodiscard]] std::string read() const;

			/**
			 * @brief Overwrites the file with the provided content.
			 * @param content The content to write to the file.
			 * @return true on success.
			 * @throws r_utils::exception::FileException on open or write failure.
			 */
			bool write(const std::string& content) const;

			/**
			 * @brief Appends the provided content to the end of the file.
			 * @param content The content to append to the file.
			 * @return true on success.
			 * @throws r_utils::exception::FileException on open or write failure.
			 */
			bool append(const std::string& content) const;

			/**
			 * @brief Removes the file from the filesystem.
			 * @return true if the file was successfully removed.
			 * @throws r_utils::exception::FileException if removal fails.
			 */
			bool remove();

			/**
			 * @brief Creates the file (or truncates it if it exists).
			 * @return true on success.
			 * @throws r_utils::exception::FileException if the file cannot be created.
			 */
			bool create() const;

			/**
			 * @brief Returns the stored file path.
			 * @return The file path as std::string.
			 */
			std::string getFilePath() const;
		private:
			std::string filePath;
		};
	} // io
} // r_utils