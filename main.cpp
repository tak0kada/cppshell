#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "shell.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "ERROR: too many or no specified commands." << std::endl;
        return EXIT_FAILURE;
    }
    std::string cmd{argv[1]};

    std::cout << "test shell::exec()" << std::endl;
    shell::exec(cmd);

    std::cout << "test shell::valueof()" << std::endl;
    auto result = shell::valueof(cmd);
    if (result)
    {
        std::vector<std::string> lines;
        boost::algorithm::split(lines, result.value(), boost::is_any_of(" \n"));
        for (std::size_t i = 0; i < lines.size(); ++i)
        {
            std::cout << "result" << i << ": " << lines[i] << std::endl;
        }
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}
