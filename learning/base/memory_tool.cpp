#include "memory_tool.h"
#include <iostream>
#include <fstream>

namespace roobtyan {
    MemoryTool::MemoryTool() = default;

    MemoryTool::~MemoryTool() = default;

    void MemoryTool::Process() {
        loadData();

        while (true) {
            std::cout << "Choose an option: (1) Add Memory (2) Review Memory (3) Exit\n";
            int choice;
            std::cin >> choice;
            if (choice == 1) {
                addMemory();
            } else if (choice == 2) {
                reviewMemory();
            } else {
                break;
            }
        }

        saveData();
    }

    void MemoryTool::addMemory() {
        std::string question, answer;
        std::cout << "Enter question: ";
        std::cin.ignore(); // 清除输入缓冲区
        std::getline(std::cin, question);
        std::cout << "Enter answer: ";
        std::getline(std::cin, answer);

        memoryItems.push_back({question, answer, 0, 0});
    }

    void MemoryTool::reviewMemory() {
        if (memoryItems.empty()) {
            std::cout << "No memory items available.\n";
            return;
        }

        // 简单随机选择一个问题
        int index = rand() % memoryItems.size();
        MemoryItem &item = memoryItems[index];

        std::cout << "Question: " << item.question << "\nYour Answer: ";
        std::string userAnswer;
        std::cin.ignore();
        std::getline(std::cin, userAnswer);

        if (userAnswer == item.answer) {
            std::cout << "Correct!\n";
            item.correctCount++;
        } else {
            std::cout << "Incorrect. The correct answer is: " << item.answer << "\n";
        }

        item.reviewCount++;
    }

    void MemoryTool::loadData() {
        // 从文件加载数据
        std::ifstream inFile("memory_data.txt");
        if (!inFile) return;

        std::string question, answer;
        int reviewCount, correctCount;
        while (inFile >> question >> answer >> reviewCount >> correctCount) {
            memoryItems.push_back({question, answer, reviewCount, correctCount});
        }

        inFile.close();
    }

    void MemoryTool::saveData() {
        // 保存数据到文件
        std::ofstream outFile("memory_data.txt");
        for (const auto &item: memoryItems) {
            outFile << item.question << " " << item.answer << " "
                    << item.reviewCount << " " << item.correctCount << "\n";
        }

        outFile.close();
    }

} // roobtyan