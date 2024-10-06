#include "tools/utils/path_parser.hpp"

#include <algorithm>

namespace Engine::Tools::Utils
{
    std::string PathParser::GetFileName(const std::filesystem::path& path)
    {
        if (!path.has_filename())
            return "";

        std::filesystem::path filename = path.filename();
        return filename.replace_extension("").string();
    }
}
