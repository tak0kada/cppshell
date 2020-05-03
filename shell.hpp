#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <optional>
// #include <format>
#include <boost/format.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace shell
{

inline int exec(const std::string cmd)
{
    int ret_code = std::system(("set -euo pipefail\n" + cmd + ">/dev/null 2>&1").c_str());
    if (ret_code != 0)
    {
        std::cerr << boost::format("ERROR: failed to execute \"%1%\".") % cmd << std::endl;
    }
    return ret_code;
}

inline std::optional<std::string> valueof(const std::string cmd)
{
    std::string result;

    FILE* pipe = popen(("set -euo pipefail\n" + cmd).c_str(), "r");
    if (pipe == NULL)
    {
        std::cerr << boost::format("ERROR: failed to execute \"%1%\".") % cmd << std::endl;
        return {};
    }

    char buffer[256];
    // without checking feof, reading EOF will cause SEGV.
    while(!feof(pipe))
    {
        if(fgets(buffer, sizeof(buffer), pipe) != NULL)
        {
            result.append(buffer);
        }
    }
    pclose(pipe);

    return result.substr(0, result.size() - 1);
}

} // namespace shell
