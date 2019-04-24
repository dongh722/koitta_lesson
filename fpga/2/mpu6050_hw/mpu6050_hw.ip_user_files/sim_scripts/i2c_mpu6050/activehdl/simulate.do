onbreak {quit -force}
onerror {quit -force}

asim -t 1ps +access +r +m+i2c_mpu6050 -L xilinx_vip -L xil_defaultlib -L xpm -L axi_infrastructure_v1_1_0 -L smartconnect_v1_0 -L axi_protocol_checker_v2_0_3 -L axi_vip_v1_1_3 -L processing_system7_vip_v1_0_5 -L xilinx_vip -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.i2c_mpu6050 xil_defaultlib.glbl

do {wave.do}

view wave
view structure

do {i2c_mpu6050.udo}

run -all

endsim

quit -force
