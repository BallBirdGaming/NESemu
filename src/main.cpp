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

    if(bus.load_cartridge("../testrom/smb.nes")){
        std::cout << "Cartridge loaded." << std::endl;
    }else{
        std::cout << "FUCK." << std::endl;
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