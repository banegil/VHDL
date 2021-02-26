library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_arith.all;

entity prueba is
    Port ( rst , jugar, clk: in  STD_LOGIC;
           num1, num2, num3 : out std_logic_vector (7 downto 0);
			  basura: out std_logic_vector (4 downto 0);
			  pMedio, pGrande : out  STD_LOGIC);
end prueba;

architecture Behavioral of prueba is

component bin5_to_7seg is 
	port(
		entrada:	in 	STD_LOGIC_VECTOR (4 downto 0);
		LED:	out	STD_LOGIC_VECTOR (7 downto 0)
	);
end component bin5_to_7seg;

component debouncer is 
   port (
    rst             : in  std_logic;
    clk             : in  std_logic;
    x               : in  std_logic;
    xDeb            : out std_logic;
    xDebFallingEdge : out std_logic;
    xDebRisingEdge  : out std_logic
    );
end component debouncer;

component contador is
  port (rst  : in  std_logic;         
        clk  : in  std_logic;           
        enable : in std_logic;
        cntr : out std_logic_vector(4 downto 0));
end component contador;

component divisor1 is 
    port (
        rst, clk_in: in STD_LOGIC;
        clk_out: out STD_LOGIC
    );
end component;

type ESTADOS is (S0, S1, S2, S3, S4);
signal ESTADO, SIG_ESTADO: ESTADOS;
signal cont1, cont2, cont3: std_logic_vector(4 downto 0);
signal aux7seg_1, aux7seg_2, aux7seg_3: std_logic_vector(7 downto 0);
signal clk_out, boton, load1, load2, load3, medio, grande: std_logic;

begin
divis: divisor1 port map (rst, clk_in=>clk, clk_out=>clk_out);
ini_debouncer: debouncer port map (rst, clk, jugar, open, boton, open);
ctr1: contador port map (rst,clk_out,load1,cont1);
ctr2: contador port map (rst,clk_out,load2,cont2);
ctr3: contador port map (rst,clk_out,load3,cont3);
seg_7_1: bin5_to_7seg port map(cont1, aux7seg_1);
seg_7_2: bin5_to_7seg port map(cont2, aux7seg_2);
seg_7_3: bin5_to_7seg port map(cont3, aux7seg_3);	

premioMedio: process (cont1, cont2, cont3, grande)
begin
     if(cont1=cont2 or cont1=cont3 or cont2=cont3) then
			if(grande='0') then
				medio <= '1';
			else
			   medio <= '0';
			end if;
	  else
			medio <= '0';
	  end if;
end process premioMedio;

premioGrande: process (cont1, cont2, cont3)
begin
    if(cont1=cont2 and cont1=cont3) then
		grande <= '1';
	 else 
		grande <= '0';
	 end if;
end process premioGrande;	
	
SINC_ESTADO: process(clk,rst)
begin
	if rst ='0' then
		ESTADO<=S0;
	elsif clk'event and clk='1' then
		ESTADO<= SIG_ESTADO;
	end if;
end process SINC_ESTADO;

ASINC_ESTADO: process(ESTADO, boton)
	begin
		case ESTADO is
	when S0 =>
	   basura <= "00000";
      pMedio <= '0';
		pGrande <= '0';
		num1 <= "00000000";
		num2 <= "00000000";
		num3 <= "00000000";
	   load1 <= '1';
		load2 <= '0';
		load3 <= '0';
		if(boton = '1') then
			SIG_ESTADO<=S1;			
		else
			SIG_ESTADO<=S0;
		end if;
	when S1 =>
	   load1 <= '0';
		load2 <= '1';
		load3 <= '0';
		num1 <= aux7seg_1;
		if(boton = '1') then
			SIG_ESTADO<=S2;			
		else
			SIG_ESTADO<=S1;
		end if;
	when S2 =>
	   load1 <= '0';
		load2 <= '0';
		load3 <= '1';
		num1 <= aux7seg_1;
		num2 <= aux7seg_2;
		if(boton = '1') then
			SIG_ESTADO<=S3;			
		else
			SIG_ESTADO<=S2;
		end if;
	when S3 =>
	   load1 <= '0';
		load2 <= '0';
		load3 <= '0';
		num2 <= aux7seg_2;
		num3 <= aux7seg_3;
		if(boton = '1') then
			SIG_ESTADO<=S4;			
		else
			SIG_ESTADO<=S3;
		end if;
	when S4 =>
		pGrande <= grande;
		pMedio <= medio;
		num1 <= "00000000";
		num2 <= "00000000";
		num3 <= "00000000";
		if(boton = '1') then
			SIG_ESTADO<=S0;		
		else
			SIG_ESTADO<=S4;
		end if;
	when others =>
      SIG_ESTADO<=S0;
	end case;
end process ASINC_ESTADO;

end Behavioral;

