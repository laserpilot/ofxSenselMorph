# ofxSenselMorph
openFrameworks addon for Sensel Morph (private currently - will change on public release)

Built with openFrameworks 0.8.4 and OSX 10.10.5 + XCode 6.4

Simple example making use of the sensel C++ API

THIS IS A WORK IN PROGRESS!! Still waiting for the API to stabilize as this was made with a prototype unit. Could use a lot of refactoring and some smarter memory management techniques.

Currently only works with OSX - but it should be easy to adapt to Linux or Windows.

If you're using the addon on a new app - I left the windows .cpp file in there for now but you will need to manually remove just "sensel_serial_win.cpp" from your Xcode project if you want it to work with OSX

**To do:**

 - Windows examples
 - Add support for LED control
 - Smarter memory management
 - Support for multiple units
 - Update to latest API
