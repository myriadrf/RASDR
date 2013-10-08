create_clock -period "30.72MHz" -name FPGA_CLKI [get_ports FPGA_CLKI]
derive_pll_clocks
derive_clock_uncertainty
create_clock -period "48MHz" -name USB_IFCLK [get_ports USB_IFCLK]