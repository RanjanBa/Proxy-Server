#include<iostream>
#include<thread>
#include<chrono>

typedef unsigned long long ull;

using namespace std;

void addSum(ull start, ull end, ull &res) {
    cout << this_thread::get_id() << endl;
    for(ull s = start; s <= end; s++) {
        res += s;
    }
}

void withoutThread(ull start, ull end) {
    ull res = 0;
    chrono::time_point<chrono::system_clock> start_time, end_time;

    start_time = chrono::system_clock::now();

    addSum(start, end, res);

    end_time = chrono::system_clock::now();

    chrono::duration<double> elapse_seconds = end_time - start_time;

    time_t finished_time = chrono::system_clock::to_time_t(end_time);

    cout << "res : " << res << endl;

    cout << "finished computation at " << ctime(&finished_time) << " elapsed time : " << elapse_seconds.count() << "s\n";
}

void withThread(ull start, ull end) {
    ull res = 0;
    chrono::time_point<chrono::system_clock> start_time, end_time;

    start_time = chrono::system_clock::now();

    ull mid = start + (end - start) / 2;

    ull res1 = 0, res2 = 0;
    thread t1(addSum, start, mid, ref(res1));
    thread t2(addSum, mid+1, end, ref(res2));
    t1.join();
    t2.join();
    res = res1 + res2;
    end_time = chrono::system_clock::now();

    chrono::duration<double> elapse_seconds = end_time - start_time;

    time_t finished_time = chrono::system_clock::to_time_t(end_time);

    cout << "res : " << res << endl;

    cout << "finished computation at " << ctime(&finished_time) << " elapsed time : " << elapse_seconds.count() << "s\n";
}

int main() {
    ull start = 0, end = 1000000000;
    withoutThread(start, end);
    withThread(start, end);

    return 0;
}