#include "file_types.h"

#include "platform.h"
#include "utils.h"

#include <loguru.hpp>

AbsolutePath::AbsolutePath() {}

AbsolutePath::AbsolutePath(const std::string& path, bool validate)
    : path(path) {
  if (validate && !IsAbsolutePath(path)) {
    loguru::Text stack = loguru::stacktrace();
    LOG_S(ERROR) << "Expected " << path << " to be absolute\n" << stack.c_str();
  }
}

AbsolutePath::operator std::string() const {
  return path;
}

bool AbsolutePath::operator==(const AbsolutePath& rhs) const {
  return path == rhs.path;
}

bool AbsolutePath::operator!=(const AbsolutePath& rhs) const {
  return path != rhs.path;
}

void Reflect(Reader& visitor, AbsolutePath& value) {
  value.path = visitor.GetString();
}
void Reflect(Writer& visitor, AbsolutePath& value) {
  visitor.String(value.path.c_str(), value.path.length());
}

Directory::Directory(const AbsolutePath& path) : path(path.path) {
  EnsureEndsInSlash(this->path);
}

bool Directory::operator==(const Directory& rhs) const {
  return path == rhs.path;
}

bool Directory::operator!=(const Directory& rhs) const {
  return path != rhs.path;
}