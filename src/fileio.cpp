#include "daedalus/fileio.h"

#include <fstream>

namespace daedalus
{
namespace fileio
{

std::optional<File> load_file(std::string_view file)
{
    // Open file
    std::ifstream f(std::string(file), std::ios::binary | std::ios::ate);
    if (!f.is_open())
        return std::nullopt;

    // File size
    std::streamsize size = f.tellg();
    if (size <= 0)
        return std::nullopt;

    f.seekg(0, std::ios::beg);

    std::unique_ptr<char[]> buf = std::make_unique<char[]>(size);

    if (!f.read(buf.get(), size))
    {
        return std::nullopt;
    }

    return File{.buf = std::move(buf), .size = static_cast<size_t>(size)};
}

} // namespace fileio
} // namespace daedalus
