#include "pre_norm_addsub.h"

// Processes

// pre_norm_addsub
void PRE_NORM_ADDSUB::pre_norm_add_sub(void){
    
    // reading the input signals
    wait();
    inp_a = opa_i.read();
    inp_b = opb_i.read();
    
    // distributing the input signals and further processing
    wait();
    s_expa = inp_a.range(30,23);
    s_expb = inp_b.range(30,23);
    s_fracta = inp_a.range(22,0);
    s_fractb = inp_b.range(22,0);
    
    // setting internal signal variables the required conditions
    
    // condition 1
    if(s_expa == s_expb){
        s_expa_eq_expb = 1;
    }
    else{
        s_expa_eq_expb = 0;
    }
    
    // condition 2
    if(s_expa > s_expb){
        s_expa_lt_expb = 1;
    }
    else{
        s_expa_lt_expb = 0;
    }
    
    // '1' if fraction is not zero
    s_fracta_1 = s_fracta.or_reduce();
    s_fractb_1 = s_fractb.or_reduce();
    
    // opa or opb is denormalized
    s_opa_dn = not(s_expa.or_reduce());    //  can use xor also not by !
    s_opb_dn = not(s_expb.or_reduce());    //  can use xor also not by !
    s_op_dn = s_opa_dn or s_opb_dn;        //  can use ||
    
    // output the larger exponent
    // Note: check this condition, remove if-else if-else condition to simple if-else condition if not working properly
    s_max_exp = s_expa_lt_expb;
    if(s_max_exp == 0){
        s_exp_o = s_expb;
    }
    else if(s_max_exp == 1) {
        s_exp_o = s_expa;
    }
    else{
        s_exp_o = "11111111";
    }
    
    // convert to an easy to handle floating-point format
    
    // for s_fracta_28
    if(s_opa_dn == 0){
        s_fracta_28.range(27,26) = "01";
        s_fracta_28.range(25,3) = s_fracta;
        s_fracta_28.range(2,0) = "000";
    }
    else{
        s_fracta_28.range(27,26) = "00";
        s_fracta_28.range(25,3) = s_fracta;
        s_fracta_28.range(2,0) = "000";
    }
    
    // for s_fractb_28
    if(s_opb_dn == 0){
        s_fractb_28.range(27,26) = "01";
        s_fractb_28.range(25,3) = s_fractb;
        s_fractb_28.range(2,0) = "000";
    }
    else{
        s_fractb_28.range(27,26) = "00";
        s_fractb_28.range(25,3) = s_fractb;
        s_fractb_28.range(2,0) = "000";
    }
    
    // now setting the max difference
    s_max_diff[1] = s_expa_lt_expb;
    s_max_diff[0] = s_opa_dn xor s_opb_dn; // can use not/! ( a or b )
    
    //calculate howmany positions the fraction will be shifted
    // also can use the switch statements, if code not works properly 
    if(s_max_diff == 0){
        s_exp_diff = s_expb - s_expa;
    }
    else if(s_max_diff == 1){
        s_exp_diff = s_expb - (s_expa + 1);
    }
    else if(s_max_diff == 2){
        s_exp_diff = s_expa - s_expb;
    }
    else if(s_max_diff == 3){
        s_exp_diff = s_expa - (s_expb + 1);
    }
    else{
        s_exp_diff = "11110000";
    }
    
    // finding s_fract_sm_28
    if(s_expa_lt_expb == 0){
        s_fract_sm_28 = s_fracta_28;
    }
    else{
        s_fract_sm_28 = s_fractb_28;
    }
    
    // shifting-right the function if necessary
    s_fract_shr_28 = s_fract_sm_28>>s_exp_diff;
    
    // count the zeros from right to check if the result is inexact
    for(int i = 27; i>=0; i--){
        if(s_fract_sm_28[i] == 0){
            s_rzeros = s_rzeros + 1;
        }
    }
    
    // now specifying s_sticky
    //Note s_exp_diff is 8 bit and s_rzeros is 6 bits
    if(s_exp_diff > s_rzeros and s_fract_sm_28.or_reduce() == 1){
        s_sticky = 1;
    }
    else{
        s_sticky = 0;
    }
    
    // now finally specifying the final outputs
    
    // 1. s_fracta_28_o
    if(s_expa_lt_expb == 1){
        s_fracta_28_o = s_fracta_28;
    }
    else{
        s_fracta_28_o.range(27,1) = s_fract_shr_28.range(27,1);
        s_fracta_28_o[0] = (s_sticky or s_fract_shr_28[0]);
    }
    
    // 2. s_fractb_28_o
    if(s_expa_lt_expb == 0){
        s_fractb_28_o = s_fractb_28;
    }
    else{
        s_fractb_28_o.range(27,1) = s_fract_shr_28.range(27,1);
        s_fractb_28_o[0] = (s_sticky or s_fract_shr_28[0]);
    }
    
    // writing the results to output-port
    wait();
    exp_o.write(s_exp_o);
    fracta_28_o.write(s_fracta_28_o);
    fractb_28_o.write(s_fractb_28_o);
        
}
