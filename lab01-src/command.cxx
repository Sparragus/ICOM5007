#include "command.h"

#include <iostream>
#include <boost/xpressive/xpressive.hpp>

namespace xpr = boost::xpressive;

command::command()
  : exit_requested_(false)
{
}

bool command::is_valid_command_line(const std::string& line) const
{
  xpr::sregex valid = xpr::sregex::compile("\\w+(\\s+\\w+)*\\s*");
  return xpr::regex_match(line, valid);
}

bool command::parse_line(const std::string& line)
{
  this->parameters_.clear();

  if (!this->is_valid_command_line(line))
  {
    return false;
  }

  xpr::sregex token = +xpr::alnum;

  xpr::sregex_iterator cur(line.begin(), line.end(), token);
  xpr::sregex_iterator end;
  for (; cur != end; ++cur)
  {
    this->parameters_.push_back(cur->str());
  }

  return true;
}

bool command::readline()
{
  // TODO: Print prompt for the user.
std::cout << "koopa$ ";

  // Read line from user.
  std::string command_line;
  std::getline(std::cin, command_line);

  return parse_line(command_line);
}

void command::print_usage() const
{
  std::cout << "USAGE: command [parameters]" << std::endl;
}

void command::execute()
{
  // TODO: Execute the command.
  std::string cmd = this->parameters_[0];
  if (cmd == "exit")
  {
    this->exit_requested_ = true;
  }
  else if (cmd == "help")
  {
    //std::cout << "USAGE: " << std::endl;
    this->print_usage();
  }
  else
  {
    std::vector<std::string>::const_iterator iter = this->parameters_.begin();
    //for (; iter != this->parameters_.end(); ++iter)
    //{
      //std::cout << *iter << std::endl;
    //}

    this->execvp(this->parameters_[0], this->parameters_);

  }
}

int command::execvp(const std::string& path,
                    const std::vector<std::string>& argv) const
{
  std::vector<const char*> c_argv;
  for (std::vector<std::string>::const_iterator iter = argv.begin();
       iter != argv.end();
       ++iter)
  {
    c_argv.push_back(iter->c_str());
  }
  c_argv.push_back(0);
  return ::execvp(path.c_str(),const_cast<char* const*>(&c_argv[0]));
}
