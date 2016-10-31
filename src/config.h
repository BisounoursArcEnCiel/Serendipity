/**
 * @file 
 * @author
 * @date 
 * @brief Define default global configuration
 **/

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <boost/filesystem.hpp>

 namespace fs = boost::filesystem;

 /** 
  * @def VERSION
  * version of the c++ part in src
  **/
#define VERSION "0.0.0-dev1"

 /** 
  * @def LOG_PATH
  * directory where logs are stored
  **/
#ifndef LOG_PATH
     #define LOG_PATH (fs::path("log"))
#endif

#endif //CONFIG_H
