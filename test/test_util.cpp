#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <random>
#include <sstream>
#include "../include/file_util.h"

namespace fs = std::filesystem;
using namespace util;

void createTestFile(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    if (file.is_open()) {
        file << content;
        file.close();
    }
}

void removeTestDirectory(const std::string& path) {
    fs::remove_all(path);
}

TEST(FileUtilTest, CompareDirectories) {
    std::string dir1 = "test_dir1";
    std::string dir2 = "test_dir2";
    fs::create_directory(dir1);
    fs::create_directory(dir2);

    for (int i = 1; i <= 1000; ++i) {
        std::stringstream ss;
        ss << "/file" << i << ".txt";
        std::string fileName = ss.str();
        if (i % 2 == 0) {
            std::string content = "common content " + std::to_string(i);
            createTestFile(dir1 + fileName, content);
            createTestFile(dir2 + fileName, content);
        } else {
            createTestFile(dir1 + fileName, "unique content dir1 " + std::to_string(i));
            createTestFile(dir2 + fileName, "unique content dir2 " + std::to_string(i));
        }
    }

    util::outputFilePath = "output/";
    util::commonFile = "common";
    util::aOnlyFile = "a_only";
    util::bOnlyFile = "b_only";

    compareDirectories(dir1, dir2);

    std::ifstream commonOutput(util::outputFilePath + util::commonFile);
    std::ifstream aOnlyOutput(util::outputFilePath + util::aOnlyFile);
    std::ifstream bOnlyOutput(util::outputFilePath + util::bOnlyFile);

    std::string line;
    std::vector<std::string> commonContent;
    while (std::getline(commonOutput, line)) {
        commonContent.push_back(line);
    }
    commonOutput.close();

    std::vector<std::string> aOnlyContent;
    while (std::getline(aOnlyOutput, line)) {
        aOnlyContent.push_back(line);
    }
    aOnlyOutput.close();

    std::vector<std::string> bOnlyContent;
    while (std::getline(bOnlyOutput, line)) {
        bOnlyContent.push_back(line);
    }
    bOnlyOutput.close();

    for (int i = 2; i <= 1000; i += 2) {
        std::string expectedContent = "file" + std::to_string(i) + ".txt";
        EXPECT_TRUE(std::find(commonContent.begin(), commonContent.end(), expectedContent) != commonContent.end());
    }

    for (int i = 1; i <= 1000; i += 2) {
        std::string expectedContent = "file" + std::to_string(i) + ".txt";
        EXPECT_TRUE(std::find(aOnlyContent.begin(), aOnlyContent.end(), expectedContent) != aOnlyContent.end());
    }

    for (int i = 1; i <= 1000; i += 2) {
        std::string expectedContent = "file" + std::to_string(i) + ".txt";
        EXPECT_TRUE(std::find(bOnlyContent.begin(), bOnlyContent.end(), expectedContent) != bOnlyContent.end());
    }

    removeTestDirectory(dir1);
    removeTestDirectory(dir2);
    removeTestDirectory(util::outputFilePath);
}

TEST(FileUtilTest, ComputeMD5) {
    std::string filePath = "text.txt";
    std::string content = "Be me shall purse my ought times. Joy years doors all would again rooms these. Solicitude announcing as to sufficient my. No my reached suppose proceed pressed perhaps he. Eagerness it delighted pronounce repulsive furniture no. Excuse few the remain highly feebly add people manner say. It high at my mind by roof. No wonder worthy in dinner.";
    createTestFile(filePath, content);
    
    std::string computedMd5 = computeMD5(filePath);
    std::string expectedMd5 = "207e1cd7941e9f22ef9883cb23dd48d1"; 
    
    EXPECT_EQ(computedMd5, expectedMd5);

    fs::remove(filePath);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
