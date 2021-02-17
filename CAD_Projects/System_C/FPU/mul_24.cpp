#include "mul_24.h"


// Processes

// mul_24
void MUL_24::mul_24(void){
    
    // reading the input signals
    wait();
    s_fracta_i = fracta_i.read();
    s_fractb_i = fractb_i.read();
    s_signa_i = signa_i.read();
    s_signb_i = signb_i.read();
    s_start_i = start_i.read();
    
    // processing elements
    // conditions for receiving the data and handshake signals operations
    wait();
    if(s_start_i == 1){
        s_state = 'X'; // X -->  busy, Z --> waiting
        count = 0;
    }
    else if(count == 4 and s_state == 'X'){
        s_state = 'Z';
        s_ready_o = 1;
        count = 0;
    }
    else if(s_state == 'X'){
        count = count + 1;
        if(count == 5){
            count = 0;
        }
    }
    else{
        s_state = 'Z';
        s_ready_o = '0';
    }
    
    wait();
    
    s_sign_o = s_signa_i xor s_signb_i;
    
    // "000000000000"
    // A = a_h x 2^N + A_l, B = B_h x 2^N + B_l
    // A x B = A_hxB_h^2N + (A_h x B_l + A_lxB_h)2^N + A_lxB_l
    a_h = s_fracta_i.range(23,12);
    a_l = s_fracta_i.range(11,0);
    b_h = s_fractb_i.range(23, 12);
    b_l = s_fractb_i.range(11,0);
    
    a_h_h = a_h.range(11,6);
    a_h_l = a_h.range(5,0);
    b_h_h = b_h.range(11,6);
    b_h_l = b_h.range(5,0);
    
    a_l_h = a_l.range(11,6);
    a_l_l = a_l.range(5,0);
    b_l_h = b_l.range(11,6);
    b_l_l = b_l.range(5,0);
    
    prod[0][0] = a_h_h; prod[0][1] = b_h_h;
    prod[0][2] = a_h_h; prod[0][3] = b_h_l;
    prod[0][4] = a_h_l; prod[0][5] = b_h_h;
    prod[0][6] = a_h_l; prod[0][7] = b_h_l;
    
    prod[1][0] = a_h_h; prod[1][1] = b_l_h;
    prod[1][2] = a_h_h; prod[1][3] = b_l_l;
    prod[1][4] = a_h_l; prod[1][5] = b_l_h;
    prod[1][6] = a_h_l; prod[1][7] = b_l_l;
    
    prod[2][0] = a_l_h; prod[2][1] = b_h_h;
    prod[2][2] = a_l_h; prod[2][3] = b_h_l;
    prod[2][4] = a_l_l; prod[2][5] = b_h_h;
    prod[2][6] = a_l_l; prod[2][7] = b_h_l;
    
    prod[3][0] = a_l_h; prod[3][1] = b_l_h;
    prod[3][2] = a_l_h; prod[3][3] = b_l_l;
    prod[3][4] = a_l_l; prod[3][5] = b_l_h;
    prod[3][6] = a_l_l; prod[3][7] = b_l_l;
    
    wait();
    if(count<4){
        prod2[count][0].range(0,11) = (prod[count][0] * prod[count][1]);
        prod2[count][0].range(12,23) = "000000000000";
        
        prod2[count][1].range(0,5) = "000000";
        prod2[count][1].range(6,17) = (prod[count][2] * prod[count][3]);
        prod2[count][1].range(18,23) = "000000";
        
        prod2[count][2].range(0,5) = "000000";
        prod2[count][2].range(6,17) = (prod[count][4] * prod[count][5]);
        prod2[count][2].range(18,23) = "000000";
        
        prod2[count][3].range(0,11) = "000000000000";
        prod2[count][3].range(12,23) = (prod[count][6] * prod[count][7]);
    }
    
    wait();
    if((count > 0)  and (s_state == 'X')){
        sum[count-1] = prod2[count-1][0] + prod2[count-1][1] + prod2[count-1][2] + prod3[count-1][3];
    }
    
    // last stage
    wait();
    prod_a_b[0].range(0,23) = sum[0];
    prod_a_b[0].range(24,47) = "000000000000000000000000";
    
    prod_a_b[1].range(0,11) = "000000000000";
    prod_a_b[1].range(12,35) = sum[1];
    prod_a_b[1].range(36,47) = "000000000000";
    
    prod_a_b[2].range(0,11) = "000000000000";
    prod_a_b[2].range(12,35) = sum[2];
    prod_a_b[2].range(36,47) = "000000000000";
    
    prod_a_b[0].range(0,23) = "000000000000000000000000";
    prod_a_b[0].range(24,47) = sum[3];
    
    
    prod_a_b[4] = prod_a_b[0] + prod_a_b[1] + prod_a_b[2] +prod_a_b[3];
    
    s_fract_o = prod_a_b[4];
    
    // writing the results to output-port
    wait();
    fract_o.write(s_fract_o);
    sign_o.write(s_sign_o);
    ready_o.write(s_ready_o);
}
