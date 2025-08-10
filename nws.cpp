#include <iostream>
#include <filesystem>
#include <string>
#include <algorithm>
#include <cstring>

namespace fs = std::filesystem;

void show_help() {
    std::cout << "Usage: nws [options]\n"
              << "Options:\n"
              << "  --path, -p <directory>  Specify target directory (required for batch processing)\n"
              << "  --type, -t <extension>  Filter files by extension (e.g., html, cpp)\n"
              << "  --file, -f <filename>   Process a single file\n"
              << "  --help, -h              Show this help message\n\n"
              << "Examples:\n"
              << "  nws --path /path/files/ --type html\n"
              << "  nws --file \"archivo con espacios.cpp\"\n";
}

void replace_spaces_in_file(const fs::path& filepath) {
    if (!fs::exists(filepath)) {
        std::cerr << "Error: File does not exist: " << filepath << std::endl;
        return;
    }

    std::string filename = filepath.filename().string();
    if (filename.find(' ') == std::string::npos) {
        std::cout << "No spaces found in filename: " << filename << std::endl;
        return;
    }

    std::string newname = filename;
    std::replace(newname.begin(), newname.end(), ' ', '-');

    try {
        fs::path newpath = filepath.parent_path() / newname;
        fs::rename(filepath, newpath);
        std::cout << "Renamed: " << filename << " → " << newname << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error renaming file: " << e.what() << std::endl;
    }
}

void process_directory(const fs::path& dirpath, const std::string& extension = "") {
    if (!fs::exists(dirpath)) {
        std::cerr << "Error: Directory does not exist: " << dirpath << std::endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(dirpath)) {
        if (!fs::is_regular_file(entry.status())) continue;

        std::string filename = entry.path().filename().string();
        if (!extension.empty() && entry.path().extension() != ("." + extension)) {
            continue;
        }

        if (filename.find(' ') != std::string::npos) {
            replace_spaces_in_file(entry.path());
        }
    }
}

int main(int argc, char* argv[]) {
    fs::path directory_path;
    std::string file_extension;
    fs::path single_file;
    bool has_path = false;
    bool has_file = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "--help" || arg == "-h") {
            show_help();
            return 0;
        } else if ((arg == "--path" || arg == "-p") && i + 1 < argc) {
            directory_path = argv[++i];
            has_path = true;
        } else if ((arg == "--type" || arg == "-t") && i + 1 < argc) {
            file_extension = argv[++i];
        } else if ((arg == "--file" || arg == "-f") && i + 1 < argc) {
            single_file = argv[++i];
            has_file = true;
        } else {
            std::cerr << "Unknown option or missing argument: " << arg << std::endl;
            show_help();
            return 1;
        }
    }

    if (has_file) {
        replace_spaces_in_file(single_file);
    } else if (has_path) {
        process_directory(directory_path, file_extension);
    } else {
        std::cerr << "Error: Either --path or --file must be specified\n";
        show_help();
        return 1;
    }

    return 0;
}
