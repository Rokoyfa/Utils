#include <iostream>
#include <string>

#include "RUtils.h";
#include "gui/Window.h"

r_utils::RUtils utils = r_utils::RUtils::create()
    .withLogger()
    .initialize();

int main() {
    try {
        r_utils::gui::Window mainWindow("Test", 800, 600, false);
        mainWindow.show();

        // Hier fehlt die Haupt-Event-Schleife. Die Anwendung w�rde normalerweise sofort beendet werden.
        // F�r einen ersten Test sollte das Fenster aber kurz angezeigt werden, bevor das Programm terminiert.

        // Eine einfache M�glichkeit, das Fenster offen zu halten (nur f�r Testzwecke!):
        std::cout << "Dr�cke Enter zum Beenden..." << std::endl;
        std::cin.get();

    }
    catch (const std::exception& e) {
        std::cerr << "Fehler beim Erstellen des Fensters: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
