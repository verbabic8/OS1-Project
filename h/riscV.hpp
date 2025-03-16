#pragma once

#include "../lib/hw.h"

class RiscV{
public:

    static void popSppSpie(); //nije sa steka nego iz registara, mora da bude non-inline

    static uint64 r_scause();
    static void w_scause(uint64 scause);
    static uint64 r_sepc();
    static void w_sepc(uint64 sepc);
    static uint64 r_stvec();
    static void w_stvec(uint64 stvec);
    static uint64 r_stval();
    static void w_stval(uint64 stval);

    enum BitMaskSip{
        SIP_SSIE = (1 << 1),
        SIP_STIE = (1 << 5),
        SIP_SEIE = (1 << 9),
    };

    // mask set register sip
    static void ms_sip(uint64 mask);

    // mask clear register sip
    static void mc_sip(uint64 mask);

    // read register sip
    static uint64 r_sip();

    // write register sip
    static void w_sip(uint64 sip);

    enum BitMaskSstatus{
        SSTATUS_SIE = (1UL << 1),
        SSTATUS_SPIE = (1UL << 5),
        SSTATUS_SPP = (1UL << 8),
    };

    // mask set register sstatus
    static void ms_sstatus(uint64 mask);

    // mask clear register sstatus
    static void mc_sstatus(uint64 mask);

    // read register sstatus
    static uint64 r_sstatus();

    // write register sstatus
    static void w_sstatus(uint64 sstatus);

    static void supervisorTrap();

    static void restorePriv();

private:
    static void handleSupervisorTrap();
};


inline uint64 RiscV::r_scause() {
    uint64 volatile scause;
    __asm__ volatile ("csrr %[scause], scause" : [scause] "=r" (scause));
    return scause;
}

inline void RiscV::w_scause(uint64 scause){
    __asm__ volatile ("csrw scause, %[scause]" : : [scause] "r"(scause));
}

inline uint64 RiscV::r_sepc(){
    uint64 volatile sepc;
    __asm__ volatile ("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
    return sepc;
}

inline void RiscV::w_sepc(uint64 sepc){
    __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));
}

inline uint64 RiscV::r_stvec(){
    uint64 volatile stvec;
    __asm__ volatile ("csrr %[stvec], stvec" : [stvec] "=r"(stvec));
    return stvec;
}

inline void RiscV::w_stvec(uint64 stvec){
    __asm__ volatile ("csrw stvec, %[stvec]" : : [stvec] "r"(stvec));
}

inline uint64 RiscV::r_stval(){
    uint64 volatile stval;
    __asm__ volatile ("csrr %[stval], stval" : [stval] "=r"(stval));
    return stval;
}

inline void RiscV::w_stval(uint64 stval){
    __asm__ volatile ("csrw stval, %[stval]" : : [stval] "r"(stval));
}

inline void RiscV::ms_sip(uint64 mask){
    __asm__ volatile ("csrs sip, %[mask]" : : [mask] "r"(mask));
}

inline void RiscV::mc_sip(uint64 mask){
    __asm__ volatile ("csrc sip, %[mask]" : : [mask] "r"(mask));
}

inline uint64 RiscV::r_sip(){
    uint64 volatile sip;
    __asm__ volatile ("csrr %[sip], sip" : [sip] "=r"(sip));
    return sip;
}

inline void RiscV::w_sip(uint64 sip){
    __asm__ volatile ("csrw sip, %[sip]" : : [sip] "r"(sip));
}

inline void RiscV::ms_sstatus(uint64 mask){
    __asm__ volatile ("csrs sstatus, %[mask]" : : [mask] "r"(mask));
}

inline void RiscV::mc_sstatus(uint64 mask){
    __asm__ volatile ("csrc sstatus, %[mask]" : : [mask] "r"(mask));
}

inline uint64 RiscV::r_sstatus(){
    uint64 volatile sstatus;
    __asm__ volatile ("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));
    return sstatus;
}

inline void RiscV::w_sstatus(uint64 sstatus){
    __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
}
