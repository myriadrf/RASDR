-- ----------------------------------------------------------------------------	
-- FILE:        nux25.vhd
-- DESCRIPTION:	25 bit multiplexer
-- DATE:	       Sep 06, 2012
-- AUTHOR(s):	  Lime Microsystems
-- REVISIONS:
-- ----------------------------------------------------------------------------	

library ieee;
use ieee.std_logic_1164.all;

-- ----------------------------------------------------------------------------
-- Entity declaration
-- ----------------------------------------------------------------------------
entity iqmux is
    port (
		iq0: in std_logic_vector(11 downto 0);	-- Input
		iqsel0: in std_logic;
		iq1: in std_logic_vector(11 downto 0);	-- Input
		iqsel1: in std_logic;
		sel: in std_logic;
		yiq: out std_logic_vector(11 downto 0);	-- Output
	   yiqsel: out std_logic
    );
end iqmux;

-- ----------------------------------------------------------------------------
-- Architecture
-- ----------------------------------------------------------------------------
architecture iqmux_arch of iqmux is
begin

	yiq <= iq0 when sel = '0' else iq1;
	yiqsel <= iqsel0 when sel = '0' else iqsel1;

end iqmux_arch;

