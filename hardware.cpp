
#include "stdafx.h"
#include <systemc.h>

SC_MODULE(hardware){
	sc_in<sc_uint<8>> input;
	sc_uint<8> in;
	sc_out<sc_uint<8>> hexes;
	sc_out<sc_uint<8>> diodes;
	int fl = 0;
	void run(){
		while (1){
			in = input.read();
			if (in == 'E'&&fl!=1) {
				cout << "hw error" << endl;
				fl = 1;

			}
			else if (in == 1&&diodes.read()!=8){
				fl = 0;
				wait(50, SC_MS);
				cout << "1:czerwone 2: zielone" << endl;
				diodes.write(8);//2|3
				hexes.write(3);
			}
			/*else if (in == 4 && diodes.read() != 4)
			{	
				cout << "1:zolte 2:czerwone+zolte" << endl;
				diodes.write(4);
				hexes.write(2);
			}*/
			wait(50, SC_MS);
		}
	}

	SC_CTOR(hardware){
		SC_THREAD(run);
	}
};