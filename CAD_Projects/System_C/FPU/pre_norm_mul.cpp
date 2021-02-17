#include "pre_norm_mul.h"

// Processes

// pre_norm_mul
void PRE_NORM_MUL::pre_norm_mul(void){
    
    // reading the input signals
    wait();
    inp_a = opa_i.read();
    inp_b = opb_i.read();
    
    s_expa = inp_a.range(30,23);
    s_axpb = inp_b.range(30,23);
    s_fracta = inp_a.range(22,0);
    s_fractb = inp_b.range(22,0);
    
    // opa or opb is denormalized
    s_opa_dn = not(s_expa.or_reduce());
    s_opb_dn = not(s_expb.or_reduce());
    
    s_fracta_24_o[23] = not(s_opa_dn);
    s_fracta_24_o.range(22,0) = s_fracta;
    
    s_fractb_24_o[23] = not(s_opb_dn);
    s_fractb_24_o.range(22,0) = s_fractb;
    
    s_expa_10.range(9,8) = "00";
    s_expa_10.range(7,0) = s_expa;
    s_expb_10.range(9,8) = "00";
    s_expb_10.range(7,0) = s_expb;
    
    s_opa_dn_10.range(9,1) = "000000000";
    s_opa_dn_10[0] = s_opa_dn;
    s_opb_dn_10.range(9,1) = "000000000";
    s_opb_db_10[0] = s_opb_dn;
    
    s_expa_in = s_expa_10 + s_opa_dn_10;
    s_expb_in = s_expb_10 + s_opb_dn_10;
    
    s_exp_10_o = s_expa_in + s_expb_in - "0001111111";
    
    // writing the results to output-port
    wait();
    fracta_24_o.write(s_fracta_24_o);
    fractb_24_o.write(s_fractb_24_o);
    exp_10_o.write(s_exp_10_o);
    
}
