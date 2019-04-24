-makelib ies_lib/xilinx_vip -sv \
  "/media/kiott01a/SAMSUNG/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
  "/media/kiott01a/SAMSUNG/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
  "/media/kiott01a/SAMSUNG/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
  "/media/kiott01a/SAMSUNG/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
  "/media/kiott01a/SAMSUNG/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
  "/media/kiott01a/SAMSUNG/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
  "/media/kiott01a/SAMSUNG/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
  "/media/kiott01a/SAMSUNG/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
  "/media/kiott01a/SAMSUNG/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/rst_vip_if.sv" \
-endlib
-makelib ies_lib/xil_defaultlib -sv \
  "/media/kiott01a/SAMSUNG/Xilinx/Vivado/2018.2/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
  "/media/kiott01a/SAMSUNG/Xilinx/Vivado/2018.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
  "/media/kiott01a/SAMSUNG/Xilinx/Vivado/2018.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
-endlib
-makelib ies_lib/xpm \
  "/media/kiott01a/SAMSUNG/Xilinx/Vivado/2018.2/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib ies_lib/axi_infrastructure_v1_1_0 \
  "../../../../mpu6050_hw.srcs/sources_1/bd/i2c_mpu6050/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \
-endlib
-makelib ies_lib/smartconnect_v1_0 -sv \
  "../../../../mpu6050_hw.srcs/sources_1/bd/i2c_mpu6050/ipshared/5bb9/hdl/sc_util_v1_0_vl_rfs.sv" \
-endlib
-makelib ies_lib/axi_protocol_checker_v2_0_3 -sv \
  "../../../../mpu6050_hw.srcs/sources_1/bd/i2c_mpu6050/ipshared/03a9/hdl/axi_protocol_checker_v2_0_vl_rfs.sv" \
-endlib
-makelib ies_lib/axi_vip_v1_1_3 -sv \
  "../../../../mpu6050_hw.srcs/sources_1/bd/i2c_mpu6050/ipshared/b9a8/hdl/axi_vip_v1_1_vl_rfs.sv" \
-endlib
-makelib ies_lib/processing_system7_vip_v1_0_5 -sv \
  "../../../../mpu6050_hw.srcs/sources_1/bd/i2c_mpu6050/ipshared/70fd/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/i2c_mpu6050/ip/i2c_mpu6050_processing_system7_0_0/sim/i2c_mpu6050_processing_system7_0_0.v" \
  "../../../bd/i2c_mpu6050/sim/i2c_mpu6050.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  glbl.v
-endlib

