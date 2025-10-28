#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>

#include "RUtils.h"
#include "time/TimeUtils.h"
#include "time/Timer.h"
#include "gui/Window.h"
#include "gui/Application.h"
#include <logger/LoggerMakro.h>
#include "string/StringUtils.h"

#include "event/IEventListener.h"

class MeinFenster : public r_utils::gui::Window {
public:
    MeinFenster(std::string id, const std::string& title,
        r_utils::logger::Logger* logger,
        r_utils::events::EventDispatcher& dispatcher)
        : r_utils::gui::Window(id, title, dispatcher, 600, 600, logger), logger_(logger) {}

    void onEvent(r_utils::events::Event& event) override {
        r_utils::gui::Window::onEvent(event);
        switch (event.getType()) {
        case r_utils::events::EventType::WINDOW_RESIZE: 
        {
            event.setHandled(true);
            break;
        }
        case r_utils::events::EventType::KEY_PRESSED: 
        {
            event.setHandled(true);
            break;
        }
        default:
            break;
        }
    }

    void draw() override {
    }
private:
    r_utils::logger::Logger* logger_;
};

int main() {
    r_utils::RUtils utils = r_utils::RUtils::create()
        .withLogger()
        .initialize();

    /*r_utils::logger::Logger* mainLogger = utils.getLogger();
    mainLogger->error("Hallo");
    r_utils::gui::Application* app = utils.getApplication();

    if (!app) {
        std::cerr << "FEHLER: RUtils, Application oder Logger konnte nicht initialisiert werden!" << std::endl;
        return 1;
    }

    mainLogger->enableColors(true);

    LOG_DEBUG(mainLogger, "Anwendung und Logger erfolgreich �ber RUtils initialisiert.");

    r_utils::gui::Window* window1 = new MeinFenster("Fenster1", "Mein Erstes Fenster", nullptr, app->getEventDispatcher());

    app->registerWindow(window1);

    std::thread appThread(static_cast<void(r_utils::gui::Application::*)()>(&r_utils::gui::Application::run), app);

    LOG_WARN(mainLogger, "Dr�cke Enter, um die Anwendung zu beenden...");
    std::cin.get();

    app->stop();

    if (appThread.joinable()) {
        appThread.join();
    }

    std::cout << "Anwendung beendet." << std::endl;*/

    /*r_utils::time::Timer* timer = new r_utils::time::Timer();
    
    timer->startPeriodic([] {
        std::cout << "Timer finished!" << std::endl;
	    }, 1000);


	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Main thread doing other work..." << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "Main thread finished." << std::endl;*/

	/*std::cout << r_utils::string::capitalize("hallo welt! dies ist ein test.") << std::endl;
	r_utils::string::StringUtils string = r_utils::string::StringUtils("hallo welt! dies ist ein test.");

	std::cout << string.reverse().str() << std::endl;*/

    return 0;
}