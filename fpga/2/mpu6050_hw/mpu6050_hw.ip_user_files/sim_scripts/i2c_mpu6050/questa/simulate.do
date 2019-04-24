onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib i2c_mpu6050_opt

do {wave.do}

view wave
view structure
view signals

do {i2c_mpu6050.udo}

run -all

quit -force
