#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(int argc, char **argv) {
    if (argc != 3) {
        fputs("Invalid number of arguments\n", stderr);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == nullptr) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }

    const size_t BUF_SIZE = 4096;
    std::array<char, BUF_SIZE> buffer;
    size_t index = 0;
    size_t len = strlen(argv[2]);
    while (!feof(file)) {
        size_t read_n = fread(buffer.data(), 1, buffer.size(), file);
        for (size_t i = 0; i < read_n; ++i) {
            if (buffer[i] == argv[2][index]) {
                index++;
            } else {
                index = 0;
            }
            if (index == len) {
                puts("YES");
                fclose(file);
                return EXIT_SUCCESS;
            }
        }
    }

    if (ferror(file)) {
        perror("Input reading error");
        fclose(file);
        return EXIT_FAILURE;
    }

    puts("NO");
    fclose(file);
    return EXIT_SUCCESS;
}