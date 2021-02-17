#include "post_norm_mul.h"


// Processes

// mul_24
void POST_NORM_MUL::post_norm_mul(void){
    
    // reading the input signals
    wait();
    s_opa_i = opa_i.read();
    s_opb_i = opb_i.read();
    s_expa = opa_i.read().range(30,23);
    s_expb = opb_i.read().range(30,23);
    s_exp_10_i = exp_10_i.read();
    s_fract_48_i = fract_48_i.read();
    s_sign_i = sign_i.read();
    s_rmode_i = rmode_i.read();
    
    // middle logics and functions 
    
    // to be made constructed ahaead
    
    // writing the results to output-port
    wait();
    optput_o.write(s_output_o);
    ine_o.write(s_ine_o);
}
