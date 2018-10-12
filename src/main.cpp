#include "App.hpp"

int main(int argc, char *argv[])
{
    // App app(640, 480, 60);
    App app("resources/1.level");
    app.Run();

    return 0;
}