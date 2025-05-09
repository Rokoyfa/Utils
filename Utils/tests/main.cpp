#include <iostream>
#include <string>
#include "json/JsonParser.h"
#include "json/JsonObject.h"
#include "json/JsonElement.h"
#include "json/JsonArray.h"
#include "json/Json.h"
#include "file/File.h"

#include "exception/file/FileException.h"

int main() {
    /*
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
    


    try {

        std::ifstream file("nicht_existierende_datei.txt");
        if (!file.is_open()) {
            throw r_utils::exception::FileException("Datei konnte nicht geöffnet werden.");
        }

        // Beispiel für eine weitere Exception
        std::string content;
        file >> content;
        if (content.empty()) {
        }

        std::cout << "Inhalt: " << content << std::endl;
    }
    catch (const r_utils::exception::Exception& ex) {
        std::cerr << "[Fehler]: " << ex.what() << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "[std::exception]: " << ex.what() << std::endl;
    }

    */


    std::string json = "{\"name\":\"Marc\",\"langs\":[\"cpp\",\"java\",\"python\"],\"obj\":{\"döner\":\"lecker\"}}";
    r_utils::json::Json jsn = r_utils::json::Json().parse(json);
    
    r_utils::json::JsonObject obj = jsn.asObject();
    r_utils::json::JsonObject obj2 = obj.get("obj").asObject();
    std::cout << obj << std::endl;
    std::cout << obj2 << std::endl;

    std::string input = "[\"Hello\", 123, true, null, {\"key\": \"value\"}]";
    r_utils::json::Json test2 = r_utils::json::Json::parse(input);

    if (test2.isArray()) {
        std::cout << "Parsed Array: " << test2.toString() << std::endl;
        auto arr = test2.asArray();
        std::cout << "Size: " << arr.size() << std::endl;
        std::cout << "Element 0: " << arr[0].asString() << std::endl;
    }
    return 0;
}