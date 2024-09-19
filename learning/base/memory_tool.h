#pragma once

#include <vector>
#include <string>
#include <absl/time/time.h>
#include "absl/status/status.h"
#include "utils.h"

namespace roobtyan {

    class MemoryTool {
    public:
        MemoryTool();

        ~MemoryTool();

        void Process();

        static int GetMemoryItemNextReviewGap(const int& correct_count);

    private:
        void AddMemory();

        void ReviewMemory();

        void LoadData();

        void SaveData();

        struct MemoryItem {
            std::string uuid;
            std::string question;
            std::string answer;
            int review_count = 0;
            int correct_count = 0;
            bool is_restart = false;
            std::string create_time;
            std::string last_review_time;
            std::string next_review_time;

            MemoryItem();

            MemoryItem(std::string question, std::string answer);

            [[nodiscard]] std::string ToString() const;
        };

        std::vector<MemoryItem> memoryItems;
    };

} // roobtyan