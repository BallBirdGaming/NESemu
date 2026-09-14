#pragma once

#include "bus.hpp"

#include <cstdint>
#include <iostream>

// this is the cpu of the emulator it might not be feature complete but thats to be expected

constexpr uint8_t status_register_carry = 1 << 0;
constexpr uint8_t status_register_zero = 1 << 1;
constexpr uint8_t status_register_interrupt_disable = 1 << 2;
constexpr uint8_t status_register_decimal = 1 << 3;
constexpr uint8_t status_register_bflag = 1 << 4;
//constexpr uint8_t status_register_1 = 1 << 5;
constexpr uint8_t status_register_overflow = 1 << 6;
constexpr uint8_t status_register_negative = 1 << 7;

constexpr uint8_t bit0 = 1 << 0;
constexpr uint8_t bit1 = 1 << 1;
constexpr uint8_t bit2 = 1 << 2;
constexpr uint8_t bit3 = 1 << 3;
constexpr uint8_t bit4 = 1 << 4;
constexpr uint8_t bit5 = 1 << 5;
constexpr uint8_t bit6 = 1 << 6;
constexpr uint8_t bit7 = 1 << 7;

constexpr uint8_t NOP_instructions_delay = 1;
constexpr uint8_t transfer_instructions_delay = 1;
constexpr uint8_t clear_or_set_instruction_delay = 1;

constexpr uint8_t opcode_NOP = 0xea;

constexpr uint8_t opcode_CLC = 0x18;
constexpr uint8_t opcode_SEC = 0x38;

constexpr uint8_t opcode_CLD = 0xd8;
constexpr uint8_t opcode_SED = 0xf8;

class CPU{
private:

    BUS* bus;

    uint64_t CPU_cycle_count;

    uint8_t cycle_remaining;

    uint8_t accumulator;    // uhh magic
                            // works with ALU

    // index X and Y
    uint8_t X;
    uint8_t Y;

    uint16_t program_counter;   // basicly where the cpu is reading instructions it points somewhere in memory

    uint8_t stack_pointer;  // pointer to stack 0x0100-0x01FF

    uint8_t status_register;    // holds flags such as carry, zero, ...
public:

    CPU(BUS* _bus){
        bus = _bus;
        CPU_cycle_count = 0;
        cycle_remaining = 0;
    }

    void CPU_clock();

    void hard_reset();
    void soft_reset();

    void interpret_instruction(uint8_t instruction);

    // official instructions
    // i will leave some empty because more knowlage is needed

    void ADC();
    void AND();
    void ASL();
    void BCC();
    void BCS();
    void BEQ();
    void BIT();
    void BMI();
    void BNI();
    void BPL();
    void BRK();
    void BVC();
    void BVS();
    void CLC();
    void CLD();
    void CLI();
    void CLV();

    void CMP();
    void CPX();
    void CPY();

    void DEC();
    void DEX();
    void DEY();

    void EOR();

    void INC();
    void INX();
    void INY();

    void JMP();
    void JSR();

    void LDA();
    void LDX();
    void LDY();

    void LSR();

    void NOP();

    void ORA();
    void PHA();
    void PHP();
    void PLA();
    void PLP();
    void ROL();
    void ROR();
    void RTI();
    void RTS();
    void SBC();
    void SEC();
    void SED();
    void SEI();

    void STA();
    void STX();
    void STY();

    void TAX();
    void TAY();
    void TSX();
    void TXA();
    void TXS();
    void TYA();

    /*
        Test functions

        these functions are used to test stuff without modifying specific functions 
        needed to emulate the NES corectly
    */

    void show_cyclecount();

};