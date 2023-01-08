#include "App.hpp"

#include <boxer/boxer.h>

int main()
{
    try
    {
        gr::App app;
        app.run();
    }
    catch (std::exception& e)
    {
        boxer::show(e.what(), "Error!", boxer::Style::Error);
    }
    catch (const char* msg)
    {
        boxer::show(msg, "Error!", boxer::Style::Error);
    }
}
