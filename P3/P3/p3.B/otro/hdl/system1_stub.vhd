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
    microblaze_0_MB_RESET_pin : in std_logic;
    coprocesador_0_leds_pin : out std_logic_vector(0 to 7);
    plb_v46_0_PLB_Clk_pin : in std_logic;
    coprocesador_0_switches_pin : in std_logic_vector(0 to 3)
  );
end system1_stub;

architecture STRUCTURE of system1_stub is

  component system1 is
    port (
      plb_v46_0_SYS_Rst_pin : in std_logic;
      xps_uartlite_0_TX_pin : out std_logic;
      xps_uartlite_0_RX_pin : in std_logic;
      microblaze_0_MB_RESET_pin : in std_logic;
      coprocesador_0_leds_pin : out std_logic_vector(0 to 7);
      plb_v46_0_PLB_Clk_pin : in std_logic;
      coprocesador_0_switches_pin : in std_logic_vector(0 to 3)
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
      microblaze_0_MB_RESET_pin => microblaze_0_MB_RESET_pin,
      coprocesador_0_leds_pin => coprocesador_0_leds_pin,
      plb_v46_0_PLB_Clk_pin => plb_v46_0_PLB_Clk_pin,
      coprocesador_0_switches_pin => coprocesador_0_switches_pin
    );

end architecture STRUCTURE;

