@ECHO OFF
@REM ###########################################
@REM # Script file to run the flow 
@REM # 
@REM ###########################################
@REM #
@REM # Command line for ngdbuild
@REM #
ngdbuild -p xc3s1000ft256-5 -nt timestamp -bm system1.bmm "C:/Users/baneg/Desktop/SE/practicas/P3/P3/p3.C/otro/implementation/system1.ngc" -uc system1.ucf system1.ngd 

@REM #
@REM # Command line for map
@REM #
map -o system1_map.ncd -pr b -ol high -timing -detail system1.ngd system1.pcf 

@REM #
@REM # Command line for par
@REM #
par -w -ol high system1_map.ncd system1.ncd system1.pcf 

@REM #
@REM # Command line for post_par_trce
@REM #
trce -e 3 -xml system1.twx system1.ncd system1.pcf 

