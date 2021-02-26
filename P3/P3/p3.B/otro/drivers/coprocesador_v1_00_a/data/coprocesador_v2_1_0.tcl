##############################################################################
## Filename:          C:\hlocal\otro/drivers/coprocesador_v1_00_a/data/coprocesador_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Fri Nov 13 18:42:12 2020 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "coprocesador" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
