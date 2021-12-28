//`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////////

//module counter #(parameter n=3)(input clk, reset, Inc, UpDown, output reg [n:0]count);
//always @(posedge clk, posedge reset) begin

// if (reset == 1)
// count <= 0; // non blocking assignment 
// else if (UpDown == 0)
 
//    if (Inc == 0) 
//         count <= count + 1; // non blocking assignment
//     else 
//        count <= count +2;
// else if(UpDown == 1)
        
//       if (Inc == 0)
//        count <= count -1;
//       else
//        count <= count -2;

//end
//endmodule