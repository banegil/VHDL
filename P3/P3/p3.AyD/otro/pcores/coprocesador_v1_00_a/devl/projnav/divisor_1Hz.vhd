----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    22:56:59 11/15/2020 
-- Design Name: 
-- Module Name:    divisor_1Hz - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
USE IEEE.std_logic_unsigned.ALL;

entity divisor_1Hz is
    port (
        rst: in STD_LOGIC;
        clk_in: in STD_LOGIC;
        clk_out: out STD_LOGIC
    );
end divisor_1Hz;

architecture divisor1_arch of divisor_1Hz is
 SIGNAL cuenta: std_logic_vector(26 downto 0);
  SIGNAL clk, clk_aux: std_logic;
  
  begin

 
clk <= clk_in;
clk_out<=clk_aux;
  contador:
  PROCESS( rst, clk )
  BEGIN
    IF (rst='1') THEN
      cuenta<= (OTHERS=>'0');
    ELSIF(clk'EVENT AND clk='1') THEN
      IF (cuenta="101111101011110000100000000") THEN
      	clk_aux <= not clk_aux;
        cuenta<= (OTHERS=>'0');
      ELSE
        cuenta <= cuenta+'1';
      END IF;
    END IF;
  END PROCESS contador;

end divisor1_arch;

