#ifndef POST_NORM_ADDSUB_H_INCLUDED
#define POST_NORM_ADDSUB_H_INCLUDED

#include "systemc.h"

class POST_NORM_ADDSUB:
public sc_module{
    
    public:
    
    // ports: inputs
    sc_in< bool >        clk_i;
    sc_in< sc_uint<32> > opa_i;
    sc_in< sc_uint<32> > opb_i;
    sc_in< sc_uint<28> > fract_28_i;
    sc_in< sc_uint<8> >  exp_i;
    sc_in< sc_uint<1> >  sign_i;
    sc_in< sc_uint<1> >  fpu_op_i;
    sc_in< sc_uint<2> >  rmode_i;
    
    // ports: output
    sc_out< sc_uint<32> > output_o;
    sc_out< sc_uint<1> >  ine_o;
    
    // internal signal data
    sc_uint<32>        s_opa_i;
    sc_uint<32>        s_opb_i;
    sc_uint<28>        s_fract_28_i;
    sc_uint<8>         s_exp_i;
    sc_uint<1>         s_sign_i;
    sc_uint<1>         s_fpu_op_i;
    sc_uint<2>         s_rmode_i;
    sc_uint<32>        s_output_o;
    sc_uint<1>         s_ine_o;
    sc_uint<1>         s_overflow;
    
    sc_uint<6>         s_zeros = 0;
    sc_uint<6>         s_shr1;
    sc_uint<6>         s_shl1;
    sc_uint<1>         s_shr2;
    sc_uint<1>         s_carry;
    
    sc_uint<10>        s_exp10;
    sc_uint<9>         s_expo9_1;
    sc_uint<9>         s_expo9_2;
    sc_uint<9>         s_expo9_3;
    
    sc_uint<28>        s_fracto28_1;
    sc_uint<28>        s_fracto28_2;
    sc_uint<28>        s_fracto28_rnd;
    
    sc_uint<1>         s_roundup;
    sc_uint<1>         s_sticky;
    
    sc_uint<1>         s_zero_fract;
    sc_uint<1>         s_lost;
    sc_uint<1>         s_infa;
    sc_uint<1>         s_infb;
    sc_uint<1>         s_nan_in;
    sc_uint<1>         s_nan_op;
    sc_uint<1>         s_nan_a;
    sc_uint<1>         s_nan_b;
    sc_uint<1>         s_nan_sign;
    
    sc_uint<10>        s_exp10_i;
    sc_uint<10>        s_carry10;
    sc_uint<10>        s_zeros10;
    
    void post_norm_addsub(void);
    
    // Module Constructor
    SC_HAS_PROCESS(POST_NORM_ADDSUB);
    POST_NORM_ADDSUB(sc_module_name name):
    sc_module(name){
        
        SC_THREAD(post_norm_addsub);
        sensitive << clk_i.neg();
        
    }
    
};

#endif
