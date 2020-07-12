#include "UserInterface.h"
#include <QtWidgets/QApplication>

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>

#include <crtdbg.h>

int main(int argc, char* argv[])
{
    {
        QApplication* app = new QApplication(argc, argv);
        Service srv{};
        UserInterface w{ srv };
        w.show();
        int exit = app->exec();
        delete app;
    }
    _CrtDumpMemoryLeaks();

    return 0;

}
