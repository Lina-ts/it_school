#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include <readline/history.h>
#include <readline/readline.h>

std::vector<std::string> list;

char *command_generator(const char *text, int state) {
  static std::vector<std::string> match;
  static size_t match_index = 0;

  if (!state) {
    match.clear();
    match_index = 0;

    std::string textstr(text);
    for (auto word : list) {
      if (word.size() >= textstr.size() && 
	  word.compare(0, textstr.size(), textstr) == 0) {
        match.push_back(word);
      }
    }
  }

  if (match_index >= match.size()) {
    return nullptr; } 
  else {
    return strdup(match[match_index++].c_str());
  }
}

char **command_completion(const char *text, int start, int end) {
  rl_attempted_completion_over = 1;
  return rl_completion_matches(text, command_generator);
}

int main(int argc, char **argv) {

  rl_attempted_completion_function = command_completion;
  
  std::string cmd;
  char *buffer;
  
  std::cout << "Choose a mobile operator: " << std::endl;
  std::ifstream file("provaders.csv");
  std::string line;

  while(getline(file, line)) {
        list.push_back(line);	
  }
  std::cout << list.back() << std::endl;
  
  while ((buffer = readline("> ")) != nullptr) {
    cmd = std::string(buffer);
    if (cmd.size() > 0) {
      add_history(buffer);
    }
    free(buffer);
    
    std::cout << cmd << std::endl;
  }
  return 0;
}
