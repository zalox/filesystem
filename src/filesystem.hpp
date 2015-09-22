#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

enum filesystem_options {
  DIRS = 0x1,
  FILES = 0x2,
  ALL = DIRS | FILES,
  SORTED = ALL | 0x4
};

class filesystem {
public:
  bool write(const std::string &path, const std::string &new_content) 
  {
    std::ofstream output(path);
    if(output)
      output << new_content;
    else
      return false;
    output.close();
    return true;
  }

  static auto read(const std::string &path)
  {
    std::stringstream ss;
    std::ifstream input(path);
    if(input) {
      ss << input.rdbuf();
      input.close();
    }
    return ss.str();
  }

  static auto read_lines(const std::string &path)
  {
    std::vector<std::string> res;
    std::ifstream input(path);
    if (input) {
      std::string line;
      while(getline(input, line)) {
        res.emplace_back(line);         
      }
    }
    input.close();
    return res;
  
  }  
  
  static auto get_directory_content(const std::string &path, int filter)
  {    
    auto p = fs::path(path);
    
    std::vector<std::string> dirs;
    
    if (fs::is_directory(p)) {
      for (fs::directory_iterator it(p); it != fs::directory_iterator(); it++) {
          if (filter & DIRS && fs::is_directory(it->path()))
            dirs.emplace_back(it->path().string());
          if (filter & FILES && fs::is_regular_file(it->path()))
            dirs.emplace_back(it->path().string());
      }
    }
    
    if (filter & SORTED)
      std::sort(dirs.begin(), dirs.end());
    
    return dirs;
  };
    
  static auto dirs(const std::string &path) 
  {
    return filesystem::get_directory_content(path, DIRS | SORTED);
  }
  
  static auto files(const std::string &path)
  {
    return filesystem::get_directory_content(path, FILES | SORTED);
  }
  
  static auto contents(const std::string &path)
  {
    return filesystem::get_directory_content(path, ALL | SORTED); // ALL = DIRS | FILES
  }
  
  static auto seperate_contents(const std::string &path)
  {
    auto a = dirs(path);
    auto b = files(path);
    a.insert(a.end(), b.begin(), b.end());
    return a;
  }
};

#endif

