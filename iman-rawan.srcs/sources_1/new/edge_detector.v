//`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////////

//module rising_edge(input clk, level, rst, output reg tick);
//reg [1:0] state, next_state;
//parameter [1:0] zero=2'b00, edg=2'b01, one=2'b10;

//always @ (*) begin

//tick = 1'b0;
//case(state)
//    zero: begin
//      //  tick = 1'b0;
//        if (level) next_state=edg;
//            else next_state=state;
//    end
//    edg: begin
//        tick = 1'b1;  // output 
//        if (level) next_state=one;
//            else next_state=zero;
//    end
//    one: begin
//    //   tick = 1'b0;
//        if (level) next_state=one;
//            else next_state=zero;
//     end
     
//endcase  

//end

//always @ (posedge clk or negedge rst) begin
//if(!rst)
//state <= zero;
//else
//state <= next_state;
//end

//endmodule