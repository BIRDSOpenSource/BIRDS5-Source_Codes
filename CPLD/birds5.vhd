library ieee;
library MACH;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity BIRDS5 is

port( 
	input: in std_logic_vector ( 50 downto 0 );
	output: out std_logic_vector ( 50 downto 0 );
	sel: in std_logic_vector ( 5 downto 0 ) );

end;

architecture BIRDS5 of BIRDS5 is
begin


	output(0) <= input(0);  -- CPLD(75)<=CPLD(1)  113<4     PINO MOSFET
	output(1) <= input(1);  -- CPLD(76)<=CPLD(2)  114<5     PINO FM_SEL
	output(2) <= input(2);  -- CPLD(77)<=CPLD(3)  115<6     PINO HVshutdown
	output(3) <= input(3);  -- CPLD(13)<=CPLD(4)  21 <7     MCAM-1 trigar
	output(4) <= input(4);  -- CPLD(14)<=CPLD(5)  22 <8     MCAM-1 MOSFET
	output(5) <= input(5);  -- CPLD(49)<=CPLD(6)  76 <9     MCAM-2 trigar
	output(6) <= input(6);  -- CPLD(50)<=CPLD(7)  77 <11    MCAM-2 MOSFET
	output(7) <= input(7);  -- CPLD(11)<=CPLD(87) 132 <15   ADCS_RX
	output(8) <= input(8);  -- CPLD(12)<=CPLD(96) 16 <143   ADCS MOSFET
	output(9) <= input(9);  -- CPLD(47)<=CPLD(A)  70 <17    S-F-1 MOSFET 
	output(10)<=input(10);  -- CPLD(48)<=CPLD(B)  71 <20    S-F-2 MOSFET
	output(11)<=input(11);  -- CPLD(63)<=CPLD(95) 95 <142   I-C$DLP MOSFET


	--sel(0) CPLD()
	--sel(1) CPLD()
	--sel(2) CPLD()

process (sel) begin
	if(sel(0)='0' and sel(1)='0' and sel(2)='0') then    --PINO/RAB
		output(12) <= input(12);  --CPLD(73)<=CPLD(81) 111<122  PINO<MB
		output(13) <= input(13);  --CPLD(82)<=CPLD(74) 123<112  MB  <PINO
		output(14) <= input(14);  --CPLD(21)<=CPLD(69) 30 <102  OBC <PINO
		output(15) <= input(15);  --CPLD(22)<=CPLD(71) 31 <104  OBC <PINO
		output(16) <= input(16);  --CPLD(70)<=CPLD(23) 103<32   PINO<OBC
		output(17) <= input(17);  --CPLD(24)<=CPLD(72) 33 <105  OBC <PINO

	elsif(sel(0)='1' and sel(1)='0' and sel(2)='0') then --I-C/RAB
		output(18) <= input(12);  --CPLD(61)<=CPLD(81) 93 <122  I-C <MB
		output(13) <= input(19);  --CPLD(82)<=CPLD(62) 123<94   MB  <I-C
		output(14) <= input(20);  --CPLD(21)<=CPLD(64) 30 <96   OBC <I-C
		output(15) <= input(21);  --CPLD(22)<=CPLD(65) 31 <97   OBC <I-C
		output(22) <= input(16);  --CPLD(66)<=CPLD(23) 98 <32   I-C <OBC
		output(17) <= input(23);  --CPLD(24)<=CPLD(67) 33 <100  OBC <I-C

	elsif(sel(0)='0' and sel(1)='1' and sel(2)='0') then    --MCAM-1/MB1
		output(24) <= input(24);  --CPLD(19)<=CPLD(84) 28 <125  MCAM-1<MB
		output(25) <= input(25);  --CPLD11(83)<=CPLD(20) 124<29   MB    <MCAM-1
		output(14) <= input(26);  --CPLD(21)<=CPLD(15) 30 <23   OBC   <MCAM-1
		output(15) <= input(27);  --CPLD(22)<=CPLD(16) 31 <24   OBC   <MCAM-1
		output(28) <= input(16);  --CPLD(17)<=CPLD(23) 25 <32   MCAM-1<OBC
		output(17) <= input(29);  --CPLD(24)<=CPLD(18) 33 <26   OBC   <MCAM-1

	elsif(sel(0)='1' and sel(1)='1' and sel(2)='0') then	  --ADCS/MB1
		output(30) <= input(24);  --CPLD(9)<=CPLD(84)  13 <125  ADCS<MB
		output(25) <= input(31);  --CPLD(83)<=CPLD(10) 124<14   MB  <ADCS

	elsif(sel(0)='0' and sel(1)='0' and sel(2)='1') then	  --MCAM-2/MB2
		output(32) <= input(32);  --CPLD(55)<=CPLD(88)  83<133  MCAM-2<MB
		output(33) <= input(33);  --CPLD(89)<=CPLD(56) 134<84   MB    <MCAM-2
		output(14) <= input(34);  --CPLD(21)<=CPLD(51) 30 <78   OBC   <MCAM-2
		output(15) <= input(35);  --CPLD(22)<=CPLD(52) 31 <79   OBC   <MCAM-2
		output(36) <= input(16);  --CPLD(53)<=CPLD(23) 80 <32   MCAM-2<OBC
		output(17) <= input(37);  --CPLD(24)<=CPLD(54) 33 <81   OBC   <MCAM-2
	
	elsif(sel(0)='1' and sel(1)='0' and sel(2)='1') then	  --S-F/MB2
		output(38) <= input(32);  --CPLD(46)<=CPLD(88) 69 <133  S-F<MB
		output(33) <= input(39);  --CPLD(89)<=CPLD(45) 134<68   MB <S-F	

	end if;

end process;


end BIRDS5;

