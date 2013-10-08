-- ----------------------------------------------------------------------------	
-- FILE: 	nco_bin.vhd
-- DESCRIPTION:	MIN MAX based NCO
-- DATE:	Jan 03, 2012
-- AUTHOR(s):	Lime Microsystems
-- REVISIONS:
-- ----------------------------------------------------------------------------	


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity nco_bin is
   port(
		clk: in std_logic;
		nrst: in std_logic;
		en: in std_logic;
		fstart: in std_logic;		-- Frame start
		iq: out std_logic_vector(11 downto 0);
		iq_sel: out std_logic
	);
end nco_bin;

architecture arch of nco_bin is
	signal iq_reg, iq_next: std_logic_vector(11 downto 0);
	signal iq_sel_reg, iq_sel_next: std_logic;
	signal en_sync0, en_sync1: std_logic;
	
   
	-- States
	type cmds is (Idle, Phase0_I, Phase0_Q, Phase1_I, Phase1_Q, Phase2_I, Phase2_Q, Phase3_I, Phase3_Q);
	signal state, next_state : cmds;

begin

--=============================================
-- Enable Sync
--=============================================
	SyncReg01: process (clk, nrst)
	begin
		--
		if (nrst = '0') then
			en_sync0 <= '0';
			en_sync1 <= '0';
		elsif (clk'event and clk = '1') then
			en_sync0 <= en_sync1;
			en_sync1 <= en;
		end if;
	end process SyncReg01;


--=============================================
-- Next state
--=============================================
	NextStateReg01: process (clk, nrst)
	begin
		--
		if (nrst = '0') then
			state <= Phase0_I;
			iq_reg <= (others => '0');
			iq_sel_reg <= '1';
		elsif (clk'event and clk = '1') then
			if en_sync0 = '1' then
				state <= next_state;
				iq_reg <= iq_next;
				iq_sel_reg <= iq_sel_next;
			end if;
		end if;
	end process NextStateReg01;
	
--=============================================
-- Next state logic
--=============================================
	nxt_state_decoder : process (state)
	begin

			iq_next <= "011111111111";
			iq_sel_next <= '1';

				case (state) is
			-- idle and wait for start
			when Phase0_I =>
				iq_next <= "011111111111";
				iq_sel_next <= '1';
				next_state <= Phase0_Q;
				
			when Phase0_Q =>
				iq_next <= "000000000000";
				iq_sel_next <= '0';
				next_state <= Phase1_I;

			when Phase1_I =>
				iq_next <= "000000000000";
				iq_sel_next <= '1';
				next_state <= Phase1_Q;
				
			when Phase1_Q =>
				iq_next <= "011111111111";
				iq_sel_next <= '0';
				next_state <= Phase2_I;

			when Phase2_I =>
				iq_next <= "100000000000";
				iq_sel_next <= '1';
				next_state <= Phase2_Q;
				
			when Phase2_Q =>
				iq_next <= "000000000000";
				iq_sel_next <= '0';
				next_state <= Phase3_I;
	
			when Phase3_I =>
				iq_next <= "000000000000";
				iq_sel_next <= '1';
				next_state <= Phase3_Q;
				
			when Phase3_Q =>
				iq_next <= "100000000000";
				iq_sel_next <= '0';
				next_state <= Phase0_I;


--			when Phase0_I =>
--				iq_next <= "111111111111";
--				iq_sel_next <= '1';
--				next_state <= Phase0_Q;
--				
--			when Phase0_Q =>
--				iq_next <= "000000000000";
--				iq_sel_next <= '0';
--				next_state <= Phase1_I;
--
--			when Phase1_I =>
--				iq_next <= "111111111111";
--				iq_sel_next <= '1';
--				next_state <= Phase1_Q;
--				
--			when Phase1_Q =>
--				iq_next <= "000000000000";
--				iq_sel_next <= '0';
--				next_state <= Phase2_I;
--
--			when Phase2_I =>
--				iq_next <= "111111111111";
--				iq_sel_next <= '1';
--				next_state <= Phase2_Q;
--				
--			when Phase2_Q =>
--				iq_next <= "000000000000";
--				iq_sel_next <= '0';
--				next_state <= Phase3_I;
--	
--			when Phase3_I =>
--				iq_next <= "111111111111";
--				iq_sel_next <= '1';
--				next_state <= Phase3_Q;
--				
--			when Phase3_Q =>
--				iq_next <= "000000000000";
--				iq_sel_next <= '0';
--				next_state <= Phase0_I;

			--	
			when others =>
				next_state <= Phase0_I;

		end case;
	end process nxt_state_decoder;

	iq <= iq_reg;
	
	iq_sel <= iq_sel_reg when fstart = '1' else not iq_sel_reg;
	--iq_sel <= not iq_sel_reg;		-- Frame start = 0

end arch;