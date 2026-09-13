#pragma once

#include <cstdint>
#include <string>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>

constexpr uint32_t iNES_prgrom_size_unit = 0x4000;
constexpr uint32_t iNES_chrrom_size_unit = 0x2000;

class BUS{
private:

    std::array<uint8_t, 0xffff + 1> memory;

public:
    void hard_reset();

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);

    bool load_chartridge(const std::string &file);

    /*
        Test functions

        these functions are used to test stuff without modifying specific functions 
        needed to emulate the NES corectly
    */
    
    void fill_NOP();
};