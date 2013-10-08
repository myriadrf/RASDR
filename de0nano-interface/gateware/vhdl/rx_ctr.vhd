-- ----------------------------------------------------------------------------	
-- FILE: 	rx_ctr.vhd
-- DESCRIPTION:	Compress 4*12 bit data to 3*16 bit word.
-- DATE:	Jan 03, 2012
-- AUTHOR(s):	Lime Microsystems
-- REVISIONS:
-- ----------------------------------------------------------------------------	


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity rx_ctr is
   port(
		clk: in std_logic;
		nrst: in std_logic;
		en: in std_logic;
		go: in std_logic;				-- Read data from LMS and write to FIFO, if go = '1'
		fstart: in std_logic;		-- Frame start
		iq_sel: in std_logic;
		iqd: in std_logic_vector(11 downto 0);

		fifo_wrfull: in std_logic;
		fifo_wrempty: in std_logic;
		wr_req: out std_logic;
		wr_word: out std_logic_vector(47 downto 0);
		fifo_clr: out std_logic
	);
end rx_ctr;

architecture arch of rx_ctr is
	
	signal nfstart: std_logic;
	signal capen: std_logic;
	signal wsel: unsigned(1 downto 0);
	signal w0, w1, w2, w3: std_logic_vector(11 downto 0);
	
	-- States
	type cmds is (wait4go, wait4notf, wait4sync, rx0, rx1, rx2);
	signal state, next_state : cmds;

begin

	nfstart <= not fstart;
	
--=============================================
-- Address in 48 bit register
--=============================================
	baddrp: process (clk, nrst)
	begin
		if (nrst = '0') then
			wsel <= (others => '0');
		elsif (clk'event and clk = '1') then
			if en = '1' then
				if capen = '1' then
					wsel <= wsel + 1;
				else
					wsel <= (others => '0');
				end if;
			end if;
		end if;
	end process baddrp;
	
--=============================================
-- Write request register
--=============================================
	wr_reqp: process (clk, nrst)
	begin
		if (nrst = '0') then
			wr_req <= '0';
		elsif (clk'event and clk = '1') then
			if en = '1' then
				if wsel = "11" and capen = '1' then
					wr_req <= '1';
				else
					wr_req <= '0';
				end if;
			end if;
		end if;
	end process wr_reqp;

--	wr_req <= '1' when wsel = "11" and capen = '1' else '0';
	wr_word <= w3 & w2 & w1 & w0;
	
	
--=============================================
-- 48 bit register
--=============================================
	wrdp: process (clk, nrst)
	begin
		if (nrst = '0') then
			w0 <= (others => '0');
			w1 <= (others => '0');
			w2 <= (others => '0');
			w3 <= (others => '0');
		elsif (clk'event and clk = '1') then
			if en = '1' then
				if    capen = '1' and wsel = "00" then
					w0 <= iqd;
				elsif capen = '1' and wsel = "01" then
					w1 <= iqd;
				elsif capen = '1' and wsel = "10" then
					w2 <= iqd;
				elsif capen = '1' and wsel = "11" then
					w3 <= iqd;
				else
					null;
				end if;			
			end if;
		end if;
	end process wrdp;


--=============================================
-- Next state
--=============================================
	NextStateReg01: process (clk, nrst)
	begin
		if (nrst = '0') then
			state <= wait4go;
		elsif (clk'event and clk = '1') then
			if en = '1' then
				state <= next_state;
			end if;
		end if;
	end process NextStateReg01;
	
--=============================================
-- Next state logic
--=============================================
	nxt_state_decoder : process (state, go, iq_sel, nfstart, fifo_wrempty, fifo_wrfull)
	begin
		fifo_clr <= '0';
		capen <= '0';

		case (state) is
			-- idle and wait for start
			when wait4go =>
				fifo_clr <= '1';
				if go = '1' then
					next_state <= wait4notf;
				else
					next_state <= wait4go;
				end if;
				
			-- Wait for FIFO not full
			when wait4notf =>
				next_state <= wait4sync;
				if (fifo_wrfull = '1') then
					next_state <= wait4notf;
				end if;

			-- Wait for not frame start	
			when wait4sync =>
				next_state <= wait4sync;
				if (nfstart = iq_sel) then
					next_state <= rx2;
					--capen <= '1';
				end if;
				
			when rx2 =>
				capen <= '1';
				if (go = '1') then
					if (fifo_wrfull = '1') then
						next_state <= wait4notf;
						capen <= '0';
					else
						next_state <= rx2;
					end if;
				else
					next_state <= wait4go;
					capen <= '0';
				end if;

			--	
			when others =>
				next_state <= wait4go;

		end case;
	end process nxt_state_decoder;



end arch;