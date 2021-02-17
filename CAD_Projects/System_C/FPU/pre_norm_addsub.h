#ifndef PRE_NORM_ADDSUB_H_INCLUDED
#define PRE_NORM_ADDSUB_H_INCLUDED

#include "systemc.h"


class PRE_NORM_ADDSUB:
public sc_module{
    
    public:
    
    // ports: input
    sc_in< bool >          clk_i;       // Clock input
    sc_in< sc_uint<32> >   opa_i;       // operator_a_input
    sc_in< sc_uint<32> >   opb_i;       // operator_b_input
    
    // ports: output
    sc_out< sc_uint<28> >  fracta_28_o; // carry(1) & hidden(1) & fraction (23) & guard(1) & round(1) & sticky(1)
    sc_out< sc_uint<28> >  fractb_28_o; // farction b 28 bit output 
    sc_out< sc_uint<8> >   exp_o;       // exponential output
    
    // internal signal data
    sc_uint<8>    s_exp_o;
    sc_uint<28>   s_fracta_28_o;
    sc_uint<28>   s_fractb_28_o;
    sc_uint<8>    s_expa;
    sc_uint<8>    s_expb;
    sc_uint<23>   s_fracta;
    sc_uint<23>   s_fractb;
    
    sc_uint<28>   s_fracta_28;
    sc_uint<28>   s_fractb_28;
    sc_uint<28>   s_fract_sm_28;
    sc_uint<28>   s_fract_shr_28;
    
    sc_uint<8>    s_exp_diff;
    sc_uint<6>    s_rzeros = 0;
    
    sc_uint<1>    s_expa_eq_expb;
    sc_uint<1>    s_expa_lt_expb;
    sc_uint<1>    s_fracta_1;
    sc_uint<1>    s_fractb_1;
    sc_uint<1>    s_op_dn;
    sc_uint<1>    s_opa_dn;
    sc_uint<1>    s_opb_dn;
    sc_uint<2>    s_max_diff;
    sc_uint<1>    s_max_exp;
    sc_uint<1>    s_sticky;
    
    sc_uint<32>   inp_a;
    sc_uint<32>   inp_b;
    
    void pre_norm_add_sub(void);
    
    // Module Constructor
    SC_HAS_PROCESS(PRE_NORM_ADDSUB);
    PRE_NORM_ADDSUB(sc_module_name name):
    sc_module(name){
        
        SC_THREAD(pre_norm_add_sub);
        sensitive << clk_i.neg();
        
    }
    
};


#endif
