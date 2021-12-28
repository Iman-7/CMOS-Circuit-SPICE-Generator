//`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////////

module division(input [7:0] dr, dd, output [7:0] Q, R);

//dd/dr ... A/B dividend/divisor

reg [15:0] temp;
integer i;
reg [7:0] dd_neg;
reg [7:0] dr_neg;
reg [7:0] q_neg;
reg [7:0] r_neg;


wire [7:0] dd_2s;
wire [7:0] dr_2s;
wire [7:0] q_2s;
wire [7:0] r_2s;


wire [7:0] A, B;
reg [7:0] q;
reg [7:0] r;


always @(*) begin

for (i = 0; i <= 7; i=i+1)
    dd_neg[i] = ~dd[i];
  
for (i = 0; i <= 7; i=i+1)
        dr_neg[i] = ~dr[i]; 
        
for (i = 0; i <= 15; i=i+1)
        q_neg[i] = ~q[i];  
        
for (i = 0; i <= 7; i=i+1)
        r_neg[i] = ~r[i];                    
end


rca8 rca1 (8'b0, dd_neg, 1'b1,, dd_2s);
rca8 rca2 (8'b0, dr_neg, 1'b1,, dr_2s);
rca8 rca3 (8'b0, q_neg, 1'b1,, q_2s);
rca8 rca4 (8'b0, r_neg, 1'b1,, r_2s);

mux2x1 mu1(dd, dd_2s, dd[7], A);
mux2x1 mu2(dr, dr_2s, dr[7], B);

always @(*) begin
q = 0;
r = 0;
temp = {r,A}; //remainder + dividened 

for (i=7; i>=0; i = i-1) begin           
  temp = temp << 1'b1; //shift left  
    if (temp[15:8]>=B) begin
        temp[15:8] = temp[15:8]-B;
        q[i] = 1;
    end
    else
        q[i] =0;


end
r = temp[15:8];

end



mux2x1 mu3(q, q_2s, dd[7]^dr[7],Q);
mux2x1 mu4(r, r_2s, dd[7], R);

endmodule
