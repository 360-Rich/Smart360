#include "Application.h"

Smart360::Application app;

void setup()
{
    app.begin();
}

void loop()
{
    app.update();
}