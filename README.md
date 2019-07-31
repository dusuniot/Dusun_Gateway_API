# Dusun API document  
	This is a project containing APIs for Dusun IoT gateway.  

## Tutorial:  
	1. edit the example make/arch.mk, enter the correct corsstool env  
	2. cd example  
	3. execute make  
	4. transfer the example/build/test to test board run it  

## Version List:  

### Version V1.0.0:  
	description :   
	this is only debug version for ZigBee devices.

### Version V1.0.1:  
	description : 
	add set_attr/get_attr/zcl_cmd/rpt_attr/rpt_cmd for ZigBee operations;

### Version V1.0.2:  
	description : 
	1. add Z-Wave interfaces  which can be used to commnunicate with Z-Wave sensors. 
	2. add some command line functions which shows how to use API functions to send data to ZigBee/Zwave IoT devices. 
