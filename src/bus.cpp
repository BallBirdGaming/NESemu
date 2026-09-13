#include "bus.hpp"

void BUS::hard_reset(){
    memory.fill(0);
}


uint8_t BUS::read(uint16_t address){
    return memory[address];
}

void BUS::write(uint16_t address, uint8_t value){

    if(address <= 0x1fff){  // some bs
        if(address >= 1800){
            for(uint8_t i = 0; i < 4; i++){
                memory[address - (i * 800)] = value;
            }
            return;
        }

        if(address >= 1000){
            for(uint8_t i = 0; i < 4; i++){
                memory[address + 800 - (i * 800)] = value;
            }
            return;
        }

        if(address >= 800){
            for(uint8_t i = 0; i < 4; i++){
                memory[address + 1600 - (i * 800)] = value;
            }
            return;
        }


        for(uint8_t i = 0; i < 4; i++){
            memory[address + 2400 - (i * 800)] = value;
        }
        return;
    }

    if(address >= 0x8000) return;


    memory[address] = value;
}

bool BUS::load_chartridge(const std::string &_file){
    if(!std::filesystem::exists(_file)) return false;

    std::ifstream file(_file);

    std::string NES;

    for(uint8_t i = 0; i < 3; i++) NES.push_back(file.get());
    
    if(NES == "NES" && file.get() == 0x1a){
        uint32_t prgrom_size = 0;
        uint32_t chrrom_size = 0;

        prgrom_size = static_cast<uint8_t>(file.get()) * iNES_prgrom_size_unit;
        chrrom_size = static_cast<uint8_t>(file.get()) * iNES_chrrom_size_unit;

        /*
            NOTE: i wont be fully reading the iNES header because im lazy 
                and i dont know what the rest of the bytes mean

                also i have to implement chrrom but ill get there when im done with cpu
        */

        for(int i = 0; i < 10; i++){    // posistion ourselfs to the begin of prgrom
            file.get();
        }
        
        for(uint32_t i = 0; i < prgrom_size; i++){
            memory[0x8000 + i] = static_cast<uint8_t>(file.get());
        }
        return true;
    }else{
        return false;
    }
}

/*
    Test functions

    these functions are used to test stuff without modifying specific functions 
    needed to emulate the NES corectly
*/

void BUS::fill_NOP(){
    memory.fill(0xea);
}