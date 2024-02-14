#pragma once

class Processor {
private:
    int** data;
    int* lead_time; 
    int* memory_access; 
    int Pn;
    int Kr;
    int M;
    int K;
    int N;

public:
    Processor();
    Processor(int Pn, int Kr, int M, int K, int N); 
    ~Processor();
    void set_pn(int Pn); 
    void set_kr(int Kr); 
    void set_m(int M); 
    void set_k(int K); 
    void set_n(int N);
    void set_data_to_memory();

    void commutator(int flag); 
    void bus(int flag);
    
    int memory(int req, int num); 
    int memory(int req);
    int worktime(); 
};
