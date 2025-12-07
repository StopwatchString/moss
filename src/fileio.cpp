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

std::string_view get_line(const char* str, size_t max_search_size, char delim)
{
    const char* endl = reinterpret_cast<const char*>(std::memchr(str, delim, max_search_size));
    if (endl == nullptr)
    {
        endl = str + max_search_size;
    }
    return std::string_view(str, endl - str);
}

std::vector<std::string_view> split(const char* buf, size_t size, char delim)
{
    const char* front = buf;
    const char* back = buf + size;
    std::vector<std::string_view> svs;
    while (front < back)
    {
        std::string_view s = get_line(front, back - front, delim);
        front += s.size() + 1;
        svs.push_back(s);
    }
    return svs;
}

std::string_view trim(std::string_view sv)
{
    static const char* space_characters = " \t\n\v\f\r";
    size_t front = sv.find_first_not_of(space_characters);
    if (front == std::string_view::npos)
        return {};
    size_t back = sv.find_last_not_of(space_characters);
    return sv.substr(front, back - front + 1);
}

} // namespace fileio
} // namespace daedalus
