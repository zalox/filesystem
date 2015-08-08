#define BOOST_TEST_MODULE filesystem_tests
#include <boost/test/included/unit_test.hpp>
#include "../src/filesystem.hpp"
#include <iostream>

using namespace std;

std::vector<std::string> a = {"case/aardwark", "case/file", "case/lines"};
std::vector<std::string> b = {"case/dir"};
std::vector<std::string> c = {"one", "two"};

BOOST_AUTO_TEST_CASE(directories) {
  auto dirs = filesystem::dirs("case");
  BOOST_CHECK(dirs.size() == 1);
  for (int i = 0; i < dirs.size(); i++)  
    BOOST_CHECK(dirs[i] == b[i]);
};

BOOST_AUTO_TEST_CASE(filesystem_files) {
  auto files = filesystem::files("case");
  BOOST_CHECK(files.size() == 3);
  for (int i = 0; i < files.size(); i++)
    BOOST_CHECK(files[i] == a[i]);
};

BOOST_AUTO_TEST_CASE(contents) {
  auto contents = filesystem::contents("case");
  BOOST_CHECK(contents.size() == 4);
  std::vector<std::string> s(a);
  s.insert(s.begin()+1, b.begin(), b.end());
  for (int i = 0; i < contents.size(); i++)  
    BOOST_CHECK(contents[i] == s[i]);
};

BOOST_AUTO_TEST_CASE(seperate_contents) {
  auto contents = filesystem::seperate_contents("case");
  BOOST_CHECK(contents.size() == 4);
  std::vector<std::string> s(b);
  s.insert(s.end(), a.begin(), a.end());
  for (int i = 0; i < contents.size(); i++)  
    BOOST_CHECK(contents[i] == s[i]);
};

BOOST_AUTO_TEST_CASE(lines) {
  auto lines = filesystem::read_lines("case/lines");
  BOOST_CHECK(lines.size() == 2);
  for (int i = 0; i < lines.size(); i++)  
    BOOST_CHECK(lines[i] == c[i]);
}

BOOST_AUTO_TEST_CASE(read_file) {
  auto file_content = filesystem::read("case/lines");
  BOOST_CHECK(file_content == "one\ntwo");
}
