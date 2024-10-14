load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
  name = "com_google_absl",
  urls = ["https://github.com/abseil/abseil-cpp/archive/0e9921b75a0fdd639a504ec8443fc1fe801becd7.zip"],
  strip_prefix = "abseil-cpp-0e9921b75a0fdd639a504ec8443fc1fe801becd7",
  sha256 = "8061df0ebbd3f599bcd3f5e57fb8003564d50a9b6a81a7f968fb0196b952365d"
)

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
git_repository(
    name = "gtest",
    remote = "https://github.com/google/googletest",
    branch = "v1.10.x",
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
_RULES_BOOST_COMMIT = "652b21e35e4eeed5579e696da0facbe8dba52b1f"

http_archive(
    name = "com_github_nelhage_rules_boost",
    sha256 = "c1b8b2adc3b4201683cf94dda7eef3fc0f4f4c0ea5caa3ed3feffe07e1fb5b15",
    strip_prefix = "rules_boost-%s" % _RULES_BOOST_COMMIT,
    urls = [
        "https://github.com/nelhage/rules_boost/archive/%s.tar.gz" % _RULES_BOOST_COMMIT,
    ],
)

http_archive(
    name = "glfw",
    build_file = "@//:BUILD.glfw",
    sha256 = "fd21a5f65bcc0fc3c76e0f8865776e852de09ef6fbc3620e09ce96d2b2807e04",
    strip_prefix = "glfw-3.3.7",
    urls = ["https://github.com/glfw/glfw/archive/3.3.7.tar.gz"],
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()
