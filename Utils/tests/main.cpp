#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "RUtils.h"
#include "gui/Window.h"
#include "gui/Application.h"

extern r_utils::RUtils utils;

// Definiere eine benutzerdefinierte Fensterklasse
class MeinFenster : public r_utils::gui::Window {
public:
    MeinFenster(std::string id, const std::string& title) : r_utils::gui::Window(id, title) {
        // Todo: With Logger implimentation
    }

    void handleEvent(r_utils::events::Event& event) override {
        r_utils::gui::Window::handleEvent(event);
    }

    void draw() override {

    }
};

int main() {
    // Initialisiere RUtils (Logger, etc.)
    r_utils::RUtils utils = r_utils::RUtils::create()
        .withLogger()
        .initialize();

    // Erstelle die Application-Instanz
    r_utils::gui::Application app;

    // Erstelle ein oder mehrere Fenster (im Heap, damit sie nicht am Ende von main zerstört werden)
    r_utils::gui::Window* window1 = new MeinFenster("Fenster1", "Mein Erstes Fenster");

    app.registerWindow(window1);
    std::thread appThread(static_cast<void (r_utils::gui::Application::*)()>(&r_utils::gui::Application::run), &app);

    // Gib dem Benutzer eine Möglichkeit, die Anwendung zu beenden
    std::cout << "Drücke Enter, um die Anwendung zu beenden..." << std::endl;
    std::cin.get();

    // Beende die Application
    app.stop();

    // Warte auf das Ende des Application-Threads
    if (appThread.joinable()) {
        appThread.join();
    }

    std::cout << "Anwendung beendet." << std::endl;
    return 0;
}