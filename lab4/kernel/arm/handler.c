/*
 * handler.c: install and restore handler routines
 *
 * Author:  Huacong Cai <hcai@andrew.cmu.edu>
 *          Qingyu Tong <qtong@andrew.cmu.edu>
 * Date:    2014-11-08
 */

#include <types.h>
#include <exports.h>

#define LDR_OFFSET 0x00000FFF
#define LDR_INSTRCTION 0xFFFFF000
#define LDR_UBIT 0x00800000

#define LDR_PC_PLUS 0xE59FF000
#define LDR_PC_MINUS 0xE51FF000
#define LDR_PC_MINUS_FOUR 0xE51FF004

/*
 * ret 0 success
 *     0x0badc0de instruction in vec_address is unrecognized
 */
unsigned install_handler(uint32_t vec_address, uint32_t *new_address, uint32_t **handler_location,
                     uint32_t *instruction1, uint32_t *instruction2)
{
    uint32_t vec_instruction;
    uint32_t offset;
    uint32_t instruction;
    uint32_t *jumptable;
    
    //verify if given vec_address is valid
    vec_instruction = *((uint32_t *)vec_address);
    offset = vec_instruction & LDR_OFFSET;
    instruction = vec_instruction & LDR_INSTRCTION;
    
    if ((instruction != LDR_PC_PLUS) &&
        (instruction != LDR_PC_MINUS)) //LDR pc, [pc, +/-]
    {
        puts("The instruction in vec_address is unrecognized\n");
        return 0x0badc0de;
    }
    
    jumptable = (unsigned*)(offset + vec_address + 0x08);
    *handler_location = (unsigned*)(*jumptable);

    //Save system's handler instruction
    *instruction1 = *(*handler_location);
    *instruction2 = *((*handler_location) + 1);
    
    //Hijacking SWI handler
    *(*handler_location) = LDR_PC_MINUS_FOUR; //LDR pc, [pc, #-4]
    *((*handler_location) + 1) = (uint32_t)new_address;
    
    return 0;
}

void restore_handler(uint32_t *handler_location, uint32_t instruction1, uint32_t instruction2)
{
    //Restore system's SWI handler
    *handler_location = instruction1;
    *(handler_location + 1) = instruction2;
}
