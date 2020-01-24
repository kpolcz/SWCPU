
#include <systemc.h>
#include "stdafx.h"
using namespace std;

SC_MODULE(cpu2) {
	sc_fifo_in<int> input;
	sc_out<sc_uint<8>> out;
	sc_uint<8> a = 0;
	int fl = 0;
	void task1() {

		while (1) {
			out = input.read();
			a = input.read();
			
			if(a==4&&fl!=1){

				cout << "1:zolte 2:czerwone+zolte" << endl;
				fl = 1;
			}
				wait(300, SC_MS);
			
			out = 0;
		}
	}

	SC_CTOR(cpu2) {
		SC_THREAD(task1);
	}
};