#ifndef DAEDALUS_FILE_IO_H
#define DAEDALUS_FILE_IO_H

#include "types.h"

#include <memory>
#include <optional>
#include <string_view>
#include <vector>

namespace daedalus
{
namespace fileio
{

/**
 * @brief A struct to hold the data of a file. Contains a char buffer and size.
 */
struct File
{
    std::unique_ptr<char[]> buf;
    daedalus::primitives::u64 size{0};
};

/**
 * @brief Attempts to load a file into a buffer.
 *
 * @note If the file does not exist, or any issues are encountered, the optional will be empty.
 *
 * @param file_path The path to the file.
 *
 * @return File struct on success, or std::nullopt on failure.
 */
[[nodiscard]] std::optional<File> load_file(std::string_view file_path);

/**
 * @brief Given a character buffer, returns a string_view of the first line in the buffer delineated by a passed in
 * delimiter, up to a maximum search size.
 *
 * @note This function can be easily used to parse an entire buffer, by repeatedly calling it with the same buffer,
 * while incrementing the pointer to the buffer by the size of the last returned string_view.
 *
 * @param str The string buffer to search.
 * @param max_search_size The most characters that can be searched for the delimiter.
 * @param delim The delimiter to search for to delineate the string.
 *
 * @return A std::string_view of the first line encountered.
 */
[[nodiscard]] std::string_view get_line(const char* str, size_t max_search_size, char delim);

/**
 * @brief Splits a char buffer into a vector of string_views based on a given delimiter.
 *
 * @note The string_views are views of the passed in buffer, so the buffer must be kept alive while the string_views are
 * in use.
 *
 * @param buf A character buffer to split.
 * @param size The size of the character buffer.
 * @param delim The delimiter to split the character buffer with.
 *
 * @return A vector of string_views based on buf.
 */
[[nodiscard]] std::vector<std::string_view> split(const char* buf, size_t size, char delim);

/**
 * @brief Removes the whitespace from the front and back of a string_view.
 *
 * @param sv The string view to trim whitespace from.
 *
 * @return A string_view of the passed in string without whitespace in the front or back.
 */
[[nodiscard]] std::string_view trim(std::string_view sv);

} // namespace fileio
} // namespace daedalus

#endif
