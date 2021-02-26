##############################################################################
## Filename:          C:\Users\baneg\Desktop\p3.C\otro/drivers/altavozumbador_v1_00_a/data/altavozumbador_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Wed Feb 17 14:29:18 2021 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "altavozumbador" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
