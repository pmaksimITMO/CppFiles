#include <bits/stdc++.h>
using namespace std;

int count_hits = 0;
int count_tact = 0;
int count_questions = 0;
int cur_time = 0;
int n = 60, m = 64, k = 32;
map<pair<int, int>, int> l_a, l_b, l_c;

class mem {
    vector<int> data;
public:
    mem() {
        data.assign(1 << 20, 0);
    }
    void write_line(int pos, vector<int> val) {
        for (int i = 0; i < 32; i++) {
            data[pos/32 + i] = val[i];
            count_tact++;
        }
    }
    vector<int> read_line(int pos) {
        vector<int> result(32, 0);
        for (int i = 0; i < 32; i++) {
            result[i] = data[pos/32 + i];
            count_tact++;
        }
        return result;
    }
};

class cache {
    vector<vector<vector <int>>> data;
    vector<vector<bool>> valid, dirty;
    vector<vector<int>> last_use, line_tag;
    mem op_mem;
public:
    cache() {
        op_mem = *new mem();
        dirty.assign(16, vector<bool>(2, false));
        valid.assign(16, vector<bool>(2, false));
        line_tag.assign(16, vector<int>(2, -1));
        last_use.assign(16, vector<int>(2, 0));
        data.resize(16, vector<vector<int>>(2, vector<int>(32, 0)));
    }
    int read(int pos) {
        int set_num = (pos / 32) % 16, offset_num = pos % 32, tag = (pos / 32) / 16;
        count_questions++;
        if (line_tag[set_num][0] == tag && valid[set_num][0]) {
            //HIT
            count_tact += 6;
            count_hits++;
            last_use[set_num][0] = cur_time++;
            return data[set_num][0][offset_num];
        } else if (line_tag[set_num][1] == tag && valid[set_num][1]) {
            //HIT
            count_tact += 6;
            count_hits++;
            last_use[set_num][1] = cur_time++;
            return data[set_num][1][offset_num];
        } else {
            //MISS
            count_tact += 4;
            int id;
            if (!valid[set_num][0]) id = 0;
            else if (!valid[set_num][1]) id = 1;
            else id = last_use[set_num][0] <= last_use[set_num][1] ? 0 : 1;
            data[set_num][id] = op_mem.read_line(pos);
            valid[set_num][id] = true;
            dirty[set_num][id] = false;
            line_tag[set_num][id] = tag;
            return data[set_num][id][offset_num];
        }
    }
    int read16(int pos) {
        int res = read(pos) * (1 << 8);
        int a = count_hits, b = count_questions;
        res += read(pos + 1);
        count_hits = a, count_questions = b;
        return res;
    }
    int read32(int pos) {
        int res = read(pos) * (1 << 8);
        int a = count_hits, b = count_questions;
        res = ((res + read(pos + 1)) * (1 << 8) + read(pos + 2)) * (1 << 8) + read(pos + 3);
        count_hits = a, count_questions = b;
        return res;
    }
    void write(int pos, int val) {
        int set_num = (pos / 32) % 16, offset_num = pos % 32, tag = (pos / 32) / 16;
        count_questions++;
        if (line_tag[set_num][0] == tag && valid[set_num][0]) {
            //HIT
            count_tact += 6;
            count_hits++;
            last_use[set_num][0] = cur_time++;
            dirty[set_num][0] = true;
            data[set_num][0][offset_num] = val;
        } else if (line_tag[set_num][1] == tag && valid[set_num][1]) {
            //HIT
            count_tact += 6;
            count_hits++;
            last_use[set_num][1] = cur_time++;
            dirty[set_num][1] = true;
            data[set_num][1][offset_num] = val;
        } else {
            //MISS
            count_tact += 4;
            int id;
            if (!valid[set_num][0]) id = 0;
            else if (!valid[set_num][1]) id = 1;
            else id = (last_use[set_num][0] <= last_use[set_num][1] ? 0 : 1);
            if (dirty[set_num][id]) {
                op_mem.write_line(((line_tag[set_num][id] * 16) + set_num) * 32, data[set_num][id]);
            }
            data[set_num][id] = op_mem.read_line(pos);
            valid[set_num][id] = true;
            dirty[set_num][id] = true;
            line_tag[set_num][id] = tag;
            data[set_num][id][offset_num] = val;
        }
    }
    void write16(int pos, int val) {
        write(pos, val % 64);
        int a = count_hits, b = count_questions;
        write(pos + 1, val/64);
        count_hits = a, count_questions = b;
    }
    void write32(int pos, int val) {
        write(pos, val % 64);
        int a = count_hits, b = count_questions;
        write(pos + 1, (val / 64) % 64);
        write(pos + 2, ((val / 64) / 64) % 64);
        write(pos + 3, ((val / 64) / 64) / 64);
        count_hits = a, count_questions = b;
    }
};

void mmul() {
    cache lru_cache = *new cache();
    count_tact += 2;
    for (int y = 0; y < m; y++) {
        for (int x = 0; x < n; x++) {
            count_tact += 2;
            for (int z = 0; z < k; z++) {
                lru_cache.read(l_a[{y, z}]);
                lru_cache.read16(l_b[{z, x}]);
                count_tact += 1 + 5;
                count_tact++;
            }
            lru_cache.write32(l_c[{y, x}], 1);
        }
        count_tact += 2;
    }
    count_tact += m * n * k + 1;
}

void calc_mem_adr() {
    int p = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            l_a[{i, j}] = p;
            p++;
        }
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            l_b[{i, j}] = p;
            p += 2;
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            l_c[{i, j}] = p;
            p += 4;
        }
    }
}

int main() {
    calc_mem_adr();
    mmul();
    cout << count_tact << '\n';
    cout << count_questions << ' ' << count_hits << '\n';
    cout << fixed << setprecision(6) << (count_hits + .0)/count_questions;
}
