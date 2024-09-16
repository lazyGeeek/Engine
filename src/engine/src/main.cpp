#include <exception>
#include <iostream>
#include <memory>

#include "engine/application.hpp"
#include "logs/logger.hpp"

int main(int argc, char* argv[])
{
    try
    {
        std::filesystem::path parentPath = std::filesystem::path(argv[0]).parent_path();
        std::unique_ptr<Engine::Application> app = std::make_unique<Engine::Application>(parentPath);
        if (app) app->Run();
    }
    catch (std::exception e)
    {
        Engine::Logs::Logger::PrintLog(std::string("EXCEPTION: ") + e.what(), Engine::Logs::ELogLevel::Error);
        return -1;
    }

    return 0;
}
