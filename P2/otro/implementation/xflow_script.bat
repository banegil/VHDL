@ECHO OFF
@REM ###########################################
@REM # Script file to run the flow 
@REM # 
@REM ###########################################
@REM #
@REM # Command line for ngdbuild
@REM #
ngdbuild -p xc3s1000ft256-5 -nt timestamp -bm system1.bmm "C:/Users/baneg/Desktop/SE/practicas/P2/otro/implementation/system1.ngc" -uc system1.ucf system1.ngd 

