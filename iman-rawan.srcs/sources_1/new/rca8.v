`timescale 1ns / 1ps

//Q4
module FA(input a, b, cin, output co, sum);
assign sum = a^b^cin;
assign co = (b&cin) | (a&cin) | (a&b);

endmodule


module rca8 (input [7:0] a8, [7:0]b8, input cin, output co8, output [7:0] sum8);
//method 1
wire co8_1, co8_2, co8_3, co8_4, co8_5, co8_6, co8_7;
//wire co8;
FA inst1 (a8[0], b8[0], cin,co8_1, sum8[0]); //cin =1
FA inst2 (a8[1], b8[1], co8_1,co8_2, sum8[1]);
FA inst3 (a8[2], b8[2], co8_2,co8_3, sum8[2]);
FA inst4 (a8[3], b8[3], co8_3,co8_4, sum8[3]);
FA inst5 (a8[4], b8[4], co8_4,co8_5, sum8[4]);
FA inst6 (a8[5], b8[5], co8_5,co8_6, sum8[5]);
FA inst7 (a8[6], b8[6], co8_6,co8_7, sum8[6]);
FA inst8 (a8[7], b8[7], co8_7,co8, sum8[7]);
 
endmodule

module rca16 (input [15:0] a8, [15:0]b8, output [15:0] sum8);

wire co, co_useless;
rca8 r1 (a8[7:0], b8[7:0], 1, co, sum8[7:0]);
rca8 r2 (a8[15:8],b8[15:8], co, co_useless, sum8[15:8]);

endmodule

module mux2x1 (input [15:0] po, neg, input sel, output [15:0] p);

assign p = (sel)? neg: po;

endmodule