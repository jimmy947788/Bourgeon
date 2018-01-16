#ifndef BOURGEON_CORE_BOURGEON_H_
#define BOURGEON_CORE_BOURGEON_H_

#include <pybind11/embed.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "utils/log_console.h"

class Bourgeon {
 public:
  // Singleton stuff
  static Bourgeon& Instance() {
    static Bourgeon instance;
    return instance;
  }
  Bourgeon(Bourgeon const&) = delete;
  void operator=(Bourgeon const&) = delete;

  bool Initialize();
  // Python related
  void RegisterCallback(const std::string& callback_name,
                        const pybind11::object& function);
  const std::vector<pybind11::object>& GetCallbackRegistrees(
      const std::string& callback_name);

 private:
  Bourgeon();
  void LoadPlugins(const std::string& folder);

 private:
  LogConsole console_;
  pybind11::scoped_interpreter interpreter_;
  std::unordered_map<std::string, std::vector<pybind11::object>> callbacks_;
};

#endif /* BOURGEON_CORE_BOURGEON_H_ */