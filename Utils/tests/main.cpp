#include <iostream>
#include <string>
#include "json/JsonParser.h"
#include "json/JsonObject.h"
#include "json/JsonElement.h"
#include "json/JsonArray.h"
#include "json/Json.h"
#include "file/File.h"

int main() {
    try {
        // Path to the JSON file
        std::string filePath = "storage/storage.json";
        r_utils::io::File jsonFile(filePath);

        std::cout << "Attempting to read JSON data from file: " << jsonFile.getFilePath() << std::endl;

        // Read JSON data from the file
        std::string jsonString = jsonFile.read();
        std::cout << "Successfully read JSON content:\n" << jsonString << std::endl;

        // Parse the JSON data
        r_utils::json::JsonObject rootObject = r_utils::json::JsonParser::parse(jsonString);

        std::cout << "\nSuccessfully parsed JSON object:\n" << rootObject.toString(true) << std::endl;

        // Example operations on the parsed data
        if (rootObject.contains("users") && rootObject.get("users").isArray()) {
            r_utils::json::JsonArray usersArray = rootObject.get("users").asArray();
            std::cout << "\nIterating through users:" << std::endl;
            for (size_t i = 0; i < usersArray.size(); ++i) {
                if (usersArray.getValues()[i].isObject()) {
                    r_utils::json::JsonObject userObject = usersArray.getValues()[i].asObject();
                    if (userObject.contains("username") && userObject.contains("email")) {
                        std::cout << "- Username: " << userObject.get("username").asString()
                            << ", Email: " << userObject.get("email").asString() << std::endl;
                    }
                }
            }

            // Example of adding a new element (assuming you have a method to modify JsonObject/JsonArray)
            // Here, only the string representation is created for output
            r_utils::json::JsonObject newUser;
            newUser.set("username", r_utils::json::JsonElement("new_user"));
            newUser.set("email", r_utils::json::JsonElement("new@example.com"));

            // Add the new user object (as a string) to the output
            std::stringstream updatedJsonStream;
            updatedJsonStream << rootObject.toString(true).substr(0, rootObject.toString(true).size() - 2) // Remove last "}"
                << ",\n  \"newUser\": " << newUser.toJson().toString() << "\n}";
            std::cout << "\nExample of adding a new element (output string):\n" << updatedJsonStream.str() << std::endl;

            // Convert the modified JsonObject back to a JSON string and write it to the file
            r_utils::json::Json jsonWrapper = rootObject.toJson();
            std::string updatedJsonString = jsonWrapper.toString();
            jsonFile.write(updatedJsonString);

            std::cout << "\nUpdated JSON written back to " << jsonFile.getFilePath() << std::endl;
        }
        else {
            std::cout << "\n'users' array not found in the JSON data." << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "\nError during application execution: " << e.what() << std::endl;
    }

    return 0;
}