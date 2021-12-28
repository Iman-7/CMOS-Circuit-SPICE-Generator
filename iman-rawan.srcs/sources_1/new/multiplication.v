`timescale 1ns / 1ps

module multiplication(input [7:0] mc, [7:0] mr, output [15:0] p);

reg [15:0] w_mc;
reg [7:0] w_mr;

reg [7:0] mc_neg;
reg [7:0] mr_neg;
reg [15:0] p_neg;

wire [7:0] mc_2s;
wire [7:0] mr_2s;
wire [15:0] p_2s;

integer i;
reg [15:0] pro;

always @(*) begin

for (i = 0; i <= 7; i=i+1)
    mc_neg[i] = ~mc[i];
  
for (i = 0; i <= 7; i=i+1)
        mr_neg[i] = ~mr[i]; 
        
for (i = 0; i <= 15; i=i+1)
        p_neg[i] = ~pro[i];            

end


rca8 i1 (8'b0, mc_neg, 1,, mc_2s);
rca8 i2 (8'b0, mr_neg, 1,, mr_2s);

wire [7:0] B; //mr
wire [7:0] A; //mc

mux2x1 m2(mc, mc_2s, mc[7], A);
mux2x1 m3(mr, mr_2s, mr[7], B);


always @(*)begin
pro =0; 
w_mc [15:8] = 0; 
w_mc [7:0] = A;
w_mr = B;

for (i=0; i<8; i = i+1) begin
if(w_mr[0])
pro = pro +w_mc;

w_mc=  w_mc << 1'b1; // shift left multiplicand
w_mr = w_mr >> 1'b1; // shift right multiplier

end
end

rca16 i3 (8'b0, p_neg, p_2s);
mux2x1 m1(pro, p_2s, mc[7]^mr[7], p);

endmodule
