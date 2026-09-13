#include "cpu.hpp"
#include "bus.hpp"
#include "raylib.h"
#include <iostream>
#include <thread>
#include <chrono>

int main(){
    BUS bus;

    CPU cpu(&bus);

    bus.hard_reset();
    bus.fill_NOP();

    bus.write(0xfffc, 0x00);
    bus.write(0xfffd, 0x80);

    bus.write(0x0000, 0x00);

    bus.write(0x8000, 0xff);

    if(bus.load_chartridge("your game here")){
        std::cout << "Cartridge loaded." << std::endl;
    }

    cpu.hard_reset();


    //cpu.soft_reset();

    while(true){
        //GetTime();
        cpu.CPU_clock();
        //cpu.show_cyclecount();
        std::this_thread::sleep_for(std::chrono::nanoseconds(602));
    }
    

    return 0;
}