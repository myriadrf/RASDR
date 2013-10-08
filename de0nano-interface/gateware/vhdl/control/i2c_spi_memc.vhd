-- Copyright (c) 2006 Frank Buss (fb@frank-buss.de), 2012 Lime Microsystems
-- See ..i2c_slave/license.txt for license
--
-- An entity like the PCA9555, but without interrupt and maybe different latching timings.
-- Fireset a byte is written for addressing a register:
-- 0: input port 0
-- 1: input port 1
-- 2: output port 0
-- 3: output port 1
-- 4: input polarity inversion port 0 (1=input is inverted)
-- 5: input polarity inversion port 1
-- 6: configuration port 0 (1=pin is input)
-- 7: configuration port 0
-- Then you can write to the register or you can send a repeated start with
-- read bit set and read from it.
-- For details see http://www.nxp.com/acrobat_download/datasheets/PCA9555_6.pdf

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity i2c_spi_memc is
	generic(
		clock_frequency: natural := 1e7;
		--address: unsigned(6 downto 0) := b"0000000");
		address: unsigned(6 downto 0) := to_unsigned(85, 7));
	port(
		clock: in std_logic;
		reset: in std_logic;
		scl: in std_logic;
		sda: inout std_logic;
		porti_0: in unsigned(7 downto 0);
		porti_1: in unsigned(7 downto 0);
		en: out std_logic;
		txden: out std_logic;
		rxden: out std_logic;
		txen: out std_logic;
		rxen: out std_logic;
		rxsrc: out std_logic;
		snreset: out std_logic
		);
end entity i2c_spi_memc;

architecture rtl of i2c_spi_memc is

	component i2c_slave is
		generic(
			clock_frequency: natural;
			address: unsigned(6 downto 0));
		port(
			clock: in std_logic;
			reset: in std_logic;
			data_out: in unsigned(7 downto 0);
			data_in: out unsigned(7 downto 0);
			read_mode: out boolean;
			start_detected: out boolean;
			stop_detected: out boolean;
			transfer_started: out boolean;
			data_out_requested: out boolean;
			data_in_valid: out boolean;
			sda: inout std_logic;
			scl: in std_logic);
	end component i2c_slave;

	-- I2C slave signals
	signal data_out: unsigned(7 downto 0);
	signal data_in: unsigned(7 downto 0);
	signal stop_detected: boolean;
	signal transfer_started: boolean;
	signal data_out_requested: boolean;
	signal data_in_valid: boolean;
	
	-- PCA9555 signals
	type registers_type is array (0 to 15) of unsigned(7 downto 0);
	signal registers: registers_type := (others => x"00");
	signal selected_register_index: unsigned(3 downto 0);

	type state_type is (
		idle,
		wait_for_command,
		wait_for_read_write,
		wait_for_event_released);

	signal state: state_type := idle;

begin

	i2c_slave_instance: i2c_slave
		generic map(
			clock_frequency => clock_frequency,
			address => address)
		port map(
			clock => clock,
			reset => reset,
			data_out => data_out,
			data_in => data_in,
			read_mode => open,
			start_detected => open,
			stop_detected => stop_detected,
			transfer_started => transfer_started,
			data_out_requested => data_out_requested,
			data_in_valid => data_in_valid,
			sda => sda,
			scl => scl);

	test_process: process(clock, reset)
	begin
		if reset = '1' then
			-- input
			registers(0) <= x"00";
			registers(1) <= x"00";
			-- output
			--registers(2) <= x"1C";	-- TXEN, RXEN, TXDEN, RXDEN, EN
			registers(2) <= x"18";	-- TXEN, RXEN, TXDEN, RXDEN, EN
			registers(3) <= x"00";	-- SNRESET
			registers(4) <= x"00";
			registers(5) <= x"00";
			registers(6) <= x"00";
			registers(7) <= x"00";
			registers(8) <= x"00";
			registers(9) <= x"00";
			registers(10) <= x"00";
			registers(11) <= x"00";
			registers(12) <= x"00";
			registers(13) <= x"00";
			registers(14) <= x"00";
			registers(15) <= x"00";
			
			state <= idle;
		else
			if rising_edge(clock) then
				-- I2C send/receive
				case state is
					when idle =>
						if transfer_started then
							state <= wait_for_command;
						end if;
					when wait_for_command =>
						if data_in_valid then
							selected_register_index <= data_in(3 downto 0);-- xor b"001";
							state <= wait_for_event_released;
						end if;
					when wait_for_read_write =>
						if data_in_valid then
							registers(to_integer(selected_register_index)) <= data_in;
							state <= wait_for_event_released;
						end if;
						if data_out_requested then
							data_out <= registers(to_integer(selected_register_index));
							state <= wait_for_event_released;
						end if;
					when wait_for_event_released =>
						if (data_in_valid = false) and (data_out_requested = false) then
							--selected_register_index(0) <= not selected_register_index(0);
							state <= wait_for_read_write;
						end if;
				end case;

				if stop_detected then
					state <= idle;
				end if;

				-- update input registers
				registers(0) <= porti_0;
				registers(1) <= porti_1;
				
			end if;
		end if;
	end process;

	en		<= registers(2)(0);
	rxden <= registers(2)(1);
	txden <= registers(2)(2);
	rxen	<= registers(2)(3);
	txen	<= registers(2)(4);
	rxsrc <= registers(2)(5);
	
	snreset <= registers(3)(0);

end architecture rtl;



