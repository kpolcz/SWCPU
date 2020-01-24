#include "stdafx.h"
#include <systemc.h>
#include <conio.h>

//#include "modulSprzetowy.cpp"

using namespace std;



SC_MODULE(cpu1) {
	sc_inout<sc_uint<8>> program;
	sc_inout<sc_uint<8>> switches;
	sc_inout<sc_uint<8>> hexes;
	sc_fifo_out<int> output;
	

	sc_inout<sc_uint<8>> diodes;

	int state = 0, d;
	int p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0;
	bool er = false;
	bool er_read = false;
	int last = 0;
	int count;
	bool constructed = false;

	bool sw_states[6] = { false, false, false, false, false, false };

	void task1() {
		//vector<int> stack;
		int f = 0;
		int k = 0;//kierunek
		while (1)
		{
			wait(500, SC_NS);

			if (_kbhit()) {
				displayHEX();
				displayLED();
				displaySW();

				wait(25, SC_NS);
				cout << "Wybrany switch: " << endl;
				cin >> f;
				cout << "Switch kierunkowy" << endl;
				cin >> k;

					wait(500, SC_NS);
					sc_uint<8> sw_state = toBitFlag(f, k);

					switches.read();
					switches.write(sw_state);
					
					wait(500, SC_NS);
				

			}
			wait(500, SC_NS);
			program.write(f);
			wait(500, SC_NS);


			count = 0;
			wait(500, SC_NS);
			sc_uint<8> sw_state = toBitFlag(f, k);

			sc_uint<8> oldest_bit = 0x80;
			wait(500, SC_NS);
			

			 if ( sw_state == 2 && diodes.read()!=2) {
				cout << "1:zielone 2:czerwone " << endl;
				diodes.write(2);
				hexes.write(1);
			}

			wait(500, SC_NS);
			switches.write(sw_state);

			wait(100, SC_MS);
		}
	}
	//na cpu2
	void task2() {
		while (1) {
			sc_uint<8> progNo = switches.read();
			if (progNo == 4)
			output.write(4);
			wait(10, SC_MS);
			
		}
	}//dorota.dariusz@gmail.com
	void task4() {
		while (1) {
			sc_uint<8> progNo = switches.read();
			if (progNo == 16 && diodes.read() != 16) {
				cout << "1:czerwone+zolte 2:zolte" << endl;
				diodes.write(16);//led4
				hexes.write(4);
			}
			wait(10, SC_MS);
		}
	}

	void task5() {
		while (1) {
			sc_uint<8> progNo = switches.read();
			if (progNo == 32 && diodes.read() != 32) {
				cout << "1:uprzywilejowane 2:uprzywilejowane" << endl;
				diodes.write(32);
				hexes.write(5);
			}
			wait(10, SC_MS);
		}
	}

	void task6() {
		while (1) {
			sc_uint<8> progNo = switches.read();
			if (progNo == 3 &&diodes.read()!=3) {
				cout << "1:czerwone 2:zielone" << endl;
				diodes.write(3);//led3
				hexes.write(3);
			}
			wait(200, SC_MS);
		}
	}
	void task3() {
		while (1) {
			sc_uint<8> progNo = switches.read();
			if (progNo == 8 && diodes.read() != 8) {
				output.write(1);

			}
			wait(10, SC_MS);
		}
	}
	void task7() {
		while (1) {
			sc_uint<8> progNo = switches.read();
			if (progNo == 5 && diodes.read()!=5) {
				cout << "1:zolte 2:czerwone+zolte" << endl;
				diodes.write(5);//led3|2
				hexes.write(4);
			}
			wait(200, SC_MS);
		}
	}
	void task8() {
		while (1) {
			sc_uint<8> progNo = switches.read();
			if (progNo == 9 && diodes.read() != 9) {
				cout << "1:zielone 2:czerwone" << endl;
				diodes.write(9);//led1
				hexes.write(2);
			}
			wait(200, SC_MS);
		}
	}

	void task9() {
		while (1) {
			sc_uint<8> progNo = switches.read();
			if (progNo == 17 && diodes.read() != 17) {
				cout << "1:zolte 2:czerwone+ zolte" << endl;
				diodes.write(17);//led2
				hexes.write(5);
			}
			wait(200, SC_MS);
		}
	}
	void task10() {
		while (1) {
			sc_uint<8> progNo = switches.read();
			if (progNo == 33 && diodes.read()!=33) {
				cout << "1:uprzywilejowane 2:uprzywilejowane" << endl;
				diodes.write(33);//led5
				hexes.write(5);
			}
			wait(200, SC_MS);
		}
	}
	void taskErr() {
		//sc_uint<8> progNo = switches.read();
		while (1) {
			sc_uint<8> progNo = switches.read();
			if (progNo == 50 && diodes.read() != 50) {
				cout << "1:ERROR 2: ERROR" << endl;
				//output.write('E');
				diodes.write(50);//led5
				hexes.write(50);
			}
			wait(200, SC_MS);
		}
	}

	void displayLED() {
		sc_uint<8> diodes_state = diodes.read();

		switch (diodes_state)
		{
		case 2:
			cout << "dioda 1" << endl;
			break;
		case 3:
			cout << "dioda 3" << endl;
			break;
		case 4:
			cout << "dioda 2" << endl;
			break;
		case 5:
			cout << "diody 2 i 3" << endl;
			break;
		case 8:
			cout << "diody 3" << endl;
			break;
		case 9:
			cout << "dioda 1" << endl;
			break;
		case 16:
			cout << "dioda 2 i 3" << endl;
			break;
		case 17:
			cout << "dioda 2" << endl;
			break;
		case 32:
			cout << "dioda 5" << endl;
			break;
		case 33:
			cout << "dioda 5" << endl;
			break;
		case 50:
			cout << "dioda 8" << endl;
		


		}
	
	}

	void displaySW() {

		sc_uint<8> switches_state = switches.read();
		switch (switches_state)
		{
		case 2:
			cout << "switch 1" << endl;
			break;
		case 3:
			cout << "switch 1 i 0" << endl;
			break;
		case 4:
			cout << "switch 2" << endl;
			break;
		case 5:
			cout << "switch 2 i 0" << endl;
			break;
		case 8:
			cout << "switch 3" << endl;
			break;
		case 9:
			cout << "switch 3 i 0" << endl;
			break;
		case 16:
			cout << "switch 4" << endl;
			break;
		case 17:
			cout << "switch 4 i 0" << endl;
			break;
		case 32:
			cout << "switch 5" << endl;
			break;
		case 33:
			cout << "switch 5 i 0" << endl;
			break;


		}

	}

	void displayHEX() {
		sc_uint<8> hex = hexes.read();
		if (hex == 50)
			cout << "hex= ERR" << endl;
		else
		cout << "hex = " << hex << endl;

	}
	
	sc_uint<8> toBitFlag(int value, int k) {
		if (k == 0) {
			switch (value) {

			case 1:
				return 2;
			case 2:
				return 4;
			case 3:
				return 8;
			case 4:
				return 16;
			case 5:
				return 32;


			}
		}
		else if (k == 1) {
			switch (value) {

			case 1:
				return 3;
			case 2:
				return 5;
			case 3:
				return 9;
			case 4:
				return 17;
			case 5:
				return 33;

			}
		}
		return 50;

	}


	SC_CTOR(cpu1) {
		SC_THREAD(task1);
		SC_THREAD(task2);
		SC_THREAD(task3);
		SC_THREAD(task4);
		SC_THREAD(task5);
		SC_THREAD(task6);
		SC_THREAD(task7);
		SC_THREAD(task8);
		SC_THREAD(task9);
		SC_THREAD(task10);
		SC_THREAD(taskErr);
	}
};