#ifndef ADDSUB_28_H_INCLUDED
#define ADDSUB_28_H_INCLUDED

#include "systemc.h"


class ADDSUB_28:
public sc_module{
    
    public:
    
    // ports: input
    sc_in< bool >          clk_i;    // Clock input
    sc_in< sc_uint<1> >    fpu_op_i; //
    sc_in< sc_uint<28> >   fracta_i; // fraction a as input
    sc_in< sc_uint<28> >   fractb_i; // fraction b as input
    sc_in< sc_uint<1> >    signa_i;  //
    sc_in< sc_uint<1> >    signb_i;  //
    
    // ports: output
    sc_out< sc_uint<28> >  fract_o; //
    sc_out< sc_uint<1> >   sign_o;  //
    
    void addsub_28(void);
    
    // internal signal data
    sc_uint<28>        s_fracta_i;
    sc_uint<28>        s_fractb_i;
    sc_uint<28>        s_fract_o;
    
    sc_uint<1>         s_signa_i;
    sc_uint<1>         s_signb_i;
    sc_uint<1>         s_sign_o;
    
    sc_uint<1>         s_fpu_op_i;
    sc_uint<1>         fracta_lt_fractb;
    sc_uint<1>         s_addop;
    
    sc_uint<28>        zero_vector_28 = 0;
        
    // Module Constructor
    SC_HAS_PROCESS(ADDSUB_28);
    ADDSUB_28(sc_module_name name):
    sc_module(name){
        
        SC_THREAD(addsub_28);
        sensitive << clk_i.neg();
        
    }
    
};

#endif
