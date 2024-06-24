#include <filesystem>
#include <iostream>
#include <openssl/md5.h>
#include <thread>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

namespace fs = std::filesystem;

namespace util {

    std::string outputFilePath = "/Users/akhil/Desktop/diff_checker/output/";
    std::string commonFile = "common";
    std::string aOnlyFile = "a_only";
    std::string bOnlyFile = "b_only";

    bool isPathValid(const std::string &path) {
        return fs::exists(path);
    }

    std::string computeMD5(const std::string& filePath) {
        std::ifstream file(filePath, std::ifstream::binary);
        if (!file) {
            std::cerr << "Error opening file: " << filePath << std::endl;
            return "";
        }

        MD5_CTX md5Context;
        MD5_Init(&md5Context);

        char buffer[1024];
        while (file.good()) {
            file.read(buffer, sizeof(buffer));
            MD5_Update(&md5Context, buffer, file.gcount());
        }

        unsigned char hash[MD5_DIGEST_LENGTH];
        MD5_Final(hash, &md5Context);

        std::ostringstream oss;
        for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }

        return oss.str();
    }

    void writeContentToFile(const std::string &path, const std::string& content) {

        fs::path filePath(path);
        fs::path dir = filePath.parent_path();

        if (!dir.empty() && !fs::exists(dir)) {
            fs::create_directories(dir);
        }

        std::ofstream outFile(path, std::ios_base::app);

        if (outFile.is_open()) {
            outFile << content << std::endl;
            outFile.close();
        } else {
            std::cerr << "Unable to open file for writing: " << path << std::endl;
        }
    }

    void writeContentToFile(const std::string &path, const std::vector<std::string>& content) {
        for (const auto& line : content) {
            writeContentToFile(path, line);
        }
    }

    void computeDirectoryHashes(const std::string &path, std::unordered_map<std::string, std::vector<std::string>> &fileHashes) {
        try {
            for (const fs::directory_entry& dir_entry : fs::recursive_directory_iterator(path)) {
                if (fs::is_regular_file(dir_entry.path())) {
                    std::string hash = computeMD5(dir_entry.path().string());
                    fileHashes[hash].push_back(dir_entry.path().filename().string());
                }
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
        }
    }

    void compareDirectories(const std::string &path1, const std::string &path2) {
        std::unordered_map<std::string, std::vector<std::string>> a_files, b_files;
        std::thread t1(computeDirectoryHashes, path1, std::ref(a_files));
        std::thread t2(computeDirectoryHashes, path2, std::ref(b_files));

        t1.join();
        t2.join();

        std::string aOutputPath = outputFilePath + aOnlyFile;
        std::string bOutputPath = outputFilePath + bOnlyFile;
        std::string commonOutputPath = outputFilePath + commonFile;

        for (const auto& [key, value] : a_files) {
            if (b_files.count(key) > 0) {
                writeContentToFile(commonOutputPath, value);
                writeContentToFile(commonOutputPath, b_files[key]);
                b_files.erase(key);
            } else {
                writeContentToFile(aOutputPath, value);
            }
        }

        for (const auto& [key, value] : b_files) {
            writeContentToFile(bOutputPath, value);
        }
    }

}
