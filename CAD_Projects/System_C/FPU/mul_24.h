#ifndef MUL_24_H_INCLUDED
#define MUL_24_H_INCLUDED

#include "systemc.h"

class MUL_24:
public sc_module{
    
    public:
    
    // ports: inputs
    sc_in< bool >             clk_i;     //
    sc_in< sc_uint<24> >      fracta_i;  //
    sc_in< sc_uint<24> >      fractb_i;  //
    sc_in< sc_uint<1> >       signa_i;   //
    sc_in< sc_uint<1> >       signb_i;   //
    sc_in< sc_uint<1> >       start_i;   //
    
    // ports: output
    sc_out< sc_uint<48> >     fract_o;   //
    sc_out< sc_uint<1> >      sign_o;    //
    sc_out< sc_uint<1> >      ready_o;   //     
    
    // internal signal data
    sc_uint<24>         s_fracta_i;
    sc_uint<24>         s_fractb_i;
    sc_uint<1>          s_signa_i;
    sc_uint<1>          s_signb_i;
    sc_uint<1>          s_sign_o;
    sc_uint<48>         s_fract_o;
    sc_uint<1>          s_start_i;
    sc_uint<1>          s_ready_o;
    
    sc_uint<12>         a_h, a_l, b_h, b_l;
    sc_uint<6>          a_h_h, a_h_l, b_h_h, b_h_l, a_l_h, a_l_l, b_l_h, b_l_l;
    
    sc_uint<6>          op_6[8];
    sc_uint<6>          prod_6[4][8]; // prod
    
    sc_uint<48>         prod_48[5]; //prod_a_b
    sc_uint<24>         sum_24[4]; // sum
    
    sc_uint<24>         a[4];
    sc_uint<24>         prod_24[4][4]; // prod2
    
    sc_uint<6>          prod = prod_6; // this can also be defined using pointers
    sc_uint<48>         prod_a_b = prod_48; // this can also be defined using pointers
    sc_uint<24>         sum = sum_24; // this can also be defined using pointers
    
    sc_int<4>           count = 0;   // ??? for --> signal count : integer range 0 to 4
    
    // type t_state is (waiting, busy) --?
    sc_lv<1>            t_state;
    // s_state : t_state;
    sc_lv<1>            s_state = t_state;
    
    sc_uint<24>         prod2 = prod_24;
    
    void mul_24(void);
    
    // Module Constructor
    SC_HAS_PROCESS(MUL_24);
    MUL_24(sc_module_name name):
    sc_module(name){
        
        SC_THREAD(mul_24);
        sensitive << clk_i.neg();
        
    }
    
};

#endif
