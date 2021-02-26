library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_arith.all;

entity prueba is
    Port ( rst , jugar, clk: in  STD_LOGIC;
           num1, num2, num3 : out std_logic_vector (1 downto 0);
			  pGrande7seg: out std_logic_vector (6 downto 0);
			  pGrande, bitBasura, bitBasura2 :  out  STD_LOGIC);
end prueba;

architecture Behavioral of prueba is

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
        cntr : out std_logic_vector(1 downto 0));
end component contador;

component divisor1 is 
    port (
        rst, clk_in: in STD_LOGIC;
        clk_out: out STD_LOGIC
    );
end component;

type ESTADOS is (S0, S1, S2, S3, S4);
signal ESTADO, SIG_ESTADO: ESTADOS;
signal cont1, cont2, cont3: std_logic_vector(1 downto 0);
signal aux7G: std_logic_vector(6 downto 0);
signal clk_out, boton, load1, load2, load3, medio, grande, aux7M: std_logic;

begin
divis: divisor1 port map (rst, clk_in=>clk, clk_out=>clk_out);
ini_debouncer: debouncer port map (rst, clk, jugar, open, boton, open);
ctr1: contador port map (rst,clk_out,load1,cont1);
ctr2: contador port map (rst,clk_out,load2,cont2);
ctr3: contador port map (rst,clk_out,load3,cont3);
	
seg7_b: process(clk_out)
begin
	  if (rising_edge(clk_out)) then
			aux7G <= not aux7G;
			aux7M <= not aux7M; 
	  end if;
end process seg7_b;

estado4: process(ESTADO, grande, medio)
begin
	if(ESTADO=S4 and grande='0' and medio='1') then
		pGrande7seg(6) <= aux7M; --pGrande7seg(6) y aux7M comparten led
	elsif(ESTADO=S4 and grande='1') then
		pGrande7seg <= aux7G;
	else 
		pGrande7seg <= "0000000";
	end if;
end process estado4;		

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
	   bitBasura <= '0';
		bitBasura2 <= '0';
		pGrande <= '0';
		num1 <= "00";
		num2 <= "00";
		num3 <= "00";
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
		num1 <= cont1;
		if(boton = '1') then
			SIG_ESTADO<=S2;			
		else
			SIG_ESTADO<=S1;
		end if;
	when S2 =>
	   load1 <= '0';
		load2 <= '0';
		load3 <= '1';
		num1 <= cont1;
		num2 <= cont2;
		if(boton = '1') then
			SIG_ESTADO<=S3;			
		else
			SIG_ESTADO<=S2;
		end if;
	when S3 =>
	   load1 <= '0';
		load2 <= '0';
		load3 <= '0';
		num2 <= cont2;
		num3 <= cont3;
		if(boton = '1') then
			SIG_ESTADO<=S4;			
		else
			SIG_ESTADO<=S3;
		end if;
	when S4 =>
		pGrande <= grande;
		num1 <= "00";
		num2 <= "00";
		num3(0) <= medio; --num(0) y medio comparten led
		num3(1) <= '0';
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

