#include "addsub_28.h"
// Processes

// addsub_28
void ADDSUB_28::addsub_28(void){
while(true){    
    // reading the input signals
    wait();
    s_fracta_i = fracta_i.read();
    s_fractb_i = fractb_i.read();
    s_signa_i  = signa_i.read();
    s_signb_i  = signb_i.read();
    s_fpu_op_i = fpu_op_i.read(); 
    
    // processing the received signals
    wait();
    if(s_fracta_i > s_fractb_i){
        fracta_lt_fractb = 1;
    }
    else{
        fracta_lt_fractb = 0;
    }
    
    // checking if it is a subtarction or addition operation
    s_addop = ((s_signa_i xor s_signb_i) and not (s_fpu_op_i)) or (not((s_signa_i) xor (s_signb_i)) and (s_fpu_op_i));
    
    // add/subtract
    wait();
    // in vhdl code function given below is input sensitive isdtead of clock senstitive
    if( s_addop == 0){
       s_fract_o = s_fracta_i + s_fractb_i;
    }
    else{
        if( fracta_lt_fractb == 1){
            s_fract_o = s_fracta_i - s_fractb_i;
        }
        else{
            s_fract_o = s_fractb_i - s_fracta_i;
        }
    }
    
    // sign of result
    if( (s_fract_o == zero_vector_28) and ((s_signa_i and s_signb_i) == 0) ){
        s_sign_o = 0;
    }
    else{
        s_sign_o = ((not s_signa_i) and ((not fracta_lt_fractb) and (s_fpu_op_i xor s_signb_i)) or ((s_signa_i) and (fracta_lt_fractb or (s_fpu_op_i xor s_signb_i))));
    }
    
    // writing the results to output-port
    wait();
    fract_o.write(s_fract_o);
    sign_o.write(s_sign_o);
 }   
}
