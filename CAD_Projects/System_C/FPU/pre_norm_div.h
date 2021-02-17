#ifndef PRE_NORM_DIV_H_INCLUDED
#define PRE_NORM_DIV_H_INCLUDED

#include "systemc.h"


class PRE_NORM_DIV:
public sc_module{
    
    public:
       // ports: input
    sc_in< bool >          clk_i;    // Clock input
    sc_in< sc_bv<32> >    opa_i; //
    sc_in< sc_bv<32> >   opb_i; // fraction a as input

    
    // ports: output
    sc_out< sc_bv<10> >  exp_10_o; //
    sc_out< sc_bv<50> >  dvdnd_50_o;  //
    sc_out< sc_bv<27> >  dvsor_27_o;  //  
  
    
     void pre_norm_div(void);
    
    // internal signal data
    sc_uint<8>        s_expa;
    sc_uint<8>        s_expb;
    sc_uint<23>        s_fracta;
    sc_uint<23>        s_fractb;
    sc_uint<50>        s_dvdnd_50_o;
    sc_uint<27>        s_dvsor_27_o;
    sc_uint<6>        s_dvd_zeros;
    sc_uint<6>        s_div_zeros;
    sc_uint<10>        s_exp_10_o;
    sc_uint<10>        s_expa_in;
    sc_uint<10>        s_expb_in;
    sc_uint<24>        s_fracta_24;
    sc_uint<24>        s_fractb_24;
  sc_uint<32>        s_opa_i;
    sc_uint<32>        s_opb_i;
  
    sc_uint<1>         s_opa_dn;
    sc_uint<1>         s_opb_dn;
    

        
    // Module Constructor
    SC_HAS_PROCESS(PRE_NORM_DIV);
    PRE_NORM_DIV(sc_module_name name):
    sc_module(name){
        
        SC_THREAD(pre_norm_div);
        sensitive << clk_i.neg();
        
    }
    
};

#endif
