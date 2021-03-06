/**
 * @file split.hpp
 * @brief Implementation of various split functions.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef COMMON_SPLIT_HPP_
#define COMMON_SPLIT_HPP_

#include <regex>
#include <string>

/** @brief The namespace of the Common */
namespace common {

/**
 * @brief The function slices a string into substrings.
 *
 * @details
 * This function slices a given string into substrings and writes them to a
 * string vector. The line feed character (";") is used as a separator.
 *
 * @note If the delimiter is at the beginning of the line, then the first
 * substring will be empty. That is, the line is empty before the separator.
 *
 * @param [in] str - input of data string.
 * @return Vector of substrings.
 */
inline std::vector<std::string> split(const std::string& str) {
  using namespace std::string_literals;
  std::regex ws_re(";");
  std::vector<std::string> res{std::sregex_token_iterator(str.begin(), str.end(), ws_re, -1),
                               std::sregex_token_iterator()};
  if (str.substr(str.size() - 1, 1) == ";"s)
    res.push_back("");
  return res;
}

} /* common:: */

#endif /* COMMON_SPLIT_HPP_ */
