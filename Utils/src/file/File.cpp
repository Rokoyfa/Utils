#include "file/File.h"

#include "exception/file/FileException.h"
#include <fstream>
#include <sstream>
#include <filesystem>

namespace r_utils 
{
    namespace io 
    {

        File::File(std::string filePath) : filePath(std::move(filePath)) 
        {
            if (this->filePath.empty()) 
            {
                throw r_utils::exception::FileException("The path to the file must not be empty.");
            }
        }

        bool File::exists() const 
        {
            try 
            {
                return std::filesystem::exists(filePath);
            }
            catch (const std::filesystem::filesystem_error& e) {
                throw r_utils::exception::FileException("Error checking file existence: " + std::string(e.what()));
            }
        }

        std::string File::read() const 
        {
            std::ifstream in(filePath);
            if (!in.is_open()) 
            {
                throw r_utils::exception::FileException("Failed to open file: \"" + filePath + "\"");
            }

            std::stringstream buffer;
            buffer << in.rdbuf();
            return buffer.str();
        }

        bool File::write(const std::string& content) const
        {
            std::ofstream out(filePath);
            if (!out.is_open()) 
            {
                throw r_utils::exception::FileException("Failed to open file for writing: \"" + filePath + "\"");
            }

            if (!(out << content)) 
            {
                throw r_utils::exception::FileException("Error writing to file: " + filePath);
            }

            return true;
        }

        bool File::append(const std::string& content) const
        {
            std::ofstream out(filePath, std::ios::app);
            if (!out.is_open()) 
            {
                throw r_utils::exception::FileException("Failed to open file for appending: \"" + filePath + "\"");
            }

            if (!(out << content)) 
            {
                throw r_utils::exception::FileException("Error appending to file: " + filePath);
            }

            return true;
        }


        bool File::remove() 
        {
            try {
                if (!std::filesystem::remove(filePath)) 
                {
                    throw r_utils::exception::FileException("File could not be deleted (maybe doesn't exist): " + filePath);
                }
                return true;
            }
            catch (const std::filesystem::filesystem_error& e) 
            {
                throw r_utils::exception::FileException("Error deleting the file: " + std::string(e.what()));
            }
        }

        bool File::create() const 
        {
            std::ofstream out(filePath);
            if (!out.is_open()) 
            {
                throw r_utils::exception::FileException("File could not be created: " + filePath);
            }
            return true;
        }

        std::string File::getFilePath() const 
        {
            return filePath;
        }
    } // io
} // r_utils