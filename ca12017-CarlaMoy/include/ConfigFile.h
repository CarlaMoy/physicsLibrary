#ifndef CONVERT_H_
#define CONVERT_H_

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>

///@file ConfigFile.h
///@brief Configuration file class for configuring initial values for a rigid body to a .cfg (config) file.
/// Modified from : http://www.dreamincode.net/forums/topic/183191-create-a-simple-configuration-file-parser/
///@author Carla Moy
///@class Convert ConfigFile

class Convert
{
public:
  ///@brief Method to convert T to string and return string
  template <typename T>
  static std::string T_to_string(T const &val)
  {
    std::ostringstream ostr;
    ostr << val;

    return ostr.str();
  }

  ///@brief Method to convert string to T and return T
  template <typename T>
  static T string_to_T(std::string const &val)
  {
    std::istringstream istr(val);
    T returnVal;
    if (!(istr >> returnVal))
      exit(EXIT_FAILURE);

    return returnVal;
  }
};



class ConfigFile
{
public:
  ///@brief Constructor for ConfigFile
  ///@param fName name of the .cfg file
  ConfigFile(const std::string &fName);

  ///@brief Method to check key exists
  ///@param key The string to check for
  bool keyExists(const std::string &key) const;

  ///@brief Method to get value from the key
  ///@param key The key to look at
  ///@param defaultValue Returns default value if key is not found, else returns converted value from string to ValueType
  template <typename ValueType>
  ValueType getValueOfKey(const std::string &key, ValueType const &defaultValue = ValueType()) const
  {
    if (!keyExists(key))
      return defaultValue;

    return Convert::string_to_T<ValueType>(contents.find(key)->second);
  }

private:
  ///@brief std::map to hold pairs of key-value
  std::map<std::string, std::string> contents;
  ///@brief String name of file
  std::string fName;

  ///@brief Method to remove comment
  ///@param line to remove
  void removeComment(std::string &line) const;

  ///@brief Method that returns false if non-space character is found, else true
  ///@param line The line to check
  bool onlyWhitespace(const std::string &line) const;
  ///@brief Method to check if line is correct structure and is therefore valid
  ///@param line Line to check
  bool validLine(const std::string &line) const;

  ///@brief Method to extract key from the pair of key=value
  ///@param key The key to check
  ///@param sepPos The position of the = in the line
  ///@param line The line to check
  void extractKey(std::string &key, size_t const &sepPos, const std::string &line) const;
  ///@brief Method to extract value from the pair of key=value
  ///@param key The key to check
  ///@param sepPos The position of the = in the line
  ///@param line The line to check
  void extractValue(std::string &value, size_t const &sepPos, const std::string &line) const;

  ///@brief Extracts to contents of a line
  ///@param line The line to extract
  void extractContents(const std::string &line);
  ///@brief Method to parse the line
  ///@param line The line to parse
  ///@param lineNo the line number
  void parseLine(const std::string &line, size_t const lineNo);

  ///@brief Method to extract and parse all keys
  void ExtractKeys();
};


#endif
