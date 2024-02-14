#include <iostream> 
#include <time.h> 
#include "Processor.h"

using namespace std;

enum
{
    DENIED,
    ALLOWED,
    ACCESSED
};

enum
{
    REQUEST,
    FREE
};

int ACCESS = DENIED;

Processor::Processor(int Pn, int Kr, int M, int K, int N) {
    this->Pn = Pn;
    this->Kr = Kr;
    this->M = M;
    this->K = K;
    this->N = N;

    memory_access = new int[this->N]; 
    lead_time = new int[this->N]; 
    data = new int* [this->N];

    for (int i = 0; i < this->N; i++) {
        memory_access[i] = ALLOWED; 
        lead_time[i] = 0;
        data[i] = new int[this->K];
    } 
}

Processor::~Processor() {
    for (int i = 0; i < N; i++) {
        delete[] data[i]; 
    }
    delete[] data;
    delete[] memory_access; 
    delete[] lead_time;
}

void Processor::set_pn(int Pn) {
    this->Pn = Pn; 
}

void Processor::set_kr(int Kr) {
    this->Kr = Kr; 
}

void Processor::set_m(int M) {
    this->M = M; 
}

void Processor::set_k(int K) {
    this->K = K; 
}

void Processor::set_n(int N) {
    this->N = N; 
}

void Processor::set_data_to_memory() {
    for (int id = 0; id < N; id++) {
        srand(time(NULL) - 100 * id);
        int delta_K = K - K * Kr / 100;
        int delta_K_to_block = delta_K * Pn / 100; 
        int memory = 0;

        for (int i = 0; i < K; i++) {
            if (delta_K && rand() % ((K - i) / delta_K) == 0) {
                if (delta_K - delta_K_to_block != 0 && rand() % (delta_K / (delta_K - delta_K_to_block)) == 0){
                     while (true){
                        memory = rand() % N + 1; if (memory != id + 1)
                        break;
                    } 
                } else {
                    memory = id + 1;
                    delta_K_to_block--;
                } 

                data[id][i] = memory;
                delta_K--;
            }
            else{
                data[id][i] = 0;
            }
        }
    }    
}

void Processor::commutator(int flag){
    int access;
    int delay = 1;
    for (int i = 0; i < K; i++){
        for (int id = 0; id < N; id++) {
            if (data[id][i]) {
                if (flag == 1) {
                    cout << "Data transfer request" << "\t" << data[id][i] << "\t\tProc " << id + 1 << endl; 
                }
                while (true){
                    access = memory(REQUEST, data[id][i]);

                    if (access == ACCESSED) {
                        if (flag == 1) {
                            cout << "Memory access" << "\t\t" << data[id][i] << "\t\tProc " << id + 1 << "\t" << endl;
                        }
                    lead_time[id] += M; break;
                    }
                    else{
                        if (flag == 1){
                            cout << "Memory wait" << "\t\t" << data[id][i] << "\t\tProc " << id + 1 << "\t" << endl;
                        }
                        lead_time[id] += 1 * delay; 
                        delay++;
                        memory(FREE, data[id][i]);
                    }
                }
            }
            else{
                lead_time[id] += 1;
                if(flag == 1){
                    cout << "Without memory request" << "\t-" << "\t\tProc " << id + 1 << "\t" << endl;
                }
            }
        }
        for (int i = 0; i < N; i++)
        {
            memory_access[i] = ALLOWED;
        }
        delay = 1;
    }

    if (flag == 1){
        cout << endl;
    }
    cout << "Work time commutator: " << worktime() << endl;
    if (flag == 1){
        cout << endl;
    }
}

void Processor::bus(int flag) {
    int access;
    int delay = 1;
    for (int i = 0; i < K; i++) {
        for (int id = 0; id < N; id++) {
            if (data[id][i]) {
                if (flag == 1) {
                    cout << "Data transfer request" << "\t" << data[id][i] << "\t\tProc " << id + 1 << "\t" << endl;
                    }
                while (true) {
                    access = memory(REQUEST);

                    if (access == ACCESSED) {
                        if (flag == 1) {
                            cout << "Memory access" << "\t\t" << data[id][i] << "\t\tProc " << id + 1 << "\t" << endl;
                        }
                        lead_time[id] += M; 
                        break;
                    } else{
                        if (flag == 1){
                            cout << "Memory wait" << "\t\t" << data[id][i] << "\t\tProc " << id + 1 << "\t" << endl;
                        }
                        lead_time[id] += 1 * delay; 
                        delay++;
                        memory(FREE);
                    }
                }
            } else{
                lead_time[id] += 1;
                if (flag == 1){
                    cout << "Without memory request" << "\t-" << "\t\tProc " << id + 1 << "\t" << endl;
                }
            }
        }
        delay = 1;
    }
    if (flag == 1){
        cout << endl;
    }
    cout << "Work time bus: " << worktime() << endl;
    if (flag == 1){
        cout << endl;
    }
}

int Processor::memory(int req, int num){ //функция доступа к памяти для коммутатора 
    ACCESS = memory_access[num - 1]; //переменной аксес присваиваем команду из массива имен доступа

    if (ACCESS == ALLOWED && req == REQUEST) {
        ACCESS = DENIED; 
        memory_access[num - 1] = DENIED; 
        return ACCESSED;
    }
    else if (ACCESS == DENIED && req == REQUEST) {
        return DENIED;
    }
    else if (ACCESS == DENIED && req == FREE) {
        ACCESS = ALLOWED; 
    }

    memory_access[num - 1] = ALLOWED;
    return ACCESS; 
}

int Processor::memory(int req) {
    if (ACCESS == ALLOWED && req == REQUEST) {
        ACCESS = DENIED;
        return ACCESSED; 
    }
    else if (ACCESS == DENIED && req == FREE) {
        ACCESS = ALLOWED; 
    }
    return ACCESS; 
}

int Processor::worktime() {
    int max = 0;
    for (int i = 0; i < N; ++i) {
        if (lead_time[i] > max) {
            max = lead_time[i]; 
        }
    }
    
    for (int i = 0; i < N; i++) {
        lead_time[i] = 0; 
    }

    return max; 
}