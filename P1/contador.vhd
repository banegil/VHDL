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
  generic (k : integer := 9;           
           n : integer := 4);           

  port (rst  : in  std_logic;          
        clk  : in  std_logic;        
        enable : in std_logic;
        cntr : out std_logic_vector(n downto 0));
end contador;

architecture rtl of contador is
  signal cntr_reg : unsigned(n downto 0);
begin

  cntr <= std_logic_vector(cntr_reg);

  p_cntr_reg : process(clk, rst, enable)
  begin
    if rst = '0' then
      cntr_reg <= (others => '0');
    elsif rising_edge(clk) and enable = '1' then
      if cntr_reg < k then
        cntr_reg <= cntr_reg+1;
      else
        cntr_reg <= (others => '0');
      end if;
    end if;
  end process p_cntr_reg;

end rtl;

