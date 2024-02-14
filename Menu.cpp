#include<iostream>
#include "Menu.h"
#include "Processor.h"

using namespace std;

void Menu::main_menu()
{
    cout << "Research of multiprocessing system. Console version." << endl << endl;
    cout << "All data should be inputted as integer numbers!" << endl;
    processor_settings();
}

void Menu::processor_settings()
{
    int Pn, Kr, M, K, N, flag = 1;
    int c;

    cout << "Input number of blocks(N): ";
    cin >> N;
    cout << "Inputdata,usinginonememoryblock(Pn): ";
    cin >> Pn;
    cout << "Input commands that aren't using external memory(Kr): ";
    cin >> Kr;
    cout << "Inputunittime(Mininteger): ";
    cin >> M;
    cout << "Inputnumberofcommands(Kininteger): ";
    cin >> K;

    Processor proc(Pn,Kr,M,K,N);
    proc.set_data_to_memory();

    cout << "\nDo you want to output a commands' list for commutator and bus?" << endl;
    cout << "1 - Yes" << endl;
    cout << "2 - No" << endl;
    cout << ">";
    cin >> c;

    if(c == 1) {
        flag = 1;
    }
    else {
        flag = 0;
    }

    cout << "\nWorktime report for bus and commutator:" << endl;
    if(flag == 1)
    {
        cout << "\n" << "Command name" << "\t\t" << "Command to" << "\t" <<
        "Processor" << "\n" << endl;
    }
    proc.commutator(flag);
    proc.bus(flag);
}