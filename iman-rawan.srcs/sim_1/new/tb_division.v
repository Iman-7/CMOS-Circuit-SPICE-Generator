`timescale 1ns / 1ps

//////////////////////////////////////////////////////////////////////////////////

module tb_division();
reg [7:0] dr, dd;

wire [7:0] Q, R;

division uut(.dr(dr), .dd(dd), .Q(Q), .R(R));

initial begin
 
dd = 8'b00100111;
dr = 8'b00000011; //Ans: Q = 00001101 R = 0

#200
dd = 8'b10001100;
dr = 8'b00001001; //Ans: Q = 11110100 (244 in decimal) R = 11111000  

#200
dd = 8'b01110100; 
dr = 8'b00001001; //Ans: Q = 00001100  R = 00001000

#200
dd = 8'b10001100;
dr = 8'b11110111; //Ans: Q = 00001100  R = 11111000

end
endmodule
