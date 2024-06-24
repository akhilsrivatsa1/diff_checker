#include <filesystem> 
#include <unordered_map>
#include <vector>
#pragma once
namespace fs = std::filesystem;

namespace util{

    extern std::string outputFilePath;
    extern std::string commonFile;
    extern std::string aOnlyFile;
    extern std::string bOnlyFile;

    bool isPathValid(const std::string &path);
    void writeContentToFile(std::string &path, std::string &content);
    void writeContentToFile(std::string &path, const std::vector<std::string>& content);
    void computeDirectoryHashes(const std::string &path, std::unordered_map<std::string, std::vector<std::string>> &fileHashes);
    std::string computeMD5(const std::string& filePath);
    void compareDirectories(const std::string &path1, const std::string &path2);
}