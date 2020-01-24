// SW.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include <iostream>
#include "systemc.h"
#include "CPU_1.cpp"
#include "CPU_2.cpp"
#include "hardware.cpp"


SC_MODULE(queue) {
	sc_fifo<int> Que;

	SC_CTOR(queue) {
		sc_fifo<int> Que(6);
	}
};

// sc_main in top level function like in C++ main
int sc_main(int argc, char* argv[]) {
	sc_signal<sc_uint<8>, SC_MANY_WRITERS> diodes;
	sc_signal<sc_uint<8>, SC_MANY_WRITERS> program;
	sc_signal<sc_uint<8>, SC_MANY_WRITERS> switches;
	sc_signal<sc_uint<8>, SC_MANY_WRITERS> hex;
	sc_signal<sc_uint<8>, SC_MANY_WRITERS> cpu_2_hardware;

	queue q("queue");

	cpu1 proc1("cpu1");
	proc1.output(q.Que);
	proc1.diodes(diodes);
	proc1.program(program);
	proc1.switches(switches);
	proc1.hexes(hex);

	cpu2 procek2("cpu2");
	procek2.input(q.Que);
	procek2.out(cpu_2_hardware);;

	hardware hard("hardware");
	hard.diodes(diodes);
	hard.hexes(hex);
	hard.input(cpu_2_hardware);

	sc_start();

	cout << endl << endl;
	return(0);
}