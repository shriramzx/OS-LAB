#include <iostream>
#include <string>
#include <vector>

int main() {
    constexpr int disk_blocks = 12;
    std::vector<bool> used(disk_blocks, false);
    std::vector<std::string> names;
    std::vector<int> indexes;
    std::vector<std::vector<int>> data_blocks;
    std::cout << "College Examination Document Storage - Indexed File Allocation\n";
    int count;
    std::cout << "Number of files (1-12): ";
    if (!(std::cin >> count) || count < 1 || count > disk_blocks) {
        std::cerr << "Invalid file count.\n"; return 1;
    }
    for (int f = 0; f < count; ++f) {
        std::string name; int index, n;
        std::cout << "File name, index block, and data-block count: ";
        if (!(std::cin >> name >> index >> n) || index < 0 || index >= disk_blocks || n < 1 || n >= disk_blocks) {
            std::cerr << "Invalid file details.\n"; return 1;
        }
        if (used[index]) { std::cerr << "Index block is already allocated.\n"; return 1; }
        std::vector<int> blocks(n);
        std::cout << "Enter " << n << " data block numbers: ";
        for (int &b : blocks) {
            if (!(std::cin >> b) || b < 0 || b >= disk_blocks || b == index || used[b]) {
                std::cerr << "Data blocks must be valid, free, and different from the index block.\n"; return 1;
            }
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j)
                if (blocks[i] == blocks[j]) { std::cerr << "Duplicate data block in one file.\n"; return 1; }
        used[index] = true;
        for (int b : blocks) used[b] = true;
        names.push_back(name); indexes.push_back(index); data_blocks.push_back(blocks);
    }
    puts("\nFile\tIndex block\tData blocks");
    for (int f = 0; f < count; ++f) {
        std::cout << names[f] << '\t' << indexes[f] << "\t\t";
        for (std::size_t i = 0; i < data_blocks[f].size(); ++i)
            std::cout << data_blocks[f][i] << (i + 1 == data_blocks[f].size() ? "" : " ");
        std::cout << '\n';
    }
    std::cout << "Simulation assumption: each disk block holds one data block or one index block.\n";
    return 0;
}
