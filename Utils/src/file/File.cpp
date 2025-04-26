#include "file/File.h"

namespace r_utils {
    namespace io {

        File::File(std::string filePath) : filePath(filePath) {}


        bool File::exists() const {
            return std::filesystem::exists(filePath);
        }

        std::string File::read() const {
            std::ifstream in(filePath);
            if (!in.is_open()) {
                throw std::runtime_error("Failed to open file: " + filePath);
            }

            std::stringstream buffer;
            buffer << in.rdbuf();
            return buffer.str();
        }

        bool File::write(std::string content)
        {
            std::ofstream out(this->getFilePath());

            if (!out.is_open())
            {
                return false;
            }

            out << content;
            out.close();

            return true;
        }

        bool File::append(std::string content)
        {
            std::ofstream out(this->getFilePath(), std::ios::app);

            if (!out.is_open())
            {
                return false;
            }

            out << content;
            out.close();

            return true;
        }


        bool File::remove() {
            return std::filesystem::remove(filePath);
        }

        bool File::create() {
            std::ofstream out(filePath);
            if (!out.is_open()) {
                return false;
            }
            out.close();
            return true;
        }


        std::string File::getFilePath()
        {
            return this->filePath;
        }
    }
}