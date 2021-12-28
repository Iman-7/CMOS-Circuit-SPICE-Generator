`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////


module mult_div(input [7:0] bit_mc, input [7:0] bit_mr, input clk, input RxD, output [3:0] decoder_out, output [6:0] seg_leds, output [15:0] leds);

reg [7:0] mc = 8'b00000000, mr = 8'b00000000;
wire [15:0] p;
wire rst, start_mult, start_div;
wire [7:0] Q, R;

reg [1:0] state, next_state;
parameter [1:0] s0 = 2'b00, s1 = 2'b01, s2 = 2'b10;

reg [15:0] z;
wire [15:0] displayed;

//cases: 15, 3 .... 8, 2 

//wire [7:0] bit_mc, bit_mr;

//assign bit_mc[0] = 0; 
//assign bit_mc[1] = 0;
//assign bit_mc[2] = 1;
//assign bit_mc[3] = 1;
//assign bit_mc[4] = 0;
//assign bit_mc[5] = 0;
//assign bit_mc[6] = 0;
//assign bit_mc[7] = 1;

//assign bit_mr[0] = 1; 
//assign bit_mr[1] = 0;
//assign bit_mr[2] = 0;
//assign bit_mr[3] = 1;
//assign bit_mr[4] = 0;
//assign bit_mr[5] = 0;
//assign bit_mr[6] = 0;
//assign bit_mr[7] = 0;



UART #(8'b01101101) u1(.clk(clk), .RxD(RxD), .RxData(), .output_level(rst)); // ascii code for 'm'
UART #(8'b01101110) u2(.clk(clk),  .RxD(RxD), .RxData(), .output_level(start_mult)); // ascii code for 'n'
UART #(8'b01101111) u3(.clk(clk),  .RxD(RxD), .RxData(), .output_level(start_div)); // ascii code for 'o'


integer i;
always @(rst or start_mult or start_div) begin
if (rst)begin
    mc = 8'b0; mr =8'b0;
end

for(i=0; i <8; i = i+1) begin
    mc[i] = bit_mc[i];
    mr[i] = bit_mr[i];

end
end


assign leds[7:0] = bit_mc;
assign leds[15:8] = bit_mr;

multiplication m1(mc, mr, p);
division div (mr, mc, Q, R);

always @(state or RxD)begin

case(state)
s0: begin z = 0;
    if(!start_mult && !start_div) next_state = s0; //both start_div w start_mult zeros  
    else if(start_mult) next_state = s1;
    else if (start_div) next_state = s2;  
end
s1: begin z = p;
    if(start_div) next_state = s2; //start_mult one
    else if(!start_mult && !start_div) next_state = s1;
end
s2: begin z = Q;
     if(start_mult) next_state = s1; //start_div one
        else if(!start_mult && !start_div)next_state = s2; 
end

endcase
end

always @ (posedge clk, posedge rst) begin
if(rst)
state <= s0;
else
state <= next_state;
end

assign displayed = z;

seg7 se1 (clk, displayed, decoder_out, seg_leds);

endmodule
