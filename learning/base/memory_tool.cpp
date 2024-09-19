#include "memory_tool.h"
#include <absl/time/time.h>
#include <iostream>
#include <fstream>
#include <random>
#include <utils.h>

namespace roobtyan {
    MemoryTool::MemoryTool() = default;

    MemoryTool::~MemoryTool() = default;

    void MemoryTool::Process() {
        LoadData();

        while (true) {
            std::cout << "Choose an option: (1) Add Memory (2) Review Memory (3) Exit\n";
            int choice;
            std::cin >> choice;
            if (choice == 1) {
                AddMemory();
            } else if (choice == 2) {
                ReviewMemory();
            } else {
                break;
            }
        }

        SaveData();
    }

    void MemoryTool::AddMemory() {
        std::string question, answer;
        std::cout << "Enter question: ";
        std::cin.ignore();
        std::getline(std::cin, question);
        std::cout << "Enter answer: ";
        std::getline(std::cin, answer);
        memoryItems.emplace_back(question, answer);
    }

    void MemoryTool::ReviewMemory() {
        if (memoryItems.empty()) {
            std::cout << "No memory to review.\n";
            return;
        }

        // 查找所有今天需要复习的题目
        std::vector<MemoryItem> today_review_items;
        for (const auto &item: memoryItems) {
            absl::Time next_review_time = get_time_only_day(item.next_review_time);
            if (next_review_time <= get_current_time_str_only_day()) {
                today_review_items.push_back(item);
            }
        }

        if (today_review_items.empty()) {
            std::cout << "No memory to review today.\n";
            return;
        }

        // 顺序复习
        int index = 1;
        for (auto &item: today_review_items) {
            std::cout << "Question(" << index++ << "/" << today_review_items.size() << ")" << " " << item.question
                      << "\n";
            std::string answer;
            std::cout << "Enter answer: ";
            std::cin.ignore();
            std::getline(std::cin, answer);
            if (answer == item.answer) {
                std::cout << "Correct!\n";
                item.correct_count++;
                item.next_review_time = get_time_str_with_offset(GetMemoryItemNextReviewGap(item.correct_count));
            } else {
                std::cout << "Incorrect!\n";
                item.correct_count = 0;
                item.is_restart = true;
                item.next_review_time = get_time_str_with_offset(1);
            }

            item.review_count++;
            item.last_review_time = get_current_time_str();
        }

        // 更新数据
        for (const auto &item: today_review_items) {
            for (auto &memory_item: memoryItems) {
                if (memory_item.uuid == item.uuid) {
                    memory_item = item;
                    break;
                }
            }
        }

        std::cout << "Review completed.\n";
    }

    void MemoryTool::LoadData() {
        std::ifstream inFile("memory_data.txt");
        if (!inFile) return;

        auto memory_item = MemoryItem();
        while (inFile >> memory_item.uuid >> memory_item.question >> memory_item.answer >> memory_item.review_count >>
                      memory_item.correct_count >> memory_item.is_restart >> memory_item.create_time
                      >> memory_item.last_review_time >> memory_item.next_review_time) {
            memoryItems.push_back(memory_item);
        }

        inFile.close();
    }

    void MemoryTool::SaveData() {
        std::ofstream outFile("memory_data.txt");
        for (const auto &item: memoryItems) {
            outFile << item.ToString() + "\n";
        }
        outFile.close();
    }

    int MemoryTool::GetMemoryItemNextReviewGap(const int &correct_count) {
        std::vector<int> gap = {1, 3, 7, 15, 30, 60};
        if (correct_count >= gap.size()) {
            return correct_count * 15;
        }
        return gap[correct_count];
    }

    MemoryTool::MemoryItem::MemoryItem() = default;

    MemoryTool::MemoryItem::MemoryItem(std::string question, std::string answer)
            : question(std::move(question)), answer(std::move(answer)) {
        uuid = generate_uuid();
        create_time = get_current_time_str();
        last_review_time = create_time;
        // 默认第一次复习时间为24小时后
        auto in_next_review_time = get_current_time() + absl::Hours(24);
        std::string next_review_time_str;
        auto status = time_to_string(in_next_review_time, &next_review_time_str);
        if (!status.ok()) {
            std::cerr << "Error: " << status.message() << "\n";
            return;
        }
        next_review_time = next_review_time_str;
    }

    std::string MemoryTool::MemoryItem::ToString() const {
        std::string str;
        str += uuid + " " + question + " " + answer + " " + std::to_string(review_count) + " " +
               std::to_string(correct_count) + " " + std::to_string(is_restart) + " " + create_time + " " +
               last_review_time + " " + next_review_time;
        return str;
    }
} // roobtyan