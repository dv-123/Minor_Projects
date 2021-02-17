#include "pre_norm_div.h"
// Processes

void PRE_NORM_DIV::pre_norm_div(void){
while(true){    
    // reading the input signals
    wait();
    s_opa_i = opa_i.read();
    s_opb_i = opb_i.read();
    s_fracta = s_opa_i.range(22,0);
    s_fractb = s_opb_i.range(22,0);
    dvdnd_50_o = s_dvdnd_50_o.read(); 
    dvsor_27_o = s_dvsor_27_o.read();
  s_expa =s_opa_i .range(30,23);
    s_expb =s_opb_is_opa_i .range(30,23);
    wait();
  
  	s_opa_dn = not (s_expa.or_reduce());
	s_opb_dn = not (s_expb.or_reduce());
  
  	s_fracta_24 = (not s_opa_dn) & s_fracta;
	s_fractb_24 = (not s_opb_dn) & s_fractb;
  
    //counting leading zeros
  
      for(int i = 23; i>=0; i--){
        if(s_fracta_24[i] == 0){
            s_dvd_zeros = s_dvd_zeros + 1;
        }
    }

  
      for(int j = 23; j>=0; j--){
        if(s_fractb_24[j] == 0){
            s_div_zeros = s_div_zeros + 1;
        }
    }
    
  
   // left-shift the dividend and divisor
   for(int j = s_dvd_zeros; j>0; j--){
              s_fracta_24<<1 ;
    }
   s_dvdnd_50_o= & "00000000000000000000000000";
  
    
  for(int j = s_did_zeros; j>0; j--){
              s_fractb_24<<1 ;
    }
  
  s_dvsor_27_o = "000" & s_fractb_24 ;
  
  // pre-calculate exponent
			s_expa_in = ("00"&s_expa) + ("000000000"&s_opa_dn);
			s_expb_in = ("00"&s_expb) + ("000000000"&s_opb_dn);	
			s_exp_10_o = s_expa_in - s_expb_in + "0001111111" -("0000"&s_dvd_zeros) + ("0000"&s_div_zeros);
  
  
   // writing the results to output-port
    wait();
    dvdnd_50_o.write(s_dvdnd_50_o);
    dvsor_27_o.write(s_dvsor_27_o);
    exp_10_o.write(s_exp_10_o);
 }   
}
