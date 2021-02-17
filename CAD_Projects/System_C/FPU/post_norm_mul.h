#ifndef POST_NORM_MUL_H_INCLUDED
#define POST_NORM_MUL_H_INCLUDED

#include "systemc.h"

class POST_NORM_MUL:
public sc_module{
    
    public:
    
    // ports: inputs
    sc_in< bool >           clk_i;
    sc_in< sc_uint<32> >    opa_i;
    sc_in< sc_uint<32> >    opb_i;
    sc_in< sc_uint<10> >    exp_10_i;
    sc_in< sc_uint<48> >    fract_48_i;
    sc_in< sc_uint<1> >     sign_i;
    sc_in< sc_uint<2> >     rmode_i;
    
    // ports: output
    sc_out< sc_uint<32> >   output_o;
    sc_out< sc_uint<1> >    ine_o;
    
    // internal signal data
    sc_uint<8>       s_expa, s_expb;
    sc_uint<10>      s_exp_10_i;
    sc_uint<48>      s_fract_48_i;
    sc_uint<1>       s_sign_i;
    sc_uint<32>      s_output_o;
    sc_uint<1>       s_ine_o, s_overflow;
    sc_uint<32>      s_opa_i, s_opb_i;
    sc_int<2>        s_rmode_i;
    
    sc_uint<6>       s_zeros;
    sc_uint<1>       s_carry;
    sc_uint<6>       s_shr2, shl2;
    sc_uint<9>       s_expo1, s_expo2b;
    sc_uint<10>      s_expa_10a, s_exp_10b;
    sc_uint<48>      s_fract2a;         
    
    sc_uint<1>       s_sticky, s_guard, s_round;
    sc_uint<1>       s_roundup;
    sc_uint<25>      s_frac_rnd, d_frac3;
    sc_uint<1>       s_shr3;
    sc_uint<6>       s_r_zeros;
    sc_uint<1>       s_lost;
    sc_uint<1>       s_op_0;
    sc_uint<9>       s_expo3;
    
    sc_uint<1>       s_infa, s_infb;
    sc_uint<1>       s_nan_in, s_nan_op, s_nan_a, s_nan_b;
    
    void post_norm_mul (void);
    
    // Module Constructor
    SC_HAS_PROCESS(POST_NORM_MUL);
    POST_NORM_MUL(sc_module_name name):
    sc_module(name){
        
        SC_THREAD(post_norm_mul);
        sensitive << clk_i.neg();
        
    }
    
};

#endif
