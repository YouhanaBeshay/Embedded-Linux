#include <initializer_list>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum myerror_t {
  OK,
  NULL_PTR,
  EMPTY_ACTIONS,

};

class FileActions {
private:
  int *fd_;
  int *&fdREF_ = fd_;
  bool isCopied_;
  std::vector<std::pair<std::string, int>> actions_;

public:
  FileActions(std::string &path);
  FileActions(const FileActions &obj);
  void
  registerActions(std::initializer_list<std::pair<std::string, int>> &&actions);
  myerror_t executeActions();

  ~FileActions();
};

FileActions::FileActions(std::string &path) {
  fdREF_ = new int;
  *fdREF_ = open(path.data(), O_RDWR);
  isCopied_ = false;
  std::cout << "Default constructor called"
            << "\n";
}
FileActions::FileActions(const FileActions &obj) {
  fdREF_ = obj.fdREF_;
  actions_ = obj.actions_;
  isCopied_ = true;
  std::cout << "Copy constructor called"
            << "\n";
}

void FileActions::registerActions(
    std::initializer_list<std::pair<std::string, int>> &&actions) {
  actions_ = actions;
}
myerror_t FileActions::executeActions() {
  myerror_t errorStatus = OK;

  if (actions_.size() <= 0) {
    errorStatus = EMPTY_ACTIONS;
  } else {
    for (int i = 0; i < actions_.size(); i++) {
      if (actions_[i].first == "Write" || actions_[i].first == "write") {
        std::string intString = std::to_string(actions_[i].second);
        write(*fdREF_, intString.c_str(), intString.size());
        lseek(*fdREF_, 0, SEEK_SET); // return fd to start (for reading)
      } else if (actions_[i].first == "Read" || actions_[i].first == "read") {
        char *buffer = new char[actions_[i].second];
        auto readBytes = read(*fdREF_, buffer, actions_[i].second);
        for (size_t j = 0; j < readBytes; j++) {
          std::cout << buffer[j];
        }
        std ::cout << "\n";
        delete[] buffer;
      } else if (actions_[i].first == "Close" || actions_[i].first == "close") {
        close(*fd_);
      } else {
        // Empty else
      }
    }
  }
  return errorStatus;
}
FileActions::~FileActions() {
  if (isCopied_ != true) {
    close(*fdREF_);
    delete fdREF_;
  }
}

void doExecuteActions(FileActions obj) { obj.executeActions(); }

int main(int argc, char const *argv[]) {
  std::string mypath = "/sys/class/leds/input7::capslock/brightness";
  FileActions capslockfile(mypath);

  capslockfile.registerActions({{"write", 0}, {"read", 1}});

  doExecuteActions(capslockfile);

  return 0;
}
