#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "RUtils.h"
#include "gui/Window.h"
#include "gui/Application.h"
#include <logger/LoggerMakro.h>

extern r_utils::RUtils utils;

class MeinFenster : public r_utils::gui::Window {
public:
    MeinFenster(std::string id, const std::string& title, r_utils::logger::Logger* logger) : r_utils::gui::Window(id, title, logger) {
        logger_ = logger;
    }

    void draw() override {
    }

    r_utils::logger::Logger* logger_;
};

int main() {
    r_utils::RUtils utils = r_utils::RUtils::create()
        .withLogger()
        .initialize();

    r_utils::logger::Logger* mainLogger = utils.getLogger();
    mainLogger->error("Hallo");
    r_utils::gui::Application* app = utils.getApplication();

    if (!app || !mainLogger) {
        std::cerr << "FEHLER: RUtils, Application oder Logger konnte nicht initialisiert werden!" << std::endl;
    }

    LOG_INFO(mainLogger, "Anwendung und Logger erfolgreich über RUtils initialisiert.");

    r_utils::gui::Window* window1 = new MeinFenster("Fenster1", "Mein Erstes Fenster", mainLogger);
    app->registerWindow(window1);

    std::thread appThread(static_cast<void (r_utils::gui::Application::*)()>(&r_utils::gui::Application::run), app);

    LOG_WARN(mainLogger, "Drücke Enter, um die Anwendung zu beenden...");
    std::cin.get();

    app->stop();

    if (appThread.joinable()) {
        appThread.join();
    }

    std::cout << "Anwendung beendet." << std::endl;
    return 0;
}