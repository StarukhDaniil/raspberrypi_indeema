# This is Raspberry PI project

# "common" is a static library

# "JsonCpp" library is connected

# TSafeContainer:
Template class that is used to communicate between threads. It doesn`t provide any logic for communication itself, just keeps info about container, mutex, condition variable and lambda for cv.wait().

# JsonParser:
Class that takes json string as input TSafeContainer.
When JsonParser::start_event_loop() is called, it creates seperate thread, that handles events(new jsons) and returns unique pointer to jthread

# SerialListener:
Class that reads serial port and throws input from port to JsonParser.
When SerialListener::start_event_loop() is called, it created seperate thread that reads port and throws data to JsonParser via TSafeContainer