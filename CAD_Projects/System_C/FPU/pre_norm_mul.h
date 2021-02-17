#ifndef PRE_NORM_MUL_H_INCLUDED
#define PRE_NORM_MUL_H_INCLUDED

#include "systemc.h"

class PRE_NORM_MUL:
public sc_module{
    
    public:
    
    // ports: inputs
    sc_in< bool >           clk_i; //
    sc_in< sc_uint<32> >    opa_i; //
    sc_in< sc_uint<32> >    opb_i; //
    
    // ports: output
    sc_out< sc_uint<10> >   exp_10_o; //
    sc_out< sc_uint<24> >   fracta_24_o; //
    sc_out< sc_uint<24> >   fractb_24_o; //
    
    // internal signal data
    sc_uint<8>          s_expa;
    sc_uint<8>          s_expb;
    sc_uint<23>         s_fracta;
    sc_uint<23>         s_fractb;
    sc_uint<10>         s_expa_in;
    sc_uint<10>         s_expb_in;
    sc_uint<10>         s_exp_10_o;
    sc_uint<24>         s_fracta_24_o;
    sc_uint<24>         s_fractb_24_o;
    
    sc_uint<10>         s_expa_10;
    sc_uint<10>         s_opa_dn_10;
    sc_uint<10>         s_expb_10;
    sc_uint<10>         s_opb_dn_10;
    
    sc_uint<1>          s_opa_dn;
    sc_uint<1>          s_opb_dn;
    
    sc_uint<32>         inp_a;
    sc_uint<32>         inp_b;
    
    void pre_norm_mul(void);
    
    // Module Constructor
    SC_HAS_PROCESS(PRE_NORM_MUL);
    PRE_NORM_MUL(sc_module_name name):
    sc_module(name){
        
        SC_THREAD(pre_norm_mul);
        sensitive << clk_i.neg();
        
    }
    
};

#endif
