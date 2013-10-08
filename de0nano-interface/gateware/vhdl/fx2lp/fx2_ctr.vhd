-- ----------------------------------------------------------------------------	
-- FILE: 	fx2_ctr.vhd
-- DESCRIPTION:	Read data from FIFO and send to PC using FX2LP's slave FIFO interface.
-- DATE:	Jan 03, 2012
-- AUTHOR(s):	Lime Microsystems
-- REVISIONS:
-- ----------------------------------------------------------------------------	

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity fx2_ctr is
   port(
	 -- System
			nrst: in std_logic;
			en: in std_logic;
  
	-- FIFO Interface
			fifo_data: in std_logic_vector(47 downto 0);
			fifo_empty: in std_logic;
			fifo_full: in std_logic;
			fifo_rdreq: buffer std_logic;
  
  -- FX2 Interface
      ifclki: in std_logic;
      slwr: buffer std_logic;											--
      slrd: out std_logic;											--
      flagA: in std_logic;											-- 
      flagB: in std_logic;											-- FIFO Full
      flagC: in std_logic;											-- FIFO Empty
      fd: inout std_logic_vector(15 downto 0);	--
      pktend: out std_logic;										-- Packet End. Commit not full packet to the host.
      slcs: out std_logic;											-- Active Low. Chip select.
      fifoaddr0, fifoaddr1: out std_logic;			-- 
      sloe: out std_logic												--
  );
end fx2_ctr;

architecture arch of fx2_ctr is
	-- States
	type state_type is (idle, w0, w1, w2, w3);
	signal state_reg, state_next: state_type;
	
	-- Packet counter
	signal pcktc: unsigned(7 downto 0);
	signal pckt_inc: std_logic;
	-- FIFO overflow detection
	signal fifoovr: std_logic;
	-- Read word counter from FIFO
	signal wrdc: unsigned(7 downto 0);
	signal wrdc_inc, wrdc_rst: std_logic;
	
	signal wsel: std_logic_vector(2 downto 0);	--Word selector
	--signal fdi: std_logic_vector(15 downto 0);

begin
   
	fifoaddr1 <= '1';
	fifoaddr0 <= '0';
	sloe <= '1';
	slrd <= '1';
	slcs <= '0';
	--fd <= fdi(7 downto 0) & fdi(15 downto 8);	-- Revert to simplify life at PC side.
	fd <=	fifo_data(15 downto 0)  when wsel = "000" else
					fifo_data(31 downto 16) when wsel = "001" else
					fifo_data(47 downto 32) when wsel = "010" else
					std_logic_vector(pcktc) & "1010000" & fifoovr;-- when wsel = "011" else
					--std_logic_vector(to_unsigned(16#1234#, 16));
	

	
--=============================================
-- Sent packet counter
--=============================================
	pcktp: process (ifclki, nrst)
	begin
		if (nrst = '0') then
			pcktc <= (others => '0');
		elsif (ifclki'event and ifclki = '1') then
			if (en = '1') and (pckt_inc = '1') then
				pcktc <= pcktc + 1;
			end if;
		end if;
	end process pcktp;
	
--=============================================
-- FIFO overflow detection
--=============================================
	ovrp: process (ifclki, nrst)
	begin
		if (nrst = '0') then
			fifoovr <= '0';
		elsif (ifclki'event and ifclki = '1') then
			if (en = '1') then
				if wrdc_rst = '0' then
					fifoovr <= fifo_full or fifoovr;
				else
					fifoovr <= fifo_full;
				end if;
			end if;
		end if;
	end process ovrp;

--=============================================
-- Read word counter from FIFO
--=============================================
	wrdcp: process (ifclki, nrst)
	begin
		if (nrst = '0') then
			wrdc <= (others => '0');
		elsif (ifclki'event and ifclki = '1') then
			if en = '1' then
				if wrdc_rst = '1' then
					wrdc <= to_unsigned(0, 8); --(others => '0');
				elsif fifo_rdreq = '1' then
					wrdc <= wrdc + 1;
				else
					wrdc <= wrdc;
				end if;
			end if;
		end if;
	end process wrdcp;
	
	--wrdc_rst <= '1' when wrdc = to_unsigned(84, 7) else '0';
	
--=============================================
-- State register
--=============================================
	NextStateReg01: process (ifclki, nrst)
	begin
		if (nrst = '0') then
			state_reg <= idle;
		elsif (ifclki'event and ifclki = '1') then
			if en = '1' then
				state_reg <= state_next;
			end if;
		end if;
	end process NextStateReg01;


	
--=============================================
-- Read from FIFO, write to FX2 logic
--=============================================
	RDWR: process(flagB, fifo_empty, state_reg, wrdc)
	begin
		pktend <= '1';	--Commit Fx2 packet. Default is not active
		fifo_rdreq <= '0';
		wsel <= "000";
		slwr <= '1';
		pckt_inc <= '0';
		wrdc_rst <= '0';
		state_next <= state_reg;
		
		case (state_reg) is
		
			-- idle and wait for start
			when idle =>
				state_next <= idle;
				wsel <= "000";
				if(fifo_empty = '0') then
					fifo_rdreq <= '1';		--Read from FIFO
					state_next <= w0;
				end if;
				
			-- 
			when w0 =>
				state_next <= w0;
				wsel <= "000";
				if(flagB = '1') then
					slwr <= '0';
					state_next <= w1;
				end if;

			--
			when w1 =>
				state_next <= w1;
				wsel <= "001";
				if(flagB = '1') then
					slwr <= '0';
					state_next <= w2;
				end if;
		
			--
			when w2 =>
				state_next <= w2;
				wsel <= "010";
				if(flagB = '1') then
					slwr <= '0';
					
					if(wrdc = to_unsigned(85, 7)) then
						state_next <= w3;
						wrdc_rst <= '1';		-- Reset FIFO word counter
					else
						if(fifo_empty = '0') then
							fifo_rdreq <= '1';	--Read from FIFO
							state_next <= w0;
						else
							state_next <= idle;
						end if;
					end if;
					
				end if;

			--		
			when w3 =>
				state_next <= w3;
				wsel <= "011";
				if(flagB = '1') then
					slwr <= '0';		-- Write technical information in the last 16 bit word of 256 word buffer
					pckt_inc <= '1';	
				
					if(fifo_empty = '0') then
						fifo_rdreq <= '1';		--Read from FIFO
						state_next <= w0;
					else
						state_next <= idle;
					end if;
				end if;
					
			--	
			when others =>
				state_next <= idle;

		end case;

	end process RDWR;

end arch;