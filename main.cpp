lude <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "pixel.h"

std::vector<Pixel> read_pixel_data(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Pixel> pixel_list;
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return pixel_list;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t pos = 0;
        int x, y;
        float r, g, b;

        pos = line.find(',');
        x = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(',');
        y = std::stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(',');
        r = std::stof(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find(',');
        g = std::stof(line.substr(0, pos));
        line.erase(0, pos + 1);

        b = std::stof(line);

        Pixel pixel = {r, g, b, x, y};
        pixel_list.push_back(pixel);
    }

    file.close();
    return pixel_list;
}

void average_colors(const std::vector<Pixel>& pixel_list) {
    float sum_r = 0.0, sum_g = 0.0, sum_b = 0.0;
    for (const auto& pixel : pixel_list) {
        sum_r += pixel.r;
        sum_g += pixel.g;
        sum_b += pixel.b;
    }

    float avg_r = sum_r / pixel_list.size();
    float avg_g = sum_g / pixel_list.size();
    float avg_b = sum_b / pixel_list.size();

    std::cout << "Average R: " << avg_r << "\n";
    std::cout << "Average G: " << avg_g << "\n";
    std::cout << "Average B: " << avg_b << "\n";
}

void flip_vertically(std::vector<Pixel>& pixel_list) {
    int max_y = 255; // As given, the maximum y value is 255 (since y-length is 256)
    for (auto& pixel : pixel_list) {
        pixel.y = max_y - pixel.y;
    }
}

void write_flipped_data(const std::string& filename, const std::vector<Pixel>& pixel_list) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    for (const auto& pixel : pixel_list) {
        file << pixel.x << "," << pixel.y << ","
             << pixel.r << "," << pixel.g << "," << pixel.b << "\n";
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string input_filename = argv[1];
    std::vector<Pixel> pixel_list = read_pixel_data(input_filename);

    average_colors(pixel_list);

    flip_vertically(pixel_list);

    write_flipped_data("flipped.dat", pixel_list);

    return 0;
}
