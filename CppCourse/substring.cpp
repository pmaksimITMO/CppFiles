#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int calc_func(const int* func, int value, const char* pattern, char searchable) {
    if (value > 0 && pattern[value] != searchable) {
        value = func[value - 1];
    }
    if (searchable == pattern[value]) {
        ++value;
    }
    return value;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Invalid number of arguments: expected - 2, found: %i\n", argc);
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[1], "rb");
    if (file == nullptr) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }

    const size_t BUF_SIZE = 4096;
    const size_t len = strlen(argv[2]);
    std::array<char, BUF_SIZE> buffer{};

    int* func = static_cast<int*>(std::malloc(len * sizeof(int)));
    if (func == nullptr) {
        perror("Not enough memory");
        fclose(file);
        return EXIT_FAILURE;
    }

    int index = 0;
    size_t read_n;

    func[0] = 0;
    for (int i = 1; i < len; ++i) {
        func[i] = calc_func(func, func[i - 1], argv[2], argv[2][i]);
    }

    do {
        read_n = fread(buffer.data(), 1, buffer.size(), file);
        if (ferror(file)) {
            perror("Input reading error");
            fclose(file);
            free(func);
            return EXIT_FAILURE;
        }
        for (size_t i = 0; i < read_n; ++i) {
            index = calc_func(func, index, argv[2], buffer[i]);
            if (index == len) {
                puts("Yes");
                fclose(file);
                free(func);
                return EXIT_SUCCESS;
            }
        }
    } while (read_n != 0);

    puts("No");
    fclose(file);
    free(func);
    return EXIT_SUCCESS;
}