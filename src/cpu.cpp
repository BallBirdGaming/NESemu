#include "cpu.hpp"

void CPU::hard_reset(){
    accumulator = 0;
    X = 0;
    Y = 0;

    program_counter = static_cast<uint16_t>(bus->read(0xfffd) << 8) | bus->read(0xfffc);

    stack_pointer = 0xfd;

    status_register &= (status_register_bflag | bit5);
    status_register |= status_register_interrupt_disable;

    std::cout << "PC: " << program_counter << std::endl; 
}

void CPU::soft_reset(){
    program_counter = static_cast<uint16_t>(bus->read(0xfffd) << 8) | bus->read(0xfffc);

    stack_pointer -= 3;

    status_register |= status_register_interrupt_disable;

    std::cout << "PC: " << program_counter << std::endl; 
}

/*
    CPU clock function

*/

void CPU::CPU_clock(){
    if(cycle_remaining == 0){
        uint8_t instruction = bus->read(program_counter++);
        interpret_instruction(instruction);
    }

    cycle_remaining--;
    
    CPU_cycle_count++;
}



/*

    This function interprets bytes as instructions for the cpu to carry out it will adjust the pc and cycle_remaining acordingly

*/

void CPU::interpret_instruction(uint8_t instruction){
    switch (instruction){
        case(opcode_NOP): // NOP instruction
            cycle_remaining = NOP_instructions_delay;
            NOP();
            break;


        case(opcode_CLC):
            cycle_remaining = clear_or_set_instruction_delay;
            CLC();
            break;

        case(opcode_SEC):
            cycle_remaining = clear_or_set_instruction_delay;
            SEC();
            break;

        case(opcode_CLD):
            cycle_remaining = clear_or_set_instruction_delay;
            CLD();
            break;

        case(opcode_SED):
            cycle_remaining = clear_or_set_instruction_delay;
            SED();
            break;
    

        default:
            std::cout << "Illegal instruction can not execute. instruction: " << static_cast<int>(instruction) << std::endl;
            break;
    }
}



/*
    Instructions    

    Note:
        there might be some ugly or unordered code ahead be aware of it!
*/

void CPU::NOP(){    // clears the carry flag c = 0
    return;
}


void CPU::CLC(){    // clears the carry flag c = 0
    status_register &= ~status_register_carry;
}

void CPU::SEC(){    // sets the carry flag c = 1
    status_register |= status_register_carry;
}


void CPU::CLD(){    // clears the decimal flag d = 0
    status_register &= ~status_register_decimal;
}

void CPU::SED(){    // sets the decimal flag d = 1
    status_register |= status_register_decimal;
}


/*
    THIS SECTION NEEDS 1 CYCLE DELAY
*/

void CPU::CLI(){    // clears interrupt disable i = 0
    status_register &= ~status_register_interrupt_disable;
}

void CPU::SEI(){    // sets interrupt disable i = 1
    status_register |= status_register_interrupt_disable;
}



void CPU::DEX(){    // decrement X
    X--;

    // set negative flag
    status_register = (status_register & ~status_register_negative) | (X & status_register_negative);

    // set zero flag
    status_register &= ~status_register_zero;
    if(X == 0) status_register |= status_register_zero;
}

void CPU::DEY(){    // decrement X
    Y--;

    // set negative flag
    status_register = (status_register & ~status_register_negative) | (X & status_register_negative);

    // set zero flag
    status_register &= ~status_register_zero;
    if(Y == 0) status_register |= status_register_zero;
}


void CPU::INX(){    // decrement X
    X++;

    // set negative flag
    status_register = (status_register & ~status_register_negative) | (X & status_register_negative);

    // set zero flag
    status_register &= ~status_register_zero;
    if(X == 0) status_register |= status_register_zero;
}

void CPU::INY(){    // decrement X
    Y++;

    // set negative flag
    status_register = (status_register & ~status_register_negative) | (Y & status_register_negative);

    // set zero flag
    status_register &= ~status_register_zero;
    if(Y == 0) status_register |= status_register_zero;
}

/*
    Transfer instructions
*/

void CPU::TAX(){    // sets X to accumulator
    X = accumulator;

    // set negative flag
    status_register = (status_register & ~status_register_negative) | (X & status_register_negative);

    // set zero flag
    status_register &= ~status_register_zero;
    if(X == 0) status_register |= status_register_zero;    
}

void CPU::TAY(){    // sets Y to accumulator
    Y = accumulator;

    // set negative flag
    status_register = (status_register & ~status_register_negative) | (Y & status_register_negative);

    // set zero flag
    status_register &= ~status_register_zero;
    if(Y == 0) status_register |= status_register_zero;    
}

void CPU::TSX(){    // sets X to stack pointer
    X = stack_pointer;

    // set negative flag
    status_register = (status_register & ~status_register_negative) | (X & status_register_negative);

    // set zero flag
    status_register &= ~status_register_zero;
    if(X == 0) status_register |= status_register_zero;    
}

void CPU::TXA(){    // sets X to accumulator
    X = accumulator;

    // set negative flag
    status_register = (status_register & ~status_register_negative) | (X & status_register_negative);

    // set zero flag
    status_register &= ~status_register_zero;
    if(X == 0) status_register |= status_register_zero;    
}

void CPU::TXS(){    // sets stack pointer to X 
    stack_pointer = X; 
}

void CPU::TYA(){    // sets accumulator to Y
    accumulator = Y;

    // set negative flag
    status_register = (status_register & ~status_register_negative) | (accumulator & status_register_negative);

    // set zero flag
    status_register &= ~status_register_zero;
    if(accumulator == 0) status_register |= status_register_zero;    
}

/*
    Test functions

    these functions are used to test stuff without modifying specific functions 
    needed to emulate the NES corectly
*/

void CPU::show_cyclecount(){
    std::cout << CPU_cycle_count << std::endl;
}