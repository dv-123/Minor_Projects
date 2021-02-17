#include "post_norm_addsub.h"

// Processes

// post_norm_addsub
void POST_NORM_ADDSUB::post_norm_addsub(void){
    
    // reading the input signals
    wait();
    s_opa_i = opa_i.read();
    s_opb_i = opb_i.read();
    s_fract_28_i = fract_28_i.read();
    s_exp_i = exp_i.read();
    s_sign_i = sign_i.read();
    s_fpu_op_i = fpu_op_i.read();
    s_rmode_i = rmode_i.read();
    
    // processing the received data
    
    // Stage 1
    wait();
    
    // figure out the output exponent and how much the fraction has to be shifted right/left
    
    s_carry = s_fract_28_i[27];
    
    if(s_fract_28_i[27] == 0){
        for(int i = 0; i < 27; i++){
            if(s_fract_28_i[i] == 0){
                s_zeros = s_zeros + 1;
            }
        }
    }
    else{
        s_zeros = 0;
    }
    
    // negative flag & large flag & exp
    s_exp10_i.range(9,8) = "00";
    s_exp10_i.range(7,0) = s_exp_i;
    
    s_carry10.range(9,1) = "000000000";
    s_carry10[0] = s_carry;
    
    s_zeros10.range(9,6) = "0000";
    s_zeros10.range(5,0) = s_zeros;
    
    s_exp10 = s_exp10_i + s_carry10 + s_zeros10;
    
    // further processing and conditions
    if( (s_exp10[9] == 1) or (s_exp10 == 0) ){
        s_shr1 = 0;  // refrence to s_shr1 <= (others => '0') in vhdl
        if(s_exp_i.or_reduce() != 0){
            s_shl1 = s_exp_i.range(5,0) - 1;
        }
        else{
            s_shl1 = 0;
        }
        s_expo9_1 = 1;
    }
    else if(s_exp10[8] == 1){
        s_shr1 = 0;
        s_shl1 = 0;
        s_expo9_1 = "011111111";
    }
    else{
        s_shr1.range(5,1) = "00000";
        s_shr1[0] = s_carry;
        s_shl1 = s_zeros;
        s_expo9_1 = s_exp10.range(8,0); 
    }
    
    // stage 2
    wait();
    
    // shifting the fraction and rounding
    if( s_shr1 != 0){
        s_fracto28_1 = s_fract_28_i>>s_shr1;
    }
    else{
        s_fracto28_1 = s_fract_28_i<<s_shl1;
    }
    
    if(s_fracto28_1.range(27,26) == 0){
        s_expo9_2 = s_expo9_1 - 1;
    }
    else{
        s_expo9_2 = s_expo9_1;
    }
    
    //round
    // checking the last bit, before and after roght-shift
    if( (s_fracto28_1[0] == 1) or ((s_fract_28_i[0] and s_fract_28_i[27]) == 1)){
        s_sticky = 1;
    }
    else{
        s_sticky = 0;
    }
    
    if(s_rmode_i == 0){// round to nearest event
        s_roundup = s_fracto28_1[2] and ((s_fracto28_1[1] or s_sticky) or s_fracto28_1[3]);
    }
    else if (s_rmode_i == 2){ //  roundup
        s_roundup = (s_fracto28_1[2] or s_fracto28_1[1] or s_sticky) and (not s_sign_i);
    }
    else if (s_rmode_i == 3){ //round down
        s_roundup = (s_fracto28_1[2] or s_fracto28_1[1] or s_sticky) and (s_sign_i);
    }
    else{ // round to zero (truncate = no rounding)
        s_roundup = 0; 
    }
    
    if(s_roundup == 1){
        s_fracto28_rnd = s_fracto28_1 + "0000000000000000000000001000"; // or we can symply write + 8
    }
    else{
        s_fracto28_rnd = s_fracto28_1;
    }
    
    // stage 3
    wait();
    
    // right-shift after rounding (if necessary)
    s_shr2 = s_fracto28_rnd[27];
    
    if((s_shr2 == 1) && (s_expo9_2 != 256)){
        s_expo9_3 = s_expo9_2 + 1;
    }
    else{
        s_expo9_3 = s_expo9_2;
    }
    
    if( s_shr2 == 1){
        s_fracto28_2[27] = 0;
        s_fracto28_2.range(26,0) = s_fracto28_rnd.range(27,1);
    }
    else{
        s_fracto28_2 = s_fracto28_rnd;
    }
    
    // -------
    
    if( s_opa_i.range(30,23) == 256){
        s_infa = 1;
    }
    else{
        s_infa = 0;
    }
    
    if( s_opb_i.range(30,23) == 256){
        s_infb = 1;
    }
    else{
        s_infb = 0;
    }
    
    if( (s_infa == 1) and (s_opa_i.range(22,0).or_reduce() == 1)){
        s_nan_a = 1;
    }
    else{
        s_nan_a = 0;
    }
    
    if( (s_infb == 1) and (s_opb_i.range(22,0).or_reduce() == 1)){
        s_nan_b = 1;
    }
    else{
        s_nan_b = 0;
    }
    
    if( s_nan_a == 1 or s_nan_b == 1){
        s_nan_in = 1;
    }
    else{
        s_nan_in = 0;
    }
    
    if( ((s_infa and s_infb) == 1) and ((s_opa_i[31] xor (s_fpu_op_i xor s_opb_i[31])) == 1)){
        s_nan_op = 1;
    }
    else {
        s_nan_op = 0;
    }
    
    if( ((s_nan_a and s_nan_b) == 1)){
        s_nan_sign = s_sign_i;    
    }
    else if( s_nan_a == 1){
        s_nan_sign = s_opa_i[31];
    }
    else {
        s_nan_sign = s_opb_i[31];
    }
    
    // check if the result is inexact
    s_lost = (s_shr1[0] and s_fract_28_i[0]) or (s_shr2[0] and s_fracto28_rnd[0]) or s_fracto28_2.range(2,0).or_reduce();
    
    if( (s_expo9_3 == 256)  and (s_infa or s_infb == 0) ){
        s_overflow = 1;
    }
    else {
        s_overflow = 0;
    }
    
    if( ((s_lost or s_overflow) == 1) and (s_infa or s_infb) == 0){
        s_ine_o = 1;
    }
    else {
        s_ine_o = 0;
    }
    
    if( (s_zeros == 27) and (s_fract_28_i[27] == 0) ){
        s_zero_fract = 1;
    }
    else {
        s_zero_fract = 0;
    } // 1 if fraction result is zero
    
    // in vhdl code the following process is input sensitive
    wait();
    
    if( (s_nan_in or s_nan_op) == 1){
        s_output_o[31] = s_nan_sign;
        s_output_o.range(30,0) = "1111111110000000000000000000000"; // QNAN 
    }
    else if( ((s_infa or s_infb) == 1) or s_overflow == 1){
        s_output_o[31] = s_sign_i;
        s_output_o.range(30,0) = "1111111100000000000000000000000"; // INF
    }
    else if( s_zero_fract == 1 ){
        s_output_o[31] = s_sign_i;
        s_output_o.range(30,0) = "0000000000000000000000000000000"; // ZERO VECTOR 
    }
    else {
        s_output_o[31] = s_sign_i; // sign bit
        s_output_o.range(30,23) = s_expo9_3.range(7,0); // exp bits
        s_output_o.range(22,0) = s_fracto28_2.range(25,3); // mantisa / fraction bits
    }
    
    // writing the results to output-port
    wait();
    output_o.write(s_output_o);
    ine_o.write(s_ine_o);
 

}
