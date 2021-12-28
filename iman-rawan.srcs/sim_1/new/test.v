module test();
reg [7:0] mc, mr;

wire [15:0] p;

multiplication uut( .mc(mc),  .mr(mr),  .p(p));


initial begin 

mr = 8'b01101010; 
mc = 8'b01001100; 

#100

mr = 8'b01101010;
mc = 8'b10110100; //-8056  0010000010001000

#100 

mr = 8'b10010110;
mc = 8'b10110100;
end
endmodule