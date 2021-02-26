-------------------------------------------------------------------------------
-- system1_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity system1_stub is
  port (
    plb_v46_0_SYS_Rst_pin : in std_logic;
    xps_uartlite_0_TX_pin : out std_logic;
    xps_uartlite_0_RX_pin : in std_logic;
    coprocesador_0_S_pin : out std_logic_vector(0 to 3);
    coprocesador_0_R_pin : in std_logic_vector(0 to 3);
    altavozumbador_0_sonidozumbido_pin : out std_logic;
    plb_v46_0_PLB_Clk_pin : in std_logic;
    lcd_0_rw_pin : out std_logic;
    lcd_0_rs_pin : out std_logic;
    lcd_0_e_pin : out std_logic;
    lcd_0_lcd_data_pin : out std_logic_vector(0 to 7);
    coprocesador_0_code_infrared_pin : out std_logic
  );
end system1_stub;

architecture STRUCTURE of system1_stub is

  component system1 is
    port (
      plb_v46_0_SYS_Rst_pin : in std_logic;
      xps_uartlite_0_TX_pin : out std_logic;
      xps_uartlite_0_RX_pin : in std_logic;
      coprocesador_0_S_pin : out std_logic_vector(0 to 3);
      coprocesador_0_R_pin : in std_logic_vector(0 to 3);
      altavozumbador_0_sonidozumbido_pin : out std_logic;
      plb_v46_0_PLB_Clk_pin : in std_logic;
      lcd_0_rw_pin : out std_logic;
      lcd_0_rs_pin : out std_logic;
      lcd_0_e_pin : out std_logic;
      lcd_0_lcd_data_pin : out std_logic_vector(0 to 7);
      coprocesador_0_code_infrared_pin : out std_logic
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of system1 : component is "user_black_box";

begin

  system1_i : system1
    port map (
      plb_v46_0_SYS_Rst_pin => plb_v46_0_SYS_Rst_pin,
      xps_uartlite_0_TX_pin => xps_uartlite_0_TX_pin,
      xps_uartlite_0_RX_pin => xps_uartlite_0_RX_pin,
      coprocesador_0_S_pin => coprocesador_0_S_pin,
      coprocesador_0_R_pin => coprocesador_0_R_pin,
      altavozumbador_0_sonidozumbido_pin => altavozumbador_0_sonidozumbido_pin,
      plb_v46_0_PLB_Clk_pin => plb_v46_0_PLB_Clk_pin,
      lcd_0_rw_pin => lcd_0_rw_pin,
      lcd_0_rs_pin => lcd_0_rs_pin,
      lcd_0_e_pin => lcd_0_e_pin,
      lcd_0_lcd_data_pin => lcd_0_lcd_data_pin,
      coprocesador_0_code_infrared_pin => coprocesador_0_code_infrared_pin
    );

end architecture STRUCTURE;

