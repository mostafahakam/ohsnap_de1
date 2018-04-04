module main(CLOCK_50, LEDR, KEY, SW, HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, GPIO_0);
	input CLOCK_50;
	input[2:0] KEY;
	input[9:0] SW;
	
	input[35:0] GPIO_0;
	
	output[9:0] LEDR;
	output[6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5;
	
	wire[7:0] hex0, hex1, hex2, hex3, hex4, hex5;
	wire CLOCK_1;
	
	assign LEDR[0] = GPIO_0[35];
	assign LEDR[1] = GPIO_0[34];
	
	wire[1:0] state_in;
	assign state_in[0] = GPIO_0[35];
	assign state_in[1] = GPIO_0[34];
	
	assign LEDR[9] = CLOCK_1;
	
	hex h0(hex0, HEX0);
	hex h1(hex1, HEX1);
	hex h2(hex2, HEX2);
	hex h3(hex3, HEX3);
	hex h4(hex4, HEX4);
	hex h5(hex5, HEX5);
	
	clock1MHZ c0(CLOCK_50, CLOCK_1);
	
	state_machine s0(
						.clk_50(CLOCK_50),
						.clk_1(CLOCK_1),
						.in(state_in),
						.hex0(hex0),
						.hex1(hex1),
						.hex2(hex2),
						.hex3(hex3),
						.hex4(hex4),
						.hex5(hex5)
					);
						

endmodule


module hex(value, out);
	input[7:0] value;
	output reg[6:0] out;
	
	always@(*) begin
		case(value)
			0: out <= 7'b1111_111;
			1: out <= 7'b1111_001;
			2: out <= 7'b0100_100;
			3: out <= 7'b0110_000;
			4: out <= 7'b0011_001;
			5: out <= 7'b0010_010;
			6: out <= 7'b1000_110;	//C
			7: out <= 7'b0001_001;	//H
			8: out <= 7'b0000_110;	//E
			9: out <= 7'b0010_010;	//S
			10: out <= 7'b0001_110;	//F
			11: out <= 7'b1111_001;	//I
			12: out <= 7'b1000_111;	//L
			13: out <= 7'b0000_111;	//T
			14: out <= 7'b0101_111;	//R
			15: out <= 7'b0001_000; //A
			16: out <= 7'b0011_001; //Y
			17: out <= 7'b1000_000; //O
			18: out <= 7'b1001_000; //N
			19: out <= 7'b0001_100; //P
			default: out <= 7'b1111_111;
		endcase
	end
endmodule


module clock1MHZ(in, out);
	input in;
	output reg out = 0;
	
	reg[39:0] count = 0;
	
	always@(posedge in) begin
		if(count == 50000000) begin
			out = 1;
			count = 0;
		end else begin
			count = count + 1;
			out = 0;
		end
	end
endmodule


module state_machine(clk_50, clk_1, in, hex0, hex1, hex2, hex3, hex4, hex5);
	`define IDLE 	8'd0
	`define PHOTO0 	8'd1
	`define PHOTO1 	8'd2
	`define PHOTO2 	8'd3
	`define PHOTO3 	8'd4
	`define PHOTO4 	8'd5
	`define PHOTO5	8'd6
	`define SAY		8'd7
	`define CHEESE	8'd8
	`define FILTER 	8'd9
	`define DONE 	8'd10
	`define TITLE0	8'd11
	`define TITLE1	8'd12
	`define TITLE	8'd13
	`define POST	8'd14
	
	`define C 6
	`define H 7
	`define E 8
	`define S 9
	`define F 10
	`define I 11
	`define L 12
	`define T 13
	`define R 14
	`define A 15
	`define Y 16
	`define O 17
	`define N 18
	`define P 19
	
	input clk_50, clk_1;
	input[7:0] in;
	
	output reg[8:0] hex0, hex1, hex2, hex3, hex4, hex5;
	
	reg[7:0] state, next_state;
	
	always@(*) begin
		casez({state, in, clk_1})
			{8'dz,  8'd2, 1'dz}:		next_state <= `FILTER;
			{`TITLE,  8'd0, 1'dz}:		next_state <= `TITLE0;
			{`TITLE0, 8'd0, 1'd1}:		next_state <= `TITLE1;
			{`TITLE0, 8'd0, 1'dz}:		next_state <= `TITLE0;
			{`TITLE1, 8'd0, 1'd1}:		next_state <= `TITLE0;
			{`TITLE1, 8'd0, 1'dz}:		next_state <= `TITLE1;
			{8'dz,  8'd0, 1'dz}:		next_state <= `TITLE;	
			{`IDLE, 8'd1, 1'dz}: 		next_state <= `PHOTO0;
			{`PHOTO0, 8'd1, 1'd1}:		next_state <= `PHOTO1;
			{`PHOTO0, 8'dz, 1'dz}:		next_state <= `PHOTO0;			
			{`PHOTO1, 8'dz, 1'd1}:		next_state <= `PHOTO2;	
			{`PHOTO1, 8'dz, 1'dz}:		next_state <= `PHOTO1;	
			{`PHOTO2, 8'dz, 1'd1}:		next_state <= `PHOTO3;	
			{`PHOTO2, 8'dz, 1'dz}:		next_state <= `PHOTO2;
			{`PHOTO3, 8'dz, 1'd1}:		next_state <= `PHOTO4;	
			{`PHOTO3, 8'dz, 1'dz}:		next_state <= `PHOTO3;
			{`PHOTO4, 8'dz, 1'd1}:		next_state <= `PHOTO5;	
			{`PHOTO4, 8'dz, 1'dz}:		next_state <= `PHOTO4;		
			{`PHOTO5, 8'dz, 1'd1}:		next_state <= `SAY;	
			{`PHOTO5, 8'dz, 1'dz}:		next_state <= `PHOTO5;
			{`SAY, 8'dz, 1'd1}:			next_state <= `CHEESE;	
			{`SAY, 8'dz, 1'dz}:			next_state <= `SAY;			
			{`CHEESE, 8'dz, 1'd1}:		next_state <= `POST;
			{`CHEESE, 8'dz, 1'dz}:		next_state <= `CHEESE;
			{`POST, 8'd1, 1'dz}:		next_state <= `POST;
			default: 					next_state <= `IDLE;
		endcase
	end

	always@(posedge clk_50) begin
		state <= next_state;
	end
	
	always@(*) begin
		if(state == `PHOTO1) begin
			hex0 = 5;
			hex1 = 0;
			hex2 = 0;
			hex3 = 0;
			hex4 = 0;
			hex5 = 0;
		end else if(state == `PHOTO2) begin
			hex0 = 4;
			hex1 = 0;
			hex2 = 0;
			hex3 = 0;
			hex4 = 0;
			hex5 = 0;
		end else if(state == `PHOTO3) begin
			hex0 = 3;
			hex1 = 0;
			hex2 = 0;
			hex3 = 0;
			hex4 = 0;
			hex5 = 0;
		end else if(state == `PHOTO4) begin
			hex0 = 2;
			hex1 = 0;
			hex2 = 0;
			hex3 = 0;
			hex4 = 0;
			hex5 = 0;
		end else if(state == `PHOTO5) begin
			hex0 = 1;
			hex1 = 0;
			hex2 = 0;
			hex3 = 0;
			hex4 = 0;
			hex5 = 0;
		end else if(state == `SAY) begin
			hex0 = `Y;
			hex1 = `A;
			hex2 = `S;
			hex3 = 0;
			hex4 = 0;
			hex5 = 0;
		end else if(state == `CHEESE) begin
			hex0 = `E;
			hex1 = `S;
			hex2 = `E;
			hex3 = `E;
			hex4 = `H;
			hex5 = `C;
		end else if(state == `FILTER) begin
			hex0 = `R;
			hex1 = `E;
			hex2 = `T;
			hex3 = `L;
			hex4 = `I;
			hex5 = `F;
		end else if(state == `TITLE0) begin
			hex0 = 0;
			hex1 = 0;
			hex2 = `H;
			hex3 = `O;
			hex4 = 0;
			hex5 = 0;
		end else if(state == `TITLE1) begin
			hex0 = 0;
			hex1 = `P;
			hex2 = `A;
			hex3 = `N;
			hex4 = `S;
			hex5 = 0;
		end else begin
			hex0 = 0;
			hex1 = 0;
			hex2 = 0;
			hex3 = 0;
			hex4 = 0;
			hex5 = 0;
		end
	end
	
endmodule