#include <stdio.h>
#include <omp.h>
#include <random>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Incorrect input, use: <file_name> <num_threads> <input_file_name> <output_file_name>");
        exit(0);
    }
    double r;
    int n;
    FILE *fin;
    try {
        fin = fopen(argv[2], "rb");
        fscanf(fin, "%lf", &r);
        fscanf(fin, "%i", &n);
        int threads = stoi(string(argv[1]));
        if (threads != 0) omp_set_num_threads(threads);
    } catch (exception e) {
        printf("Exception in opening/reading file: %s", e.what());
        fclose(fin);
    }
    int count = 0;
    random_device device;
    double start = omp_get_wtime();
    #pragma omp parallel if (string(argv[1]) != "-1") default(none) shared(count, device) firstprivate(r, n)
    {
        mt19937 rnd(device());
        uniform_real_distribution<double> distrib(-r, r);
        double x, y;
        int k = 0;
        #pragma omp for nowait schedule(guided, 128)
            for (int i = 0; i < n; ++i) {
                x = distrib(rnd), y = distrib(rnd);
                if (x * x + y * y <= r * r) k++;
            }
        #pragma omp atomic
            count += k;
    }
    double res = 4.0 * r * r * count / n;
    double end = omp_get_wtime();
    printf("%i, %f\n", count, res);
    FILE *fout;
    try {
        fout = fopen(argv[3], "wb");
        fprintf(fout, "%lf", res);
    } catch (exception e) {
        printf("Exception in output file: %s", e.what());
        fclose(fout);
    }
    printf("Time (ms): %lf", (end - start) * 1000);
}
