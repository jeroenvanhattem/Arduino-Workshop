/// @file
/// Infrared Library

#include "infrared.hpp"
#include "sam.h"
#include "wheels.hpp"
#include "hwlib.hpp"
#include "lights.hpp"
/// Global Variables
//
/// - Force for speed
/// - Pin26, forcelight 1
/// - Pin28, forcelight 2
/// - Pin30, forcelight 3
static int force = 0;
auto pin_d26 = hwlib::target::pins::d26;
auto pin_d28 = hwlib::target::pins::d28;
auto pin_d30 = hwlib::target::pins::d30;
auto pin_d3 = hwlib::target::pins::d3;

/// Get class parameters
//
/// Get the parameters which were given when creating the class
infrared::infrared(int state):
    state(state)
{}

/// Infrared::init()
//
/// Initialize infrared function by declaring the force lights and printing the code below, easy way to find out if the cout command and the connection between the car work
void infrared::init(){
	hwlib::cout << hwlib::left << hwlib::setw( 5 ) << "Initializing Infrared function | State: " << state << "\n";
}

/// Infrared::check(int pin) [RC-5 protocol]
//
/// The check() function checks for an input on the given pin. It creates a 14 character sized array. If there's an input on the pin, it checks 14 more times for an input
/// on the pin. If the value is 1, it appends the array with a '1', if it's a 0, it appends the array with a '0'. We're working with the RC-5 protocol, which means
/// an input is ready in 1.778 milliseconds. A high value looks like '-|_' and a low value look slike '_|-'. When the value switches up, it waits 3/4 of the time it
/// takes to get ready. We do this because of the delay between hitting the button on the remote and when it's available on the Arduino to work with. In the end we convert
/// the array into a integervalue, because it's hard to pass an array as parameter
int infrared::check(){
	static char code[14];
	int ir_value = 0;
    auto ir_pin = hwlib::target::pin_in(pin_d3);
    /// Check for input and process it
    //
    /// If there's an input on the pin, it checks 14 more times for an input on the pin. If the value is 1, it appends the array with a '1', if it's a 0, it 
    /// appends the array with a '0'. We're working with the RC-5 protocol, which means an input is ready in 1.778 milliseconds. A high value looks like '-|_' 
    /// and a low value look slike '_|-'. When the value switches up, it waits 3/4 of the time it takes to get ready.
	if((ir_pin.get() == true)){ // Start bit received
		for(int j = 0; j < 14; j++){
			if((ir_pin.get() == true)){
				code[j] = '1';
			}	
			else{
				code[j] = '0';
			}
            

            while(1){
                if((code[j] == '1') && (ir_pin.get() == false)){
                    hwlib::wait_ns(1333500);
                    break;
                }
                
                else if((code[j] == '0') && (ir_pin.get() == true)){
                    hwlib::wait_ns(1333500);
                    break;
                }
            }
		}
        /// Convert array to integer value
        //
		/// Here we convert the array to an integer value, which makes it easier to pass as parameter and use in a switch statement. I chose 8192 as divider, because 2^13 =
        ///  8192. We also print this value as a simple test, if you get random codes, you probably use a remote which doesn't support the RC-5 protocol. Try using a older
        /// Philips remote.
		for(int k = 0; k < 14; k++){
			ir_value = ir_value + ((code[k] - '0') * (8192 / k));
		}
        
        hwlib::cout << hwlib::left << hwlib::setw( 5 ) << code << "  |  " << ir_value << "\n\n";
        
	}
	
    /// ir_value = 0 if there's no input
    //
    /// If the Arduino receives no input from the pin or remote, it returns a '0'. If you do press a button, make sure your infrared receiver is connected correctly
	else{
		for(int i = 0; i < 14; i++){
			code[i] = 0;
		}
		ir_value = 0;
	}
	
	return ir_value;	
}

/// Infared::drive(int ir_value)
//
/// The drive function receives a ir_value as parameter, which resembles the button you pressed on the remote. It casts the ir_value to a command from the wheel library
void infrared::drive(int ir_value){
    /// Create wheels object
    //
    /// Creating and inializing a wheels object, so we can use the library. Values are as follow
    /// Wheels(int state);
    wheels w(1);
    lights l(1);
	w.init();
    /// Casting command
    //
	/// Casting integer values to a command
	/// For light commands, check wheels.cpp
    switch(ir_value){
		case 8616:
			w.off();
			break;
        case 10307:      // Up
            w.forward(force);
            break;
        case 6568:      // Down
            w.backward();
            break;
        case 5256:     // Left
            w.left(force);
            break;
        case 11346:     // Right
            w.right(force);
            break;
		case 11090: 	// 1
			l.switch_lights(6);
			break;
		case 6841:		// 2
			l.switch_lights(7);
			break;
        case 8018:     // Rewind
            if(force > 0){ 
                force--;
            }
            break;
        case 2866:      // Forward
            if(force < 2){ 
                force++;
            }
            break;
    }
    
    /// Force indicators
    //
    /// These lights show to value of the force variable, which determines how fast the car drives and rotates
    if(force == 0){
        hwlib::target::pin_out(pin_d26).set(1); // Set Force light 1 -> on
        hwlib::target::pin_out(pin_d28).set(0); // Set Force light 2 -> off
        hwlib::target::pin_out(pin_d30).set(0); // Set Force light 3 -> off
    }
    else if(force == 1){
        hwlib::target::pin_out(pin_d26).set(1); // Set Force light 1 -> on
        hwlib::target::pin_out(pin_d28).set(1); // Set Force light 2 -> on
        hwlib::target::pin_out(pin_d30).set(0); // Set Force light 3 -> off
    }
    else if(force == 2){
        hwlib::target::pin_out(pin_d26).set(1); // Set Force light 1 -> on
        hwlib::target::pin_out(pin_d28).set(1); // Set Force light 2 -> on
        hwlib::target::pin_out(pin_d30).set(1); // Set Force light 3 -> on
    }
    
}