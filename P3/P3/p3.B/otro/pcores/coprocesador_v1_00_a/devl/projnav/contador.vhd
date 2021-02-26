----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    23:01:00 11/15/2020 
-- Design Name: 
-- Module Name:    contador - Behavioral 
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
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    01:54:41 10/18/2020 
-- Design Name: 
-- Module Name:    contador - Behavioral 
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
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity contador is
       
  port (rst  : in  std_logic;          
        clk  : in  std_logic;        
        enable : in std_logic;
		  reg : in std_logic_vector(7 downto 0);
        cntr : out std_logic_vector(7 downto 0));
end contador;

architecture rtl of contador is
  signal cntr_reg : unsigned(7 downto 0);
begin

  cntr <= std_logic_vector(cntr_reg);

  p_cntr_reg : process(clk, rst, enable)
  begin
    if rst = '1' then
      cntr_reg <= (others => '0');
    elsif rising_edge(clk) and enable = '1' then
      if cntr_reg < unsigned(reg) then
        cntr_reg <= cntr_reg+1;
      else
        cntr_reg <= (others => '0');
      end if;
    end if;
  end process p_cntr_reg;

end rtl;



