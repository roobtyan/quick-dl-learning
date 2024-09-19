#pragma once

#include <vector>
#include <string>

namespace roobtyan {

    class MemoryTool {
    public:
        MemoryTool();

        ~MemoryTool();

        void Process();
    private:
        void addMemory();
        void reviewMemory();
        void loadData();
        void saveData();

        struct MemoryItem {
            std::string question;
            std::string answer;
            int reviewCount;
            int correctCount;
        };

        std::vector<MemoryItem> memoryItems;
    };

} // roobtyan